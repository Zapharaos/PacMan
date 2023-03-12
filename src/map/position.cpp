//
// Created by mfrei on 10/03/2023.
//

#include <iostream>
#include <cmath>
#include "../../include/map/position.h"

Position::Position() = default;

Position::Position(const pair<int, int> &position) : position_(position)
{}

bool Position::operator==(const Position &rhs) const
{
    return position_ == rhs.position_;
}

bool Position::operator!=(const Position &rhs) const
{
    return !(rhs == *this);
}

const int &Position::getAbscissa() const
{
    return position_.first;
}

const int &Position::getOrdinate() const
{
    return position_.second;
}

bool Position::isOutOfBounds(int width, int height) const
{
    return (position_.first < 0 || position_.first >= width ||
            position_.second < 0 || position_.second >= height);
}

bool Position::isBetween(const Position &a, const Position &b) const
{
    return (b.position_.first < position_.first &&
            position_.first <= a.position_.first) ||
           (a.position_.first <= position_.first &&
            position_.first < b.position_.first) ||
           (b.position_.second < position_.second &&
            position_.second <= a.position_.second) ||
           (a.position_.second <= position_.second &&
            position_.second < b.position_.second);
}

int Position::getSingleAxisDistance(const Position &position) const
{
    if (position_.first == position.position_.first)
        return abs(position_.second - position.position_.second);
    return abs(position_.first - position.position_.first);
}

Position Position::getPositionScaled(int scale) const
{
    return Position({position_.first * scale, position_.second * scale});
}

Position Position::getPositionUnscaled(int scale) const
{
    float x = (float) getAbscissa() / (float) scale;
    float y = (float) getOrdinate() / (float) scale;
    return Position{{floor(x), floor(y)}};
}

bool Position::isNeighbor(const Position &position) const
{
    return (position.getAbscissa() - 1 == getAbscissa() ||
            position.getAbscissa() + 1 == getAbscissa() ||
            position.getOrdinate() - 1 == getOrdinate() ||
            position.getOrdinate() + 1 == getOrdinate());
}

Position Position::getNeighbor(const Direction &direction) const
{
    auto position = position_;
    if (direction.isLeft())
        position.first--;
    else if (direction.isRight())
        position.first++;
    else if (direction.isUp())
        position.second--;
    else if (direction.isDown())
        position.second++;
    return Position{position};
}

Position Position::moveIntoDirection(const Direction &direction, int distance) const
{
    auto position = position_;
    if (direction.isLeft()) position.first -= distance;
    else if (direction.isRight()) position.first += distance;
    else if (direction.isUp()) position.second -= distance;
    else if (direction.isDown()) position.second += distance;
    return Position{position};
}

void Position::print() const
{
    cout << "(" << position_.first << ", " << position_.second << ")" << endl;
}


