//
// Created by matthieu on 28/02/2023.
//

#include "../include/movingEntity.h"

MovingEntity::MovingEntity() = default;

MovingEntity::MovingEntity(const pair<int, int> &coordinates, int size, const SDL_Rect &image, int speed) :
        Entity(coordinates, size, image), speed_(speed) {}

MovingEntity::MovingEntity(const pair<int, int> &coordinates, int size, SDL_Rect image, int points, bool isDisabled, int speed,
                           const vector<SDL_Rect> &left, const vector<SDL_Rect> &right, const vector<SDL_Rect> &up, const vector<SDL_Rect> &down) :
                           Entity(coordinates, size, image, points, isDisabled), speed_(speed), left_(left), right_(right), up_(up), down_(down) {}

MovingEntity::MovingEntity(const pair<int, int> &coordinates, int size, SDL_Rect image, int speed, const vector<SDL_Rect> &left,
                           const vector<SDL_Rect> &right, const vector<SDL_Rect> &up, const vector<SDL_Rect> &down) :
                            Entity(coordinates, size, image), speed_(speed), left_(left), right_(right), up_(up), down_(down) {}

directions MovingEntity::getPreviousDirection() const {
    return previous_direction_;
}

bool MovingEntity::isMovingLeftOrUp() const {
    return isMovingLeftOrUp_;
}

std::pair<int, int> MovingEntity::getDestination(directions direction) {
    std::pair<int, int> destination = getCoordinates();
    switch(direction) {
        case LEFT:
            destination.first -= speed_;
            break;
        case RIGHT:
            destination.first += speed_;
            break;
        case UP:
            destination.second -= speed_;
            break;
        case DOWN:
            destination.second += speed_;
            break;
        default:
            break; // nothing to do here
    }
    return destination;
}

bool MovingEntity::move(Map map, directions direction) {

    std::pair<int, int> destination = getDestination(direction);
    bool isMovingLeftOrUp = (direction == LEFT || direction == UP);
    if(!map.canMoveToCell(destination, isMovingLeftOrUp)) return false;

    setCoordinates(map.getDestination());
    previous_direction_ = direction;
    isMovingLeftOrUp_ = isMovingLeftOrUp;

    animate(direction);

    return true;

    /*SDL_Rect image_position = getImagePosition();
    std::cout << "destination => x : " << destination.first << ", y : " << destination.second << std::endl;
    std::cout << "Image => x: " << image.x << ", y: " << image.y << ", w: " << image.w << ", h: " << image.h << std::endl;
    std::cout << "Position => x: " << image_position.x << ", y: " << image_position.y << ", w: " << image_position.w << ", h: " << image_position.h << "\n" << std::endl;*/
}

void MovingEntity::animate(directions direction) {
    SDL_Rect image = getImage();
    std::pair<bool, int> position = previous_imagePosition_;

    switch(direction) {
        case LEFT:
            if(left_.empty()) break; // keep default image
            position = updateImagePosition(direction, left_.size() - 1);
            image = left_.at(position.second);
            break;
        case RIGHT:
            if(right_.empty()) break; // keep default image
            position = updateImagePosition(direction, right_.size() - 1);
            image = right_.at(position.second);
            break;
        case UP:
            if(up_.empty()) break; // keep default image
            position = updateImagePosition(direction, up_.size() - 1);
            image = up_.at(position.second);
            break;
        case DOWN:
            if(down_.empty()) break; // keep default image
            position = updateImagePosition(direction, down_.size() - 1);
            image = down_.at(position.second);
            break;
        default:
            break; // nothing to do here
    }

    if(refreshAnimation_counter_ == refreshAnimation_rate_ || previous_direction_ != direction) // reset
    {
        refreshAnimation_counter_ = 0;
        previous_imagePosition_ = position;
        setImage(image);
    } else
    {
        refreshAnimation_counter_++;
    }

    /*SDL_Rect image_position = getImagePosition();
    std::cout << "destination => x : " << destination.first << ", y : " << destination.second << std::endl;
    std::cout << "Image => x: " << image.x << ", y: " << image.y << ", w: " << image.w << ", h: " << image.h << std::endl;
    std::cout << "Position => x: " << image_position.x << ", y: " << image_position.y << ", w: " << image_position.w << ", h: " << image_position.h << "\n" << std::endl;*/
}

std::pair<bool, int> MovingEntity::updateImagePosition(directions direction, unsigned max_index) {

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
