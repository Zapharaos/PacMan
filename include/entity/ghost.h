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
class Ghost : public MovingEntity<
        visuals::pacman::left::kAnimationSize,
        visuals::pacman::right::kAnimationSize,
        visuals::pacman::up::kAnimationSize,
        visuals::pacman::down::kAnimationSize>
{

public:

    enum class GhostType
    {
        kUndefined,
        kBlinky,
        kPinky,
        kInky,
        kClyde
    };

    /**
     * @brief Default Ghost constructor.
     */
    Ghost();

    explicit Ghost(Ghost::GhostType type);

    /**
     * @brief Handle the moving entity.
     * @param map The board with all the cells.
     * @param pacman The position this entity is targeting.
     */
    void tick(const Map &map, const SDL_Rect &pacman);

    /**
     * @brief Resets the entity object.
     * @param coordinates Raw position coordinates.
     * @see MovingEntity::reset()
     */
    void reset(const Position &coordinates) override;

private:

    GhostType type_ {GhostType::kUndefined};

    enum class GhostStatus
    {
        kDefault,
        kScared,
        kLessScared,
        kInvisible
    };

    GhostStatus status_ {GhostStatus::kDefault};

    Counter counter_ {};
};


#endif //PEC_MEN_GHOST_H
