//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_CONSTANTS_H
#define PACMAN_CONSTANTS_H

// define your own namespace to hold constants
namespace constants
{
    inline constexpr int MAP_START_X {200};
    inline constexpr int MAP_START_Y {3};
    inline constexpr int MAP_WIDTH {168};
    inline constexpr int MAP_HEIGHT {216};
    inline constexpr int MAP_SCALE_RATIO {4};

    inline constexpr int GHOST_START_X {3};
    inline constexpr int GHOST_START_Y {123};
    inline constexpr int GHOST_WIDTH {16};
    inline constexpr int GHOST_HEIGHT {16};

    inline constexpr int CELL_WIDTH {32};
    inline constexpr int CELL_HEIGHT {32};
}

#endif //PACMAN_CONSTANTS_H