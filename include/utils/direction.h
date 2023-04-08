/**
 * @file direction.h
 * @brief Contains the Direction class which represents the direction something is moving towards to.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 07/03/2023
*/

#ifndef PACMAN_DIRECTION_H
#define PACMAN_DIRECTION_H

#include <iostream>
#include <random>

/**
 * @brief Represents the direction something is moving towards to.
 */
enum class DirectionType
{
    kUninitialized, /**< The direction is not initialized. */
    kLeft, /**< The direction is left. */
    kRight, /**< The direction is right. */
    kUp, /**< The direction is up. */
    kDown /**< The direction is down. */
};

/**
 * @brief Represents the direction something is moving towards to.
*/
class Direction
{

private:

    /** Direction taken. */
    DirectionType direction_{DirectionType::kUninitialized};

public:

    /**
     * @brief Default constructor.
     */
    inline Direction() = default;

    /**
     * @brief Constructor with direction.
     * @param direction DirectionType direction.
     */
    inline explicit Direction(DirectionType direction) : direction_(direction) {};

    /**
     * @brief Indicates if both directions are equal.
     * @param direction The direction to compare.
     * @return true if both directions are equal, else false.
     */
    inline bool operator==(const Direction &direction) const
    { return direction_ == direction.direction_; };

    /**
     * @brief Indicates if both directions are different.
     * @param direction The direction to compare.
     * @return true if both directions are different, else false.
     */
    inline bool operator!=(const Direction &direction) const
    { return !(direction == *this); };

    /**
     * @brief Updates the direction type.
     * @param direction The new direction type.
     */
    inline void setDirection(const DirectionType &direction)
    { direction_ = direction; };

    /**
     * @brief Indicates if the direction is uninitialized.
     * @return true if the direction is uninitialized, else false.
     */
    [[nodiscard]] inline bool isUninitialized() const
    { return direction_ == DirectionType::kUninitialized; };

    /**
     * @brief Indicates if the direction is left.
     * @return true if the direction is left, else false.
     */
    [[nodiscard]] inline bool isLeft() const
    { return direction_ == DirectionType::kLeft; };

    /**
     * @brief Indicates if the direction is right.
     * @return true if the direction is right, else false.
     */
    [[nodiscard]] inline bool isRight() const
    { return direction_ == DirectionType::kRight; };

    /**
     * @brief Indicates if the direction is up.
     * @return true if the direction is up, else false.
     */
    [[nodiscard]] inline bool isUp() const
    { return direction_ == DirectionType::kUp; };

    /**
     * @brief Indicates if the direction is down.
     * @return true if the direction is down, else false.
     */
    [[nodiscard]] inline bool isDown() const
    { return direction_ == DirectionType::kDown; };

    /**
     * @brief Indicates if the direction is moving towards left or up.
     * @return true if the direction is moving towards left or up, else false.
     */
    [[nodiscard]] inline bool isLeftOrUp() const
    {
        return direction_ == DirectionType::kLeft ||
               direction_ == DirectionType::kUp;
    };

    /**
     * @brief Indicates if the direction is horizontal.
     * @return true if the direction is horizontal, else false.
     */
    [[nodiscard]] inline bool isHorizontal() const
    {
        return direction_ == DirectionType::kLeft ||
               direction_ == DirectionType::kRight;
    };

    /**
     * @brief Indicates if the direction is vertical.
     * @return true if the direction is vertical, else false.
     */
    [[nodiscard]] inline bool isVertical() const
    {
        return direction_ == DirectionType::kUp ||
               direction_ == DirectionType::kDown;
    };

    /**
     * @brief Indicates if both directions are moving on the same axis (i.e. vertical or horizontal).
     * @param direction The other direction to compare to.
     * @return true if both directions are moving on the same axis, else false.
     */
    [[nodiscard]] inline bool isSameAxis(const Direction &direction) const
    {
        return isHorizontal() == direction.isHorizontal() ||
               isVertical() == direction.isVertical();
    };

    /**
     * @brief Indicates if the direction is a turn (i.e. not the same as the other direction and not on the same axis).
     * @param direction The other direction to compare to.
     * @return true if the direction is a turn, else false.
     */
    [[nodiscard]] inline bool isTurn(const Direction &direction) const
    {
        return direction_ != direction.direction_ && !isSameAxis(direction);
    }

    [[nodiscard]] inline Direction reverse() const
    {
        switch(direction_)
        {
            case DirectionType::kLeft:
                return Direction{DirectionType::kRight};
            case DirectionType::kRight:
                return Direction{DirectionType::kLeft};
            case DirectionType::kUp:
                return Direction{DirectionType::kDown};
            case DirectionType::kDown:
                return Direction{DirectionType::kUp};
            default:
                return Direction{DirectionType::kUninitialized};
        }
    }

    /**
     * @brief Resets the direction to uninitialized.
     */
    inline void reset()
    { direction_ = {DirectionType::kUninitialized}; };

    [[nodiscard]] inline static Direction randomize()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3);
        switch (dis(gen)) {
            case 0:
                return static_cast<Direction>(DirectionType::kLeft);
            case 1:
                return static_cast<Direction>(DirectionType::kRight);
            case 2:
                return static_cast<Direction>(DirectionType::kUp);
            case 3:
                return static_cast<Direction>(DirectionType::kDown);
            default: // unreachable
                return static_cast<Direction>(DirectionType::kUninitialized);
        }

    };

    /**
     * @brief Prints the direction for debugging purposes.
     */
    inline void print() const
    {
        switch (direction_)
        {
            case DirectionType::kLeft:
                std::cout << "LEFT" << std::endl;
                break;
            case DirectionType::kRight:
                std::cout << "RIGHT" << std::endl;
                break;
            case DirectionType::kUp:
                std::cout << "UP" << std::endl;
                break;
            case DirectionType::kDown:
                std::cout << "DOWN" << std::endl;
                break;
            case DirectionType::kUninitialized:
                std::cout << "UNINITIALIZED" << std::endl;
                break;
        }
    };
};


#endif //PACMAN_DIRECTION_H
