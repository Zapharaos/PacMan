/**
 * @file ghost.cpp
 * @brief Implements the Ghost class, which is the second entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 03/04/2023
*/

#include "../../include/entity/ghost.h"

#include <utility>

Ghost::Ghost() = default;

// TODO : update to have dynamic animations
Ghost::Ghost(Ghost::GhostType type, const Position &position, Position target,
             Animation left, Animation right, Animation up, Animation down) :
    type_(type), target_(std::move(target)),
    MovingEntity(position, true, static_cast<int>(Score::kGhost), config::settings::kSpeedGhost,
                 std::move(left), std::move(right), std::move(up), std::move(down))
{
    frightened_ = visuals::ghosts::frightened::kAnimation;
    frightened_blinking_ = visuals::ghosts::frightened_blinking::kAnimation;
}

void Ghost::handleStatusChange() {

    if(status_changes_ >= config::settings::kGhostStatusChangesBeforeInfiniteChase)
    {
        if(status_ == GhostStatus::kFrightened)
            status_ = GhostStatus::kFrightenedBlinking;
        return;
    }

    switch(status_)
    {
        case GhostStatus::kChase:
            status_changes_++;
            next_direction_ = getPreviousDirection().reverse();
        case GhostStatus::kStart:
            status_ = GhostStatus::kScatter;
            counter_.start(status_timers.at(status_changes_) * config::settings::kFramesPerSecond);
            break;
        case GhostStatus::kScatter:
            status_changes_++;
            status_ = GhostStatus::kChase;
            next_direction_ = getPreviousDirection().reverse();
            if(status_changes_ < config::settings::kGhostStatusChangesBeforeInfiniteChase)
                counter_.start(status_timers.at(status_changes_) * config::settings::kFramesPerSecond);
            break;
        case GhostStatus::kFrightened:
            status_ = GhostStatus::kFrightenedBlinking;
            break;
        default: // unreachable
            break;
    }
}

Direction Ghost::getNextDirection(const Map &map)
{
    auto current_position = getPosition().getPositionUnscaled(map.getCellSize());
    auto current_cell = map.getCell(current_position);

    auto next_position = current_position.moveIntoDirection(getPreviousDirection(), getSpeed());
    auto next_cell = map.getCell(next_position);

    // TODO : temp
    if(getPreviousDirection().isUninitialized())
        return Direction::randomize();

    if(current_cell == next_cell)
        return {};

    if(!next_direction_.isUninitialized())
    {
        Direction direction;
        direction = next_direction_;
        next_direction_.reset();
        return direction;
    }

    return {};

    /*
    else if(atIntersection)
    {
        if(isFrightened())
            return Direction::randomize();
//        return map.findPath(status_ == GhostStatus::kChase ? pacman : target_);
    }*/
}

void Ghost::tick(const Map &map, const Position &pacman) {

    // Handle ghost status
    if(counter_.isActive())
        counter_.increment();
    else
        handleStatusChange();

    MovingEntity::tick(map, getNextDirection(map));

    // Override MovingEntity::animate() in special cases.
    if(status_ == GhostStatus::kFrightened)
        setSprite(frightened_.animate());
    else if(status_ == GhostStatus::kFrightenedBlinking)
        setSprite(frightened_blinking_.animate());
}

bool Ghost::isFrightened()
{
    return (status_ == GhostStatus::kFrightened || status_ == GhostStatus::kFrightenedBlinking);
}

void Ghost::frightened()
{
    if(!isFrightened())
        previous_status_ = status_;

    next_direction_ = getPreviousDirection().reverse();

    if(status_timers.at(1) == 0)
        status_ = GhostStatus::kFrightenedBlinking;
    else {
        status_ = GhostStatus::kFrightened;
        counter_.start(status_timers.at(1)*config::settings::kFramesPerSecond);
    }
}

void Ghost::unfrightened()
{
    status_ = previous_status_;
}

void Ghost::reset()
{
    MovingEntity::reset();
    status_ = GhostStatus::kStart;
    counter_.stop();
    status_changes_ = 1;
}
