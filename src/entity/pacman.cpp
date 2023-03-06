//
// Created by matthieu on 28/02/2023.
//

#include "../../include/entity/pacman.h"

Pacman::Pacman() = default;

Pacman::Pacman(const pair<int, int> &coordinates, int size, Sprite sprite, int speed, const vector<Sprite> &left,
               const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down) :
               MovingEntity(coordinates, size, sprite, speed, left, right, up, down) {}

const pair<int, int> &Pacman::getCoordinates() const {
    return Entity::getCoordinates();
}

bool Pacman::isMovingLeftOrUp() const {
    return MovingEntity::isMovingLeftOrUp();
}

Sprite Pacman::getSprite() const {
    return Entity::getSprite();
}

SDL_Rect Pacman::getImagePosition() const {
    return Entity::getImagePosition();
}

bool Pacman::hasCollided(const Entity& entity) const {
    auto e_coor = entity.getCoordinates();
    auto e_size = entity.getSize();
    auto p_coor = this->getCoordinates();
    auto p_size = this->getSize();

    bool left = (e_coor.first <= p_coor.first && p_coor.first < e_coor.first + e_size);
    bool right = (p_coor.first <= e_coor.first && e_coor.first < p_coor.first + p_size);
    bool up = (e_coor.second <= p_coor.second && p_coor.second < e_coor.second + e_size);
    bool down = (p_coor.second <= e_coor.second && e_coor.second < p_coor.second + p_size);
    bool horizontal = left || right;
    bool vertical = up || down;

    switch (getPreviousDirection()) {
        case Direction::LEFT:
            return left && vertical;
        case Direction::RIGHT:
            return right && vertical;
        case Direction::UP:
            return up && horizontal;
        case Direction::DOWN:
            return down && horizontal;
        default:
            return false; // unreachable
    }
}

Direction Pacman::move(const Map& map, Direction continuous_direction, Direction try_direction) {
    return MovingEntity::move(map, continuous_direction, try_direction);
}

void Pacman::move(const Map& map, Direction continuous_direction) {
    MovingEntity::move(map, continuous_direction);
}

Direction Pacman::getPreviousDirection() const
{
    return MovingEntity::getPreviousDirection();
}
