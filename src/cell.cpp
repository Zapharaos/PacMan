//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include "../include/cell.h"

Cell::Cell() = default;

Cell::Cell(int x, int y, cell_type type) : x_(x), y_(y), type_(type) {}

int Cell::getX() const {
    return x_;
}

void Cell::setX(int x) {
    x_ = x;
}

int Cell::getY() const {
    return y_;
}

void Cell::setY(int y) {
    y_ = y;
}

cell_type Cell::getType() const {
    return type_;
}

void Cell::setType(cell_type type) {
    type_ = type;
}

bool Cell::isWall() const {
    return type_ == cell_type::WALL;
}

void Cell::print() const{
    std::cout << "x: " << x_ << ", y: " << y_ << ", type: " << type_ << std::endl;
}