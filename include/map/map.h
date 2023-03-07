//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H

#include <vector>
#include "cell.h"
#include "../entity/entity.h"
#include "../utils/direction.h"


class Map {

    public:
        Map();
        Map(int width, int height, int cell_size, const std::vector<CellType>& cell_types);

        [[nodiscard]] bool canMoveToCell(std::pair<int, int> origin, std::pair<int, int> destination, Direction direction);
        [[nodiscard]] bool canTurnToCell(pair<int, int> origin, pair<int, int> destination, Direction direction, Direction turn);
        [[nodiscard]] const std::pair<int, int> &getDestination() const;
        [[nodiscard]] std::vector<Cell> getCellsWithActiveEntities();
        [[nodiscard]] Cell& getCellFromCoordinates(pair<int, int> coordinates, bool toFloor);

    private:
        int width_ = 0;
        int height_ = 0;
        int cell_size_ = 0;
        std::vector<Cell> cells_;
        std::pair<int, int> destination_;

        [[nodiscard]] Cell& getCellAtPosition(std::pair<int, int> position);
        [[nodiscard]] static bool isPositionInBetween(Direction direction, pair<int, int> position, pair<int, int> origin, pair<int, int> destination) ;
        [[nodiscard]] static pair<int, int> changeDestinationOnTurn(pair<int, int> origin, int remainder, Direction direction);
        [[nodiscard]] static int getRemainder(pair<int, int> origin, pair<int, int> middle, pair<int, int> destination, Direction direction);
        [[nodiscard]] pair<int, int> getPositionFromCoordinates(pair<int, int> coordinates, bool toFloor) const;
        [[nodiscard]] Cell getWarpEntryCell(pair<int, int> coordinates, bool toFloor);
        [[nodiscard]] Cell getWarpExitCell(pair<int, int> coordinates, bool toFloor);
        [[nodiscard]] bool hasExit(const Cell &cell);
};


#endif //PACMAN_MAP_H
