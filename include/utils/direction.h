//
// Created by matthieu on 07/03/2023.
//

#ifndef PACMAN_DIRECTION_H
#define PACMAN_DIRECTION_H

#include <iostream>

/** Direction something is moving towards to. */
enum class DirectionType
{
    kUninitialized,
    kLeft,
    kRight,
    kUp,
    kDown
};

/** Direction something is moving towards to. */
class Direction
{

private:

    /** Direction taken. */
    DirectionType direction_{DirectionType::kUninitialized};

    /** Is moving towards left / top. */
    bool left_or_up_ = false;

public:

    /** Default Direction constructor. */
    Direction();

    /** Default Direction constructor.
     *
     * @param direction Direction taken.
     */
    explicit Direction(const DirectionType &direction);

    /** If both directions are equals. */
    bool operator==(const Direction &direction) const;

    /** If both directions are different. */
    bool operator!=(const Direction &direction) const;

    /** Updates the direction type. */
    void setDirection(const DirectionType &direction);

    /** Is moving towards left / top. */
    [[nodiscard]] bool isLeftOrUp() const;

    /** Indicates if the direction is uninitialized. */
    [[nodiscard]] inline bool isUninitialized() const
    { return direction_ == DirectionType::kUninitialized; };

    /** Indicates if direction is left. */
    [[nodiscard]] inline bool isLeft() const
    { return direction_ == DirectionType::kLeft; };

    /** Indicates if direction is right. */
    [[nodiscard]] inline bool isRight() const
    { return direction_ == DirectionType::kRight; };

    /** Indicates if direction is up. */
    [[nodiscard]] inline bool isUp() const
    { return direction_ == DirectionType::kUp; };

    /** Indicates if direction is down. */
    [[nodiscard]] inline bool isDown() const
    { return direction_ == DirectionType::kDown; };

    /** Indicates if direction is horizontal. */
    [[nodiscard]] inline bool isHorizontal() const
    {
        return direction_ == DirectionType::kLeft ||
               direction_ == DirectionType::kRight;
    };

    /** Indicates if direction is vertical. */
    [[nodiscard]] inline bool isVertical() const
    {
        return direction_ == DirectionType::kUp ||
               direction_ == DirectionType::kDown;
    };

    /** Indicates if both directions are moving on the same axis (i.e. vertical or horizontal). */
    [[nodiscard]] inline bool isSameAxis(const Direction &direction) const
    {
        return isHorizontal() == direction.isHorizontal() ||
               isVertical() == direction.isVertical();
    };

    [[nodiscard]] inline bool isTurn(const Direction &direction) const
    {
        return direction_ != direction.direction_ && !isSameAxis(direction);
    }

    /** Resets a direction */
    void reset();

    /**
     * [Debug] : Prints the direction.
     */
    void print() const;
};


#endif //PACMAN_DIRECTION_H
