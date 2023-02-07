//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_CELL_H
#define PACMAN_CELL_H

#include <string>

class Cell {

    public:
        Cell();
        Cell(int x, int y);

    [[nodiscard]] int getX() const;

    void setX(int x);

    [[nodiscard]] int getY() const;

    void setY(int y);

    private:
        int x = 0;
        int y = 0;
};


#endif //PACMAN_CELL_H
