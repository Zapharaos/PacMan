//
// Created by matthieu on 08/02/2023.
//

#include "../include/game.h"

Game::Game() = default;

Game::Game(const int width, const int height) {
    map_ = Map{width, height};
}
