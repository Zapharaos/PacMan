//
// Created by matthieu on 28/02/2023.
//

#include "../../include/entity/pacman.h"

Pacman::Pacman() = default;

Pacman::Pacman(Sprite sprite, int speed, const pair<int, int> &coordinates, const vector<Sprite> &left,
               const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down) :
               MovingEntity(sprite, speed, coordinates, left, right, up, down) {}

const pair<int, int> &Pacman::getCoordinates() const {
    return MovingEntity::getCoordinates();
}

bool Pacman::isLeftOrUp() const {
    return MovingEntity::isLeftOrUp();
}

Sprite Pacman::getSprite() const {
    return Entity::getSprite();
}

SDL_Rect Pacman::getSpritePosition() const {
    return MovingEntity::getSpritePosition();
}

const SDL_Rect &Pacman::getSpriteImage() const {
    return MovingEntity::getSpriteImage();
}

bool Pacman::hasCollided(SDL_Rect e) const {
    auto p = this->getSpritePosition();

    bool left = (e.x <= p.x && p.x < e.x + e.w);
    bool right = (p.x <= e.x && e.x < p.x + p.w);
    bool up = (e.y <= p.y && p.y < e.y + e.h);
    bool down = (p.y <= e.y && e.y < p.y + p.h);

    bool horizontal = left || right;
    bool vertical = up || down;

    return horizontal && vertical;
}

Direction Pacman::move(const Map& map, Direction continuous_direction, Direction try_direction) {
    return MovingEntity::move(map, continuous_direction, try_direction);
}

void Pacman::move(const Map& map, Direction continuous_direction) {
    MovingEntity::move(map, continuous_direction);
}
