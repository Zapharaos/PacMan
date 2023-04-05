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
            // TODO : reverse direction when reaches next cell
        case GhostStatus::kStart:
            status_ = GhostStatus::kScatter;
            counter_.start(status_timers.at(status_changes_) * config::settings::kFramesPerSecond);
            break;
        case GhostStatus::kScatter:
            status_changes_++;
            status_ = GhostStatus::kChase;
            // TODO : reverse direction when reaches next cell
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

void Ghost::animate() {
    if(status_ == GhostStatus::kFrightened)
        setSprite(frightened_.animate());
    else if(status_ == GhostStatus::kFrightenedBlinking)
        setSprite(frightened_blinking_.animate());
}

void Ghost::tick(const Map &map, const Position &pacman) {

    // Handle ghost status
    if(counter_.isActive())
        counter_.increment();
    else
        handleStatusChange();

    // if frightened && atIntersection => randomize direction

    // TODO : get direction from pathfinding
    // Direction direction = map_.findPath(status_ == GhostStatus::kChase ? pacman : target_);
    MovingEntity::tick(map, Direction::randomize());

    animate();
}

void Ghost::frightened()
{
    if(status_ != GhostStatus::kFrightened && status_ != GhostStatus::kFrightenedBlinking)
        previous_status_ = status_;

    // TODO : reverse direction when reaches next cell

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
