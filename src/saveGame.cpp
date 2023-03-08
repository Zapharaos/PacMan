//
// Created by omar on 19/02/23.
//

#include "../include/saveGame.h"

void SaveGame::saveGameState(int high_score, int round) {

    json j =
            {
                    {"High Score",std::to_string(high_score)},
                    {"Round",std::to_string(round)}
            };

    // pretty print with indent of 4 spaces
    std::ofstream file("../resources/save.json");
    file << j ;
}

std::string  SaveGame::getHighScore() {
    std::ifstream f("../resources/save.json");
    json data  = json::parse(f);
    std::string high_score = data.value("High Score","Not found");
    return high_score ;
}

std::string SaveGame::getRound() {
    std::ifstream f("../resources/save.json");
    json data  = json::parse(f);
    std::string round = data.value("Round","Not found");
    return round ;
}
