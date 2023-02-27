//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_CELL_H
#define PACMAN_CELL_H

#include <string>
#include <array>
#include "constants.h"

class Cell {

    public:
        Cell();
        Cell(int x, int y, cell_type type);

    [[nodiscard]] int getX() const;

    void setX(int x);

    [[nodiscard]] int getY() const;

    void setY(int y);

    [[nodiscard]] cell_type getType() const;

    void setType(cell_type type);

    [[nodiscard]] bool isWall() const;

    void print() const;

    private:
        int x_ = 0;
        int y_ = 0;
        cell_type type_ = cell_type::WALL;
};


#endif //PACMAN_CELL_H
