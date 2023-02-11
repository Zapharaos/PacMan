//
// Created by matthieu on 08/02/2023.
//

#include "../include/game.h"

Game::Game() = default;

Game::Game(const int width, const int height, const char *const file_path) {
    map_ = Map{width, height, getCellsTypeFromFile(file_path)};
}

std::vector<int> Game::getCellsTypeFromFile(const std::string& file_path) {
    std::vector<int> cell_types;
    std::ifstream file; // indata is like cin
    char value; // variable for input value

    file.open(file_path); // opens the file
    if(!file) { // file couldn't be opened
        std::cerr << "Error: file could not be opened" << std::endl;
        exit(1);
    }
    file >> value;
    while ( !file.eof() ) { // keep reading until end-of-file
        cell_types.emplace_back(atoi(&value));
        file >> value; // sets EOF flag if no value found
    }
    //cell_types.emplace_back(value);
    file.close();
    return cell_types;
}

const Map &Game::getMap() const {
    return map_;
}
