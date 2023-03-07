//
// Created by matthieu on 28/02/2023.
//

#include "../../include/entity/movingEntity.h"

MovingEntity::MovingEntity() = default;

MovingEntity::MovingEntity(Sprite sprite, int points, bool isDisabled, int speed, const pair<int, int> &coordinates,
                           const vector<Sprite> &left, const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down) :
                           Entity(sprite, points, isDisabled), speed_(speed), coordinates_(coordinates), left_(left), right_(right), up_(up), down_(down) {
    Entity::setSpriteCoordinates(coordinates);
}

MovingEntity::MovingEntity(Sprite sprite, int speed, const pair<int, int> &coordinates, const vector<Sprite> &left,
                           const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down) :
                            Entity(sprite), speed_(speed), coordinates_(coordinates), left_(left), right_(right), up_(up), down_(down) {
    Entity::setSpriteCoordinates(coordinates);
}

std::pair<int, int> MovingEntity::getDestinationCoordinates(std::pair<int, int> origin, Direction direction) const {
    std::pair<int, int> destination = origin;
    if(direction.isLeft()) destination.first -= speed_;
    else if(direction.isRight()) destination.first += speed_;
    else if(direction.isUp()) destination.second -= speed_;
    else if(direction.isDown()) destination.second += speed_;
    return destination;
}

const pair<int, int> &MovingEntity::getCoordinates() const {
    return coordinates_;
}

void MovingEntity::setCoordinates(const pair<int, int> &coordinates) {
    coordinates_ = coordinates;
    Entity::setSpriteCoordinates(coordinates);
}

bool MovingEntity::isLeftOrUp() const {
    return previous_direction_.isLeftOrUp();
}

const SDL_Rect &MovingEntity::getSpriteImage() const {
    return Entity::getSpriteImage();
}

SDL_Rect MovingEntity::getSpritePosition() const {
    return Entity::getSpritePosition();
}

Direction MovingEntity::move(Map map, Direction direction, Direction turn) {

    std::pair<int, int> origin = getCoordinates();
    std::pair<int, int> destination = getDestinationCoordinates(origin, direction);

    if(direction.isUninitialized() || direction.isEqual(turn) || direction.isSameAxis(turn))
    {
        move(map, turn);
        return turn;
    }

    if(!map.canTurnToCell(origin, destination, direction, turn))
    {
        move(map, direction);
        return direction;
    }

    animate(turn);
    setCoordinates(map.getDestination());
    previous_direction_ = turn;

    return turn;
}

void MovingEntity::move(Map map, Direction direction) {

    if(direction.isUninitialized()) return;

    std::pair<int, int> origin = getCoordinates();
    std::pair<int, int> destination = getDestinationCoordinates(origin, direction);
    if(!map.canMoveToCell(origin, destination, direction)) return;

    animate(direction);
    setCoordinates(map.getDestination());
    previous_direction_ = direction;
}

void MovingEntity::animate(Direction direction) {
    Sprite sprite = getSprite();
    std::pair<bool, int> position = previous_imagePosition_; // default : same sprite

    if(!left_.empty() && direction.isLeft())
    {
        position = getCurrentSprite(direction, left_.size() - 1);
        sprite = left_.at(position.second);
    }
    else if(!right_.empty() && direction.isRight())
    {
        position = getCurrentSprite(direction, right_.size() - 1);
        sprite = right_.at(position.second);
    }
    else if(!up_.empty() && direction.isUp())
    {
        position = getCurrentSprite(direction, up_.size() - 1);
        sprite = up_.at(position.second);
    }
    else if(!down_.empty() && direction.isDown())
    {
        position = getCurrentSprite(direction, down_.size() - 1);
        sprite = down_.at(position.second);
    }

    if(refreshAnimation_counter_ == refreshAnimation_rate_ || !previous_direction_.isEqual(direction)) // reset
    {
        refreshAnimation_counter_ = 0;
        previous_imagePosition_ = position;
        setSprite(sprite);
    } else
    {
        refreshAnimation_counter_++;
    }
}

std::pair<bool, int> MovingEntity::getCurrentSprite(Direction direction, unsigned max_index) {

    if(!previous_direction_.isEqual(direction)) // direction changed => reset
        return {true, 0};

    if(refreshAnimation_counter_ != refreshAnimation_rate_) // no changes
        return previous_imagePosition_;

    if(max_index == 0) // only one image for this direction
        return {true, 0};

    bool toRight = previous_imagePosition_.first; // is moving from start to end
    int index = previous_imagePosition_.second; // previous image index in images

    if(toRight)
    {
        if(index >= max_index) // at end
            return {false, index-1}; // switch to backward movement inside images
        return {toRight, index+1}; // keep moving towards the end
    }

    if(index == 0) // at start
        return {true, index+1}; // switch to forward movement inside images
    return {toRight, index-1}; // keep moving towards the start
}
