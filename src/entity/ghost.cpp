/**
 * @file ghost.cpp
 * @brief Implements the Ghost class, which is the second entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 03/04/2023
*/

#include "../../include/entity/ghost.h"

Ghost::Ghost() : MovingEntity(Position{{config::positions::kPacmanX, config::positions::kPacmanY}},
                              config::settings::kSpeedPacman,
                              visuals::pacman::left::kAnimation,
                              visuals::pacman::right::kAnimation,
                              visuals::pacman::up::kAnimation,
                              visuals::pacman::down::kAnimation)
{}

Ghost::Ghost(Ghost::GhostType type) : Ghost() {
    type_ = type;
}

void Ghost::tick(const Map &map, const SDL_Rect &pacman) {

    // TODO : might need to handle ghost status

    // TODO : get direction from pathfinding
    Direction direction;
    MovingEntity::tick(map, direction);
}

void Ghost::reset(const Position &coordinates)
{
    MovingEntity::reset(coordinates);
    status_ = GhostStatus::kDefault;
}
