//
// Created by matthieu on 08/02/2023.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include <iostream>
#include <fstream>
#include "../include/map.h"

class Game {
public:
    [[nodiscard]] const Map &getMap() const;

    Game();
    Game(int width, int height, const char * file_path);

private:
    Map map_;

    static std::vector<int> getCellsTypeFromFile(const std::string &file_path);
};


#endif //PACMAN_GAME_H
