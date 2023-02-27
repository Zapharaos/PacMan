//
// Created by omar on 08/02/23.
//

#include "../include/entity.h"

#include <utility>



const pair<int, int> &Entity::getCoordinates() const {
    return coordinates_;
}

void Entity::setCoordinates(const pair<int, int> &coordinates) {
    coordinates_ = coordinates;
}

Entity::Entity(const pair<int, int> &coordinates, int size, string name, int points) :
    coordinates_(coordinates), size_(size), name_(std::move(name)), points_(points) {}



Entity::Entity()  = default;

Entity::Entity(const pair<int, int> &coordinates, string name) : coordinates_(coordinates), name_(std::move(name)) {}

Entity::Entity(string name, int points) : name_(std::move(name)), points_(points) {}

bool Entity::hasCollided(const Entity& entity) const {
    /*std::cout << "e.x : " << entity.coordinates_.first << ", e.x.max : " << entity.coordinates_.first + entity.size_ << std::endl;
    std::cout << "e.y : " << entity.coordinates_.second << ", e.y.max : " << entity.coordinates_.second + entity.size_ << std::endl;
    std::cout << "p.x : " << this->coordinates_.first << ", p.x.max : " << this->coordinates_.first + this->size_ << std::endl;
    std::cout << "p.y : " << this->coordinates_.second << ", p.y.max : " << this->coordinates_.second + this->size_ << "\n" << std::endl;*/
    if(entity.coordinates_.first <= this->coordinates_.first &&
        this->coordinates_.first <= entity.coordinates_.first + entity.size_ ||
        entity.coordinates_.second <= this->coordinates_.second &&
        this->coordinates_.second <= entity.coordinates_.second + entity.size_ ||
            this->coordinates_.first <= entity.coordinates_.first &&
            entity.coordinates_.first <= this->coordinates_.first + this->size_ ||
            this->coordinates_.second <= entity.coordinates_.second &&
            entity.coordinates_.second <= this->coordinates_.second + this->size_)
        return true;
    return false;
}

void Entity::print() const {
    std::cout << "x: " << coordinates_.first << ", y: " << coordinates_.second << ", size: " << size_ << ", points: " << points_ << ", isDisabled: " << isDisabled_ << std::endl;
}

int Entity::getPoints() const {
    return points_;
}

bool Entity::isDisabled() const {
    return isDisabled_;
}

void Entity::setIsDisabled(bool isDisabled) {
    Entity::isDisabled_ = isDisabled;
}

Entity::~Entity() = default;
