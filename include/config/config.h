//
// Created by matthieu on 22/03/2023.
//

#ifndef PACMAN_CONFIG_H
#define PACMAN_CONFIG_H

#include <chrono>
#include <set>
#include <array>


enum class Score
{
    kPellet = 10,
    kEnergizer = 50,
    kGhost = 200
};

namespace config {

    namespace files {
        /** File path to the bitmap. */
        inline const char *const kBitmap {"./pacman_sprites.bmp"};

        /** File path to the map. */
        inline const char *const kMap {"./pacman_map.txt"};
    }

    namespace settings {
        /** Name of the game, displayed as the window title. */
        inline const char* const kName = {"Pacman"};

        /** Amount of frames per second, the game speed. */
        inline constexpr int kFramesPerSecond {60};

        /** DO NOT MODIFY : Duration of a tick. */
        inline constexpr std::chrono::milliseconds kTickTime {1000/kFramesPerSecond};

        /** Amount of ticks between each sprite change. */
        inline constexpr int kRefreshRateTicksPacman {3};
        inline constexpr int kRefreshRateTicksGhost {10};
        inline constexpr int kRefreshRateTicksFruit {15};
        inline constexpr int kRefreshRateTicksCharacters {15};
        inline constexpr int kRefreshRateTicksEnergizer {15};

        /** Amount of ticks for each status. */
        inline constexpr int kDurationSuperpower {kFramesPerSecond * 10};
        inline constexpr int kDurationFruit {kFramesPerSecond * 10};
        inline constexpr int kDurationEatenPelletFreeze {1};
        inline constexpr int kDurationEatenEnergizerFreeze {3};
        inline constexpr int kDurationEatenGhostFreeze {kFramesPerSecond};
        inline constexpr int kDurationLevelupFreeze {kFramesPerSecond};
        inline constexpr int kDurationLevelupBlinking {kFramesPerSecond * 4};
        inline constexpr int kDurationGameStartFreeze {kFramesPerSecond * 2};
        inline constexpr int kDurationPoints {kFramesPerSecond * 3};
        inline constexpr int kDurationDeathFreeze {kFramesPerSecond};

        inline constexpr int kGhostStatusChangesBeforeInfiniteChase {6 + 1};

        /** Amount of pixels the entities are moving (per tick). */
        inline constexpr int kSpeedPacman {3};
        inline constexpr int kSpeedGhost {2};

        /** Global game settings. */
        inline constexpr int kLives {3};
        inline constexpr int kNewLifeAtPoints {10000};

        /** After how many eaten pellets does the fruits appear (by level). */
        inline std::set<int> kFruitsPercentages {30, 70};
    }

    namespace dimensions {
        /** Map dimensions (see files:kMap). */
        inline constexpr int kMapWidth {21};
        inline constexpr int kMapHeight {27};

        /** Score Board height(top and bottom), width as same as map */
        inline constexpr int kScoreBoardHeight{75};

        /** Window cell size. */
        inline constexpr int kWindowCellSize {32};

        /** DO NOT MODIFY : Window dimensions. */
        inline constexpr int kWindowWidth {kMapWidth * kWindowCellSize};
        inline constexpr int kWindowHeight {  kScoreBoardHeight * 2 + kMapHeight * kWindowCellSize};

    }

    namespace positions {

        namespace entities {
            /** Pacman default/starting position (in pixels). */
            inline constexpr int kPacmanX {10 * dimensions::kWindowCellSize};
            inline constexpr int kPacmanY {20 * dimensions::kWindowCellSize};

            /** Fruit position (in pixels). */
            inline constexpr int kFruitX {10 * dimensions::kWindowCellSize};
            inline constexpr int kFruitY {15 * dimensions::kWindowCellSize};
            inline constexpr int kFruitPointsX{330};
            inline constexpr int kFruitPointsY{490+dimensions::kScoreBoardHeight};

            namespace blinky {
                /** Ghost default/starting (in pixels). */
                inline constexpr int kDefaultX {10 * dimensions::kWindowCellSize};
                inline constexpr int kDefaultY {10 * dimensions::kWindowCellSize};

                /** Ghost target (in pixels). */
                inline constexpr int kTargetX {dimensions::kMapWidth};
                inline constexpr int kTargetY {0};
            }

            namespace pinky {
                /** Ghost default/starting (in pixels). */
                inline constexpr int kDefaultX {10 * dimensions::kWindowCellSize};
                inline constexpr int kDefaultY {13 * dimensions::kWindowCellSize};

                /** Ghost target (in pixels). */
                inline constexpr int kTargetX {0};
                inline constexpr int kTargetY {0};
            }

            namespace inky {
                /** Ghost default/starting (in pixels). */
                inline constexpr int kDefaultX {9 * dimensions::kWindowCellSize};
                inline constexpr int kDefaultY {12 * dimensions::kWindowCellSize};

                /** Ghost target (in pixels). */
                inline constexpr int kTargetX {dimensions::kMapWidth};
                inline constexpr int kTargetY {dimensions::kMapHeight};
            }

            namespace clyde {
                /** Ghost default/starting (in pixels). */
                inline constexpr int kDefaultX {11 * dimensions::kWindowCellSize};
                inline constexpr int kDefaultY {12 * dimensions::kWindowCellSize};

                /** Ghost target (in pixels). */
                inline constexpr int kTargetX {0};
                inline constexpr int kTargetY {dimensions::kMapHeight};
            }
        }

        namespace offsets{
            inline constexpr int kGhostPointsX { 10 };
            inline constexpr int kGhostPointsY { 10 + config::dimensions::kScoreBoardHeight};
            inline constexpr int kReady{2};
            inline constexpr int kPlayerOne{2};
        }
        namespace display{
            /**Score Board Positions*/
            inline constexpr int kScoreBoardX {0};
            inline constexpr int kScoreBoardY {0};
            inline constexpr int kScoreBoardOneUpTextX {50};
            inline constexpr int kScoreBoardOneUpTextY {10};
            inline constexpr int kScoreBoardScoreX { 75};
            inline constexpr int kScoreBoardScoreY {40};
            inline constexpr int kScoreBoardHighScoreTextX {200};
            inline constexpr int kScoreBoardHighScoreTextY {10};
            inline constexpr int kScoreBoardHighScoreX {285};
            inline constexpr int kScoreBoardHighScoreY {40};
            inline constexpr int kScoreBoardLivesX {30};
            inline constexpr int kScoreBoardLivesY{ dimensions::kScoreBoardHeight  + dimensions::kMapHeight * dimensions::kWindowCellSize};
            inline constexpr int kScoreBoardFruitsX {dimensions::kWindowWidth - 30 };
            inline constexpr int kScoreBoardFruitsY {dimensions::kScoreBoardHeight  + dimensions::kMapHeight * dimensions::kWindowCellSize};

            /** Welcome Screen Positions */
            inline constexpr int kCharaterNicknameX{kScoreBoardScoreX + 20 };
            inline constexpr int kCharaterNicknameY{kScoreBoardScoreY + 50};
            inline constexpr int kGhostsX {kScoreBoardOneUpTextX + 10};
            inline constexpr int kBlinkyY {kCharaterNicknameY + 10};


            /**Game Start display positions*/
            inline constexpr int kReadyTextX {280};
            inline constexpr int kReadyTextY {562};
            inline constexpr int kPlayerOneTextX {229};
            inline constexpr int kPlayerOneTextY {400};


        }
    }
}

#endif //PACMAN_CONFIG_H
