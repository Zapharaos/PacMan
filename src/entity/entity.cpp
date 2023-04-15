/**
 * @file entity.cpp
 * @brief Implements the Entity class, an object located on the map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 08/02/2023
*/

#include "../../include/entity/entity.h"

Entity::Entity() = default;

Entity::Entity(Position position) : position_(std::move(position))
{
    sprite_.updatePosition(position_);
}

Entity::Entity(Position position, Sprite sprite) : position_(
        std::move(position)),
                                                   sprite_(std::move(sprite))
{
    sprite_.updatePosition(position_);
}

Entity::Entity(Position position, Sprite sprite, bool enabled, int points)
        : position_(std::move(position)), sprite_(std::move(sprite)),
          enabled_(enabled),
          points_(points)
{
    sprite_.updatePosition(position_);
}

Entity::Entity(Position position, Sprite sprite, bool enabled, int points,
               unsigned long blinking_ticks)
        : position_(std::move(position)), sprite_(std::move(sprite)),
          enabled_(enabled),
          points_(points)
{
    sprite_.updatePosition(position_);
    if (blinking_ticks != 0)
    {
        status_counter_.start(blinking_ticks);
        blinking_ = true;
    }
}

bool Entity::isEnabled() const
{
    return enabled_;
}

void Entity::setEnabled(bool enabled)
{
    enabled_ = enabled;
}

const Position &Entity::getPosition() const
{
    return position_;
}

void Entity::setPosition(const Position &position)
{
    position_ = position;
    sprite_.updatePosition(position_);
}

int Entity::getSize() const
{
    return size_;
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

void Entity::hide()
{
    status_ = EntityStatus::kHidden;
}

void Entity::show()
{
    status_ = EntityStatus::kShown;
}

void Entity::showTimed(unsigned long ticks)
{
    if (ticks == 0) return;
    setEnabled(true);
    status_counter_.start(ticks);
    status_ = EntityStatus::kShownTimed;
}

void Entity::kill()
{
    status_ = EntityStatus::kDead;
}

void Entity::freeze(unsigned long ticks)
{
    status_ = EntityStatus::kFrozen;
    if (ticks != 0)
        status_counter_.start(ticks);
}

bool Entity::isShown() const
{
    return status_ == EntityStatus::kShown;
}

bool Entity::isHidden() const
{
    return status_ == EntityStatus::kHidden;
}

bool Entity::isDead() const
{
    return status_ == EntityStatus::kDead;
}

void Entity::handleStatus()
{
    // Changes ongoing.
    if (status_counter_.isActive())
    {
        status_counter_.increment();
        return;
    }

    if (status_ == EntityStatus::kShownTimed)
    {
        setEnabled(false);
        return;
    }

    // Switch between hidden and shown.
    if (blinking_)
    {
        isShown() ? hide() : show();
        status_counter_.increment(); // restart status_counter (i.e. blinking).
        return;
    }

    // Reset visibility.
    if (isHidden())
        show();
}

void Entity::tick()
{
    handleStatus();
}