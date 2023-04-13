//
// Created by mfrei on 13/04/2023.
//

#ifndef PACMAN_GHOSTS_H
#define PACMAN_GHOSTS_H

#include "ghost.h"
#include "../../src/entity/ghost.cpp"

class Ghosts
{

private:
    std::shared_ptr<Ghost<GhostType::kBlinky>> blinky_;
    std::shared_ptr<Ghost<GhostType::kPinky>> pinky_;
    std::shared_ptr<Ghost<GhostType::kInky>> inky_;
    std::shared_ptr<Ghost<GhostType::kClyde>> clyde_;
    std::array<std::shared_ptr<Entity>, 4> ghosts_entities {};

public:
    Ghosts();

    std::array<std::shared_ptr<Entity>, 4> getGhostsAsEntities();

    void tick(const Map& map, Position position, Direction direction);

    void show();

    void hide();

    void unfrightened();

    void frightened();

    void reset();

};


#endif //PACMAN_GHOSTS_H
