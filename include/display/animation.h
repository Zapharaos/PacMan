/**
 * @file animation.h
 * @brief Defines the Animation class which executes Sprites switches.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 13/03/2023
*/

#ifndef PACMAN_ANIMATION_H
#define PACMAN_ANIMATION_H

#include <utility>
#include <vector>
#include <optional>
#include <array>

#include "sprite.h"
#include "../utils/counter.h"
#include "../utils/utils.h"
#include "../utils/container.h"

/**
 * @brief Sprites to switch between when displayed.
 * A class that provides sprite animation by switching between a sequence of Sprites.
*/
class Animation
{

private:

    /** Sprites to switch between when displayed. */
    std::vector<Sprite> animation_{};

    /** If the Animation should reverse when it reached the end of the sprite vector. */
    bool reverse_ = false;

    /** Amount of ticks before the sprite switches. */
    long ticks_cap_ = 0;

    /** Index of the current sprite. */
    int index_ = 0;

    /** If going trough the sprite vector from left to right. */
    bool to_right_ = true;

    /** if the animation is over. */
    bool over_ = false;

    /** Object used to count frames between each sprite. */
    Counter counter_{};

public:

    /**
     * @brief Default constructor for the Animation class.
     */
    Animation();

    /**
     * @brief Animation constructor.
     * @param animation Container of sprites to switch between when displayed.
     * @param reverse If the animation should reverse when it reached the end of the sprite vector.
     * @param ticks_cap Amount of ticks before the sprite switches.
     */
    Animation(std::vector<Sprite> animation, bool reverse, long ticks_cap);

    /**
     * @brief Executes the sprite switches.
     * @param restart True if the animation has to be reset (default = false).
     * @return The current sprite to be displayed.
     */
    const Sprite &animate(bool restart = false);

    /**
     * @brief Get the current sprite to be displayed.
     * @return The current sprite to be displayed.
     */
    [[nodiscard]] const Sprite &getSprite();

    /**
     * @brief Indicates whether the animation is over.
     * @return true if the animation is over, else false.
     */
    [[nodiscard]] bool isOver() const;

    /**
     * @brief Resets the animation object to its initial state.
     */
    void reset();
};


#endif //PACMAN_ANIMATION_H
