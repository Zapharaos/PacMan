//
// Created by omar on 07/02/23.
//

#ifndef PEC_MEN_GHOST_H
#define PEC_MEN_GHOST_H
#include <SDL.h>
#include <string>
#include <iostream>
#include <utility>
#include "constants.h"
#include "entity.h"

using namespace std;

class Ghost : public Entity {

private:
    // all sprites
    SDL_Rect right ;
    SDL_Rect left ;
    SDL_Rect down ;
    SDL_Rect up ;
    SDL_Rect scared ;
    SDL_Rect less_scared ;
    SDL_Rect invis_up ;
    SDL_Rect invis_down ;
    SDL_Rect invis_right ;
    SDL_Rect invis_left ;

    //starting position on pacman_map.txt
    SDL_Rect starting ;     // ici scale x2

    int state;
public:

    Ghost(const SDL_Rect &right, const SDL_Rect &left, const SDL_Rect &down, const SDL_Rect &up, const SDL_Rect &scared,
          const SDL_Rect &lessScared, const SDL_Rect &invisUp, const SDL_Rect &invisDown, const SDL_Rect &invisRight,
          const SDL_Rect &invisLeft, const SDL_Rect &starting, int state);

    [[nodiscard]] const SDL_Rect &getRight() const;

    void setRight(const SDL_Rect &right);

    [[nodiscard]] const SDL_Rect &getLeft() const;

    void setLeft(const SDL_Rect &left);

    [[nodiscard]] const SDL_Rect &getDown() const;

    void setDown(const SDL_Rect &down);

    [[nodiscard]] const SDL_Rect &getUp() const;

    void setUp(const SDL_Rect &up);

    [[nodiscard]] const SDL_Rect &getScared() const;

    void setScared(const SDL_Rect &scared);

    [[nodiscard]] const SDL_Rect &getLessScared() const;

    void setLessScared(const SDL_Rect &lessScared);

    [[nodiscard]] const SDL_Rect &getInvisUp() const;

    void setInvisUp(const SDL_Rect &invisUp);

    [[nodiscard]] const SDL_Rect &getInvisDown() const;

    void setInvisDown(const SDL_Rect &invisDown);

    [[nodiscard]] const SDL_Rect &getInvisRight() const;

    void setInvisRight(const SDL_Rect &invisRight);

    [[nodiscard]] const SDL_Rect &getInvisLeft() const;

    void setInvisLeft(const SDL_Rect &invisLeft);

    [[nodiscard]] const SDL_Rect &getStarting() const;

    void setStarting(const SDL_Rect &starting);

    [[nodiscard]] int getState() const;

    void setState(int state);

    ~Ghost() override;
};


#endif //PEC_MEN_GHOST_H
