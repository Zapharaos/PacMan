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

const string &Entity::getName() const {
    return name_;
}

void Entity::setName(const string &name) {
    name_ = name;
}

Entity::Entity(const pair<int, int> &coordinates, string name, int points) : coordinates_(coordinates),
                                                                                    name_(std::move(name)), points(points) {}

int Entity::getPoints() const {
    return points;
}

void Entity::setPoints(int points_) {
    Entity::points = points_;
}



Entity::Entity()  {}

Entity::Entity(const pair<int, int> &coordinates, string name) : coordinates_(coordinates), name_(std::move(name)) {}

Entity::Entity(string name, int points) : name_(std::move(name)), points(points) {}

Entity::~Entity() = default;
