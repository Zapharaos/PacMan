//
// Created by matthieu on 08/02/2023.
//

#include "../include/game.h"
#include "../include/constants.h"

Game::Game() = default;

Game::Game(int width, int height, int cell_size, const char *file_path) {
    map_ = Map{width, height, cell_size, getCellsTypeFromFile(file_path)};
    pacman_ = Entity(std::pair<int, int> {10*cell_size, 20*cell_size}, "pacman");
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
        cell_types.emplace_back(strtol(&value, nullptr, 10));
        file >> value; // sets EOF flag if no value found
    }
    file.close();
    return cell_types;
}

Map Game::getMap() const {
    return map_;
}

void Game::movePacman(directions direction, SDL_Rect *rect) {

    std::pair<int, int> destination = pacman_.getCoordinates();
    bool isMovingLeftOrUp = false;

    switch(direction) {
        case LEFT:
            destination.first-=constants::SPEED_PACMAN;
            isMovingLeftOrUp = true;
            break;
        case RIGHT:
            destination.first+=constants::SPEED_PACMAN;
            break;
        case UP:
            destination.second-=constants::SPEED_PACMAN;
            isMovingLeftOrUp = true;
            break;
        case DOWN:
            destination.second+=constants::SPEED_PACMAN;
            break;
        default:
            std::cerr << "movePacman : Direction not recognized..." << std::endl;
    }

    if(!map_.canMoveToCell(destination, isMovingLeftOrUp)) return;

    destination = map_.getDestination();
    pacman_.setCoordinates(destination);
    rect->x = destination.first;
    rect->y = destination.second;

    std::cout << "Moved to => (" << pacman_.getCoordinates().first / 32 << ", " << pacman_.getCoordinates().second /32 << "), (" << pacman_.getCoordinates().first << ", " << pacman_.getCoordinates().second << ")" << std::endl;
}
