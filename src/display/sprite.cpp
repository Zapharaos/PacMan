//
// Created by matthieu on 01/03/2023.
//

#include "../../include/display/sprite.h"

#include <utility>

Sprite::Sprite() = default;

Sprite::Sprite(const SDL_Rect &image, const pair<int, int> &offset,
               const pair<int, int> &size) :
        image_(image), offset_(offset), size_(size)
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

