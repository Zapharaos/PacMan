//
// Created by omar on 08/02/23.
//

#include "../include/entity.h"

#include <utility>

Entity::~Entity() = default;

Entity::Entity()  = default;

Entity::Entity(const pair<int, int> &coordinates, int size, SDL_Rect image, int points, bool isDisabled) :
        coordinates_(coordinates), size_(size), image_(image), points_(points), isDisabled_(isDisabled) {}

Entity::Entity(const pair<int, int> &coordinates, int size, SDL_Rect image) :
        coordinates_(coordinates), size_(size), image_(image) {}

int Entity::getPoints() const {
    return points_;
}

const pair<int, int> &Entity::getCoordinates() const {
    return coordinates_;
}

void Entity::setCoordinates(const pair<int, int> &coordinates) {
    coordinates_ = coordinates;
}

bool Entity::isDisabled() const {
    return isDisabled_;
}

void Entity::setIsDisabled(bool isDisabled) {
    Entity::isDisabled_ = isDisabled;
}

SDL_Rect Entity::getImage() const {
    return image_;
}

void Entity::setImage(const SDL_Rect &image) {
    image_ = image;
}

int Entity::getSize() const {
    return size_;
}

SDL_Rect Entity::getImagePosition() const {
    return {coordinates_.first, coordinates_.second, size_, size_};
}

void Entity::print() const {
    std::cout << "x: " << coordinates_.first << ", y: " << coordinates_.second << ", size: " << size_ << ", points: " << points_ << ", isDisabled: " << isDisabled_ << std::endl;
}
