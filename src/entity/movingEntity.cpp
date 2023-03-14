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

void MovingEntity::move(const Map &map, const Direction &direction)
{
    if(counter_.isActive())
    {
        counter_.increment();
        return;
    }

    // Direction must be initialized.
    if (direction.isUninitialized()) return;

    // Get positions as pixels.
    Position origin = getPosition();
    Position destination = origin.moveIntoDirection(direction, speed_);

    // Checks if the move is legal.
    auto position = map.moveToCell(origin, destination, direction);

    if (!position) return; // Move is illegal.

    // Move is legal : updates the entity.
    animate(direction);
    setPosition(position.value());
    previousDirection_ = direction;
}

Direction MovingEntity::move(const Map &map, const Direction &direction, const Direction &turn)
{

    if(counter_.isActive())
    {
        counter_.increment();
        return direction;
    }

    // Trivial cases that allows an instant direction change.
    if (direction.isUninitialized() || direction == turn || direction.isSameAxis(turn))
    {
        move(map, turn);
        return turn;
    }

    // Get positions as pixels.
    Position origin = getPosition();
    Position destination = origin.moveIntoDirection(direction, speed_);

    // Checks if the turn is legal.
    auto position = map.turnToCell(origin, destination, direction, turn);

    if (!position) // Move is illegal.
    {
        move(map, direction); // Move towards to the original direction.
        return direction;
    }

    // Turn is legal : updates the entity.
    animate(turn);
    setPosition(position.value());
    return (previousDirection_ = turn);
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
}
