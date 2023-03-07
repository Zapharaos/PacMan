//
// Created by omar on 07/03/23.
//

#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H


#include <SDL_rect.h>
#include <SDL_surface.h>

class utils {
public:
    void static spriteRender(SDL_Rect src, SDL_Rect dest, bool flag, SDL_Surface planche, SDL_Surface win_surface);
};


#endif //PACMAN_UTILS_H
