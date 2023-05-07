//
// Created by matthieu on 22/03/2023.
//

#ifndef PACMAN_CONFIG_H
#define PACMAN_CONFIG_H

#include "../map/position.h"

#include <chrono>
#include <set>
#include <array>

enum class Score {
    kPellet = 10,
    kEnergizer = 50,
    kGhost = 200
};

namespace config {

    namespace files {
        /** File path to the bitmap. */
        inline const char *const kBitmap{"./pacman_sprites.bmp"};

        /** File path to the map. */
        inline const char *const kMap{"./pacman_map.txt"};
    }

    namespace settings {
        /** Name of the game, displayed as the window title. */
        inline const char *const kName = {"Pacman"};

        /** Amount of frames per second, the game speed. */
        inline constexpr int kFramesPerSecond{60};

        /** DO NOT MODIFY : Duration of a tick. */
        inline constexpr std::chrono::milliseconds kTickTime{1000 / kFramesPerSecond};

        /** Amount of ticks between each sprite change. */
        inline constexpr int kRefreshRateTicksPacman{3};
        inline constexpr int kRefreshRateTicksGhost{10};
        inline constexpr int kRefreshRateTicksFruit{15};
        inline constexpr int kRefreshRateTicksCharacters{15};
        inline constexpr int kRefreshRateTicksEnergizer{15};

        /** Amount of ticks for each game status. */
        inline constexpr int kDurationSuperpower{kFramesPerSecond * 10};
        inline constexpr int kDurationFruit{kFramesPerSecond * 10};
        inline constexpr int kDurationEatenPelletFreeze{1};
        inline constexpr int kDurationEatenEnergizerFreeze{3};
        inline constexpr int kDurationEatenGhostFreeze{kFramesPerSecond};
        inline constexpr int kDurationLevelupFreeze{kFramesPerSecond};
        inline constexpr int kDurationLevelupBlinking{kFramesPerSecond * 4};
        inline constexpr int kDurationGameStartFreeze{kFramesPerSecond * 2};
        inline constexpr int kDurationPoints{kFramesPerSecond * 3};
        inline constexpr int kDurationDeathFreeze{kFramesPerSecond};
        inline constexpr int kDurationDeathAnimation{kFramesPerSecond * 2};
        inline constexpr int kDurationTextDeathFreeze{kFramesPerSecond * 3};
        inline constexpr int kWelcomeScreen{kFramesPerSecond * 20};

        /** Amount of ticks for each ghost status. */
        inline constexpr int kDurationGhostFrightened{kDurationSuperpower / 2};
        inline constexpr std::array<int, 7> kDurationGhostStatuses{
                7 * kFramesPerSecond, // Scatter
                20 * kFramesPerSecond, // Chase
                7 * kFramesPerSecond, // Scatter
                20 * kFramesPerSecond, // Chase
                5 * kFramesPerSecond, // Scatter
                20 * kFramesPerSecond, // Chase
                5 * kFramesPerSecond // Scatter, then infinite chase
        };

        /** Amount of pixels the entities are moving (per tick). */
        inline constexpr int kSpeedPacman{3};
        inline constexpr int kSpeedGhost{2};
        inline constexpr int kSpeedUpRatio{3};
        inline constexpr int kSpeedDownRatio{2};

        /** Global game settings. */
        inline constexpr int kLives{3};
        inline constexpr int kNewLifeAtPoints{10000};

        /** After how many eaten pellets does the fruits appear (by level). */
        inline std::set<int> kFruitsPercentages{30, 70};

        /** Ghosts chase target settings. */
        inline constexpr int kPinkyOffsetToPacman{4};
        inline constexpr int kInkyOffsetToPacman{2};
        inline constexpr int kClydeDistanceFromPacman{8};

        inline constexpr unsigned long kGhostMaxTickWithoutEatenPellet{4 * kFramesPerSecond};

        /** Ghosts pellet counting limits after pacman death. */
        inline constexpr int kGhostRestartPelletLimitPinky{7};
        inline constexpr int kGhostRestartPelletLimitInky{17};
        inline constexpr int kGhostRestartPelletLimitClyde{32};
        inline constexpr int kGhostRestartPelletLimitMax{kGhostRestartPelletLimitClyde + 1};
    }

    namespace dimensions {
        /** Map dimensions (see files:kMap). */
        inline constexpr int kMapWidth{21};
        inline constexpr int kMapHeight{27};

        /** Score Board height(top and bottom), width as same as map */
        inline constexpr int kScoreBoardHeight{75};

        /** Window cell size. */
        inline constexpr int kWindowCellSize{32};

        /** DO NOT MODIFY : Window dimensions. */
        inline constexpr int kWindowWidth{kMapWidth * kWindowCellSize};
        inline constexpr int kWindowHeight{kScoreBoardHeight * 2 + kMapHeight * kWindowCellSize};

        // Width and height of a moving entity.
        inline constexpr int kMovingEntitySize{32};

    }

    namespace positions {

        inline static const int kGhostHouseEntryX{10};
        inline static const int kGhostHouseEntryY{10};
        inline static const Position kGhostHouseEntry{kGhostHouseEntryX, kGhostHouseEntryY};

        namespace entities {
            /** Pacman default/starting position (in pixels). */
            inline constexpr int kPacmanX{10 * dimensions::kWindowCellSize};
            inline constexpr int kPacmanY{20 * dimensions::kWindowCellSize};

            /** Fruit position (in pixels). */
            inline constexpr int kFruitX{10 * dimensions::kWindowCellSize};
            inline constexpr int kFruitY{15 * dimensions::kWindowCellSize};
            inline constexpr int kFruitPointsX{330};
            inline constexpr int kFruitPointsY{490 + dimensions::kScoreBoardHeight};

            namespace blinky {
                /** Ghost default/starting (in pixels). */
                inline constexpr int kDefaultX{10 * dimensions::kWindowCellSize};
                inline constexpr int kDefaultY{10 * dimensions::kWindowCellSize};

                /** Ghost scatter target. */
                inline constexpr int kTargetX{dimensions::kMapWidth};
                inline constexpr int kTargetY{0};

                /** Ghost dead target. */
                inline constexpr int kHouseX{10};
                inline constexpr int kHouseY{13};


            }

            namespace pinky {
                /** Ghost default/starting (in pixels). */
                inline constexpr int kDefaultX{10 * dimensions::kWindowCellSize};
                inline constexpr int kDefaultY{13 * dimensions::kWindowCellSize};

                /** Ghost scatter target. */
                inline constexpr int kTargetX{0};
                inline constexpr int kTargetY{0};

                /** Ghost dead target. */
                inline constexpr int kHouseX{10};
                inline constexpr int kHouseY{13};


            }

            namespace inky {
                /** Ghost default/starting (in pixels). */
                inline constexpr int kDefaultX{9 * dimensions::kWindowCellSize};
                inline constexpr int kDefaultY{12 * dimensions::kWindowCellSize};

                /** Ghost scatter target. */
                inline constexpr int kTargetX{dimensions::kMapWidth};
                inline constexpr int kTargetY{dimensions::kMapHeight};

                /** Ghost dead target. */
                inline constexpr int kHouseX{9};
                inline constexpr int kHouseY{12};


            }

            namespace clyde {
                /** Ghost default/starting (in pixels). */
                inline constexpr int kDefaultX{11 * dimensions::kWindowCellSize};
                inline constexpr int kDefaultY{12 * dimensions::kWindowCellSize};

                /** Ghost scatter target. */
                inline constexpr int kTargetX{0};
                inline constexpr int kTargetY{dimensions::kMapHeight};

                /** Ghost dead target. */
                inline constexpr int kHouseX{11};
                inline constexpr int kHouseY{12};


            }
        }


    }
}

#endif //PACMAN_CONFIG_H
