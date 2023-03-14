//
// Created by matthieu on 28/02/2023.
//

#include "../../include/entity/pacman.h"

#include <utility>

Pacman::Pacman() = default;

Pacman::Pacman(const Position &position, const Sprite &sprite, int speed,
               const Animation &left, const Animation &right,
               const Animation &up, const Animation &down, long time,
               Animation death) : MovingEntity(position, sprite,
                                                           speed, left, right,
                                                           up, down),
                                              timer_(time), death_(std::move(death))
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
}

void Pacman::animateDeath()
{

    if (death_.isOver())
    { // end of animation
        setDead(false);
        death_.reset();
        return;
    }

    // Updates sprite.
    setSprite(death_.animate());
}

void Pacman::reset(const Position &coordinates)
{
    MovingEntity::reset(coordinates);
    timer_.kill();
    superpower_ = false;
    dead_ = false;
}
