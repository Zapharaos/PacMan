//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_CONSTANTS_H
#define PACMAN_CONSTANTS_H

namespace constants
{

    // Files path
    inline const char *const PATH_FILE_PACMAN_SPRITES {"./pacman_sprites.bmp"};
    inline const char *const PATH_FILE_PACMAN_MAP {"./pacman_map.txt"};

    // Cell types
    inline constexpr int CELL_TYPE_WALL {0};
    inline constexpr int CELL_TYPE_LOW_POINTS {1};
    inline constexpr int CELL_TYPE_HIGH_POINTS {2};
    inline constexpr int CELL_TYPE_DEFAULT {3};

    // Bitmap => Map
    inline constexpr int BMP_MAP_START_X {200};
    inline constexpr int BMP_MAP_START_Y {3};
    inline constexpr int BMP_MAP_WIDTH {168};
    inline constexpr int BMP_MAP_HEIGHT {216};

    // Bitmap => Cell
    inline constexpr int BMP_CELL_WIDTH {8};
    inline constexpr int BMP_CELL_HEIGHT {8};

    // Bitmap => Entity
    inline constexpr int BMP_ENTITY_BORDER_WIDTH {1};
    inline constexpr int BMP_ENTITY_GHOST_WIDTH {16};
    inline constexpr int BMP_ENTITY_GHOST_HEIGHT {16};
    inline constexpr int BMP_ENTITY_GHOST_TOTAL_WIDTH {BMP_ENTITY_GHOST_WIDTH + BMP_ENTITY_BORDER_WIDTH};
    inline constexpr int BMP_ENTITY_GHOST_OFFSET_TO_RIGHT_IMG {0};
    inline constexpr int BMP_ENTITY_GHOST_OFFSET_TO_LEFT_IMG {2 * BMP_ENTITY_GHOST_TOTAL_WIDTH};
    inline constexpr int BMP_ENTITY_GHOST_OFFSET_TO_UP_IMG {BMP_ENTITY_GHOST_OFFSET_TO_LEFT_IMG + 2 * BMP_ENTITY_GHOST_TOTAL_WIDTH};
    inline constexpr int BMP_ENTITY_GHOST_OFFSET_TO_DOWN_IMG{BMP_ENTITY_GHOST_OFFSET_TO_UP_IMG + 2 * BMP_ENTITY_GHOST_TOTAL_WIDTH};

    // Bitmap => Entity positions
    inline constexpr int BMP_PACMAN_START_X {3};
    inline constexpr int BMP_PACMAN_START_Y {89};
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
    inline constexpr int SPEED_PACMAN {2};
    inline constexpr int SPEED_GHOST {1};

    // Window => Map
    inline constexpr int WINDOW_MAP_START_X {0};
    inline constexpr int WINDOW_MAP_START_Y {0};
    inline constexpr int WINDOW_MAP_WIDTH {SCALE_BMP_TO_WINDOW * BMP_MAP_WIDTH};
    inline constexpr int WINDOW_MAP_HEIGHT {SCALE_BMP_TO_WINDOW * BMP_MAP_HEIGHT};

    // Window => Cell
    inline constexpr int WINDOW_CELL_WIDTH {SCALE_BMP_TO_WINDOW * BMP_CELL_WIDTH};
    inline constexpr int WINDOW_CELL_HEIGHT {SCALE_BMP_TO_WINDOW * BMP_CELL_HEIGHT};

    // Ghost states
    inline constexpr int GHOST_DEFAULT {0};
    inline constexpr int GHOST_SCARED {1};
    inline constexpr int GHOST_LESSSCARED{2};
    inline constexpr int GHOST_INVISIBLE {3};


}

enum directions
{
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN = 4
};

enum powerUps
{
    CHERRY_LONG = 1,
    CHERRY_SHORT = 2,
    BERRY_LONG = 3 ,
    BERRY_SHORT = 4,
    APPLE_LONG = 5,
    APPLE_SHORT = 6,
    MELON_LONG = 7,
    MELON_SHORT = 8,
    GALBOSS_LONG = 9,
    GALBOSS_SHORT = 10,
    BELL_LONG = 11,
    BELL_SHORT = 12,
    KEY_LONG = 13,
    KEY_SHORT =14
};

#endif //PACMAN_CONSTANTS_H