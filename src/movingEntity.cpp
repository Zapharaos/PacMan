//
// Created by matthieu on 28/02/2023.
//

#include "../include/movingEntity.h"

movingEntity::movingEntity(const pair<int, int> &coordinates, int size, int points, bool isDisabled, int speed,
                           const vector<SDL_Rect> &left, const vector<SDL_Rect> &right, const vector<SDL_Rect> &up,
                           const vector<SDL_Rect> &down) :
    Entity(coordinates, size, points, isDisabled), speed_(speed), left_(left), right_(right), up_(up), down_(down) {}

movingEntity::movingEntity(const pair<int, int> &coordinates, int size, int speed, const vector<SDL_Rect> &left,
                           const vector<SDL_Rect> &right, const vector<SDL_Rect> &up, const vector<SDL_Rect> &down) :
    Entity(coordinates, size), speed_(speed), left_(left), right_(right), up_(up), down_(down) {}

void movingEntity::move(Map map, directions direction) {

    std::pair<int, int> destination = getCoordinates();
    bool isMovingLeftOrUp = false;
    SDL_Rect image;
    std::pair<bool, int> position;

    switch(direction) {
        case LEFT:
            destination.first -= constants::SPEED_PACMAN;
            isMovingLeftOrUp = true;
            position = updateNextImage(direction, left_.size() - 1);
            image = left_.at(position.second);
            break;
        case RIGHT:
            destination.first += constants::SPEED_PACMAN;
            position = updateNextImage(direction, right_.size() - 1);
            image = right_.at(position.second);
            break;
        case UP:
            destination.second -= constants::SPEED_PACMAN;
            isMovingLeftOrUp = true;
            position = updateNextImage(direction, up_.size() - 1);
            image = up_.at(position.second);
            break;
        case DOWN:
            destination.second += constants::SPEED_PACMAN;
            position = updateNextImage(direction, down_.size() - 1);
            image = down_.at(position.second);
            break;
        default:
            return; // nothing to do here
    }

    if(!map.canMoveToCell(destination, isMovingLeftOrUp)) return;

    setImage(image);
    setCoordinates(map.getDestination());
    previous_direction_ = direction;
    previous_imagePosition_ = position;
}

std::pair<bool, int> movingEntity::updateNextImage(directions direction, unsigned last_index) {

    if(previous_direction_ != direction) // direction changed => reset
        return {true, 0};

    bool toLeft = previous_imagePosition_.first; // moving from start to end
    int index = previous_imagePosition_.second; // previous image index in images

    if(toLeft)
    {
        if(index == last_index) // end
            return {false, index--}; // switch to backward movement inside images
        return {toLeft, index++};
    }

    if(index == 0) // start
        return {true, index++}; // switch to forward movement inside images
    return {toLeft, index--};
}
