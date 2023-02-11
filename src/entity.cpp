//
// Created by omar on 08/02/23.
//

#include "../include/entity.h"

#include <utility>

Entity::Entity(const pair<int, int> &coordinates, string name) : coordinates_(coordinates), name_(std::move(name)) {}

pair<int, int> &Entity::getCoordinates() {
    return coordinates_;
}

void Entity::setCoordinates(pair<int, int> &coordinates) {
    Entity::coordinates_ = coordinates;
}

Entity::Entity() = default;
