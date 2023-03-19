//
// Created by matthieu on 28/02/2023.
//

#include "../../include/entity/movingEntity.h"

#include <utility>

MovingEntity::MovingEntity() = default;

MovingEntity::MovingEntity(const Position &position, const Sprite &sprite,
                           bool enabled, int points, int speed,
                           Animation left,
                           Animation right,
                           Animation up, Animation down)
        :
        Entity(position, sprite, enabled, points), speed_(speed), left_(std::move(left)),
        right_(std::move(right)), up_(std::move(up)), down_(std::move(down))
{}

MovingEntity::MovingEntity(const Position &position, const Sprite &sprite, int speed,
                           Animation left,
                           Animation right,
                           Animation up, Animation down)
        :
        Entity(position, sprite), speed_(speed), left_(std::move(left)), right_(std::move(right)),
        up_(std::move(up)), down_(std::move(down))
{}

void MovingEntity::move(const Map &map, Direction direction)
{

    if(counter_.isActive()) // Entity interrupted
    {
        counter_.increment();
        return;
    }

    // Reset status
    if(!isVisible()) show();

    // Direction must be initialized.
    if (direction.isUninitialized())
    {
        if(previousDirection_.isUninitialized()) return;
        direction = previousDirection_; // Repeat previous movement.
    }

    // Get positions as pixels.
    optional<Position> position;
    Position origin = getPosition();
    Position destination;

    // Direction change.
    if(direction.isTurn(previousDirection_))
    {
        destination = origin.moveIntoDirection(previousDirection_, speed_);
        position = map.turn(origin, destination, previousDirection_, direction);
        if(!position) // Turn is illegal.
            direction = previousDirection_; // Move into previous direction.
    }

    destination = origin.moveIntoDirection(direction, speed_);

    // Warping.
    if(map.isWarping(origin, destination) && direction == previousDirection_)
    {
        auto size = getSpriteSize();
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
    previousDirection_ = direction;
}

void MovingEntity::animate(const Direction &direction)
{
    // Nothing to animate yet.
    bool restart = previousDirection_ != direction;

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

void MovingEntity::reset(const Position &position)
{
    previousDirection_.reset();
    left_.reset();
    setSprite(left_.getSprite()); // default sprite
    setPosition(position); // reset position
    status_ = EntityStatus::VISIBLE;
}
