//
// Created by matthieu on 01/03/2023.
//

#include "../../include/sprite/sprite.h"

Sprite::Sprite() = default;

Sprite::Sprite(const SDL_Rect &image, const SDL_Rect &offset) : image_(image), offset_(offset) {}

Sprite::Sprite(const SDL_Rect &image, const SDL_Rect &offset, const std::pair<int, int> coordinates) : image_(image), offset_(offset) {
    position_ = getPosition(coordinates);
}

const SDL_Rect &Sprite::getImage() const {
    return image_;
}

const SDL_Rect &Sprite::getPosition() const {
    return position_;
}

SDL_Rect Sprite::getPosition(const std::pair<int, int> coordinates) const {
    return {coordinates.first + offset_.x, coordinates.second + offset_.y, offset_.w, offset_.h};
}
