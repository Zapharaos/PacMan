//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include "../include/cell.h"

cell::cell() = default;

cell::cell(int x, int y) : x_(x), y_(y) {}

int cell::getX() const {
    return x_;
}

void cell::setX(int x) {
    x_ = x;
}

int cell::getY() const {
    return y_;
}

void cell::setY(int y) {
    y_ = y;
}

bool cell::isWall() const {
    return is_wall_;
}

void cell::setIsWall(bool isWall) {
    is_wall_ = isWall;
}

void cell::print() const{
    std::cout << "x: " << x_ << ", y: " << y_ << std::endl;
}
