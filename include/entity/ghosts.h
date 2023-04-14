//
// Created by mfrei on 13/04/2023.
//

#ifndef PACMAN_GHOSTS_H
#define PACMAN_GHOSTS_H

#include "../../src/entity/ghostSpecial.cpp"

class Ghosts
{

private:

    std::shared_ptr<GhostSpecial<GhostType::kBlinky>> blinky_ {};
    std::shared_ptr<GhostSpecial<GhostType::kPinky>> pinky_ {};
    std::shared_ptr<GhostSpecial<GhostType::kInky>> inky_ {};
    std::shared_ptr<GhostSpecial<GhostType::kClyde>> clyde_ {};
    std::array<std::shared_ptr<Ghost>, 4> ghosts_entities {};

    /** Counts a number of frames between each statuses. */
    Counter status_counter_ {};

    /** The number of times the Ghost's status has changed.
    * @details Set as 1 since the 0 index is const for the frightened mode. */
    size_t status_changes_ {};

    /** Duration values for the statuses (in seconds) :
     * Index 0 is const for the frightened mode (not blinking!).
     * Index odd : scatter timers.
     * Index even : chase timers (infinite after last scatter).
     */
    inline static constexpr std::array<unsigned long, 8> status_timers {5, 7, 20, 7, 20, 5, 20, 5};

public:
    Ghosts();

    std::array<std::shared_ptr<Ghost>, 4> getGhosts();

    void tick(const Map& map, Position position, Direction direction);

    void frightened();

    void reset();

    void levelUp();

    void clear();
};


#endif //PACMAN_GHOSTS_H
