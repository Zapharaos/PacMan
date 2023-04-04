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
Ghost::Ghost(Ghost::GhostType type, const Position &position, Position target) :
    type_(type), target_(std::move(target)),
    MovingEntity(position, true, static_cast<int>(Score::kGhost),
                 config::settings::kSpeedGhost, visuals::pacman::left::kAnimation,
                 visuals::pacman::right::kAnimation, visuals::pacman::up::kAnimation,
                 visuals::pacman::down::kAnimation)
{}

void Ghost::tick(const Map &map, const SDL_Rect &pacman) {

    // Handle ghost status
    if(counter_.isActive()) {
        counter_.increment();
    } else {
        // TODO : Timers
        switch(status_)
        {
            case GhostStatus::kStart:
                status_ = GhostStatus::kScatter;
                break;
            case GhostStatus::kFrightened:
                status_ = GhostStatus::kFrightenedBlinking;
                break;
            case GhostStatus::kScatter:
                status_ = GhostStatus::kChase;
                break;
            case GhostStatus::kChase:
                status_ = GhostStatus::kScatter;
                break;
            default: // unreachable
                break;
        }
    }

    // TODO : get direction from pathfinding
    Direction direction;
    MovingEntity::tick(map, direction);

    // TODO : animate
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
            if(true) // TODO : if amount of frames for frightened is 0
            {
                status_ = GhostStatus::kFrightened;
                // TODO : start timer
            } else {
                status_ = GhostStatus::kFrightenedBlinking;
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
