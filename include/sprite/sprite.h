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
    Sprite(const SDL_Rect &image, const SDL_Rect &offset, std::pair<int, int> coordinates);

    [[nodiscard]] const SDL_Rect &getImage() const;
    [[nodiscard]] const SDL_Rect &getPosition() const;
    [[nodiscard]] SDL_Rect getPosition(std::pair<int, int> coordinates) const;

private:
    SDL_Rect image_ {};
    SDL_Rect offset_ {};
    SDL_Rect position_ {};
};


#endif //PACMAN_SPRITE_H
