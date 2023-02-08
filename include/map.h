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
        Map(int width, int height);
        void print() const;
        inline int getCellIndexByPositions(int x, int y) { return y * height_ + x; };

    private:
        int width_ = 0;
        int height_ = 0;
        std::vector<Cell> cells_;
};


#endif //PACMAN_MAP_H
