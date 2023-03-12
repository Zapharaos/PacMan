//
// Created by matthieu on 28/02/2023.
//

#include "../../include/entity/movingEntity.h"

MovingEntity::MovingEntity() = default;

MovingEntity::MovingEntity(const Position &position, Sprite sprite,
                           bool enabled, int points, int speed,
                           const vector<Sprite> &left,
                           const vector<Sprite> &right,
                           const vector<Sprite> &up, const vector<Sprite> &down)
        :
        Entity(position, sprite, enabled, points), speed_(speed), left_(left),
        right_(right), up_(up), down_(down)
{}

MovingEntity::MovingEntity(const Position &position, Sprite sprite, int speed,
                           const vector<Sprite> &left,
                           const vector<Sprite> &right,
                           const vector<Sprite> &up, const vector<Sprite> &down)
        :
        Entity(position, sprite), speed_(speed), left_(left), right_(right),
        up_(up), down_(down)
{}

const Position &MovingEntity::getPosition() const
{
    return Entity::getPosition();
}

void MovingEntity::setPosition(const Position &position)
{
    Entity::setPosition(position);
}

const SDL_Rect &MovingEntity::getSpriteImage() const
{
    return Entity::getSpriteImage();
}

SDL_Rect MovingEntity::getSpritePosition()
{
    return Entity::getSpritePosition();
}

const pair<bool, int> &MovingEntity::getPreviousSpriteIndex() const
{
    return previousSpriteIndex_;
}

void
MovingEntity::setPreviousSpriteIndex(const pair<bool, int> &previousSpriteIndex)
{
    previousSpriteIndex_ = previousSpriteIndex;
}

void MovingEntity::move(Map map, Direction direction)
{

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

Direction MovingEntity::move(Map map, Direction direction, Direction turn)
{

    // Trivial cases that allows an instant direction change.
    if (direction.isUninitialized() || direction.isEqual(turn) ||
        direction.isSameAxis(turn))
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

void MovingEntity::animate(Direction direction)
{

    // Nothing to animate yet.
    if (ticksCount_ != tickRate_ && previousDirection_.isEqual(direction))
    {
        ticksCount_++;
        return;
    }

    Sprite sprite = getSprite();
    pair<bool, int> position = previousSpriteIndex_; // default : same sprite

    // Gets the new sprite.
    if (!left_.empty() && direction.isLeft())
    {
        position = getCurrentSprite(direction, left_.size() - 1);
        sprite = left_.at(position.second);
    } else if (!right_.empty() && direction.isRight())
    {
        position = getCurrentSprite(direction, right_.size() - 1);
        sprite = right_.at(position.second);
    } else if (!up_.empty() && direction.isUp())
    {
        position = getCurrentSprite(direction, up_.size() - 1);
        sprite = up_.at(position.second);
    } else if (!down_.empty() && direction.isDown())
    {
        position = getCurrentSprite(direction, down_.size() - 1);
        sprite = down_.at(position.second);
    }

    // Updates the display.
    ticksCount_ = 0;
    previousSpriteIndex_ = position;
    setSprite(sprite);
}

pair<bool, int>
MovingEntity::getCurrentSprite(Direction direction, unsigned max_index)
{

    if (!previousDirection_.isEqual(direction)) // direction changed => reset
        return {true, 0};

    if (ticksCount_ != tickRate_) // no changes
        return previousSpriteIndex_;

    if (max_index == 0) // only one image for this direction
        return {true, 0};

    bool toRight = previousSpriteIndex_.first; // is moving from start to end
    int index = previousSpriteIndex_.second; // previous sprite index

    if (toRight)
    {
        // at end, switch to backward movement inside images
        if (index >= max_index)
            return {false, index - 1};
        return {toRight, index + 1}; // keep moving towards the end
    }

    // at start, switch to forward movement inside images
    if (index == 0)
        return {true, index + 1};
    return {toRight, index - 1}; // keep moving towards the start
}

void MovingEntity::reset(Position position)
{
    setSprite(left_.at(1)); // default sprite
    setPosition(position); // reset position
    previousSpriteIndex_ = {true, 0};
    ticksCount_ = 0;
    previousDirection_.reset();
}
