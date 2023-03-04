//
// Created by omar on 12/02/23.
//

#include "../../include/entity/powerUp.h"

PowerUp::PowerUp() = default;

PowerUp::PowerUp(const pair<int, int> &coordinates, int size, Sprite sprite, int points, powerUps type) :
        Entity(coordinates, size, sprite, points, false), type_(type) {}





