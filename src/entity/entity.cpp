//
// Created by omar on 08/02/23.
//

#include "../../include/entity/entity.h"

#include <utility>

Entity::Entity() = default;

Entity::Entity(Position position, Sprite sprite, bool enabled, int points)
        : position_(move(position)), sprite_(move(sprite)), enabled_(enabled),
          points_(points)
{ sprite_.updatePosition(position_); }

Entity::Entity(Position position, Sprite sprite) : position_(move(position)),
                                                   sprite_(move(sprite))
{ sprite_.updatePosition(position_); }

Entity::Entity(Position position) : position_(move(position))
{ sprite_.updatePosition(position_); }

const Position &Entity::getPosition() const
{
    return position_;
}

void Entity::setPosition(const Position &position)
{
    position_ = position;
    sprite_.updatePosition(position_);
}

void Entity::setSprite(const Sprite &sprite)
{
    sprite_ = sprite;
    sprite_.updatePosition(position_);
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

const SDL_Rect &Entity::getSpritePosition() const
{
    return sprite_.getPosition();
}

void Entity::count(long frames) {
    counter_.start(frames);
}

bool Entity::tickVisibility() {

    if(!counter_.isActive())
        isVisible() ? hide() : show();

    counter_.increment();
    return isVisible();
}

void Entity::hide()
{
    status_ = EntityStatus::HIDDEN;
}

void Entity::show()
{
    status_ = EntityStatus::VISIBLE;
}

bool Entity::isVisible()
{
    return status_ == EntityStatus::VISIBLE;
}

void Entity::print() const
{
    position_.print();
    cout << "points: " << points_ << ", enabled: " << enabled_ << endl;
}
