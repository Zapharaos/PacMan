/**
 * @file pacman.cpp
 * @brief Implements the Pacman class, which is the main entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 28/02/2023
*/

#include "../../include/entity/pacman.h"

Pacman::Pacman() :
               MovingEntity(Position{config::positions::entities::kPacmanX, config::positions::entities::kPacmanY},
                            config::settings::kSpeedPacman,
                            visuals::pacman::left::kAnimation,
                            visuals::pacman::right::kAnimation,
                            visuals::pacman::up::kAnimation,
                            visuals::pacman::down::kAnimation)
{
    death_ = visuals::pacman::death::kAnimation;
}

void Pacman::death()
{

    // Updates sprite.
    setSprite(death_.animate());

    // Animation is over.
    if (death_.isOver())
    {
        death_.reset();
        hide();
    }
}
