//
// Created by matthieu on 28/02/2023.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H


#include "movingEntity.h"

class Pacman : MovingEntity {

public:
    Pacman(const pair<int, int> &coordinates, int size, Sprite sprite, int speed, const vector<Sprite> &left,
           const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down);
    Pacman();

    [[nodiscard]] const pair<int, int> &getCoordinates() const override;
    [[nodiscard]] bool isMovingLeftOrUp() const override;
    [[nodiscard]] Sprite getSprite() const override;

    [[nodiscard]] SDL_Rect getImagePosition() const override;
    [[nodiscard]] bool hasCollided(const Entity& entity) const;
    directions move(const Map& map, directions continuous_direction, directions try_direction);
    void move(const Map& map, directions continuous_direction);
};


#endif //PACMAN_PACMAN_H