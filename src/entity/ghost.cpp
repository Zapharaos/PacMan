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

void Ghost::tick(const Map &map, const Position &pacman) {

    // Handle ghost status
    if(counter_.isActive()) {
        counter_.increment();
    } else {
        // TODO : Timers
        switch(status_)
        {
            case GhostStatus::kStart:
            case GhostStatus::kChase:
                status_ = GhostStatus::kScatter;
                break;
            case GhostStatus::kScatter:
                status_ = GhostStatus::kChase;
                break;
            case GhostStatus::kFrightened:
                status_ = GhostStatus::kFrightenedBlinking;
                break;
            case GhostStatus::kFrightenedBlinking:
                counter_.restart();
                break;
            default: // unreachable
                break;
        }
    }

    // TODO : get direction from pathfinding
//    Direction direction = map_.findPath(status_ == GhostStatus::kChase ? pacman : target_);
    Direction direction; direction.setDirection(DirectionType::kLeft);
    MovingEntity::tick(map, direction);

    if(status_ == GhostStatus::kFrightened)
        setSprite(frightened_.animate());
    else if(status_ == GhostStatus::kFrightenedBlinking)
        setSprite(frightened_blinking_.animate());
}

void Ghost::toggleFrightened()
{
    switch(status_)
    {
        case GhostStatus::kFrightened:
        case GhostStatus::kFrightenedBlinking:
            status_ = previous_status_;
            break;
        default:
            previous_status_ = status_;
            if(true) // TODO : if amount of frames for frightened is not 0
            {
                status_ = GhostStatus::kFrightened;
                setSprite(frightened_.getSprite());
                counter_.start(60 * 1); // TODO : temp value
            } else {
                status_ = GhostStatus::kFrightenedBlinking;
                setSprite(frightened_blinking_.getSprite());
            }
            break;
    }
}

void Ghost::reset()
{
    MovingEntity::reset();
    status_ = GhostStatus::kStart;
    counter_.stop();
}
