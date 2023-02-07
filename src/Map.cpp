//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include "../include/constants.h"
#include "../include/Map.h"

Map::Map() = default;

Map::Map(int width, int height) : width(width), height(height)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            cells.emplace_back(Cell(x, y));
}
