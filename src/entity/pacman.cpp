/**
 * @file pacman.cpp
 * @brief Implements the Pacman class, which is the main entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 28/02/2023
*/

#include "../../include/entity/pacman.h"

#include "../../include/config/visuals.h"

Pacman::Pacman() :
               MovingEntity(Position{{config::positions::kPacmanX, config::positions::kPacmanY}},
                            config::settings::kSpeedPacman,
                            visuals::pacman::left::kAnimation,
                            visuals::pacman::right::kAnimation,
                            visuals::pacman::up::kAnimation,
                            visuals::pacman::down::kAnimation)
{
    timer_ = Timer(config::settings::kDurationSuperpower);
    death_ = visuals::pacman::death::kAnimation;
}

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

    if(!isDead()) return;

    // Updates sprite.
    setSprite(death_.animate());

    // Animation is over.
    if (death_.isOver())
    {
        setDead(false);
        death_.reset();
        hide();
    }
}

void Pacman::reset(const Position &coordinates)
{
    MovingEntity::reset(coordinates);
    timer_.kill();
    superpower_ = false;
    dead_ = false;
}
