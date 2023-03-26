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

std::pair<int, int> Entity::getSpriteSize() const
{
    auto sprite_position = getSpritePosition();
    return {sprite_position.w, sprite_position.h};
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
    status_ = EntityStatus::kHidden;
}

void Entity::show()
{
    status_ = EntityStatus::kVisible;
}

bool Entity::isVisible()
{
    return status_ == EntityStatus::kVisible;
}

void Entity::print() const
{
    position_.print();
    std::cout << "points: " << points_ << ", enabled: " << enabled_ << std::endl;
}
