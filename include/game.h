//
// Created by matthieu on 08/02/2023.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "../include/map.h"


class Game {
public:
    Game();
    Game(int width, int height);

private:
    Map map_;
};


#endif //PACMAN_GAME_H
