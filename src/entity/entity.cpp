//
// Created by omar on 08/02/23.
//

#include "../../include/entity/entity.h"

#include <utility>

Entity::~Entity() = default;

Entity::Entity()  = default;

Entity::Entity(const pair<int, int> &coordinates, int size, Sprite sprite, int points, bool isDisabled) :
        coordinates_(coordinates), size_(size), sprite_(sprite), points_(points), isDisabled_(isDisabled) {}

Entity::Entity(const pair<int, int> &coordinates, int size, Sprite sprite) :
        coordinates_(coordinates), size_(size), sprite_(sprite) {}

int Entity::getPoints() const {
    return points_;
}

void Entity::setPoints(int points) {
    points_ = points;
}

const pair<int, int> &Entity::getCoordinates() const {
    return coordinates_;
}

void Entity::setCoordinates(const pair<int, int> &coordinates) {
    coordinates_ = coordinates;
}

int Entity::getSize() const {
    return size_;
}

bool Entity::isDisabled() const {
    return isDisabled_;
}

void Entity::setIsDisabled(bool isDisabled) {
    Entity::isDisabled_ = isDisabled;
}

Sprite Entity::getSprite() const {
    return sprite_;
}

void Entity::setSprite(const Sprite &sprite) {
    sprite_ = sprite;
}

SDL_Rect Entity::getImagePosition() const {
    auto offset = getSprite().getOffset();
    return {coordinates_.first + offset.x, coordinates_.second + offset.y,
            (offset.w == 0 ? size_ : offset.w), (offset.h == 0 ? size_ : offset.h)};
}

void Entity::print() const {
    std::cout << "x: " << coordinates_.first << ", y: " << coordinates_.second << ", size: " << size_ << ", points: " << points_ << ", isDisabled: " << isDisabled_ << std::endl;
}
