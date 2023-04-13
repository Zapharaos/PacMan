//
// Created by mfrei on 13/04/2023.
//

#ifndef PACMAN_GHOSTS_H
#define PACMAN_GHOSTS_H

#include "../../src/entity/ghostSpecial.cpp"

class Ghosts
{

private:
    std::shared_ptr<GhostSpecial<GhostType::kBlinky>> blinky_;
    std::shared_ptr<GhostSpecial<GhostType::kPinky>> pinky_;
    std::shared_ptr<GhostSpecial<GhostType::kInky>> inky_;
    std::shared_ptr<GhostSpecial<GhostType::kClyde>> clyde_;
    std::array<std::shared_ptr<Ghost>, 4> ghosts_entities {};

public:
    Ghosts();

    std::array<std::shared_ptr<Ghost>, 4> getGhosts();

    void tick(const Map& map, Position position, Direction direction);

};


#endif //PACMAN_GHOSTS_H
