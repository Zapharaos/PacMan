//
// Created by matthieu on 01/03/2023.
//

#include "../../include/sprite/sprite.h"

#include <utility>

Sprite::Sprite() = default;

Sprite::Sprite(const SDL_Rect &image, pair<int, int> offset,
               pair<int, int> size) :
        image_(image), offset_(move(offset)), size_(move(size))
{}

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

