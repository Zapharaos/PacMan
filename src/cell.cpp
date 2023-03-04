//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include <utility>
#include "../include/cell.h"

Cell::Cell() = default;

Cell::Cell(std::pair<int, int> position, int size, cell_type type, const Entity& entity) : position_(std::move(position)), size_(size), type_(type), entity_(entity){}

bool Cell::operator==(const Cell &rhs) const
{
    return position_.first == rhs.position_.first && position_.second == rhs.position_.second;
}

bool Cell::operator!=(const Cell &rhs) const
{
    return !(rhs == *this);
}

cell_type Cell::getType() const {
    return type_;
}

const Entity &Cell::getEntity() const {
    return entity_;
}

void Cell::setEntity(const Entity &entity) {
    entity_ = entity;
}

bool Cell::isWall() const {
    return type_ == cell_type::WALL;
}

bool Cell::isTunnel() const
{
    return type_ == cell_type::TUNNEL;
}

void Cell::print() const{
    std::cout << "(" << position_.first << ", " << position_.second
            << "), (" << position_.first * size_ << ", " << position_.second * size_
            << "), type: " << type_ << ", ";
    entity_.print();
}

bool Cell::isAlignedWith(pair<int, int> position) const {
    return position_.first * size_ == position.first || position_.second * size_ == position.second;
}

bool Cell::equalsScaledPosition(std::pair<int, int> position) const {
    return position_.first * size_ == position.first && position_.second * size_ == position.second;
}

std::pair<int, int> Cell::getScaledPosition() const {
    return {position_.first * size_, position_.second * size_};
}

std::pair<int, int> Cell::getNeighboursPosition(directions direction) const {
    switch (direction)
    {
        case LEFT:
            return {position_.first-1, position_.second};
        case RIGHT:
            return {position_.first+1, position_.second};
        case UP:
            return {position_.first, position_.second-1};
        case DOWN:
            return {position_.first, position_.second+1};
        default:
            return position_;
    }
}

std::pair<int, int> Cell::getCornerPosition(directions direction, directions turn) const {
    std::pair<int, int> corner = getScaledPosition();

    if(direction == RIGHT && turn == UP || direction == DOWN && turn == LEFT)
        return corner;

    if(direction == DOWN && turn == RIGHT || direction == LEFT && turn == UP)
        return {corner.first + size_ - 1, corner.second};

    if(direction == LEFT && turn == DOWN || direction == UP && turn == RIGHT)
        return {corner.first + size_ - 1, corner.second + size_ - 1};

    if(direction == UP && turn == LEFT || direction == RIGHT && turn == DOWN)
        return {corner.first, corner.second + size_ - 1};

    return corner; // should be unreachable

    /*
    if(direction == LEFT)
    {
        if(turn == UP)
            return {corner.first + size_ - 1, corner.second + size_ - 1};
        else if (turn == DOWN)
            return {corner.first + size_ - 1, corner.second};
    }
    else if (direction == RIGHT)
    {
        if(turn == UP)
            return {corner.first, corner.second + size_ - 1};
        else if (turn == DOWN)
            return corner; // NOTHING
    }
    else if (direction == UP)
    {
        if(turn == LEFT)
            return {corner.first + size_ - 1, corner.second + size_ - 1};
        else if (turn == RIGHT)
            return {corner.first, corner.second + size_ - 1};
    }
    else if (direction == DOWN)
    {
        if(turn == LEFT)
            return {corner.first + size_ - 1, corner.second};
        else if (turn == RIGHT)
            return corner; // NOTHING
    }
    return corner;*/
}
