//
// Created by matthieu on 07/03/2023.
//

#include "../../include/utils/direction.h"

Direction::Direction() = default;

Direction::Direction(DirectionType direction, bool isLeftOrUp) : direction_(direction), isLeftOrUp_(isLeftOrUp) {}

DirectionType Direction::getDirection() const {
    return direction_;
}

bool Direction::isLeftOrUp() const {
    return isLeftOrUp_;
}
