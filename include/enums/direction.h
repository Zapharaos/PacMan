//
// Created by mfrei on 04/03/2023.
//

#ifndef PACMAN_DIRECTION_H
#define PACMAN_DIRECTION_H

enum class Direction
{
    NONE = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN = 4
};

static inline bool areDirectionsEqual(Direction a, Direction b) {
    return a == b;
}

static inline bool areDirectionsOpposite(Direction a, Direction b) {
    return (a == Direction::LEFT || a == Direction::RIGHT)
           == (b == Direction::LEFT || b == Direction::RIGHT);
}

#endif //PACMAN_DIRECTION_H
