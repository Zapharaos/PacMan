//
// Created by matthieu on 07/03/2023.
//

#include "../../include/utils/direction.h"

Direction::Direction() = default;

Direction::Direction(const DirectionType &direction)
{
    setDirection(direction);
}

bool Direction::operator==(const Direction &direction) const
{
    return direction_ == direction.direction_;
}

bool Direction::operator!=(const Direction &direction) const
{
    return !(direction == *this);
}

void Direction::setDirection(const DirectionType &direction)
{
    direction_ = direction;
    left_or_up_ =
            direction == DirectionType::kLeft || direction == DirectionType::kUp;
}

bool Direction::isLeftOrUp() const
{
    return left_or_up_;
}

void Direction::reset()
{
    direction_ = {DirectionType::kUninitialized};
    left_or_up_ = false;
}

void Direction::print() const
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
}