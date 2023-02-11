//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_CELL_H
#define PACMAN_CELL_H

#include <string>
#include <array>

class Cell {

    public:
        Cell();
        Cell(int x, int y, bool is_wall);

    [[nodiscard]] int getX() const;

    void setX(int x);

    [[nodiscard]] int getY() const;

    void setY(int y);

    [[nodiscard]] bool isWall() const;

    void setIsWall(bool isWall);

    void print() const;

    private:
        int x_ = 0;
        int y_ = 0;
        bool is_wall_ = false;
};


#endif //PACMAN_CELL_H
