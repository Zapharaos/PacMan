//
// Created by matthieu on 01/03/2023.
//

#include "../../include/sprite/sprite.h"

#include <utility>

Sprite::Sprite() = default;

Sprite::Sprite(const SDL_Rect &image, std::pair<int, int> offset, std::pair<int, int> size) :
        image_(image), offset_(std::move(offset)), size_(std::move(size)) {}

Sprite::Sprite(const SDL_Rect &image, std::pair<int, int> offset, std::pair<int, int> size, std::pair<int, int> coordinates) :
    image_(image), offset_(std::move(offset)), size_(std::move(size)), coordinates_(std::move(coordinates)){
    updatePosition();
}

const SDL_Rect &Sprite::getImage() const {
    return image_;
}

const SDL_Rect &Sprite::getPosition() const {
    return position_;
}

void Sprite::setCoordinates(const std::pair<int, int> &coordinates) {
    coordinates_ = coordinates;
    updatePosition();
}

void Sprite::updatePosition() {
    position_ = {coordinates_.first + offset_.first,
                 coordinates_.second + offset_.second,
                 size_.first,
                 size_.second};
}

