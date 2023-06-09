//
// Created by mfrei on 23/03/2023.
//

#ifndef PACMAN_VISUALS_H
#define PACMAN_VISUALS_H

#include "config.h"

#include "../display/sprite.h"
#include "../display/animation.h"
#include "../entity/fruitObject.h"

inline constexpr int getScale(int window, int bitmap) { return window / bitmap; };

namespace visuals {

    /** Width and height of a bitmap cell (in pixels). */
    inline constexpr int kBitmapCellSize{8};

    /** DO NOT MODIFY : Scale from bitmap to window. */
    inline constexpr auto kScaleCell{getScale(config::dimensions::kWindowCellSize, kBitmapCellSize)};

    namespace pellet {
        /** Sprite dimensions (in pixels). */
        inline constexpr int kBitmapWidth{2};
        inline constexpr int kBitmapHeight{2};

        /** Sprite positions (in pixels). */
        inline constexpr int kBitmapPositionX{4};
        inline constexpr int kBitmapPositionY{81};

        /** Sprite offset when displayed (in pixels). */
        inline constexpr int kBitmapOffsetX{3};
        inline constexpr int kBitmapOffsetY{3};

        /** DO NOT MODIFY : Pellet Sprite. */
        inline constexpr Sprite kSprite{{kBitmapPositionX,            kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                        {kBitmapOffsetX * kScaleCell, kBitmapOffsetY * kScaleCell},
                                        {kBitmapWidth * kScaleCell,   kBitmapHeight * kScaleCell}};
    }

    namespace energizer {
        /** Sprite dimensions (in pixels). */
        inline constexpr int kBitmapWidth{7};
        inline constexpr int kBitmapHeight{7};

        /** Sprite positions (in pixels). */
        inline constexpr int kBitmapPositionX{9};
        inline constexpr int kBitmapPositionY{79};

        /** Sprite offset when displayed (in pixels). */
        inline constexpr int kBitmapOffsetX{0};
        inline constexpr int kBitmapOffsetY{0};

        /** DO NOT MODIFY : Energizer Sprite. */
        inline constexpr Sprite kSprite{{kBitmapPositionX,            kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                        {kBitmapOffsetX * kScaleCell, kBitmapOffsetY * kScaleCell},
                                        {kBitmapWidth * kScaleCell,   kBitmapHeight * kScaleCell}};
    }

    namespace map {

        namespace sprite_default {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{168};
            inline constexpr int kBitmapHeight{216};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{369};
            inline constexpr int kBitmapPositionY{3};

            /** Sprite offset when displayed (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Default Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,            kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScaleCell, kBitmapOffsetY * kScaleCell},
                                            {kBitmapWidth * kScaleCell,   kBitmapHeight * kScaleCell}};
        }

        namespace sprite_blinking {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{168};
            inline constexpr int kBitmapHeight{216};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{540};
            inline constexpr int kBitmapPositionY{3};

            /** Sprite offset when displayed (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,            kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScaleCell, kBitmapOffsetY * kScaleCell},
                                            {kBitmapWidth * kScaleCell,   kBitmapHeight * kScaleCell}};
        }

        /** The amount of sprites inside the animation. */
        inline constexpr int kAnimationSize{2};

        /** The amount of times the animation is repeated. */
        inline constexpr int kAnimationRepeat{4};

        /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
        inline constexpr bool kAnimationReverse{false};

        /** DO NOT MODIFY : Amount of frames for which the current sprite is shown. */
        inline constexpr int kAnimationFrames{
                config::settings::kDurationLevelupBlinking / kAnimationRepeat / kAnimationSize};

        /** DO NOT MODIFY : Map level up blinking animation. */
        inline Animation kAnimation{{sprite_default::kSprite, sprite_blinking::kSprite}, kAnimationReverse,
                                    kAnimationFrames};
    }

    namespace pacman {

        /** Amount of frames for which the current sprite is shown. */
        inline constexpr int kAnimationRefreshRate{config::settings::kRefreshRateTicksPacman};

        /** Width and height of a bitmap pacman (in pixels). */
        inline constexpr int kBitmapSize{16};

        /** DO NOT MODIFY : Scale from bitmap to window. */
        inline constexpr auto kScale{getScale(config::dimensions::kWindowCellSize, kBitmapSize)};

        namespace sprite_default {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{14};
            inline constexpr int kBitmapHeight{14};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{4};
            inline constexpr int kBitmapPositionY{90};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{1};
            inline constexpr int kBitmapOffsetY{1};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
        }

        namespace sprite_score_board {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{10};
            inline constexpr int kBitmapHeight{12};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{169};
            inline constexpr int kBitmapPositionY{76};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{1};
            inline constexpr int kBitmapOffsetY{1};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {kBitmapWidth * kScale,   kBitmapHeight * kScale}};

            /** DO NOT MODIFY : Scale from bitmap to window. */
            inline constexpr auto kScale{2.5};
        }

        namespace left {

            namespace sprite_1 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{13};
                inline constexpr int kBitmapHeight{14};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{48};
                inline constexpr int kBitmapPositionY{90};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{2};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{9};
                inline constexpr int kBitmapHeight{14};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{64};
                inline constexpr int kBitmapPositionY{90};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{7};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{true};

            /** DO NOT MODIFY : Pacman left animation. */
            inline Animation kAnimation{{sprite_default::kSprite, sprite_1::kSprite, sprite_2::kSprite},
                                        kAnimationReverse, kAnimationRefreshRate};
        }

        namespace right {

            namespace sprite_1 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{13};
                inline constexpr int kBitmapHeight{14};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{21};
                inline constexpr int kBitmapPositionY{90};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{9};
                inline constexpr int kBitmapHeight{14};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{36};
                inline constexpr int kBitmapPositionY{90};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{true};

            /** DO NOT MODIFY : Pacman right animation. */
            inline Animation kAnimation{{sprite_default::kSprite, sprite_1::kSprite, sprite_2::kSprite},
                                        kAnimationReverse, kAnimationRefreshRate};
        }

        namespace up {

            namespace sprite_1 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{14};
                inline constexpr int kBitmapHeight{13};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{76};
                inline constexpr int kBitmapPositionY{91};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{2};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{14};
                inline constexpr int kBitmapHeight{9};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{93};
                inline constexpr int kBitmapPositionY{95};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{7};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{true};

            /** DO NOT MODIFY : Pacman up animation. */
            inline Animation kAnimation{{sprite_default::kSprite, sprite_1::kSprite, sprite_2::kSprite},
                                        kAnimationReverse, kAnimationRefreshRate};
        }

        namespace down {

            namespace sprite_1 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{14};
                inline constexpr int kBitmapHeight{13};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{110};
                inline constexpr int kBitmapPositionY{91};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{14};
                inline constexpr int kBitmapHeight{9};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{127};
                inline constexpr int kBitmapPositionY{95};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{true};

            /** DO NOT MODIFY : Pacman down animation. */
            inline Animation kAnimation{{sprite_default::kSprite, sprite_1::kSprite, sprite_2::kSprite},
                                        kAnimationReverse, kAnimationRefreshRate};
        }

        namespace death {

            namespace sprite_1 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{16};
                inline constexpr int kBitmapHeight{8};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{4};
                inline constexpr int kBitmapPositionY{111};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{0};
                inline constexpr int kBitmapOffsetY{0};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{16};
                inline constexpr int kBitmapHeight{6};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{23};
                inline constexpr int kBitmapPositionY{113};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{0};
                inline constexpr int kBitmapOffsetY{2};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_3 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{16};
                inline constexpr int kBitmapHeight{5};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{42};
                inline constexpr int kBitmapPositionY{114};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{0};
                inline constexpr int kBitmapOffsetY{3};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_4 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{16};
                inline constexpr int kBitmapHeight{5};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{61};
                inline constexpr int kBitmapPositionY{114};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{0};
                inline constexpr int kBitmapOffsetY{4};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_5 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{16};
                inline constexpr int kBitmapHeight{6};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{80};
                inline constexpr int kBitmapPositionY{113};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{0};
                inline constexpr int kBitmapOffsetY{4};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_6 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{14};
                inline constexpr int kBitmapHeight{6};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{99};
                inline constexpr int kBitmapPositionY{112};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{4};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_7 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{10};
                inline constexpr int kBitmapHeight{7};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{116};
                inline constexpr int kBitmapPositionY{112};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{3};
                inline constexpr int kBitmapOffsetY{4};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_8 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{6};
                inline constexpr int kBitmapHeight{7};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{129};
                inline constexpr int kBitmapPositionY{112};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{5};
                inline constexpr int kBitmapOffsetY{4};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_9 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{2};
                inline constexpr int kBitmapHeight{7};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{138};
                inline constexpr int kBitmapPositionY{112};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{7};
                inline constexpr int kBitmapOffsetY{4};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_10 {

                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{11};
                inline constexpr int kBitmapHeight{10};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{143};
                inline constexpr int kBitmapPositionY{109};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{3};
                inline constexpr int kBitmapOffsetY{3};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            /** The amount of sprites inside the animation. */
            inline constexpr int kAnimationSize{10};

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{false};

            /** DO NOT MODIFY : Amount of frames for which the current sprite is shown. */
            inline constexpr int kAnimationFrames{config::settings::kDurationDeathAnimation / kAnimationSize};

            /** DO NOT MODIFY : Pacman death animation. */
            inline Animation kAnimation{
                    {sprite_1::kSprite, sprite_2::kSprite, sprite_3::kSprite, sprite_4::kSprite, sprite_5::kSprite,
                     sprite_6::kSprite, sprite_7::kSprite, sprite_8::kSprite, sprite_9::kSprite, sprite_10::kSprite},
                    kAnimationReverse, kAnimationFrames};
        }

    }

    namespace fruit {

        /** Amount of frames for which the current sprite is shown. */
        inline constexpr int kAnimationRefreshRate{config::settings::kRefreshRateTicksFruit};

        /** Width and height of a bitmap pacman (in pixels). */
        inline constexpr int kBitmapSize{16};

        /** DO NOT MODIFY : Scale from bitmap to window. */
        inline constexpr auto kScale{getScale(config::dimensions::kWindowCellSize, kBitmapSize)};

        namespace cherry {

            namespace sprite_1 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{12};
                inline constexpr int kBitmapHeight{12};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{290};
                inline constexpr int kBitmapPositionY{238};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{2};
                inline constexpr int kBitmapOffsetY{2};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{12};
                inline constexpr int kBitmapHeight{12};

                /** Size up (in pixels). */
                inline constexpr int kSizeupX{2};
                inline constexpr int kSizeupY{2};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{290};
                inline constexpr int kBitmapPositionY{258};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,                   kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale,            kBitmapOffsetY * kScale},
                                                {(kBitmapWidth + kSizeupX) * kScale, (kBitmapHeight + kSizeupY) *
                                                                                     kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{false};

            /** Points earned when the fruit gets eaten. */
            inline constexpr int kPoints{100};

            /** Levels at which the fruit appears. */
            inline std::set<int> kLevels{1};

            /** DO NOT MODIFY : Cherry animation. */
            inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                        kAnimationRefreshRate};

            /** DO NOT MODIFY : Cherry object. */
            inline FruitObject kFruit{kPoints, kLevels, kAnimation};
        }

        namespace strawberry {

            namespace sprite_1 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{11};
                inline constexpr int kBitmapHeight{12};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{307};
                inline constexpr int kBitmapPositionY{238};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{2};
                inline constexpr int kBitmapOffsetY{2};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{11};
                inline constexpr int kBitmapHeight{12};

                /** Size up (in pixels). */
                inline constexpr int kSizeupX{2};
                inline constexpr int kSizeupY{2};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{307};
                inline constexpr int kBitmapPositionY{258};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,                   kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale,            kBitmapOffsetY * kScale},
                                                {(kBitmapWidth + kSizeupX) * kScale, (kBitmapHeight + kSizeupY) *
                                                                                     kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{false};

            /** Points earned when the fruit gets eaten. */
            inline constexpr int kPoints{300};

            /** Levels at which the fruit appears. */
            inline std::set<int> kLevels{2};

            /** DO NOT MODIFY : Cherry animation. */
            inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                        kAnimationRefreshRate};

            /** DO NOT MODIFY : Cherry object. */
            inline FruitObject kFruit{kPoints, kLevels, kAnimation};
        }

        namespace orange {

            namespace sprite_1 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{12};
                inline constexpr int kBitmapHeight{12};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{322};
                inline constexpr int kBitmapPositionY{238};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{2};
                inline constexpr int kBitmapOffsetY{2};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{12};
                inline constexpr int kBitmapHeight{12};

                /** Size up (in pixels). */
                inline constexpr int kSizeupX{1};
                inline constexpr int kSizeupY{2};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{322};
                inline constexpr int kBitmapPositionY{258};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,                   kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale,            kBitmapOffsetY * kScale},
                                                {(kBitmapWidth + kSizeupX) * kScale, (kBitmapHeight + kSizeupY) *
                                                                                     kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{false};

            /** Points earned when the fruit gets eaten. */
            inline constexpr int kPoints{500};

            /** Levels at which the fruit appears. */
            inline std::set<int> kLevels{3, 4};

            /** DO NOT MODIFY : Cherry animation. */
            inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                        kAnimationRefreshRate};

            /** DO NOT MODIFY : Cherry object. */
            inline FruitObject kFruit{kPoints, kLevels, kAnimation};
        }

        namespace apple {

            namespace sprite_1 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{12};
                inline constexpr int kBitmapHeight{12};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{338};
                inline constexpr int kBitmapPositionY{238};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{2};
                inline constexpr int kBitmapOffsetY{2};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{12};
                inline constexpr int kBitmapHeight{12};

                /** Size up (in pixels). */
                inline constexpr int kSizeupX{1};
                inline constexpr int kSizeupY{2};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{338};
                inline constexpr int kBitmapPositionY{258};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,                   kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale,            kBitmapOffsetY * kScale},
                                                {(kBitmapWidth + kSizeupX) * kScale, (kBitmapHeight + kSizeupY) *
                                                                                     kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{false};

            /** Points earned when the fruit gets eaten. */
            inline constexpr int kPoints{700};

            /** Levels at which the fruit appears. */
            inline std::set<int> kLevels{5, 6};

            /** DO NOT MODIFY : Cherry animation. */
            inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                        kAnimationRefreshRate};

            /** DO NOT MODIFY : Cherry object. */
            inline FruitObject kFruit{kPoints, kLevels, kAnimation};
        }

        namespace melon {

            namespace sprite_1 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{11};
                inline constexpr int kBitmapHeight{14};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{355};
                inline constexpr int kBitmapPositionY{236};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{2};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{11};
                inline constexpr int kBitmapHeight{14};

                /** Size up (in pixels). */
                inline constexpr int kSizeupX{2};
                inline constexpr int kSizeupY{1};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{355};
                inline constexpr int kBitmapPositionY{256};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{0};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,                   kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale,            kBitmapOffsetY * kScale},
                                                {(kBitmapWidth + kSizeupX) * kScale, (kBitmapHeight + kSizeupY) *
                                                                                     kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{false};

            /** Points earned when the fruit gets eaten. */
            inline constexpr int kPoints{1000};

            /** Levels at which the fruit appears. */
            inline std::set<int> kLevels{7, 8};

            /** DO NOT MODIFY : Cherry animation. */
            inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                        kAnimationRefreshRate};

            /** DO NOT MODIFY : Cherry object. */
            inline FruitObject kFruit{kPoints, kLevels, kAnimation};
        }

        namespace flagship {

            namespace sprite_1 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{11};
                inline constexpr int kBitmapHeight{11};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{371};
                inline constexpr int kBitmapPositionY{239};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{2};
                inline constexpr int kBitmapOffsetY{2};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{11};
                inline constexpr int kBitmapHeight{11};

                /** Size up (in pixels). */
                inline constexpr int kSizeupX{2};
                inline constexpr int kSizeupY{2};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{371};
                inline constexpr int kBitmapPositionY{259};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,                   kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale,            kBitmapOffsetY * kScale},
                                                {(kBitmapWidth + kSizeupX) * kScale, (kBitmapHeight + kSizeupY) *
                                                                                     kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{false};

            /** Points earned when the fruit gets eaten. */
            inline constexpr int kPoints{2000};

            /** Levels at which the fruit appears. */
            inline std::set<int> kLevels{9, 10};

            /** DO NOT MODIFY : Cherry animation. */
            inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                        kAnimationRefreshRate};

            /** DO NOT MODIFY : Cherry object. */
            inline FruitObject kFruit{kPoints, kLevels, kAnimation};
        }

        namespace bell {

            namespace sprite_1 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{12};
                inline constexpr int kBitmapHeight{13};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{387};
                inline constexpr int kBitmapPositionY{237};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{2};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{12};
                inline constexpr int kBitmapHeight{13};

                /** Size up (in pixels). */
                inline constexpr int kSizeupX{2};
                inline constexpr int kSizeupY{2};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{387};
                inline constexpr int kBitmapPositionY{257};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{0};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,                   kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale,            kBitmapOffsetY * kScale},
                                                {(kBitmapWidth + kSizeupX) * kScale, (kBitmapHeight + kSizeupY) *
                                                                                     kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{false};

            /** Points earned when the fruit gets eaten. */
            inline constexpr int kPoints{3000};

            /** Levels at which the fruit appears. */
            inline std::set<int> kLevels{11, 12};

            /** DO NOT MODIFY : Cherry animation. */
            inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                        kAnimationRefreshRate};

            /** DO NOT MODIFY : Cherry object. */
            inline FruitObject kFruit{kPoints, kLevels, kAnimation};
        }

        namespace key {

            namespace sprite_1 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{7};
                inline constexpr int kBitmapHeight{13};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{405};
                inline constexpr int kBitmapPositionY{237};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{4};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{7};
                inline constexpr int kBitmapHeight{13};

                /** Size up (in pixels). */
                inline constexpr int kSizeupX{2};
                inline constexpr int kSizeupY{2};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{405};
                inline constexpr int kBitmapPositionY{257};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{3};
                inline constexpr int kBitmapOffsetY{0};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,                   kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale,            kBitmapOffsetY * kScale},
                                                {(kBitmapWidth + kSizeupX) * kScale, (kBitmapHeight + kSizeupY) *
                                                                                     kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{false};

            /** Points earned when the fruit gets eaten. */
            inline constexpr int kPoints{5000};

            /** Levels at which the fruit appears. */
            inline std::set<int> kLevels{13};

            /** DO NOT MODIFY : Cherry animation. */
            inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                        kAnimationRefreshRate};

            /** DO NOT MODIFY : Cherry object. */
            inline FruitObject kFruit{kPoints, kLevels, kAnimation};
        }

        inline std::vector<FruitObject> kFruits{cherry::kFruit, strawberry::kFruit, orange::kFruit, apple::kFruit,
                                                melon::kFruit, flagship::kFruit, bell::kFruit, key::kFruit};
    }

    namespace ghosts {

        /** Amount of frames for which the current sprite is shown. */
        inline constexpr int kAnimationRefreshRate{config::settings::kRefreshRateTicksGhost};

        /** Width and height of a bitmap pacman (in pixels). */
        inline constexpr int kBitmapSize{16};

        /** DO NOT MODIFY : Scale from bitmap to window. */
        inline constexpr auto kScale{getScale(config::dimensions::kWindowCellSize, kBitmapSize)};

        /**Scale used to for the welcome screen*/
        inline constexpr float kWelComeScreenScale{2.75};

        namespace blinky {

            namespace left {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{38};
                    inline constexpr int kBitmapPositionY{124};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{55};
                    inline constexpr int kBitmapPositionY{124};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace right {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{4};
                    inline constexpr int kBitmapPositionY{124};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{21};
                    inline constexpr int kBitmapPositionY{124};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace up {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{13};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{72};
                    inline constexpr int kBitmapPositionY{125};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{2};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{13};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{89};
                    inline constexpr int kBitmapPositionY{125};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{2};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace down {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{106};
                    inline constexpr int kBitmapPositionY{124};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{123};
                    inline constexpr int kBitmapPositionY{124};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

        }

        namespace pinky {

            namespace left {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{38};
                    inline constexpr int kBitmapPositionY{142};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{55};
                    inline constexpr int kBitmapPositionY{142};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace right {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{4};
                    inline constexpr int kBitmapPositionY{142};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{21};
                    inline constexpr int kBitmapPositionY{142};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace up {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{13};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{72};
                    inline constexpr int kBitmapPositionY{143};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{2};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{13};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{89};
                    inline constexpr int kBitmapPositionY{143};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{2};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace down {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{106};
                    inline constexpr int kBitmapPositionY{142};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{123};
                    inline constexpr int kBitmapPositionY{142};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

        }

        namespace inky {

            namespace left {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{38};
                    inline constexpr int kBitmapPositionY{160};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{55};
                    inline constexpr int kBitmapPositionY{160};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace right {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{4};
                    inline constexpr int kBitmapPositionY{160};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{21};
                    inline constexpr int kBitmapPositionY{160};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace up {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{13};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{72};
                    inline constexpr int kBitmapPositionY{161};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{2};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{13};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{89};
                    inline constexpr int kBitmapPositionY{161};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{2};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace down {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{106};
                    inline constexpr int kBitmapPositionY{160};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{123};
                    inline constexpr int kBitmapPositionY{160};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

        }

        namespace clyde {

            namespace left {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{38};
                    inline constexpr int kBitmapPositionY{178};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{55};
                    inline constexpr int kBitmapPositionY{178};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace right {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{4};
                    inline constexpr int kBitmapPositionY{178};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{21};
                    inline constexpr int kBitmapPositionY{178};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace up {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{13};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{72};
                    inline constexpr int kBitmapPositionY{179};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{2};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{13};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{89};
                    inline constexpr int kBitmapPositionY{179};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{2};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

            namespace down {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{106};
                    inline constexpr int kBitmapPositionY{178};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                namespace sprite_2 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{14};
                    inline constexpr int kBitmapHeight{14};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{123};
                    inline constexpr int kBitmapPositionY{178};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{1};
                    inline constexpr int kBitmapOffsetY{1};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{true};

                /** DO NOT MODIFY : Pacman left animation. */
                inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                            kAnimationRefreshRate};
            }

        }

        namespace frightened {

            namespace sprite_1 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{14};
                inline constexpr int kBitmapHeight{14};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{4};
                inline constexpr int kBitmapPositionY{196};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{14};
                inline constexpr int kBitmapHeight{14};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{21};
                inline constexpr int kBitmapPositionY{196};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{true};

            /** DO NOT MODIFY : Pacman left animation. */
            inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite}, kAnimationReverse,
                                        kAnimationRefreshRate};
        }

        namespace frightened_blinking {

            namespace sprite_1 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{14};
                inline constexpr int kBitmapHeight{14};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{38};
                inline constexpr int kBitmapPositionY{196};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            namespace sprite_2 {
                /** Sprite dimensions (in pixels). */
                inline constexpr int kBitmapWidth{14};
                inline constexpr int kBitmapHeight{14};

                /** Sprite positions (in pixels). */
                inline constexpr int kBitmapPositionX{55};
                inline constexpr int kBitmapPositionY{196};

                /** Sprite positions offset (in pixels). */
                inline constexpr int kBitmapOffsetX{1};
                inline constexpr int kBitmapOffsetY{1};

                /** DO NOT MODIFY : Sprite. */
                inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
            }

            /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
            inline constexpr bool kAnimationReverse{false};

            /** DO NOT MODIFY : Pacman left animation. */
            inline Animation kAnimation{{sprite_1::kSprite, sprite_2::kSprite, frightened::sprite_1::kSprite,
                                         frightened::sprite_2::kSprite}, kAnimationReverse, kAnimationRefreshRate};
        }

        namespace dead {

            namespace left {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{10};
                    inline constexpr int kBitmapHeight{5};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{92};
                    inline constexpr int kBitmapPositionY{202};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{3};
                    inline constexpr int kBitmapOffsetY{6};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{false};

                /** DO NOT MODIFY : Dead ghost left animation. */
                inline Animation kAnimation{{sprite_1::kSprite}, kAnimationReverse, kAnimationRefreshRate};
            }

            namespace right {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{10};
                    inline constexpr int kBitmapHeight{5};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{74};
                    inline constexpr int kBitmapPositionY{202};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{3};
                    inline constexpr int kBitmapOffsetY{6};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{false};

                /** DO NOT MODIFY : Dead ghost left animation. */
                inline Animation kAnimation{{sprite_1::kSprite}, kAnimationReverse, kAnimationRefreshRate};
            }

            namespace up {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{10};
                    inline constexpr int kBitmapHeight{5};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{108};
                    inline constexpr int kBitmapPositionY{202};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{3};
                    inline constexpr int kBitmapOffsetY{6};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{false};

                /** DO NOT MODIFY : Dead ghost left animation. */
                inline Animation kAnimation{{sprite_1::kSprite}, kAnimationReverse, kAnimationRefreshRate};
            }

            namespace down {

                namespace sprite_1 {
                    /** Sprite dimensions (in pixels). */
                    inline constexpr int kBitmapWidth{10};
                    inline constexpr int kBitmapHeight{5};

                    /** Sprite positions (in pixels). */
                    inline constexpr int kBitmapPositionX{125};
                    inline constexpr int kBitmapPositionY{202};

                    /** Sprite positions offset (in pixels). */
                    inline constexpr int kBitmapOffsetX{3};
                    inline constexpr int kBitmapOffsetY{6};

                    /** DO NOT MODIFY : Sprite. */
                    inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                                    {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                                    {kBitmapWidth * kScale,   kBitmapHeight * kScale}};
                }

                /** When animation's over : True if the animation should reverse, false if it should restart from zero. */
                inline constexpr bool kAnimationReverse{false};

                /** DO NOT MODIFY : Dead ghost left animation. */
                inline Animation kAnimation{{sprite_1::kSprite}, kAnimationReverse, kAnimationRefreshRate};
            }

        }

    }
    namespace welcome_screen {
        /** DO NOT MODIFY : Welcome Screen animation. */
        //Animate pacman going left with ghosts chasing
    }
    namespace welcome_screen {
        /** DO NOT MODIFY : Welcome Screen animation. */
        //Animate pacman going left with ghosts chasing
    }

}
namespace characters {

    /** Width and height of a bitmap pacman (in pixels). */
    inline constexpr int kBitmapSize{14};

    /** DO NOT MODIFY : Scale from bitmap to window. */
    inline constexpr auto kScale{4};


    namespace letters {
        /** Sprite dimensions (in pixels). */
        inline constexpr int kBitmapWidth{7};
        inline constexpr int kBitmapHeight{7};

        namespace a {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{12};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{1};
            inline constexpr int kBitmapOffsetY{1};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace b {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Size up (in pixels). */
            inline constexpr int kSizeupX{2};
            inline constexpr int kSizeupY{2};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{20};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace c {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{28};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace d {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{36};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace e {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{44};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace f {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{52};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace g {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{60};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace h {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{68};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace i {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{77};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace j {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{84};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace k {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{92};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace l {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{100};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace m {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{108};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace n {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{116};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace o {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{124};
            inline constexpr int kBitmapPositionY{61};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace p {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{4};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace q {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{12};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace r {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{20};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace s {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{28};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace t {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{37};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace u {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{44};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace v {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{53};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace w {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{61};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace x {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{69};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace y {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{6};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{77};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace z {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{84};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
    }

    namespace numbers {
        /** Sprite dimensions (in pixels). */
        inline constexpr int kBitmapWidth{7};
        inline constexpr int kBitmapHeight{7};

        namespace zero {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{4};
            inline constexpr int kBitmapPositionY{53};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace one {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{6};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{13};
            inline constexpr int kBitmapPositionY{53};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace two {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{20};
            inline constexpr int kBitmapPositionY{53};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace three {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{28};
            inline constexpr int kBitmapPositionY{53};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace four {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{36};
            inline constexpr int kBitmapPositionY{53};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace five {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{44};
            inline constexpr int kBitmapPositionY{53};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace six {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{52};
            inline constexpr int kBitmapPositionY{53};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace seven {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{60};
            inline constexpr int kBitmapPositionY{53};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace eight {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{68};
            inline constexpr int kBitmapPositionY{53};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace nine {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{76};
            inline constexpr int kBitmapPositionY{53};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
    }
    namespace points {
        namespace points_100 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{13};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{180};
            inline constexpr int kBitmapPositionY{133};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_200 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{14};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{155};
            inline constexpr int kBitmapPositionY{176};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_300 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{14};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{179};
            inline constexpr int kBitmapPositionY{142};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_400 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{14};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{155};
            inline constexpr int kBitmapPositionY{185};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_500 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{14};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{179};
            inline constexpr int kBitmapPositionY{151};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_700 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{14};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{179};
            inline constexpr int kBitmapPositionY{160};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_800 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{14};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{155};
            inline constexpr int kBitmapPositionY{194};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_1000 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{16};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{177};
            inline constexpr int kBitmapPositionY{169};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_1600 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{15};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{154};
            inline constexpr int kBitmapPositionY{203};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_2000 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{16};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{177};
            inline constexpr int kBitmapPositionY{178};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_3000 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{16};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{177};
            inline constexpr int kBitmapPositionY{187};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_5000 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{16};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{177};
            inline constexpr int kBitmapPositionY{196};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_10 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{5};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{151};
            inline constexpr int kBitmapPositionY{212};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_50 {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{7};
            inline constexpr int kBitmapHeight{5};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{162};
            inline constexpr int kBitmapPositionY{212};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_small {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{14};
            inline constexpr int kBitmapHeight{5};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{178};
            inline constexpr int kBitmapPositionY{212};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }
        namespace points_big {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{15};
            inline constexpr int kBitmapHeight{5};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{178};
            inline constexpr int kBitmapPositionY{205};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};

        }

    }
    namespace special {
        namespace dot {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{6};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{91};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace slash {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{5};
            inline constexpr int kBitmapHeight{5};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{93};
            inline constexpr int kBitmapPositionY{54};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace corp {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{8};
            inline constexpr int kBitmapHeight{8};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{116};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace dash {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{6};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{84};
            inline constexpr int kBitmapPositionY{53};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace apostrophe {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{5};
            inline constexpr int kBitmapHeight{4};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{125};
            inline constexpr int kBitmapPositionY{69};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace exclamation {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{5};
            inline constexpr int kBitmapHeight{7};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{102};
            inline constexpr int kBitmapPositionY{52};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
        namespace points {
            /** Sprite dimensions (in pixels). */
            inline constexpr int kBitmapWidth{10};
            inline constexpr int kBitmapHeight{5};

            /** Sprite positions (in pixels). */
            inline constexpr int kBitmapPositionX{178};
            inline constexpr int kBitmapPositionY{212};

            /** Sprite positions offset (in pixels). */
            inline constexpr int kBitmapOffsetX{0};
            inline constexpr int kBitmapOffsetY{0};

            /** DO NOT MODIFY : Sprite. */
            inline constexpr Sprite kSprite{{kBitmapPositionX,        kBitmapPositionY, kBitmapWidth, kBitmapHeight},
                                            {kBitmapOffsetX * kScale, kBitmapOffsetY * kScale},
                                            {(kBitmapWidth) * kScale, (kBitmapHeight) * kScale}};
        }
    }

}
/**Text scale up*/
namespace scales {
    inline constexpr float kReadyTextScale{3};
    inline constexpr float kPlayerOneText{2.9};
    inline constexpr float kGameOverText{2.9};
    inline constexpr float kCreditText{2.9};
    inline constexpr float kScore{3.0};

}

/**Offsets between characters when writing text (in pixels) */
namespace offsets {
    inline constexpr int kGhostPointsX{10};
    inline constexpr int kGhostPointsY{10 + config::dimensions::kScoreBoardHeight};
    inline constexpr int kReady{2};
    inline constexpr int kPlayerOne{2};
    inline constexpr int kGameOverText{2};
    inline constexpr int kCreditText{1};
    inline constexpr int kGhostNames{1};
}

/**Colours*/
namespace colours {
    inline const std::tuple<int, int, int> kCyan = std::make_tuple(0, 232, 216);
    inline const std::tuple<int, int, int> kPink = std::make_tuple(252, 196, 252);
    inline const std::tuple<int, int, int> kOrange = std::make_tuple(252, 152, 56);
    inline const std::tuple<int, int, int> kWhite = std::make_tuple(252, 252, 252);
    inline const std::tuple<int, int, int> kRed = std::make_tuple(216, 43, 0);
    inline const std::tuple<int, int, int> kYellow = std::make_tuple(240, 188, 60);
}

namespace display {

    namespace scoreboard {

        /**Score Board Positions*/
        inline constexpr int kScoreBoardX{0};
        inline constexpr int kScoreBoardY{0};
        inline constexpr int kScoreBoardOneUpTextX{50};
        inline constexpr int kScoreBoardOneUpTextY{10};
        inline constexpr int kScoreBoardScoreX{75};
        inline constexpr int kScoreBoardScoreY{40};
        inline constexpr int kScoreBoardHighScoreTextX{200};
        inline constexpr int kScoreBoardHighScoreTextY{10};
        inline constexpr int kScoreBoardHighScoreX{285};
        inline constexpr int kScoreBoardHighScoreY{40};
        inline constexpr int kScoreBoardLivesX{30};
        inline constexpr int kScoreBoardLivesY{
                config::dimensions::kScoreBoardHeight +
                config::dimensions::kMapHeight * config::dimensions::kWindowCellSize};
        inline constexpr int kScoreBoardFruitsX{config::dimensions::kWindowWidth - 30};
        inline constexpr int kScoreBoardFruitsY{
                config::dimensions::kScoreBoardHeight +
                config::dimensions::kMapHeight * config::dimensions::kWindowCellSize};


        inline constexpr int kCreditPosX{60};
        inline constexpr int kCreditPosY{config::dimensions::kWindowHeight - 50};
    }

    namespace welcome_screen {

        namespace text {
            /**Positions*/
            inline constexpr int kCharaterNicknameX{140};
            inline constexpr int kCharaterNicknameY{scoreboard::kScoreBoardScoreY + 50};
            inline constexpr int kCharaterNicknameOffset{1};
            inline constexpr float kCharaterNicknameScale{2.75};
            inline constexpr int kMidwayX{120};
            inline constexpr int kMidwayY{650};
            inline constexpr int kMidwayOffset{1};
            inline constexpr float kMidwayScale{2.75};

        }

        namespace pellet {

            /**Sprite position*/
            inline constexpr int kPosX{250};
            inline constexpr int kPosY{500};

            /**pts sprite position*/
            inline constexpr int kPointsPosX{320};
            inline constexpr int kPointsPosY{495};

            /**Points number*/
            inline constexpr int kPointsTextPosX{280};
            inline constexpr int kPointsTextPosY{495};

            inline constexpr float kPointsScale{2.7};
            inline constexpr float kPointsTextscale{2.2};
            inline constexpr float kScale{3};
            inline constexpr int kOffset{1};


            inline constexpr float kSpriteHeight{visuals::pellet::kBitmapHeight * kScale};
            inline constexpr float kSpriteWidth{visuals::pellet::kBitmapWidth * kScale};

            inline constexpr float kPointsSpriteHeight{characters::special::points::kBitmapHeight * kPointsScale};
            inline constexpr float kPointsSpriteWidth{characters::special::points::kBitmapWidth * kPointsScale};
        }

        namespace energizer {

            /**Sprite position*/
            inline constexpr int kPosX{242};
            inline constexpr int kPosY{520};

            /**pts sprite position*/
            inline constexpr int kPointsPosX{320};
            inline constexpr int kPointsPosY{525};

            /**Points number*/
            inline constexpr int kPointsTextPosX{280};
            inline constexpr int kPointsTextPosY{522};

            inline constexpr float kPointsScale{2.7};
            inline constexpr float kPointsTextscale{2.2};
            inline constexpr float kScale{3};
            inline constexpr int kOffset{1};


            inline constexpr float kSpriteHeight{visuals::energizer::kBitmapHeight * kScale};
            inline constexpr float kSpriteWidth{visuals::energizer::kBitmapHeight * kScale};

            inline constexpr float kPointsSpriteHeight{characters::special::points::kBitmapHeight * kPointsScale};
            inline constexpr float kPointsSpriteWidth{characters::special::points::kBitmapWidth * kPointsScale};
        }

        /**Scales*/
        namespace ghosts {
            /**Name text scale Up */
            inline constexpr float kNameScale{2.75};
            inline constexpr float kSpriteHeight{visuals::ghosts::blinky::right::sprite_1::kBitmapHeight * 2.75};
            inline constexpr float kSpriteWidth{visuals::ghosts::blinky::right::sprite_1::kBitmapWidth * 2.75};

            namespace blinky {

                /**Welcome Screen Positions*/
                inline constexpr int kWelcomeScreenX{60};
                inline constexpr int kWelcomeScreenY{170};

                /**Name Position*/
                inline constexpr int kNameX{140};
                inline constexpr int kNameY{180};

                /**Nickname position*/
                inline constexpr int kNickNameX{360};
                inline constexpr int kNickNameY{180};
            }
            namespace pinky {

                /**Welcome Screen Positions*/
                inline constexpr int kWelcomeScreenX{60};
                inline constexpr int kWelcomeScreenY{240};

                /**Name Position*/
                inline constexpr int kNameX{140};
                inline constexpr int kNameY{250};

                /**Nickname position*/
                inline constexpr int kNickNameX{360};
                inline constexpr int kNickNameY{250};
            }
            namespace inky {
                /**Welcome Screen Positions*/
                inline constexpr int kWelcomeScreenX{60};
                inline constexpr int kWelcomeScreenY{310};

                /**Name Position*/
                inline constexpr int kNameX{140};
                inline constexpr int kNameY{320};

                /**Nickname position*/
                inline constexpr int kNickNameX{360};
                inline constexpr int kNickNameY{320};
            }
            namespace clyde {
                /**Welcome Screen Positions*/
                inline constexpr int kWelcomeScreenX{60};
                inline constexpr int kWelcomeScreenY{380};

                /**Name Position*/
                inline constexpr int kNameX{140};
                inline constexpr int kNameY{390};

                /**Nickname position*/
                inline constexpr int kNickNameX{360};
                inline constexpr int kNickNameY{390};
            }
        }


    }

    namespace game_messages {

        /**Game Start display positions*/
        inline constexpr int kReadyTextX{280};
        inline constexpr int kReadyTextY{562};
        inline constexpr int kPlayerOneTextX{229};
        inline constexpr int kPlayerOneTextY{400};

        /**Game Over*/
        inline constexpr int kGameOverTextX{227};
        inline constexpr int kGameOverTextY{562};

        /** Credit Position*/
        inline constexpr int kCreditTextX{60};
        inline constexpr int kCreditTextY{964};
    }


}


#endif //PACMAN_VISUALS_H
