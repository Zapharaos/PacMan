/**
 * @file ghost.cpp
 * @brief Implements the Ghost class, which is the second entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 03/04/2023
*/

#include "../../include/entity/ghost.h"

#include <utility>

Ghost::Ghost() = default;

Ghost::Ghost(const Position &position, Position scatter_target,
             Position house_target, Animation left, Animation right, Animation up, Animation down) :
    scatter_target_(std::move(scatter_target)), house_target_(std::move(house_target)),
    MovingEntity(position, true, static_cast<int>(Score::kGhost), config::settings::kSpeedGhost,
                 std::move(left), std::move(right), std::move(up), std::move(down))
{
    frightened_ = visuals::ghosts::frightened::kAnimation;
    frightened_blinking_ = visuals::ghosts::frightened_blinking::kAnimation;
    dead_left_ = visuals::ghosts::dead::left::kAnimation;
    dead_right_ = visuals::ghosts::dead::right::kAnimation;
    dead_up_ = visuals::ghosts::dead::up::kAnimation;
    dead_down_ = visuals::ghosts::dead::down::kAnimation;
}

std::optional<Position> Ghost::getTarget(const Position &pacman)
{
    switch(status_)
    {
        case GhostStatus::kChase:
            return pacman; // TODO : get pacman target per ghost
        case GhostStatus::kScatter:
            return scatter_target_;
        case GhostStatus::kDead:
            return house_target_;
        default:
            return std::nullopt;
    }
}

bool Ghost::isFrightened()
{
    return (status_ == GhostStatus::kFrightened || status_ == GhostStatus::kFrightenedBlinking);
}

void Ghost::handleStatus()
{
    // Handle ghost status.
    if(counter_.isActive())
        counter_.increment();
    else
        handleStatusChange();

    // Handle parent moving entity status.
    MovingEntity::handleStatus();
}

void Ghost::handleStatusChange() {

    if(!isEnabled())
    {
        if(isDead()) // Death.
        {
            auto position =  getPosition().scaleDown(config::dimensions::kWindowCellSize);
            if(position.getAbscissa() == 10 && position.getOrdinate() == 10)
                position = position;
            if (house_target_ == position)
            {
                setEnabled(true);
                counter_.loadSave();
                status_ = previous_status_;
                resetNextDirection();
                setZoneTunnelSlow(true);
                setZoneHorizontalOnly(true);
                setGhostHouseDoorAccess(false);
                show();
            }
        }
        else if(status_ == GhostStatus::kHouse)// Ghost house.
        {
            // TODO : ghost house status
        }
        return;
    }

    if (status_ == GhostStatus::kFrightened)
    {
        status_ = GhostStatus::kFrightenedBlinking;
        return;
    }

    if(status_changes_ > config::settings::kGhostStatusChangesBeforeInfiniteChase)
        return;

    switch(status_)
    {
        case GhostStatus::kChase:
            status_changes_++;
            setDirectionReverse(true);
        case GhostStatus::kStart:
            status_ = GhostStatus::kScatter;
            counter_.start(status_timers.at(status_changes_) * config::settings::kFramesPerSecond);
            return;
        case GhostStatus::kScatter:
            status_changes_++;
            status_ = GhostStatus::kChase;
            setDirectionReverse(true);
            if(status_changes_ < config::settings::kGhostStatusChangesBeforeInfiniteChase)
                counter_.start(status_timers.at(status_changes_) * config::settings::kFramesPerSecond);
            return;
        default: // unreachable
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

void Ghost::tick(const Map &map, const Position &pacman) {

    handleStatus();

    // Current direction and prepare next move.
    Direction direction = prepare(map, getTarget(pacman));

    if(move(map, direction)) // Move legal => animate.
        animate(getPreviousDirection());
}

void Ghost::kill() {
    if(!isFrightened())
    {
        previous_status_ = status_;
        counter_.save();
    }
    status_ = GhostStatus::kDead;
    counter_.stop();
    resetNextDirection();
    setZoneTunnelSlow(false);
    setZoneHorizontalOnly(false);
    setGhostHouseDoorAccess(true);
    setDirectionReverse(false);
    setSpeedSlow(false);
    Entity::kill();
}

void Ghost::frightened()
{
    if(isDead() || status_ == GhostStatus::kHouse)
        return;

    if(!isFrightened())
    {
        previous_status_ = status_;
        setDirectionReverse(true);
        setZoneHorizontalOnly(false);
        setSpeedSlow(true);
    }

    if(status_timers.at(1) == 0)
        status_ = GhostStatus::kFrightenedBlinking;
    else {
        status_ = GhostStatus::kFrightened;
        counter_.save();
        counter_.start(status_timers.at(0)*config::settings::kFramesPerSecond);
    }
}

void Ghost::unfrightened()
{
    if(!isFrightened())
        return;
    if(status_ == GhostStatus::kFrightened && counter_.isActive())
        counter_.loadSave();
    status_ = previous_status_;
    resetNextDirection();
    setZoneHorizontalOnly(true);
    setSpeedSlow(false);
}

void Ghost::reset()
{
    MovingEntity::reset();
    status_ = GhostStatus::kStart;
    counter_.stop();
    status_changes_ = 1;
    resetNextDirection();
    setZoneTunnelSlow(false);
    setZoneHorizontalOnly(false);
    setGhostHouseDoorAccess(true);
    setSpeedSlow(false);
}
