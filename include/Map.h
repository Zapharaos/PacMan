//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H

#include <vector>
#include "Cell.h"

class Map {

    public:
        Map();
        Map(int width, int height);

private:
        int width = 0;
        int height = 0;
        std::vector<Cell> cells;
};


#endif //PACMAN_MAP_H
