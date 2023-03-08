//
// Created by matthieu on 07/03/2023.
//

#ifndef PACMAN_DIRECTION_H
#define PACMAN_DIRECTION_H

enum class DirectionType
{
    UNINITIALIZED = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN = 4
};

class Direction {

public:

    Direction();
    Direction(DirectionType direction, bool isLeftOrUp);

    [[nodiscard]] DirectionType getDirection() const;
    [[nodiscard]] bool isLeftOrUp() const;

    inline bool isUninitialized() { return direction_ == DirectionType::UNINITIALIZED;};
    inline bool isLeft() { return direction_ == DirectionType::LEFT;};
    inline bool isRight() { return direction_ == DirectionType::RIGHT;};
    inline bool isUp() { return direction_ == DirectionType::UP;};
    inline bool isDown() { return direction_ == DirectionType::DOWN;};

    inline bool isEqual(Direction direction) { return direction_ == direction.getDirection(); };
    inline bool isSameAxis(Direction direction) { return (isLeft() || isRight()) && (direction.isLeft() || direction.isRight()); };

    inline void reset() { direction_ = {DirectionType::UNINITIALIZED};};

private:
    DirectionType direction_ {DirectionType::UNINITIALIZED};
    bool isLeftOrUp_ = false;
};


#endif //PACMAN_DIRECTION_H
