//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H

#include <vector>
#include "cell.h"
#include "entity.h"

class Map {

    public:
        Map();
        Map(int width, int height, int cell_size, const std::vector<cell_type>& cell_types);

        void printAsMap() const;
        [[nodiscard]] bool canMoveToCell(std::pair<int, int> destination, bool isMovingLeftOrUp);
        [[nodiscard]] const std::pair<int, int> &getDestination() const;
        [[nodiscard]] Cell& getCellAtDestination(std::pair<int, int> destination, bool isMovingLeftOrUp);

    private:
        int width_ = 0;
        int height_ = 0;
        int cell_size_ = 0;
        std::vector<Cell> cells_;
        std::pair<int, int> destination_;

        [[nodiscard]] std::pair<int, int> getCellCoordinatesFromPositions(std::pair<int, int> destination, bool isMovingLeftOrUp);
        [[nodiscard]] float getScaledPosition(int position) const;
        [[nodiscard]] bool isDirectNeighbour(std::pair<int, int> destination) const;
        [[nodiscard]] bool isTunnel(std::pair<int, int> position) const;
        [[nodiscard]] std::pair<int, int> getTunnelCoordinates(std::pair<int, int> destination) const;
        [[nodiscard]] Cell& getCellAtPosition(std::pair<int, int> position);
        [[nodiscard]] bool isPositionOutOfBounds(std::pair<int, int> position) const;
        [[nodiscard]] inline int getCellIndexFromPosition(std::pair<int, int> position) const;
};


#endif //PACMAN_MAP_H
