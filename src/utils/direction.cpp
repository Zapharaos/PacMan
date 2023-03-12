//
// Created by matthieu on 07/03/2023.
//

#include "../../include/utils/direction.h"

Direction::Direction() = default;

Direction::Direction(DirectionType direction)
{
    setDirection(direction);
}

void Direction::setDirection(DirectionType direction)
{
    direction_ = direction;
    isLeftOrUp_ =
            direction == DirectionType::LEFT || direction == DirectionType::UP;
}

bool Direction::isLeftOrUp() const
{
    return isLeftOrUp_;
}

void Direction::reset()
{
    direction_ = {DirectionType::UNINITIALIZED};
    isLeftOrUp_ = false;
}

void Direction::print() const
{
    switch (direction_)
    {
        case DirectionType::LEFT:
            cout << "LEFT" << endl;
            break;
        case DirectionType::RIGHT:
            cout << "RIGHT" << endl;
            break;
        case DirectionType::UP:
            cout << "UP" << endl;
            break;
        case DirectionType::DOWN:
            cout << "DOWN" << endl;
            break;
        case DirectionType::UNINITIALIZED:
            cout << "UNINITIALIZED" << endl;
            break;
    }
}