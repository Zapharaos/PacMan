//
// Created by matthieu on 01/03/2023.
//

#include "../include/sprite.h"

Sprite::Sprite() = default;

Sprite::Sprite(const SDL_Rect &image, const SDL_Rect &offset) : image_(image), offset_(offset) {}

const SDL_Rect &Sprite::getImage() const {
    return image_;
}

const SDL_Rect &Sprite::getOffset() const {
    return offset_;
}
