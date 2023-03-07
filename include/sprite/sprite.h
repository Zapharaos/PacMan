//
// Created by matthieu on 01/03/2023.
//

#ifndef PACMAN_SPRITE_H
#define PACMAN_SPRITE_H


#include <SDL_rect.h>

class Sprite {
public:
    Sprite();
    Sprite(const SDL_Rect &image, std::pair<int, int> offset, std::pair<int, int> size);
    Sprite(const SDL_Rect &image, std::pair<int, int> offset, std::pair<int, int> size, std::pair<int, int> coordinates);

    [[nodiscard]] const SDL_Rect &getImage() const;
    [[nodiscard]] const SDL_Rect &getPosition() const;
    void setCoordinates(const std::pair<int, int> &coordinates);

private:
    SDL_Rect image_ {};
    SDL_Rect position_ {};
    std::pair<int, int> offset_ {};
    std::pair<int, int> size_ {};
    std::pair<int, int> coordinates_ {};

    void updatePosition();
};


#endif //PACMAN_SPRITE_H
