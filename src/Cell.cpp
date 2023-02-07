//
// Created by matthieu on 07/02/2023.
//

#include "../include/Cell.h"

Cell::Cell() = default;

Cell::Cell(int x, int y) : x(x), y(y) {}

int Cell::getX() const {
    return x;
}

void Cell::setX(int x) {
    Cell::x = x;
}

int Cell::getY() const {
    return y;
}

void Cell::setY(int y) {
    Cell::y = y;
}
