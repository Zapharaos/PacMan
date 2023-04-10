/**
 * @file pacman.h
 * @brief Defines the Pacman class, which is the main entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 28/02/2023
*/

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include "movingEntity.h"

/**
 * @brief The Pacman entity.
 * Inherits from the MovingEntity class.
 * @see MovingEntity
*/
class Pacman : public MovingEntity
{

private:

    /** Has died. */
    bool dead_ = false;

    /** Animations when has died. */
    Animation death_{};

public:

    /**
     * @brief Default Pacman constructor.
     */
    Pacman();

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
     * @see MovingEntity::reset()
     */
    void reset() override;
};


#endif //PACMAN_PACMAN_H
