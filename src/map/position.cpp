/**
 * @file position.cpp
 * @brief Implementation of the Position class representing a position on a 2D grid.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 10/02/2023
 */

#include "../../include/map/position.h"

#include <iostream>
#include <cmath>
#include <utility>

Position::Position() = default;

Position::Position(std::pair<int, int> position) : position_(std::move(position))
{}

Position::Position(int abscissa, int ordinate) : position_({abscissa, ordinate})
{}

bool Position::operator==(const Position &position) const
{
    return position_ == position.position_;
}

bool Position::operator!=(const Position &position) const
{
    return !(position == *this);
}

const int &Position::getAbscissa() const
{
    return position_.first;
}

const int &Position::getOrdinate() const
{
    return position_.second;
}

double Position::getDistance(const Position& position) const {
    int dx = position.getAbscissa() - position_.first;
    int dy = position.getOrdinate() - position_.second;
    return std::sqrt(dx * dx + dy * dy);
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
    return Position{position_.first * scale, position_.second * scale};
}

Position Position::getPositionUnscaled(int scale) const
{
    auto x = getAbscissa() / scale;
    auto y = getOrdinate() / scale;
    return Position{static_cast<int>(floor(x)), static_cast<int>(floor(y))};
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
        --position.first;
    else if (direction.isRight())
        ++position.first;
    else if (direction.isUp())
        --position.second;
    else if (direction.isDown())
        ++position.second;
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

Position Position::shift(int x, int y) const
{
    return Position{position_.first+x, position_.second+y};
}

Position Position::getOpposite(int width, int height) const
{
    auto x = position_.first;
    auto y = position_.second;

    if(x < 0) // Opposite on the right
        x = width - 1;
    if (y < 0) // Opposite on the top
        y = height - 1;
    if (x > width - 1) // Opposite on the left
        x = 0;
    if (y > height - 1) // Opposite on the bottom
        y = 0;

    return Position{x, y};
}

void Position::print() const
{
    std::cout << "(" << position_.first << ", " << position_.second << ")" << std::endl;
}
