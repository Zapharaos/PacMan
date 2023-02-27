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
    if(entity.coordinates_.first <= this->coordinates_.first &&
        this->coordinates_.first <= entity.coordinates_.first + entity.size_ &&
        entity.coordinates_.second <= this->coordinates_.second &&
        this->coordinates_.second <= entity.coordinates_.second + entity.size_)
        return true;
    return false;
}

void Entity::print() const {
    std::cout << "x: " << coordinates_.first << ", y: " << coordinates_.second << ", size: " << size_ << ", points: " << points_ << std::endl;
}

int Entity::getPoints() const {
    return points_;
}

Entity::~Entity() = default;
