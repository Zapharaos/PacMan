/**
 * @file movingEntity.h
 * @brief Implements the movingEntity class, an entity that can move across the map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 28/02/2023
*/

#include "../../include/entity/movingEntity.h"

MovingEntity::MovingEntity() = default;

MovingEntity::MovingEntity(const Position &position, bool enabled, int points, int speed,
                           Animation left, Animation right, Animation up, Animation down) :
        Entity(position, left.getSprite(), enabled, points), start_(position), speed_(speed),
        left_(std::move(left)), right_(std::move(right)), up_(std::move(up)), down_(std::move(down))
{}

MovingEntity::MovingEntity(const Position &position, int speed, Animation left,
                           Animation right, Animation up, Animation down) :
        Entity(position, left.getSprite()), start_(position), speed_(speed),
        left_(std::move(left)), right_(std::move(right)), up_(std::move(up)), down_(std::move(down))
{}

void MovingEntity::tick(const Map &map, Direction direction)
{
    if(isCounterActive()) {
        counterIncrement();
        return;
    }

    // Reset status
    if(!isVisible()) show();

    move(map, direction);
}

void MovingEntity::move(const Map &map, Direction direction)
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
}

void MovingEntity::animate(const Direction &direction)
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
}

void MovingEntity::reset()
{
    previous_direction_.reset();
    left_.reset();
    setSprite(left_.getSprite()); // default sprite
    setPosition(start_); // reset position
}
