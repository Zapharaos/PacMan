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

    // Bitmap => PowerUps
    inline constexpr int BMP_ENTITY_POWERUP_WIDTH{12};
    inline constexpr int BMP_ENTITY_POWERUP_HEIGHT{12};
    inline constexpr int BMP_ENTITY_POWERUP_TOTAL_WIDTH{ BMP_ENTITY_POWERUP_WIDTH + BMP_ENTITY_BORDER_WIDTH};
    inline constexpr int BMP_ENTITY_POWERUP_TOTAL_HEIGHT{ BMP_ENTITY_POWERUP_HEIGHT + BMP_ENTITY_BORDER_WIDTH};
    inline constexpr int BMP_ENTITY_POWERUP_OFFSET_TO_RIGHT_IMG {0};
    inline constexpr int BMP_ENTITY_POWERUP_OFFSET_TO_LEFT_IMG {2 * BMP_ENTITY_POWERUP_TOTAL_WIDTH};
    inline constexpr int BMP_ENTITY_POWERUP_OFFSET_TO_UP_IMG {BMP_ENTITY_POWERUP_OFFSET_TO_LEFT_IMG + 2 * BMP_ENTITY_POWERUP_TOTAL_WIDTH};
    inline constexpr int BMP_ENTITY_POWERUP_OFFSET_TO_DOWN_IMG{BMP_ENTITY_POWERUP_OFFSET_TO_UP_IMG + 2 * BMP_ENTITY_POWERUP_TOTAL_WIDTH};

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
    // Bottom Row
    inline constexpr int BMP_POWERUP_LONG_START_X {264};
    inline constexpr int BMP_POWERUP_SHORT_START_X {244};
    inline constexpr int BMP_POWERUP_START_Y {289};

    //Bitmap->Letters and numbers
    inline constexpr int BMP_CHARACTER_WIDTH {7};
    inline constexpr int BMP_CHARACTER_HEIGHT {7};
    inline constexpr int BMP_CHARACTER_OFFSET_TO_LEFT_IMG {2 * BMP_CHARACTER_WIDTH};
    inline constexpr int BMP_CHARACTER_OFFSET_TO_UP_IMG {BMP_CHARACTER_OFFSET_TO_LEFT_IMG + 2 * BMP_CHARACTER_WIDTH};
    inline constexpr int BMP_CHARACTER_OFFSET_TO_DOWN_IMG{BMP_CHARACTER_OFFSET_TO_UP_IMG + 2 * BMP_CHARACTER_WIDTH};

    //Bitmap -> Letter and number positions
    inline constexpr int BMP_NUMBER_START_ZERO_ROW_X {4};
    inline constexpr int BMP_NUMBER_START_FIRST_ROW_X {13};
    inline constexpr int BMP_NUMBER_START_FIRST_ROW_Y {53};
    inline constexpr int BMP_NUMBER_START_SECOND_ROW_X {12};
    inline constexpr int BMP_NUMBER_START_SECOND_ROW_Y {61};
    inline constexpr int BMP_NUMBER_START_THIRD_ROW_X {4};
    inline constexpr int BMP_NUMBER_START_THIRD_ROW_Y {69};

    //Bitmap -> points
    inline constexpr int BMP_POINTS_START_ROW_1_X {155};
    inline constexpr int BMP_POINTS_START_ROW_1_Y {176};
    inline constexpr int BMP_POINTS_START_ROW_2_X {154};
    inline constexpr int BMP_POINTS_START_ROW_2_Y {133};
    inline constexpr int BMP_POINTS_WIDTH {16};
    inline constexpr int BMP_POINTS_HEIGHT {7};


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

    //POWER Up Points
    inline constexpr int SMALL_PELLET_POINTS {10};
    inline constexpr int BIG_PELLET_POINTS {50};
    inline constexpr int GHOST_BASE_POINTS {200};

    //Powerup points per round
    inline constexpr int POWERUP_POINTS_ROUND_1 {100};
    inline constexpr int POWERUP_POINTS_ROUND_2 {300};
    inline constexpr int POWERUP_POINTS_ROUND_3 {500};
    inline constexpr int POWERUP_POINTS_ROUND_4 {500};
    inline constexpr int POWERUP_POINTS_ROUND_5 {700};
    inline constexpr int POWERUP_POINTS_ROUND_6 {700};
    inline constexpr int POWERUP_POINTS_ROUND_7 {1000};
    inline constexpr int POWERUP_POINTS_ROUND_8 {1000};
    inline constexpr int POWERUP_POINTS_ROUND_9 {2000};
    inline constexpr int POWERUP_POINTS_ROUND_10 {2000};
    inline constexpr int POWERUP_POINTS_ROUND_11 {3000};
    inline constexpr int POWERUP_POINTS_ROUND_12 {3000};
    inline constexpr int POWERUP_POINTS_ROUND_13_MORE {5000};

    //POWERUP Time in seconds
    inline constexpr int POWERUP_TIME_VERY_LONG_PLUS {6};
    inline constexpr int POWERUP_TIME_VERY_LONG {5};
    inline constexpr int POWERUP_TIME_LONG {3};
    inline constexpr int POWERUP_TIME_MEDIUM {2};
    inline constexpr int POWERUP_TIME_SHORT {1};


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