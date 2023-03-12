//
// Created by matthieu on 07/03/2023.
//

#ifndef PACMAN_DIRECTION_H
#define PACMAN_DIRECTION_H

#include <iostream>

using namespace std;

/** Direction something is moving towards to. */
enum class DirectionType
{
    UNINITIALIZED,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

/** Direction something is moving towards to. */
class Direction
{

private:

    /** Direction taken. */
    DirectionType direction_{DirectionType::UNINITIALIZED};

    /** Is moving towards left / top. */
    bool isLeftOrUp_ = false;

public:

    /** Default Direction constructor. */
    Direction();

    /** Default Direction constructor.
     *
     * @param direction Direction taken.
     */
    explicit Direction(DirectionType direction);

    /** Updates the direction type. */
    void setDirection(DirectionType direction);

    /** Is moving towards left / top. */
    [[nodiscard]] bool isLeftOrUp() const;

    /** Indicates if the direction is uninitialized. */
    inline bool isUninitialized()
    { return direction_ == DirectionType::UNINITIALIZED; };

    /** Indicates if direction is left. */
    inline bool isLeft()
    { return direction_ == DirectionType::LEFT; };

    /** Indicates if direction is right. */
    inline bool isRight()
    { return direction_ == DirectionType::RIGHT; };

    /** Indicates if direction is up. */
    inline bool isUp()
    { return direction_ == DirectionType::UP; };

    /** Indicates if direction is down. */
    inline bool isDown()
    { return direction_ == DirectionType::DOWN; };

    /** Indicates if direction is horizontal. */
    inline bool isHorizontal()
    {
        return direction_ == DirectionType::LEFT ||
               direction_ == DirectionType::RIGHT;
    };

    /** Indicates if direction is vertical. */
    inline bool isVertical()
    {
        return direction_ == DirectionType::UP ||
               direction_ == DirectionType::DOWN;
    };

    /** Indicates if both directions are equals. */
    inline bool isEqual(Direction direction)
    { return direction_ == direction.direction_; };

    /** Indicates if both directions are moving on the same axis (i.e. vertical or horizontal). */
    inline bool isSameAxis(Direction direction)
    {
        return isHorizontal() == direction.isHorizontal() ||
               isVertical() == direction.isVertical();
    };

    /** Resets a direction */
    void reset();

    /**
     * [Debug] : Prints the direction.
     */
    void print() const;
};


#endif //PACMAN_DIRECTION_H
