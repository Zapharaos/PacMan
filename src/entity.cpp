//
// Created by omar on 08/02/23.
//

#include "../include/entity.h"

#include <utility>

Entity::~Entity() = default;

Entity::Entity()  = default;

Entity::Entity(const pair<int, int> &coordinates, int size, int points, bool isDisabled, SDL_Rect image) :
        coordinates_(coordinates), size_(size), points_(points), isDisabled_(isDisabled), image_(image) {}

Entity::Entity(const pair<int, int> &coordinates, int size, int points) :
        coordinates_(coordinates), size_(size), points_(points) {}

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

bool Entity::hasCollided(directions direction, const Entity& entity) const {
    /*std::cout << "e.x : " << entity.coordinates_.first << ", e.x.max : " << entity.coordinates_.first + entity.size_ << std::endl;
    std::cout << "e.y : " << entity.coordinates_.second << ", e.y.max : " << entity.coordinates_.second + entity.size_ << std::endl;
    std::cout << "p.x : " << this->coordinates_.first << ", p.x.max : " << this->coordinates_.first + this->size_ << std::endl;
    std::cout << "p.y : " << this->coordinates_.second << ", p.y.max : " << this->coordinates_.second + this->size_ << "\n" << std::endl;*/
    switch (direction) {
        case LEFT:
            return (entity.coordinates_.first <= this->coordinates_.first &&
               this->coordinates_.first <= entity.coordinates_.first + entity.size_);
        case RIGHT:
            return (this->coordinates_.first <= entity.coordinates_.first &&
                    entity.coordinates_.first <= this->coordinates_.first + this->size_);
        case UP:
            return (entity.coordinates_.second <= this->coordinates_.second &&
                    this->coordinates_.second <= entity.coordinates_.second + entity.size_);
        case DOWN:
            return (this->coordinates_.second <= entity.coordinates_.second &&
                    entity.coordinates_.second <= this->coordinates_.second + this->size_);
        default:
            return false;
    }
}

SDL_Rect Entity::getImagePosition() const {
    return {coordinates_.first, coordinates_.second, size_, size_};
}

void Entity::print() const {
    std::cout << "x: " << coordinates_.first << ", y: " << coordinates_.second << ", size: " << size_ << ", points: " << points_ << ", isDisabled: " << isDisabled_ << std::endl;
}
