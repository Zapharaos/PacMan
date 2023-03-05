//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include <utility>
#include "../../include/map/cell.h"

Cell::Cell() = default;

Cell::Cell(std::pair<int, int> position, int size, CellType type, const Entity& entity) : position_(std::move(position)), size_(size), type_(type), entity_(entity){}

bool Cell::operator==(const Cell &rhs) const
{
    return position_.first == rhs.position_.first && position_.second == rhs.position_.second;
}

bool Cell::operator!=(const Cell &rhs) const
{
    return !(rhs == *this);
}

CellType Cell::getType() const {
    return type_;
}

const Entity &Cell::getEntity() const {
    return entity_;
}

void Cell::setEntity(const Entity &entity) {
    entity_ = entity;
}

bool Cell::isWall() const {
    return type_ == CellType::WALL;
}

bool Cell::isWarp() const {
    return type_ == CellType::WARP;
}

void Cell::print() const{
    std::cout << "(" << position_.first << ", " << position_.second << "), ("
        << position_.first * size_ << ", " << position_.second * size_ << "), ";
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

std::pair<int, int> Cell::getWarpExit(int width, int height) const {
    std::pair<int, int> exit = getScaledPosition();
    if(position_.first == width - 1)
        exit.first = width * size_ - 1;
    else if(position_.second == height - 1)
        exit.second = height * size_ - 1;
    return exit;
}
