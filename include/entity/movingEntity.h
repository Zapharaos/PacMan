//
// Created by matthieu on 28/02/2023.
//

#ifndef PACMAN_MOVINGENTITY_H
#define PACMAN_MOVINGENTITY_H

#include <SDL.h>
#include <vector>
#include "entity.h"
#include "../map/map.h"
#include "../utils/direction.h"
#include "../display/animation.h"

/** Entity that can move across the map.
 *
 * @see Entity class
 */
class MovingEntity : public Entity
{

protected:

    enum class MovingEntityStatus : underlying_type_t<EntityStatus> {
        FROZEN,
        ANIMATED, // frozen but still animate
        DEAD // ?
    };
    // EntityStatus test = (EntityStatus)MovingEntityStatus::FROZEN;

private:

    /** Speed per tick at which the entity is moving. */
    int speed_{};

    /** Animations when moving towards the left. */
    Animation left_{};

    /** Animations when moving towards the right. */
    Animation right_{};

    /** Animations when moving towards the top. */
    Animation up_{};

    /** Animations when moving towards the bottom. */
    Animation down_{};

    /** Previous direction.
     * @details Used to determine a swap of animation. */
    Direction previousDirection_{};

public:

    /** Default MovingEntity constructor. */
    MovingEntity();

    /** MovingEntity constructor.
     *
     * @param position Raw position.
     * @param sprite Image when displayed.
     * @param enabled If the entity is active.
     * @param points Points earned when entity is eaten.
     * @param speed Speed per tick at which the entity is moving.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    MovingEntity(const Position &position, const Sprite &sprite, bool enabled,
                 int points, int speed, Animation left,
                 Animation right, Animation up,
                 Animation down);

    /** MovingEntity constructor.
     *
     * @param position Raw position.
     * @param sprite Image when displayed.
     * @param speed Speed per tick at which the entity is moving.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    MovingEntity(const Position &position, const Sprite &sprite, int speed,
                 Animation left,
                 Animation right, Animation up,
                 Animation down);

    /** If legal, moves into a given direction.
     *
     * @param map The board with all the cells.
     * @param direction The direction the entity is moving towards to.
     */
    void move(const Map &map, Direction direction);

    /** Switches between sprites depending on the direction.
     *
     * @details Called when a move is legal.
     * @see Animation::animate()
     *
     * @param direction the direction of the current move.
     */
    void animate(const Direction &direction);

    /**
     * Resets the entity object.
     */
    virtual void reset(const Position &coordinates);
};


#endif //PACMAN_MOVINGENTITY_H
