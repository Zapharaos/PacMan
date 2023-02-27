//
// Created by matthieu on 08/02/2023.
//

#include "../include/game.h"
#include "../include/constants.h"
#include "../include/entity.h"

Game::Game() = default;

Game::Game(int width, int height, int cell_size, const char *file_path, int lives) {
    map_ = Map{width, height, cell_size, getCellsTypeFromFile(file_path)};

    pacman_ = Entity({constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y}, cell_size, "pacman", 0);
    // TODO : setup ghosts

    lives_ = lives; // TODO : temp

    // TODO : better to link these to cells ?
    powers_ = map_.getPowerEntities();
    points_ = map_.getPointEntities();
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

void Game::handleCollisions() {
    bool lowPoints = score_ < constants::NEW_UP_POINTS_CAP;
    for(auto & power : powers_)
    {
        if(pacman_.hasCollided(power))
        {
            power.print();
            score_ += power.getPoints();
            powerup_ = true;
            // TODO : handle power ups
        }
    }
    for(auto & ghost : ghosts_)
    {
        if(pacman_.hasCollided(ghost))
        {
            ghost.print();
            if(powerup_)
            {
                score_ += ghost.getPoints();
                // TODO : remove ghost sprite
            }
            else
            {
                lives_--;
                if(lives_ == 0)
                {
                    // TODO : game lost
                }
                else
                {
                    // TODO : continue round but life lost
                }
            }
        }
    }
    for(auto & point : points_)
    {
        if(pacman_.hasCollided(point))
        {
            point.print();
            score_ += point.getPoints();
            // TODO : remove point sprite
        }
    }
    if(lowPoints)
    {
        if(score_ >= constants::NEW_UP_POINTS_CAP)
        {
            lives_++;
            // TODO : update lives
        }
    }
}

void Game::movePacman(directions direction, SDL_Rect *rect) {

    std::pair<int, int> destination = pacman_.getCoordinates();
    bool isMovingLeftOrUp = false;

    switch(direction) {
        case LEFT:
            destination.first -= constants::SPEED_PACMAN;
            isMovingLeftOrUp = true;
            break;
        case RIGHT:
            destination.first += constants::SPEED_PACMAN;
            break;
        case UP:
            destination.second -= constants::SPEED_PACMAN;
            isMovingLeftOrUp = true;
            break;
        case DOWN:
            destination.second += constants::SPEED_PACMAN;
            break;
        default:
            std::cerr << "movePacman : Direction not recognized..." << std::endl;
    }

    if(!map_.canMoveToCell(destination, isMovingLeftOrUp)) return;

    destination = map_.getDestination();
    pacman_.setCoordinates(destination);
    rect->x = destination.first;
    rect->y = destination.second;

    std::cout << "Moved to => (" << pacman_.getCoordinates().first / constants::WINDOW_CELL_HEIGHT << ", " << pacman_.getCoordinates().second / constants::WINDOW_CELL_HEIGHT << "), (" << pacman_.getCoordinates().first << ", " << pacman_.getCoordinates().second << ")" << std::endl;
}
