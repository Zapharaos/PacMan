//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_CELL_H
#define PACMAN_CELL_H

#include <string>
#include <array>
#include "../utils/constants.h"
#include "../entity/entity.h"

enum class CellType
{
    WALL = 0,
    POINT = 1,
    POWER = 2,
    PATH = 3,
    WARP = 4
};

class Cell {

    private:
        std::pair<int, int> position_ {};
        int size_ {};
        CellType type_ = CellType::WALL;
        Entity entity_ {};

    public:
        Cell();
        Cell(std::pair<int, int> position, int size, CellType type, const Entity& entity);

        bool operator==(const Cell &rhs) const;
        bool operator!=(const Cell &rhs) const;

        [[nodiscard]] CellType getType() const;
        [[nodiscard]] const Entity &getEntity() const;
        void setEntity(const Entity &entity);
        [[nodiscard]] bool isWall() const;
        [[nodiscard]] bool isWarp() const;

        void print() const;
        [[nodiscard]] bool isAlignedWith(pair<int, int> position) const;
        [[nodiscard]] bool equalsScaledPosition(std::pair<int, int> position) const;
        [[nodiscard]] std::pair<int, int> getScaledPosition() const;
};


#endif //PACMAN_CELL_H
