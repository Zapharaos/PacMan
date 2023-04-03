/**
 * @file pacman.cpp
 * @brief Implements the Pacman class, which is the main entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 28/02/2023
*/

#include "../../include/entity/pacman.h"

Pacman::Pacman() :
               MovingEntity(Position{{config::positions::kPacmanX, config::positions::kPacmanY}},
                            config::settings::kSpeedPacman,
                            visuals::pacman::left::kAnimation,
                            visuals::pacman::right::kAnimation,
                            visuals::pacman::up::kAnimation,
                            visuals::pacman::down::kAnimation)
{
    death_ = visuals::pacman::death::kAnimation;
}

void Pacman::setSuperpower(bool superpower)
{
    if ((superpower_ = superpower))
        count_superpower_.start(config::settings::kDurationSuperpower);
}

bool Pacman::isSuperpower() const
{
    return superpower_;
}

void Pacman::tick(const Map &map, Direction direction)
{
    if(isSuperpower())
    {
        if(count_superpower_.isActive())
            count_superpower_.increment();
        else
            setSuperpower(false);
    }

    MovingEntity::tick(map, direction);
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
    superpower_ = false;
    dead_ = false;
}
