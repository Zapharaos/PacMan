//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H

#include <vector>
#include "cell.h"

class Map {

    public:
        Map();
        Map(int width, int height, const std::vector<int>& cell_types);
        void print() const;
        void printAsMap() const;

    private:
        int width_ = 0;
        int height_ = 0;
        std::vector<Cell> cells_;
};


#endif //PACMAN_MAP_H
