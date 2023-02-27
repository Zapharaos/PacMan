//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include "../include/cell.h"

Cell::Cell() = default;

Cell::Cell(int x, int y, cell_type type, const Entity& entity) : x_(x), y_(y), type_(type), entity_(entity){}

int Cell::getX() const {
    return x_;
}

int Cell::getY() const {
    return y_;
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

void Cell::print() const{
    std::cout << "x: " << x_ << ", y: " << y_ << ", type: " << type_;
    entity_.print();
}