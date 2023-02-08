//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include "../include/map.h"

map::map() = default;

map::map(int width, int height) : width_(width), height_(height)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            cells_.emplace_back(cell{x, y});
}

void map::print() const
{
    std::cout << "width: " << width_ << ", height: " << height_ << ", cells: " << std::endl;
    for(const auto& cell: cells_) cell.print();
}
