/**
 * @file pacman.h
 * @brief Defines the Pacman class, which is the main entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 28/02/2023
*/

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include "movingEntity.h"
#include "../utils/timer.h"

/**
 * @brief The Pacman entity.
 * Inherits from the MovingEntity class.
 * @see MovingEntity
*/
class Pacman : public MovingEntity
{

private:

    /**
     * This is a static constexpr integer used to copy elements from the configuration files,
     * making it easier to understand and reference in the code.
     */
    static constexpr int kAnimationDeathSize {visuals::pacman::death::kAnimationSize};

    /** Superpower mode is activated. */
    bool superpower_ = false;

    /** Has died. */
    bool dead_ = false;

    /** Animations when has died. */
    Animation<kAnimationDeathSize> death_{};

public:

    /**
     * @brief Default Pacman constructor.
     */
    Pacman();

    /**
     * @brief Setter for superpower mode.
     */
    void setSuperpower(bool superpower);

    /**
     * @brief Getter for superpower mode.
     */
    [[nodiscard]] bool isSuperpower() const;

    /**
     * @brief Update the superpower counter and disable it when it's over.
     */
    void tick();

    /**
     * @brief Getter for "dead" status.
     */
    [[nodiscard]] bool isDead() const;

    /**
     * @brief Setter for "dead" status.
     */
    void setDead(bool dead);

    /**
     * @brief Executes the death animation.
     */
    void animateDeath();

    /**
     * @brief Resets the entity object.
     * @param coordinates Raw position coordinates.
     * @see MovingEntity::reset()
     */
    void reset(const Position &coordinates) override;
};


#endif //PACMAN_PACMAN_H
