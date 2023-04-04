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

    /**
     * @brief Constructs a Ghost entity with the given type and position.
     * @param type Which type of ghosts.
     * @param position Raw position.
     * @param target The position the ghost is targeting while in scatter mode.
     */
    Ghost(Ghost::GhostType type, const Position &position, Position target);

    /**
     * @brief Handle the moving entity.
     * @param map The board with all the cells.
     * @param pacman The position this entity is targeting.
     */
    void tick(const Map &map, const SDL_Rect &pacman);

    /**
     * @brief Toggle the frightened mode.
     */
    void toggleFrightened();

    /**
     * @brief Resets the entity object.
     * @see MovingEntity::reset()
     */
    void reset() override;

private:

    GhostType type_ {GhostType::kUndefined};

    Position target_ {};

    enum class GhostStatus
    {
        kStart,
        kChase,
        kScatter,
        kFrightened,
        kFrightenedBlinking
    };

    GhostStatus status_ {GhostStatus::kStart};

    GhostStatus previous_status_ {};

    Counter counter_ {};
};


#endif //PEC_MEN_GHOST_H
