//
// Created by mfrei on 13/04/2023.
//

#ifndef PACMAN_GHOSTSPECIAL_H
#define PACMAN_GHOSTSPECIAL_H

#include "ghost.h"

enum class GhostType {
    kBlinky,
    kPinky,
    kInky,
    kClyde
};

template <GhostType T>
class GhostSpecial : public Ghost
{

private:
    GhostType type_ {T};

public:
    GhostSpecial();

    GhostSpecial(const Position &position, const Position &scatterTarget,
                 const Position &houseTarget, const Animation &left,
                 const Animation &right, const Animation &up,
                 const Animation &down);

    template <GhostType U = T, typename std::enable_if<U == GhostType::kBlinky, int>::type = 0>
    void chase(const Position &pacman);

    template <GhostType U = T, typename std::enable_if<U == GhostType::kPinky, int>::type = 0>
    void chase(const Position &pacman, const Direction &direction);

    template <GhostType U = T, typename std::enable_if<U == GhostType::kInky, int>::type = 0>
    void chase(const Position &pacman, const Direction &direction, const Position &blinky);

    template <GhostType U = T, typename std::enable_if<U == GhostType::kClyde, int>::type = 0>
    void chase(const Position &pacman);
};


#endif //PACMAN_GHOSTSPECIAL_H
