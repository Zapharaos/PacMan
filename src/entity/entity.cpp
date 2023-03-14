//
// Created by omar on 08/02/23.
//

#include "../../include/entity/entity.h"

#include <utility>

Entity::Entity() = default;

Entity::Entity(Position position, Sprite sprite, bool enabled, int points)
        : position_(move(position)), sprite_(move(sprite)), enabled_(enabled),
          points_(points)
{}

Entity::Entity(Position position, Sprite sprite) : position_(move(position)),
                                                   sprite_(move(sprite))
{}

Entity::Entity(Position position) : position_(move(position))
{}

const Position &Entity::getPosition() const
{
    return position_;
}

void Entity::setPosition(const Position &position)
{
    position_ = position;
}

void Entity::setSprite(const Sprite &sprite)
{
    sprite_ = sprite;
}

int Entity::getPoints() const
{
    return points_;
}

void Entity::setPoints(int points)
{
    points_ = points;
}

bool Entity::isEnabled() const
{
    return enabled_;
}

void Entity::setEnabled(bool enabled)
{
    enabled_ = enabled;
}

const SDL_Rect &Entity::getSpriteImage() const
{
    return sprite_.getImage();
}

const SDL_Rect &Entity::getSpritePosition()
{
    sprite_.updatePosition(position_);
    return sprite_.getPosition();
}

void Entity::count(long cap) {
    counter_.start(cap);
}

bool Entity::countLowerHalf() {
    return counter_.incrementLowerHalf();
}

void Entity::print() const
{
    position_.print();
    cout << "points: " << points_ << ", enabled: " << enabled_ << endl;
}