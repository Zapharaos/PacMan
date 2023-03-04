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

    private:
        std::pair<int, int> position_ {};
        int size_ {};
        cell_type type_ = cell_type::WALL;
        Entity entity_ {};

    public:
        Cell();
        Cell(std::pair<int, int> position, int size, cell_type type, const Entity& entity);

        bool operator==(const Cell &rhs) const;
        bool operator!=(const Cell &rhs) const;

        [[nodiscard]] cell_type getType() const;
        [[nodiscard]] const Entity &getEntity() const;
        void setEntity(const Entity &entity);
        [[nodiscard]] bool isWall() const;
        [[nodiscard]] bool isTunnel() const;

        void print() const;
        [[nodiscard]] bool isAlignedWith(pair<int, int> position) const;
        [[nodiscard]] bool equalsScaledPosition(std::pair<int, int> position) const;
        [[nodiscard]] std::pair<int, int> getScaledPosition() const;
        [[nodiscard]] pair<int, int> getNeighboursPosition(directions direction) const;
        [[nodiscard]] pair<int, int> getCornerPosition(directions direction, directions turn) const;
};


#endif //PACMAN_CELL_H
