//
// Created by matthieu on 22/03/2023.
//

#ifndef PACMAN_CONFIG_H
#define PACMAN_CONFIG_H

#include <chrono>
#include <array>

enum class Score
{
    kPellet = 10,
    kEnergizer = 50,
    kGhost = 200
};

namespace config {

    namespace files {
        inline const char *const kBitmap {"./pacman_sprites.bmp"};
        inline const char *const kMap {"./pacman_map.txt"};
    }

    namespace settings {
        inline const char* const kName = {"Pacman"};
        inline constexpr std::chrono::milliseconds kTickTime {1000/60}; // 60 FPS

        inline constexpr int kRefreshRateTicksMovingEntity {3};
        inline constexpr int kRefreshRateTicksFruit {15};
        inline constexpr int kRefreshRateTicksEnergizer {15};

        inline constexpr int kDurationSuperpower {5000};
        inline constexpr int kDurationFruit {9500};
        inline constexpr int kDurationEatenPelletFreeze {1};
        inline constexpr int kDurationEatenGhostFreeze {60};
        inline constexpr int kDurationLevelupFreeze {60};
        inline constexpr int kDurationLevelupBlinking {60 * 4};
        inline constexpr int kDurationDeathFreeze {60};

        inline constexpr int kSpeedPacman {3};
        inline constexpr int kSpeedGhost {1};

        inline constexpr int kLives {3};
        inline constexpr int kNewLifeAtPoints {10000};

        inline constexpr int kFruitsPerLevel {2};
        inline constexpr int kFruitsMaximumPerAnimation {2};
        inline constexpr int kLevelsMaximumPerFruit {2};
        inline constexpr std::array<int, kFruitsPerLevel> kFruitsPercentages {30, 70};
    }

    namespace dimensions {
        inline constexpr int kMapWidth {21};
        inline constexpr int kMapHeight {27};
        inline constexpr int kWindowCellSize {32};
        inline constexpr int kWindowWidth {kMapWidth * kWindowCellSize};
        inline constexpr int kWindowHeight {kMapHeight * kWindowCellSize};
    }

    namespace positions {
        inline constexpr int kPacmanX {10 * dimensions::kWindowCellSize};
        inline constexpr int kPacmanY {20 * dimensions::kWindowCellSize};
        inline constexpr int kFruitX {10 * dimensions::kWindowCellSize};
        inline constexpr int kFruitY {15 * dimensions::kWindowCellSize};
    }

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
    inline constexpr int BMP_POINTS_START_ROW_1_X {155};
    inline constexpr int BMP_POINTS_START_ROW_1_Y {176};
    inline constexpr int BMP_POINTS_START_ROW_2_X {154};
    inline constexpr int BMP_POINTS_START_ROW_2_Y {133};
    inline constexpr int BMP_POINTS_WIDTH {16};
    inline constexpr int BMP_POINTS_HEIGHT {7};

    //Score Board
    inline constexpr int SCORE_BOARD_WIDTH {300};
    inline constexpr int SCORE_BOARD_START_X {config::dimensions::kWindowWidth +  10 };
    inline constexpr int SCORE_BOARD_START_Y { 10 };
    inline constexpr int SCORE_BOARD_POINTS_START_X {config::dimensions::kWindowWidth  +  160 };
    inline constexpr int SCORE_BOARD_POINTS_START_Y {40};

    //OFFSET FOR Extractor
    inline constexpr int OFFSET_MAP {1};
    inline constexpr int OFFSET_CHAR {1};

}

#endif //PACMAN_CONFIG_H
