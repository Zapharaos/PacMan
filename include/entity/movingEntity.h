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
template<std::size_t L=0, std::size_t R=0, std::size_t U=0, std::size_t D=0>
class MovingEntity : public Entity
{

private:

    /** Starting position / default position (in pixels). */
    Position start_ {};

    /** Speed per tick at which the entity is moving. */
    int speed_{};

    /** Animations when moving towards the left. */
    Animation<L> left_{};

    /** Animations when moving towards the right. */
    Animation<R> right_{};

    /** Animations when moving towards the top. */
    Animation<U> up_{};

    /** Animations when moving towards the bottom. */
    Animation<D> down_{};

    /** Previous direction.
     * @details Used to determine a swap of animation. */
    Direction previous_direction_{};

public:

    /**
     * @brief Default MovingEntity constructor.
     * This is the default constructor for the MovingEntity class.
     */
    inline MovingEntity() = default;

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
    inline MovingEntity(const Position &position, bool enabled, int points, int speed,
                 Animation<L> left, Animation<R> right, Animation<U> up, Animation<D> down) :
            Entity(position, left.getSprite(), enabled, points), start_(position), speed_(speed),
            left_(std::move(left)), right_(std::move(right)), up_(std::move(up)), down_(std::move(down))
    {}

    /**
     * @brief Constructs a MovingEntity object with the given position, speed, and animations.
     * @param position Raw position.
     * @param speed Speed per tick at which the entity is moving.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    inline MovingEntity(const Position &position, int speed, Animation<L> left,
                 Animation<R> right, Animation<U> up, Animation<D> down) :
            Entity(position, left.getSprite()), start_(position), speed_(speed),
            left_(std::move(left)), right_(std::move(right)), up_(std::move(up)), down_(std::move(down))
    {}

    /**
     * @brief Handle the moving entity.
     * @param map The board with all the cells.
     * @param direction The direction the entity is moving towards.
     */
    inline virtual void tick(const Map &map, Direction direction)
    {
        if(isCounterActive()) {
            counterIncrement();
            return;
        }

        // Reset status
        if(!isVisible()) show();

        move(map, direction);
    };

    /**
     * @brief Moves the entity in the given direction if it is a legal move.
     * @param map The board with all the cells.
     * @param direction The direction the entity is moving towards.
     */
    void move(const Map &map, Direction direction)
    {

        // Direction must be initialized.
        if (direction.isUninitialized())
        {
            if(previous_direction_.isUninitialized()) return;
            direction = previous_direction_; // Repeat previous movement.
        }

        // Get positions as pixels.
        std::optional<Position> position;
        auto origin = getPosition();
        Position destination;

        // Direction change.
        if(direction.isTurn(previous_direction_))
        {
            destination = origin.moveIntoDirection(previous_direction_, speed_);
            position = map.turn(origin, destination, previous_direction_, direction);
            if(!position) // Turn is illegal.
                direction = previous_direction_; // Move into previous direction.
        }

        destination = origin.moveIntoDirection(direction, speed_);

        // Warping.
        if(map.isWarping(origin, destination) && direction == previous_direction_)
        {
            auto size = getSprite().getSize();
            auto corner = destination.shift(size.first, size.second);
            position = map.warp(destination, corner);
        }

        // No movements yet : move straight direction (or keeping same direction).
        if(!position)
        {
            position = map.move(origin, destination, direction);
            if (!position)
                return; // Move is illegal.
        }

        // Move is legal : updates the entity.
        animate(direction);
        setPosition(position.value());
        previous_direction_ = direction;
    };

    /**
     * @brief Switches between sprites depending on the direction of the current move.
     * Called when a move is legal.
     * Uses the Animation::animate() method to switch between the different animations.
     * @param direction The direction of the current move.
     */
    inline void animate(const Direction &direction)
    {
        // Nothing to animate yet.
        bool restart = previous_direction_ != direction;

        // Gets the new sprite.
        if (direction.isLeft())
            setSprite(left_.animate(restart));
        else if (direction.isRight())
            setSprite(right_.animate(restart));
        else if (direction.isUp())
            setSprite(up_.animate(restart));
        else if (direction.isDown())
            setSprite(down_.animate(restart));
    };

    /**
     * @brief Resets the entity to the given coordinates.
     */
    inline virtual void reset()
    {
        previous_direction_.reset();
        left_.reset();
        setSprite(left_.getSprite()); // default sprite
        setPosition(start_); // reset position
    };
};


#endif //PACMAN_MOVINGENTITY_H
