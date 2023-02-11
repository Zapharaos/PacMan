//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include "../include/map.h"
#include "../include/constants.h"

Map::Map() = default;

Map::Map(int width, int height, const std::vector<int>& cell_types) : width_(width), height_(height)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            cells_.emplace_back(Cell{x, y, cell_types[x + width * y] == constants::CELL_TYPE_WALL});
}

void Map::print() const
{
    std::cout << "width: " << width_ << ", height: " << height_ << ", cells: " << std::endl;
    for(const auto& cell: cells_) cell.print();
}

void Map::printAsMap() const
{
    for (int y = 0; y < height_; y++)
    {
        for (int x = 0; x < width_; x++)
        {
            std::cout << (cells_[x + width_ * y].isWall() ? " " : "1") << " ";
        }
        std::cout << std::endl;
    }
}