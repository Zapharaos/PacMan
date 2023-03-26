/**
 * @file sprite.h
 * @brief Contains the Animation class which executes Sprites switches.
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
 * @tparam N Number of sprites in the animation.
*/
template<std::size_t N>
class Animation {

private:

    /** Sprites to switch between when displayed. */
    Container<Sprite, N> animation_ {};

    /** If the animation should reverse when it reached the end of the sprite vector. */
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
    Counter counter_ {};

public:

    /**
     * @brief Default constructor for the Animation class.
     */
    inline Animation() = default;

    /**
     * @brief Animation constructor.
     * @param animation Container of sprites to switch between when displayed.
     * @param reverse If the animation should reverse when it reached the end of the sprite vector.
     * @param ticks_cap Amount of ticks before the sprite switches.
     */
    inline constexpr Animation(Container<Sprite, N> animation, bool reverse, long ticks_cap) : animation_(std::move(animation)), reverse_(reverse), ticks_cap_(ticks_cap)
    {}

    /**
     * @brief Executes the sprite switches.
     * @param restart True if the animation has to be reset (default = false).
     * @return The current sprite to be displayed.
     */
    inline const Sprite &animate(bool restart = false)
    {
        if(restart) reset();

        if(!counter_.isActive()) // if enough frames
        {
            // Restart counter.
            counter_.start(ticks_cap_);

            // Handle reverse.
            if((reverse_ && index_ == animation_.size_ - 1) || (!to_right_ && index_ == 0))
                to_right_ = !to_right_;

            // Animation is over
            if((!reverse_ && index_ == animation_.size_ - 1) || (!to_right_ && index_ == 0))
                over_ = true;

            // Update index.
            if(!reverse_ && index_ == animation_.size_ - 1)
                index_ = 0;
            else if(to_right_)
                ++index_;
            else
                --index_;
        }
        counter_.increment(); // increment number of frames
        return animation_.at(index_);
    }

    /**
     * @brief Get the current sprite to be displayed.
     * @return The current sprite to be displayed.
     */
    [[nodiscard]] inline const Sprite & getSprite()
    { return animation_.at(index_); }

    /**
     * @brief Indicates whether the animation is over.
     * @return true if the animation is over, else false.
     */
    [[nodiscard]] inline bool isOver() const
    { return over_; }

    /**
     * @brief Resets the animation object to its initial state.
     */
    inline void reset()
    {
        index_ = 0;
        to_right_ = true;
        over_ = false;
        counter_.start(ticks_cap_);
    }
};


#endif //PACMAN_ANIMATION_H
