//
// Created by omar on 07/03/23.
//


#include "../../include/utils/utils.h"

void  utils::spriteRender(SDL_Rect src, SDL_Rect dest, bool flag, SDL_Surface planche, SDL_Surface win_surface) {
    SDL_SetColorKey (&planche,flag,0);
    SDL_BlitScaled(&planche,
                   &src,
                   &win_surface,
                   &dest
            );
}
