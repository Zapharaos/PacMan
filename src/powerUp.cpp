//
// Created by omar on 12/02/23.
//

#include "../include/powerUp.h"

PowerUp::PowerUp() = default;

PowerUp::PowerUp(const pair<int, int> &coordinates, int size, SDL_Rect image, int points, powerUps type) :
        Entity(coordinates, size, image, points, false), type_(type) {}





