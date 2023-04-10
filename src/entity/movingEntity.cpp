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
{
    tunnel_slow_ = true;
}

MovingEntity::MovingEntity(const Position &position, int speed, Animation left,
                           Animation right, Animation up, Animation down) :
        Entity(position, left.getSprite()), start_(position), speed_(speed),
        left_(std::move(left)), right_(std::move(right)), up_(std::move(up)), down_(std::move(down))
{}

void MovingEntity::tick(const Map &map, Direction direction)
{
    handleStatus();

    if(move(map, direction)) // Move legal.
        animate(previous_direction_);
}

void MovingEntity::handleStatus()
{
    // Changes ongoing.
    if(isCounterActive())
    {
        counterIncrement();
        return;
    }

    // Reset status.
    if(!isVisible()) show();
}

bool MovingEntity::move(const Map &map, Direction direction)
{

    // Direction must be initialized.
    if (direction.isUninitialized())
    {
        if(previous_direction_.isUninitialized()) // No available movement.
            return false;
        direction = previous_direction_; // Repeat previous movement.
    }

    // Get positions as pixels.
    std::optional<Position> position;
    auto origin = getPosition();
    Position destination = getDestination(origin, previous_direction_);

    // Direction change.
    if(direction.isTurn(previous_direction_))
    {
        position = map.turn(origin, destination, previous_direction_, direction);
        if(!position) // Turn is illegal.
            direction = previous_direction_; // Move into previous direction.
    }

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
            return false; // Move is illegal.
    }

    // Move is legal : updates the entity.
    setPosition(position.value());
    previous_direction_ = direction;
    return true;
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

Position MovingEntity::getDestination(Position origin, Direction direction) const
{
    return origin.moveIntoDirection(direction, speed_, tunnel_slow_);
}

void MovingEntity::reset()
{
    previous_direction_.reset();
    left_.reset();
    setSprite(left_.getSprite()); // default sprite
    setPosition(start_); // reset position
}
