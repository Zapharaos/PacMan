/**
 * @file movingEntity.h
 * @brief Defines the movingEntity class, an entity that can move across the map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 28/02/2023
*/

#ifndef PACMAN_MOVINGENTITY_H
#define PACMAN_MOVINGENTITY_H

#include <SDL.h>

#include <vector>

#include "entity.h"
#include "../map/map.h"
#include "../utils/direction.h"
#include "../display/animation.h"

/**
 * @brief An entity that can move across the map.
 * This class represents an entity that is capable of moving across the game board. It inherits from the Entity class and has
 * additional functionality for movement, speed and animations.
 * @see Entity class
*/
class MovingEntity : public Entity
{

private:

    /** Starting position / default position (in pixels). */
    Position start_ {};

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
    Direction previous_direction_{};

public:

    /**
     * @brief Default MovingEntity constructor.
     * This is the default constructor for the MovingEntity class.
     */
    MovingEntity();

    /**
     * @brief Constructs a MovingEntity object with the given position, enabled state, points, speed, and animations.
     * @param position Raw position.
     * @param enabled If the entity is active.
     * @param points Points earned when entity is eaten.
     * @param speed Speed per tick at which the entity is moving.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    MovingEntity(const Position &position, bool enabled, int points, int speed,
                 Animation left, Animation right, Animation up, Animation down);

    /**
     * @brief Constructs a MovingEntity object with the given position, speed, and animations.
     * @param position Raw position.
     * @param speed Speed per tick at which the entity is moving.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    MovingEntity(const Position &position, int speed, Animation left,
                 Animation right, Animation up, Animation down);

    /**
     * @brief Getter for the speed.
     * @return The speed per tick at which the entity is moving.
     */
    [[nodiscard]] int getSpeed() const;

    /**
     * @brief Handle the moving entity.
     * @param map The board with all the cells.
     * @param direction The direction the entity is moving towards.
     */
    void tick(const Map &map, Direction direction);

    /**
     * @brief Handle the status.
     */
    virtual void handleStatus();

    /**
     * @brief Moves the entity in the given direction if it is a legal move.
     * @param map The board with all the cells.
     * @param direction The direction the entity is moving towards.
     * @return True if the move is legal, otherwise false.
     */
    bool move(const Map &map, Direction direction);

    /**
     * @brief Switches between sprites depending on the direction of the current move.
     * Called when a move is legal.
     * Uses the Animation::animate() method to switch between the different animations.
     * @param direction The direction of the current move.
     */
    virtual void animate(const Direction &direction);

    /**
     * @brief Resets the entity to the given coordinates.
     */
    virtual void reset();
};


#endif //PACMAN_MOVINGENTITY_H
