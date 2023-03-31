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

    // Bitmap => Map
    inline constexpr int BMP_MAP_START_X {369};
    inline constexpr int BMP_MAP_START_Y {3};
    inline constexpr int BMP_MAP_WIDTH {168};
    inline constexpr int BMP_MAP_HEIGHT {216};

    // Bitmap => Cell
    inline constexpr int BMP_CELL_WIDTH {8};
    inline constexpr int BMP_CELL_HEIGHT {8};

    // Bitmap => Entity
    inline constexpr int BMP_ENTITY_BORDER_WIDTH {1};
    inline constexpr int BMP_ENTITY_GHOST_WIDTH {14};
    inline constexpr int BMP_ENTITY_GHOST_HEIGHT {14};
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
    inline constexpr int BMP_PACMAN_START_X {4};
    inline constexpr int BMP_PACMAN_START_Y {90};
    inline constexpr int BMP_POINT_START_X {4};
    inline constexpr int BMP_POINT_START_Y {81};
    inline constexpr int BMP_POINT_SIZE {2};
    inline constexpr int BMP_POWER_START_X {9};
    inline constexpr int BMP_POWER_START_Y {79};
    inline constexpr int BMP_POWER_SIZE {7};
    inline constexpr int BMP_GHOST_BLINKY_START_X {4};
    inline constexpr int BMP_GHOST_BLINKY_START_Y {124};
    inline constexpr int BMP_GHOST_PINKY_START_X {4};
    inline constexpr int BMP_GHOST_PINKY_START_Y {142};
    inline constexpr int BMP_GHOST_INKY_START_X {4};
    inline constexpr int BMP_GHOST_INKY_START_Y {160};
    inline constexpr int BMP_GHOST_CLYDE_START_X {4};
    inline constexpr int BMP_GHOST_CLYDE_START_Y {178};
    inline constexpr int BMP_PACMAN_BIG_POS_TWO_START_X {38};
    inline constexpr int BMP_PACMAN_BIG_START_Y {219};
    inline constexpr int BMP_PACMAN_BIG_HEIGHT {30};
    inline constexpr int BMP_PACMAN_BIG_WIDTH {28};
    inline constexpr int BMP_PACMAN_SCORE_BOARD_START_X{169};//
    inline constexpr int BMP_PACMAN_SCORE_BOARD_START_Y {76};//
    inline constexpr int BMP_PACMAN_SCORE_BOARD_WIDTH {10};//
    inline constexpr int BMP_PACMAN_SCORE_BOARD_HEIGHT {12};//

    // Bottom Row
    inline constexpr int BMP_POWERUP_LONG_START_X {264};
    inline constexpr int BMP_POWERUP_SHORT_START_X {244};
    inline constexpr int BMP_POWERUP_START_Y {289};

    // Bitmap => Letters and numbers
    inline constexpr int BMP_CHARACTER_WIDTH {7};
    inline constexpr int BMP_CHARACTER_HEIGHT {7};
    inline constexpr int BMP_CHARACTER_OFFSET_TO_LEFT_IMG {2 * BMP_CHARACTER_WIDTH};
    inline constexpr int BMP_CHARACTER_OFFSET_TO_UP_IMG {BMP_CHARACTER_OFFSET_TO_LEFT_IMG + 2 * BMP_CHARACTER_WIDTH};
    inline constexpr int BMP_CHARACTER_OFFSET_TO_DOWN_IMG{BMP_CHARACTER_OFFSET_TO_UP_IMG + 2 * BMP_CHARACTER_WIDTH};

    // Bitmap => Letter and number positions
    inline constexpr int BMP_NUMBER_START_ZERO_ROW_X {4};
    inline constexpr int BMP_NUMBER_START_FIRST_ROW_X {12};
    inline constexpr int BMP_NUMBER_START_FIRST_ROW_Y {53};
    inline constexpr int BMP_NUMBER_START_SECOND_ROW_X {12};
    inline constexpr int BMP_NUMBER_START_SECOND_ROW_Y {61};
    inline constexpr int BMP_NUMBER_START_THIRD_ROW_X {4};
    inline constexpr int BMP_NUMBER_START_THIRD_ROW_Y {69};

    // Bitmap => points
    //200 to 800
    inline constexpr int BMP_POINTS_START_ROW_1_X {155};
    inline constexpr int BMP_POINTS_START_ROW_1_Y {176};

    //100 to 700
    inline constexpr int BMP_POINTS_START_ROW_2_X {179};
    inline constexpr int BMP_POINTS_START_ROW_2_Y {133};

    inline constexpr int BMP_POINTS_WIDTH {16};
    inline constexpr int BMP_POINTS_HEIGHT {7};
    inline constexpr int BMP_POINTS_WIDTH_THREE_CHARS {14};
    inline constexpr int BMP_POINTS_WIDTH_FOUR_CHARS {15};
    //1600
    inline constexpr int BMP_POINTS_START_ROW_1_2_X {154};
    inline constexpr int BMP_POINTS_START_ROW_1_2_Y {203};
    //Offset between sprites
    inline constexpr int BMP_POINTS_OFFSET {2};
    // Offset for scaling
    inline constexpr int BMP_POINTS_SCALING_OFFSET {2*1};
    //1000 to 3000
    inline constexpr int BMP_POINTS_START_ROW_2_2_X {177};
    inline constexpr int BMP_POINTS_START_ROW_2_2_Y {169};

    // Game =>
    inline constexpr int MAP_WIDTH {BMP_MAP_WIDTH / BMP_CELL_WIDTH};
    inline constexpr int MAP_HEIGHT {BMP_MAP_HEIGHT / BMP_CELL_HEIGHT};
    inline constexpr int SCALE_BMP_TO_WINDOW {4};
    inline constexpr int LIVES {3};
    inline constexpr int NEW_UP_POINTS_CAP {10000};


    // Entities
    inline constexpr int PACMAN_SPEED {3};
    inline constexpr int GHOST_SPEED {1};
    inline constexpr int ENTITY_REFRESH_RATE {3};

    // Window => Map
    inline constexpr int WINDOW_MAP_START_X {0};
    inline constexpr int WINDOW_MAP_START_Y {0};
    inline constexpr int WINDOW_MAP_WIDTH {SCALE_BMP_TO_WINDOW * BMP_MAP_WIDTH};
    inline constexpr int WINDOW_MAP_HEIGHT {SCALE_BMP_TO_WINDOW * BMP_MAP_HEIGHT};


    //Score Board
    inline constexpr int SCORE_BOARD_WIDTH {300};
    inline constexpr int SCORE_BOARD_START_X {WINDOW_MAP_WIDTH  +  10 };
    inline constexpr int SCORE_BOARD_START_Y { 10 };
    inline constexpr int SCORE_BOARD_POINTS_START_X {WINDOW_MAP_WIDTH  +  160 };
    inline constexpr int SCORE_BOARD_POINTS_START_Y {40};
    inline constexpr int SCORE_BOARD_LIVES_START_X {SCORE_BOARD_START_X + 150 };
    inline constexpr int SCORE_BOARD_LIVES_START_Y {SCORE_BOARD_START_Y + 400};



    // Window => Cell
    inline constexpr int WINDOW_CELL_WIDTH {SCALE_BMP_TO_WINDOW * BMP_CELL_WIDTH};
    inline constexpr int WINDOW_CELL_HEIGHT {SCALE_BMP_TO_WINDOW * BMP_CELL_HEIGHT};


    // Window => Pacman
    inline constexpr int WINDOW_PACMAN_X {10 * WINDOW_CELL_WIDTH};
    inline constexpr int WINDOW_PACMAN_Y {20 * WINDOW_CELL_HEIGHT};

    // Window => Points
    inline constexpr int WINDOW_POINTS_OFFSET {3 * SCALE_BMP_TO_WINDOW};
    inline constexpr int WINDOW_POINTS_SIZE {2 * SCALE_BMP_TO_WINDOW};

    // Window => Power
    inline constexpr int WINDOW_POWER_OFFSET {0 * SCALE_BMP_TO_WINDOW};
    inline constexpr int WINDOW_POWER_SIZE {7 * SCALE_BMP_TO_WINDOW};

    // Ghost states
    inline constexpr int GHOST_DEFAULT {0};
    inline constexpr int GHOST_SCARED {1};
    inline constexpr int GHOST_LESSSCARED{2};
    inline constexpr int GHOST_INVISIBLE {3};

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

    //OFFSET FOR Extractor
    inline constexpr int OFFSET_MAP {1};
    inline constexpr int OFFSET_CHAR {1};


}

#endif //PACMAN_CONSTANTS_H