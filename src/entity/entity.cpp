//
// Created by omar on 08/02/23.
//

#include "../../include/entity/entity.h"

#include <utility>

Entity::~Entity() = default;

Entity::Entity()  = default;

Entity::Entity(Sprite sprite, int points, bool isDisabled) : sprite_(sprite), points_(points), isDisabled_(isDisabled) {}

Entity::Entity(Sprite sprite) : sprite_(sprite) {}

int Entity::getPoints() const {
    return points_;
}

void Entity::setPoints(int points) {
    points_ = points;
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

SDL_Rect Entity::getSpritePosition() const {
    return sprite_.getPosition();
}

SDL_Rect Entity::getSpritePosition(std::pair<int, int> coordinates) const {
    return sprite_.getPosition(coordinates);
}


const SDL_Rect &Entity::getSpriteImage() const {
    return sprite_.getImage();
}

void Entity::print() const {
    std::cout << "points: " << points_ << ", isDisabled: " << isDisabled_ << std::endl;
}