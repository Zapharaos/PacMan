/**
 * @file ghost.h
 * @brief Defines the Ghost class, which is the second main entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 03/04/2023
*/

#ifndef PEC_MEN_GHOST_H
#define PEC_MEN_GHOST_H

#include "movingEntity.h"

/**
 * @brief The Ghost entity.
 * Inherits from the MovingEntity class.
 * @see MovingEntity
*/
class Ghost : public MovingEntity
{

private:

    enum class GhostStatus
    {
        kDefault,
        kScared,
        kLessScared,
        kInvisible
    };

    GhostStatus status_ {GhostStatus::kDefault};

public:

    /**
     * @brief Default Ghost constructor.
     */
    Ghost();

};


#endif //PEC_MEN_GHOST_H
