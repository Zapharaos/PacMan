//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_CELL_H
#define PACMAN_CELL_H

#include <string>
#include <array>
#include "constants.h"
#include "entity.h"

class Cell {

    public:
        Cell();
        Cell(int x, int y, cell_type type, const Entity& entity);

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    [[nodiscard]] cell_type getType() const;

    [[nodiscard]] const Entity &getEntity() const;

    void setEntity(const Entity &entity);

    [[nodiscard]] bool isWall() const;

    void print() const;

private:
        int x_ = 0;
        int y_ = 0;
        cell_type type_ = cell_type::WALL;
        Entity entity_ {};
};


#endif //PACMAN_CELL_H
