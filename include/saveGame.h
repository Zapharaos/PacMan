//
// Created by omar on 19/02/23.
//

#ifndef PACMAN_SAVEGAME_H
#define PACMAN_SAVEGAME_H
#include "utils/json.hpp"
#include <iostream>
#include <fstream>
using json = nlohmann::json;


class saveGame {

public:
    static void saveGameState(int high_score, int round);
    std::string  getHighScore();
    std::string getRound();
};


#endif //PACMAN_SAVEGAME_H
