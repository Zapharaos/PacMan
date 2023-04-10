/**
 * @file entity.h
 * @brief Implements the Entity class, an object located on the map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 08/02/2023
*/

#include "../../include/entity/entity.h"

Entity::Entity() = default;

Entity::Entity(Position position, Sprite sprite, bool enabled, int points)
        : position_(std::move(position)), sprite_(std::move(sprite)), enabled_(enabled),
          points_(points)
{ sprite_.updatePosition(position_); }

Entity::Entity(Position position, Sprite sprite) : position_(std::move(position)),
                                                   sprite_(std::move(sprite))
{ sprite_.updatePosition(position_); }

Entity::Entity(Position position) : position_(std::move(position))
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

const Sprite &Entity::getSprite() const
{
    return sprite_;
}

void Entity::setSprite(const Sprite &sprite)
{
    sprite_ = sprite;
    sprite_.updatePosition(position_);
}

unsigned long Entity::getPoints() const
{
    return points_;
}

void Entity::setPoints(unsigned long points)
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

void Entity::count(long frames) {
    counter_.start(frames);
}

bool Entity::isCounterActive() const {
    return counter_.isActive();
}

void Entity::counterIncrement() {
    counter_.increment();
}

bool Entity::tickVisibility() {

    if(!counter_.isActive())
        isVisible() ? hide() : show();

    counter_.increment();
    return isVisible();
}

void Entity::hide()
{
    status_ = EntityStatus::kHidden;
}

void Entity::show()
{
    status_ = EntityStatus::kVisible;
}

void Entity::kill()
{
    status_ = EntityStatus::kDead;
}

void Entity::freeze()
{
    status_ = EntityStatus::kFrozen;
}

bool Entity::isVisible()
{
    return status_ == EntityStatus::kVisible;
}

bool Entity::isHidden()
{
    return status_ == EntityStatus::kHidden;
}

bool Entity::isDead()
{
    return status_ == EntityStatus::kDead;
}
