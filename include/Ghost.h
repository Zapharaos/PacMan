//
// Created by omar on 07/02/23.
//

#ifndef PEC_MEN_GHOST_H
#define PEC_MEN_GHOST_H
#include <SDL.h>
#include <string>
#include <iostream>
#include <utility>

// Ghost states
#define DEFAULT 0
#define SCARED 1
#define LESSSCARED 2
#define INVISIBLE 3

class Ghost {
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

    //starting position on map
    SDL_Rect starting ;     // ici scale x2

    pair<int, int> coo;

    string name ;
    int State ;




};


#endif //PEC_MEN_GHOST_H
