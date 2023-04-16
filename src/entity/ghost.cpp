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
    setZoneTunnelSlow(true);
    setGhostHouseDoorAccess(true);
    setZoneHorizontalOnly(false);
    frightened_ = visuals::ghosts::frightened::kAnimation;
    frightened_blinking_ = visuals::ghosts::frightened_blinking::kAnimation;
    dead_left_ = visuals::ghosts::dead::left::kAnimation;
    dead_right_ = visuals::ghosts::dead::right::kAnimation;
    dead_up_ = visuals::ghosts::dead::up::kAnimation;
    dead_down_ = visuals::ghosts::dead::down::kAnimation;
    if(pellets != 0)
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
        case GhostStatus::kChase:
            setDirectionReverse(true);
            status_ = GhostStatus::kScatter;
            return;
        case GhostStatus::kScatter:
            setDirectionReverse(true);
            status_ = GhostStatus::kChase;
            return;
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

void Ghost::frightened(unsigned long seconds)
{
    switch(status_)
    {
        case GhostStatus::kDead:
        case GhostStatus::kHouse:
        case GhostStatus::kHouseWaiting:
            return;
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

    if(seconds == 0)
        status_ = GhostStatus::kFrightenedBlinking;
    else
    {
        status_ = GhostStatus::kFrightened;
        frigthened_counter_.start(seconds);
    }
}

void Ghost::handleStatus()
{
    // Handle ghost status.
    if(status_ == GhostStatus::kFrightened)
    {
        if(frigthened_counter_.isActive())
            frigthened_counter_.increment();
        else
            status_ = GhostStatus::kFrightenedBlinking;
    }
    else if(status_ == GhostStatus::kHouseWaiting || status_ == GhostStatus::kHouse)
    {
        if(config::positions::kGhostHouseEntry == getCurrentCellPosition())
        {
            status_ = GhostStatus::kScatter;
            setGhostHouseDoorAccess(false);
            setZoneHorizontalOnly(true);
        }
    }
    else if(isDead()) // Death.
    {
        if (house_target_ == getCurrentCellPosition())
        {
            setEnabled(true);
            status_ = GhostStatus::kHouseWaiting;
            setDeadSpeedUp(false);
            setZoneTunnelSlow(true);
            setZoneHorizontalOnly(false);
            setGhostHouseDoorAccess(false);
            resetNextDirection();
            show();
        }
    }

    // Handle parent moving entity status.
    MovingEntity::handleStatus();
}

void Ghost::animate(const Direction &direction)
{
    // Override MovingEntity::animate() in special cases.
    if(status_ == GhostStatus::kFrightened)
        setSprite(frightened_.animate());
    else if(status_ == GhostStatus::kFrightenedBlinking)
        setSprite(frightened_blinking_.animate());
    else if(!isDead())
        MovingEntity::animate(direction);
    else
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
        case GhostStatus::kDead:
        case GhostStatus::kHouse:
        case GhostStatus::kHouseWaiting:
            return;
        case GhostStatus::kChase:
        case GhostStatus::kScatter:
            previous_status_ = status_;
        default:
            break;
    }

    status_ = GhostStatus::kDead;
    frigthened_counter_.stop();
    setDeadSpeedUp(true);
    setSpeedSlow(false);
    setZoneTunnelSlow(false);
    setZoneHorizontalOnly(false);
    setGhostHouseDoorAccess(true);
    setDirectionReverse(false);
    MovingEntity::kill();
}

void Ghost::unfrightened()
{
    switch (status_)
    {
        case GhostStatus::kFrightened:
        case GhostStatus::kFrightenedBlinking:
            status_ = previous_status_;
            setSpeedSlow(false);
            setZoneTunnelSlow(true);
            setZoneHorizontalOnly(true);
        default:
            return;
    }
}

void Ghost::reset()
{
    MovingEntity::reset();
    status_ = GhostStatus::kHouseWaiting;
    frigthened_counter_.stop();
    pellet_counter_.restart();
    setZoneTunnelSlow(true);
    setGhostHouseDoorAccess(true);
}

bool Ghost::inHouseIncrementPelletCounter()
{
    if(status_ == GhostStatus::kHouseWaiting && pellet_counter_.isActive())
    {
        pellet_counter_.increment();
        if(!pellet_counter_.isActive())
        {
            status_ = GhostStatus::kHouse;
            setGhostHouseDoorAccess(true);
            setZoneHorizontalOnly(false);
        }
        return true;
    }
    return false;

}

Position Ghost::getCurrentCellPosition()
{
    auto position = getPosition(); // Upper left corner
    if(getPreviousDirection().isLeftOrUp()) // Bottom right corner
        position = position.shift(getSize()-1, getSize()-1);
    return position.scaleDown(config::dimensions::kWindowCellSize);
}
