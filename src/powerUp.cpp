//
// Created by omar on 12/02/23.
//

#include "../include/powerUp.h"

powerUps PowerUp::getType() const {
    return type;
}

void PowerUp::setType(powerUps type_) {
    PowerUp::type = type_;
}

const SDL_Rect &PowerUp::getSprite() const {
    return sprite;
}

void PowerUp::setSprite(const SDL_Rect &sprite_) {
    PowerUp::sprite = sprite_;
}

PowerUp::PowerUp(const pair<int, int> &coordinates, const string &name, int points, powerUps type,
                 const SDL_Rect &sprite) : Entity(coordinates, name, points), type(type), sprite(sprite) {}

PowerUp::PowerUp(const pair<int, int> &coordinates, const string &name, powerUps type, const SDL_Rect &sprite) : Entity(
        coordinates, name), type(type), sprite(sprite) {}

PowerUp::PowerUp() {}





