//
// Created by matthieu on 08/02/2023.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include <iostream>
#include <fstream>
#include "../include/map.h"
#include "../include/entity.h"

class Game {
public:
    [[nodiscard]] Map getMap() const;

    Game();
    Game(int width, int height, int cell_size, const char * file_path, int lives);

    void movePacman(directions direction, SDL_Rect *rect);

private:
    Map map_;
    std::vector<Entity> ghosts_;
    Entity pacman_;
    int lives_ = 0;
    static std::vector<int> getCellsTypeFromFile(const std::string &file_path);

};


#endif //PACMAN_GAME_H
