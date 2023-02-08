//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_CONSTANTS_H
#define PACMAN_CONSTANTS_H

namespace constants
{
    // Bitmap => Map
    inline constexpr int BMP_MAP_START_X {200};
    inline constexpr int BMP_MAP_START_Y {3};
    inline constexpr int BMP_MAP_WIDTH {168};
    inline constexpr int BMP_MAP_HEIGHT {216};

    // Bitmap => Cell
    inline constexpr int BMP_CELL_WIDTH {8};
    inline constexpr int BMP_CELL_HEIGHT {8};

    // Bitmap => Entity
    inline constexpr int BMP_ENTITY_WIDTH {16};
    inline constexpr int BMP_ENTITY_HEIGHT {16};
    inline constexpr int BMP_ENTITY_BORDER_WIDTH {1};
    inline constexpr int BMP_ENTITY_TOTAL_WIDTH {BMP_ENTITY_WIDTH + BMP_ENTITY_BORDER_WIDTH};
    inline constexpr int BMP_ENTITY_OFFSET_TO_RIGHT_IMG {0 * BMP_ENTITY_TOTAL_WIDTH};
    inline constexpr int BMP_ENTITY_OFFSET_TO_LEFT_IMG {2 * BMP_ENTITY_TOTAL_WIDTH};
    inline constexpr int BMP_ENTITY_OFFSET_TO_UP_IMG {4 * BMP_ENTITY_TOTAL_WIDTH};
    inline constexpr int BMP_ENTITY_OFFSET_TO_DOWN_IMG {6 * BMP_ENTITY_TOTAL_WIDTH};

    // Bitmap => Ghosts
    inline constexpr int BMP_GHOST_BLINKY_START_X {3};
    inline constexpr int BMP_GHOST_BLINKY_START_Y {123};
    inline constexpr int BMP_GHOST_PINKY_START_X {3};
    inline constexpr int BMP_GHOST_PINKY_START_Y {141};
    inline constexpr int BMP_GHOST_INKY_START_X {3};
    inline constexpr int BMP_GHOST_INKY_START_Y {159};
    inline constexpr int BMP_GHOST_CLIDE_START_X {3};
    inline constexpr int BMP_GHOST_CLIDE_START_Y {177};

    // Game =>
    inline constexpr int MAP_WIDTH {BMP_MAP_WIDTH / BMP_CELL_WIDTH};
    inline constexpr int MAP_HEIGHT {BMP_MAP_HEIGHT / BMP_CELL_HEIGHT};
    inline constexpr int SCALE_BMP_TO_WINDOW {4};

    // Window => Map
    inline constexpr int WINDOW_MAP_START_X {0};
    inline constexpr int WINDOW_MAP_START_Y {0};
    inline constexpr int WINDOW_MAP_WIDTH {SCALE_BMP_TO_WINDOW * BMP_MAP_WIDTH};
    inline constexpr int WINDOW_MAP_HEIGHT {SCALE_BMP_TO_WINDOW * BMP_MAP_HEIGHT};

    // Window => Cell
    inline constexpr int WINDOW_CELL_WIDTH {SCALE_BMP_TO_WINDOW * BMP_CELL_WIDTH};
    inline constexpr int WINDOW_CELL_HEIGHT {SCALE_BMP_TO_WINDOW * BMP_CELL_HEIGHT};
}

#endif //PACMAN_CONSTANTS_H