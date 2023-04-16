/**
 * @file ghost.cpp
 * @brief Implements the Ghost class, which is the second entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 03/04/2023
*/

#include "../../include/entity/ghost.h"

Ghost::Ghost() = default;

Ghost::Ghost(const Position &position, Position scatter_target, Position house_target,
             unsigned long pellets, Animation left, Animation right, Animation up, Animation down) :
    scatter_target_(std::move(scatter_target)), house_target_(std::move(house_target)),
    MovingEntity(position, true, static_cast<int>(Score::kGhost), config::settings::kSpeedGhost,
                 std::move(left), std::move(right), std::move(up), std::move(down))
{
    // Load elements from configs.
    frightened_ = visuals::ghosts::frightened::kAnimation;
    frightened_blinking_ = visuals::ghosts::frightened_blinking::kAnimation;
    dead_left_ = visuals::ghosts::dead::left::kAnimation;
    dead_right_ = visuals::ghosts::dead::right::kAnimation;
    dead_up_ = visuals::ghosts::dead::up::kAnimation;
    dead_down_ = visuals::ghosts::dead::down::kAnimation;

    // Starts in the ghost house.
    setSpeedSlow(true);
    setGhostHouseDoorAccess(true);

    if(pellets != 0) // Waiting in the ghost house.
    {
        pellet_counter_.start(pellets);
        setGhostHouseDoorAccess(false);
    }
}

const Position &Ghost::getScatterTarget() const
{
    return scatter_target_;
}

void Ghost::setChaseTarget(const Position &chaseTarget)
{
    chase_target_ = chaseTarget;
}

std::optional<Position> Ghost::getTarget()
{
    switch(status_)
    {
        case GhostStatus::kChase:
            return chase_target_;
        case GhostStatus::kScatter:
            return scatter_target_;
        case GhostStatus::kDead:
            return house_target_;
        case GhostStatus::kHouse:
            return config::positions::kGhostHouseEntry;
        default:
            return std::nullopt;
    }
}

void Ghost::statusChange()
{
    switch(status_)
    {
        // Status change immediately taken into consideration.
        case GhostStatus::kChase:
            setDirectionReverse(true);
            status_ = GhostStatus::kScatter;
            return;
        case GhostStatus::kScatter:
            setDirectionReverse(true);
            status_ = GhostStatus::kChase;
            return;
        // Do not interfere with the current status, prepare the next status.
        case GhostStatus::kDead:
        case GhostStatus::kHouse:
        case GhostStatus::kHouseWaiting:
        case GhostStatus::kFrightened:
        case GhostStatus::kFrightenedBlinking:
            if(previous_status_ == GhostStatus::kChase)
                previous_status_ = GhostStatus::kScatter;
            else
                previous_status_ = GhostStatus::kChase;
        default: // unreachable
            return;
    }
}

void Ghost::handleStatus()
{
    // Handle ghost status.
    if(status_ == GhostStatus::kFrightened)
    {
        if(frigthened_counter_.isActive()) // Frightened mode still active.
            frigthened_counter_.increment();
        else // Switch to the blinking animation.
            status_ = GhostStatus::kFrightenedBlinking;
    }
    else if(status_ == GhostStatus::kHouseWaiting || status_ == GhostStatus::kHouse)
    {
        // Reached the ghost house entry : exit the ghost house.
        if(config::positions::kGhostHouseEntry == getCurrentCellPosition())
        {
            status_ = GhostStatus::kScatter;
            setGhostHouseDoorAccess(false);
            setZoneHorizontalOnly(true);
            setZoneTunnelSlow(true);
            setSpeedSlow(false);
        }
    }
    else if(status_ == GhostStatus::kDead && house_target_ == getCurrentCellPosition())
    {
        // Reached its house target : ready to exit again.
        setEnabled(true);
        show();
        status_ = GhostStatus::kHouse;
        setSpeedSlow(true);
        setSpeedUp(false);
        setDirectionReverse(true);
    }

    // Handle parent moving entity status.
    MovingEntity::handleStatus();
}

void Ghost::tick(const Map &map) {

    handleStatus();

    Direction direction;
    if(status_ == GhostStatus::kHouseWaiting) // Stuck in the house
        direction = moveVertically(map);
    else
        direction = prepare(map, getTarget()); // Prepare next move

    if(move(map, direction)) // Move legal => animate.
        animate(getPreviousDirection());
}

void Ghost::kill() {

    switch (status_)
    {
        // Can not be killed while in those stages.
        case GhostStatus::kDead:
        case GhostStatus::kHouse:
        case GhostStatus::kHouseWaiting:
            return;
        // Saves the current status to return to after the death status.
        // Careful : previous_status_ might change in between.
        case GhostStatus::kChase:
        case GhostStatus::kScatter:
            previous_status_ = status_;
        default:
            break;
    }

    // Change settings to death.
    status_ = GhostStatus::kDead;
    frigthened_counter_.stop();
    setEnabled(false);
    hide();
    setSpeedUp(true);
    setSpeedSlow(false);
    setZoneTunnelSlow(false);
    setZoneHorizontalOnly(false);
    setGhostHouseDoorAccess(true);
    setDirectionReverse(false);
}

void Ghost::frightened(unsigned long seconds)
{
    switch(status_)
    {
        // Cannot be frightened while in those stages.
        case GhostStatus::kDead:
        case GhostStatus::kHouse:
        case GhostStatus::kHouseWaiting:
            return;
            // If not already in frightened mode : update the settings.
        case GhostStatus::kChase:
        case GhostStatus::kScatter:
            previous_status_ = status_;
            setDirectionReverse(true);
            setZoneHorizontalOnly(false);
            setSpeedSlow(true);
            setZoneTunnelSlow(false);
        default: // unreachable
            break;
    }

    if(seconds == 0) // Switch instantly to the blinking animation.
        status_ = GhostStatus::kFrightenedBlinking;
    else // Start the frightened mode.
    {
        status_ = GhostStatus::kFrightened;
        frigthened_counter_.start(seconds);
    }
}

void Ghost::unfrightened()
{
    switch (status_)
    {
        // Can only leave the frightened mode when already frightened (obviously).
        case GhostStatus::kFrightened:
        case GhostStatus::kFrightenedBlinking:
            status_ = previous_status_; // Switch back to the previous status.
            setSpeedSlow(false);
            setZoneTunnelSlow(true);
            setZoneHorizontalOnly(true);
        default:
            return;
    }
}

void Ghost::animate(const Direction &direction)
{
    // Override MovingEntity::animate() in special cases.
    if(status_ == GhostStatus::kFrightened)
        setSprite(frightened_.animate());
    else if(status_ == GhostStatus::kFrightenedBlinking)
        setSprite(frightened_blinking_.animate());
    else if(status_ == GhostStatus::kDead)
    {
        if(direction.isLeft())
            setSprite(dead_left_.animate());
        else if(direction.isRight())
            setSprite(dead_right_.animate());
        else if(direction.isUp())
            setSprite(dead_up_.animate());
        else if(direction.isDown())
            setSprite(dead_down_.animate());
    }
    else // No special cases : default animation.
        MovingEntity::animate(direction);
}

bool Ghost::exitHouse()
{
    // Can only leave the house if it actually is waiting inside of it (obviously).
    if(status_ != GhostStatus::kHouseWaiting)
        return false;

    // Leave the house.
    status_ = GhostStatus::kHouse;
    setGhostHouseDoorAccess(true);
    setZoneHorizontalOnly(false);
    return true;
}

bool Ghost::inHouseIncrementPelletCounter()
{
    if(status_ == GhostStatus::kHouseWaiting && pellet_counter_.isActive())
    {
        pellet_counter_.increment(); // Increment until it can exit the house.
        if(!pellet_counter_.isActive())
            exitHouse(); // Exit.
        return true;
    }
    return false;

}

void Ghost::restartFromHouse()
{
    MovingEntity::reset();
    status_ = GhostStatus::kHouseWaiting;
    frigthened_counter_.stop();
    // Pellet counter is paused until the ghost leaves the house again.
    pellet_counter_.pause();
    setSpeedSlow(true);
}

void Ghost::reset()
{
    MovingEntity::reset();
    status_ = GhostStatus::kHouseWaiting;
    frigthened_counter_.stop();
    pellet_counter_.restart();
    setSpeedSlow(true);
    setGhostHouseDoorAccess(true);
}

Position Ghost::getCurrentCellPosition()
{
    auto position = getPosition(); // Upper left corner
    if(getPreviousDirection().isLeftOrUp()) // Bottom right corner
        position = position.shift(getSize()-1, getSize()-1);
    return position.scaleDown(config::dimensions::kWindowCellSize);
}
