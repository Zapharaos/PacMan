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

Entity::Entity() {

}

Entity::Entity(const pair<int, int> &coordinates, const string &name) :
coordinates_(coordinates) ,name_(name) {

}

Entity::~Entity() {

}
