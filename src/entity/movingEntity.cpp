//
// Created by matthieu on 28/02/2023.
//

#include "../../include/entity/movingEntity.h"

MovingEntity::MovingEntity() = default;

MovingEntity::MovingEntity(const pair<int, int> &coordinates, int size, Sprite sprite, int points, bool isDisabled, int speed,
                           const vector<Sprite> &left, const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down) :
                           Entity(coordinates, size, sprite, points, isDisabled), speed_(speed), left_(left), right_(right), up_(up), down_(down) {}

MovingEntity::MovingEntity(const pair<int, int> &coordinates, int size, Sprite sprite, int speed, const vector<Sprite> &left,
                           const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down) :
                            Entity(coordinates, size, sprite), speed_(speed), left_(left), right_(right), up_(up), down_(down) {}

Direction MovingEntity::getPreviousDirection() const {
    return previous_direction_;
}

bool MovingEntity::isMovingLeftOrUp() const {
    return isMovingLeftOrUp_;
}

std::pair<int, int> MovingEntity::getDestination(std::pair<int, int> origin, Direction direction) const {
    std::pair<int, int> destination = origin;
    switch(direction) {
        case Direction::LEFT:
            destination.first -= speed_;
            break;
        case Direction::RIGHT:
            destination.first += speed_;
            break;
        case Direction::UP:
            destination.second -= speed_;
            break;
        case Direction::DOWN:
            destination.second += speed_;
            break;
        default:
            break; // nothing to do here
    }
    return destination;
}

Direction MovingEntity::move(Map map, Direction direction, Direction turn) {

    std::pair<int, int> origin = getCoordinates();
    std::pair<int, int> destination = getDestination(origin, direction);

    if(direction == Direction::NONE || areDirectionsOpposite(direction, turn))
    {
        move(map, turn);
        return turn;
    }

    if(areDirectionsEqual(direction, turn) || !map.canTurnToCell(origin, destination, direction, turn))
    {
        move(map, direction);
        return direction;
    }

    animate(turn);
    setCoordinates(map.getDestination());
    previous_direction_ = turn;
    isMovingLeftOrUp_ = (turn == Direction::LEFT || turn == Direction::UP);

    return turn;
}

void MovingEntity::move(Map map, Direction direction) {

    if(direction == Direction::NONE) return;

    std::pair<int, int> origin = getCoordinates();
    std::pair<int, int> destination = getDestination(origin, direction);
    if(!map.canMoveToCell(origin, destination, direction)) return;

    animate(direction);
    setCoordinates(map.getDestination());
    previous_direction_ = direction;
    isMovingLeftOrUp_ = (direction == Direction::LEFT || direction == Direction::UP);
}

void MovingEntity::animate(Direction direction) {
    Sprite sprite = getSprite();
    std::pair<bool, int> position = previous_imagePosition_;

    switch(direction) {
        case Direction::LEFT:
            if(left_.empty()) break; // keep default image
            position = updateImagePosition(direction, left_.size() - 1);
            sprite = left_.at(position.second);
            break;
        case Direction::RIGHT:
            if(right_.empty()) break; // keep default image
            position = updateImagePosition(direction, right_.size() - 1);
            sprite = right_.at(position.second);
            break;
        case Direction::UP:
            if(up_.empty()) break; // keep default image
            position = updateImagePosition(direction, up_.size() - 1);
            sprite = up_.at(position.second);
            break;
        case Direction::DOWN:
            if(down_.empty()) break; // keep default image
            position = updateImagePosition(direction, down_.size() - 1);
            sprite = down_.at(position.second);
            break;
        default:
            break; // nothing to do here
    }

    if(refreshAnimation_counter_ == refreshAnimation_rate_ || previous_direction_ != direction) // reset
    {
        refreshAnimation_counter_ = 0;
        previous_imagePosition_ = position;
        setSprite(sprite);
    } else
    {
        refreshAnimation_counter_++;
    }
}

std::pair<bool, int> MovingEntity::updateImagePosition(Direction direction, unsigned max_index) {

    if(previous_direction_ != direction) // direction changed => reset
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
