//
// Created by omar on 19/02/23.
//

#include "../include/saveGame.h"

void saveGame::saveGameState(int high_score, int round) {

    json j =
            {
                    {"High Score",high_score},
                    {"Round",round}
            };

    // pretty print with indent of 4 spaces
    std::ofstream file("../resources/save.json");
    file << j ;
}

std::string  saveGame::getHighScore() {
    std::ifstream f("../resources/save.json");
    json data  = json::parse(f);
    std::string high_score = data.value("High Score","Not found");
    return high_score ;
}

std::string saveGame::getRound() {
    std::ifstream f("../resources/save.json");
    json data  = json::parse(f);
    std::string round = data.value("Round","Not found");
    return round ;
}
