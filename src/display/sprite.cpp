//
// Created by matthieu on 01/03/2023.
//

#include "../../include/display/sprite.h"

#include <utility>

Sprite::Sprite() = default;

Sprite::Sprite(const SDL_Rect &image, std::pair<int, int> offset,
               std::pair<int, int> size) :
        image_(image), offset_(std::move(offset)), size_(std::move(size))
{
    position_ = {offset_.first, offset_.second, size_.first, size_.second};
}

const SDL_Rect &Sprite::getImage() const
{
    return image_;
}

const SDL_Rect &Sprite::getPosition() const
{
    return position_;
}

void Sprite::updatePosition(const Position &coordinates)
{
    position_ = {coordinates.getAbscissa() + offset_.first,
                 coordinates.getOrdinate() + offset_.second,
                 size_.first,
                 size_.second};
}

