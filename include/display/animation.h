//
// Created by matthieu on 13/03/2023.
//

#ifndef PACMAN_ANIMATION_H
#define PACMAN_ANIMATION_H


#include "sprite.h"
#include <vector>
#include <optional>

/** Sprites to switch between when displayed. */
class Animation {

private:

    /** Sprites to switch between when displayed. */
    vector<Sprite> animation_;

    /** If the animation should reverse when it reached the end of the sprite vector. */
    bool reverse_ = false;

    /** Amount of ticks before the sprite switches. */
    long ticksCap_ = 0;

    /** Index of the current sprite. */
    int index_ = 0;

    /** If going trough the sprite vector from left to right. */
    bool toRight_ = true;

    /** Current amount of ticks. */
    long ticksCount_ = 0;

    bool over_ = false;

public:

    /** Default Animation constructor. */
    Animation();

    /** Animation constructor.
     *
     * @param animation Sprites to switch between when displayed.
     * @param reverse If the animation should reverse when it reached the end of the sprite vector.
     * @param ticksCap Amount of ticks before the sprite switches.
     */
    Animation(const vector<Sprite> &animation, bool reverse, long ticksCap);

    /** Executes the sprite switches when conditions are met.
     *
     * @param True if the animation has to be reset (default = false).
     * @return The current sprite to be displayed.
     */
    const Sprite &animate(bool restart = false);

    /** Get the current sprite to be displayed.
     *
     * @return The current sprite to be displayed.
     */
    [[nodiscard]] const Sprite & getSprite() const;

    /** Indicates whether the animation is over.
     *
     * @return True if over, else false.
     */
    [[nodiscard]] bool isOver() const;

    /**
     * Resets the animation object.
     */
    void reset();

};


#endif //PACMAN_ANIMATION_H