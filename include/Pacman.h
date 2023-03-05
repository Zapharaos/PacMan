//
// Created by matthieu on 28/02/2023.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H


#include "movingEntity.h"

class Pacman : MovingEntity {

public:
    Pacman(const pair<int, int> &coordinates, int size, SDL_Rect image, int speed, const vector<SDL_Rect> &left,
           const vector<SDL_Rect> &right, const vector<SDL_Rect> &up, const vector<SDL_Rect> &down);
    Pacman();

    [[nodiscard]] const pair<int, int> &getCoordinates() const override;
    [[nodiscard]] bool isMovingLeftOrUp() const override;
    [[nodiscard]] SDL_Rect getImage() const override;

    [[nodiscard]] SDL_Rect getImagePosition() const override;
    [[nodiscard]] bool hasCollided(const Entity& entity) const;
    void move(Map map, directions direction) override;
};


#endif //PACMAN_PACMAN_H
