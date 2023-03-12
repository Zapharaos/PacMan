//
// Created by omar on 07/02/23.
//

#include "../../include/entity/ghost.h"

Ghost::Ghost(const SDL_Rect &right, const SDL_Rect &left, const SDL_Rect &down,
             const SDL_Rect &up,
             const SDL_Rect &scared, const SDL_Rect &lessScared,
             const SDL_Rect &invisUp, const SDL_Rect &invisDown,
             const SDL_Rect &invisRight, const SDL_Rect &invisLeft,
             const SDL_Rect &starting, int state)
        : right(right), left(left), down(down), up(up), scared(scared),
          less_scared(lessScared), invis_up(invisUp), invis_down(invisDown),
          invis_right(invisRight), invis_left(invisLeft), starting(starting),
          state(state)
{}

const SDL_Rect &Ghost::getRight() const
{
    return right;
}

void Ghost::setRight(const SDL_Rect &right_)
{
    Ghost::right = right_;
}

const SDL_Rect &Ghost::getLeft() const
{
    return left;
}

void Ghost::setLeft(const SDL_Rect &left_)
{
    Ghost::left = left_;
}

const SDL_Rect &Ghost::getDown() const
{
    return down;
}

void Ghost::setDown(const SDL_Rect &down_)
{
    Ghost::down = down_;
}

const SDL_Rect &Ghost::getUp() const
{
    return up;
}

void Ghost::setUp(const SDL_Rect &up_)
{
    Ghost::up = up_;
}

const SDL_Rect &Ghost::getScared() const
{
    return scared;
}

void Ghost::setScared(const SDL_Rect &scared_)
{
    Ghost::scared = scared_;
}

const SDL_Rect &Ghost::getLessScared() const
{
    return less_scared;
}

void Ghost::setLessScared(const SDL_Rect &lessScared)
{
    less_scared = lessScared;
}

const SDL_Rect &Ghost::getInvisUp() const
{
    return invis_up;
}

void Ghost::setInvisUp(const SDL_Rect &invisUp)
{
    invis_up = invisUp;
}

const SDL_Rect &Ghost::getInvisDown() const
{
    return invis_down;
}

void Ghost::setInvisDown(const SDL_Rect &invisDown)
{
    invis_down = invisDown;
}

const SDL_Rect &Ghost::getInvisRight() const
{
    return invis_right;
}

void Ghost::setInvisRight(const SDL_Rect &invisRight)
{
    invis_right = invisRight;
}

const SDL_Rect &Ghost::getInvisLeft() const
{
    return invis_left;
}

void Ghost::setInvisLeft(const SDL_Rect &invisLeft)
{
    invis_left = invisLeft;
}

const SDL_Rect &Ghost::getStarting() const
{
    return starting;
}

void Ghost::setStarting(const SDL_Rect &starting_)
{
    Ghost::starting = starting_;
}


int Ghost::getState() const
{
    return state;
}

void Ghost::setState(int state_)
{
    Ghost::state = state_;
}


