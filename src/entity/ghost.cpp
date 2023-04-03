/**
 * @file ghost.cpp
 * @brief Implements the Ghost class, which is the second entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 03/04/2023
*/

#include "../../include/entity/ghost.h"

Ghost::Ghost() = default;

// TODO : update to have dynamic animations
Ghost::Ghost(Ghost::GhostType type, const Position &position) :
    MovingEntity(position, true, static_cast<int>(Score::kGhost),
                 config::settings::kSpeedGhost, visuals::pacman::left::kAnimation,
                 visuals::pacman::right::kAnimation, visuals::pacman::up::kAnimation,
                 visuals::pacman::down::kAnimation) {
    type_ = type;
}

void Ghost::tick(const Map &map, const SDL_Rect &pacman) {

    // TODO : might need to handle ghost status

    // TODO : get direction from pathfinding
    Direction direction;
    MovingEntity::tick(map, direction);
}

void Ghost::toggleFrightened()
{
    if(status_ == GhostStatus::kFrightened)
    {
        status_ = previous_status_;
    } else {
        previous_status_ = status_;
        status_ = GhostStatus::kFrightened;
    }
}

void Ghost::reset(const Position &coordinates)
{
    MovingEntity::reset(coordinates);
    status_ = GhostStatus::kScatter;
}
