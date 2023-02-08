//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include "../include/Cell.h"

Cell::Cell() = default;

Cell::Cell(int x, int y) : x_(x), y_(y) {}

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

bool Cell::isWall() const {
    return is_wall_;
}

void Cell::setIsWall(bool isWall) {
    is_wall_ = isWall;
}

int Cell::getPoints() const {
    return points_;
}

void Cell::setPoints(int points) {
    points_ = points;
}

void Cell::print() const{
    std::cout << "x: " << x_ << ", y: " << y_ << std::endl;
}
