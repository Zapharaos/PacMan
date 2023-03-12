//
// Created by matthieu on 28/02/2023.
//

#include "../../include/entity/pacman.h"

Pacman::Pacman() = default;

Pacman::Pacman(const Position &position, const Sprite &sprite, int speed,
               const vector<Sprite> &left, const vector<Sprite> &right,
               const vector<Sprite> &up, const vector<Sprite> &down, long time,
               const vector<Sprite> &death) : MovingEntity(position, sprite,
                                                           speed, left, right,
                                                           up, down),
                                              timer_(time), death_(death)
{}

void Pacman::setSuperpower(bool superpower)
{
    if ((superpower_ = superpower))
    {
        timer_.kill(); // stop previous superpower if still running
        timer_.start([&]() {
            setSuperpower(false);
        }); // only activating superpower mode for a specific time
    }
}

bool Pacman::isSuperpower()
{
    timer_.setMutexLock(true);
    bool result = superpower_;
    timer_.setMutexLock(false);
    return result;
}

bool Pacman::isDead() const
{
    return dead_;
}

void Pacman::setDead(bool dead)
{
    Pacman::dead_ = dead;
    setPreviousSpriteIndex({true, 0});
}

const Position &Pacman::getPosition() const
{
    return MovingEntity::getPosition();
}

const Sprite &Pacman::getSprite() const
{
    return Entity::getSprite();
}

const SDL_Rect &Pacman::getSpritePosition()
{
    return MovingEntity::getSpritePosition();
}

const SDL_Rect &Pacman::getSpriteImage() const
{
    return MovingEntity::getSpriteImage();
}

const pair<bool, int> &Pacman::getPreviousSpriteIndex() const
{
    return MovingEntity::getPreviousSpriteIndex();
}

void Pacman::setPreviousSpriteIndex(const pair<bool, int> &previousSpriteIndex)
{
    MovingEntity::setPreviousSpriteIndex(previousSpriteIndex);
}

void Pacman::move(const Map &map, const Direction &continuous_direction)
{
    MovingEntity::move(map, continuous_direction);
}

Direction Pacman::move(const Map &map, const Direction &continuous_direction,
                       const Direction &try_direction)
{
    return MovingEntity::move(map, continuous_direction, try_direction);
}

void Pacman::animateDeath()
{

    pair<bool, int> position = getPreviousSpriteIndex();

    if (position.second == death_.size())
    { // end of animation
        setDead(false);
        return;
    }

    // Updates sprite.
    setSprite(death_.at(position.second));
    position.second++;
    setPreviousSpriteIndex(position);
}

void Pacman::reset(const Position &coordinates)
{
    MovingEntity::reset(coordinates);
    timer_.kill();
}
