//
// Created by matthieu on 01/03/2023.
//

#ifndef PACMAN_SPRITE_H
#define PACMAN_SPRITE_H


#include <SDL_rect.h>

class Sprite {
public:
    Sprite();
    Sprite(const SDL_Rect &image, const SDL_Rect &offset);

    [[nodiscard]] const SDL_Rect &getImage() const;
    [[nodiscard]] const SDL_Rect &getOffset() const;

private:
    SDL_Rect image_ {};
    SDL_Rect offset_ {};

};


#endif //PACMAN_SPRITE_H
