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

    /** Animations when has died. */
    Animation death_{};

public:

    /**
     * @brief Default Pacman constructor.
     */
    Pacman();

    /**
    * @brief Executes the death animation.
    */
    void death();

};


#endif //PACMAN_PACMAN_H
