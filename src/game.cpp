//
// Created by matthieu on 08/02/2023.
//

#include "../include/game.h"
#include "../include/constants.h"
#include "../include/entity.h"

Game::Game() = default;

Game::Game(int width, int height, int cell_size, const char *file_path, int lives) {
    map_ = Map{width, height, cell_size, getCellsTypeFromFile(file_path)};
    pacman_ = Entity({constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y}, cell_size, 0);

    // TODO : setup ghosts
    lives_ = lives; // TODO : temp, waiting for the scoreboard
}

std::vector<cell_type> Game::getCellsTypeFromFile(const std::string& file_path) {
    std::vector<cell_type> cell_types;
    std::ifstream file; // indata is like cin
    char value; // variable for input value

    file.open(file_path); // opens the file
    if(!file) { // file couldn't be opened
        std::cerr << "Error: file could not be opened" << std::endl;
        exit(1);
    }
    file >> value;
    while ( !file.eof() ) { // keep reading until end-of-file
        cell_types.emplace_back((cell_type) strtol(&value, nullptr, 10));
        file >> value; // sets EOF flag if no value found
    }
    file.close();
    return cell_types;
}

void Game::handleCollisionsWithEntities(directions direction, Cell& cell) {
    bool lowPoints = score_ < constants::NEW_UP_POINTS_CAP;

    Entity entity = cell.getEntity();
    if(!entity.isDisabled() && pacman_.hasCollided(direction, entity))
    {
        entity.setIsDisabled(true);
        cell.setEntity(entity);
        score_ += entity.getPoints();

        if(cell.getType() == POWER)
        {
            powerup_ = true;
            // TODO : handle power ups
        }
    }

    for(auto & ghost : ghosts_)
    {
        if(!ghost.isDisabled() && pacman_.hasCollided(direction, ghost))
        {
            if(powerup_)
            {
                score_ += ghost.getPoints();
                ghost.setIsDisabled(true);
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

    if(lowPoints && score_ >= constants::NEW_UP_POINTS_CAP)
    {
        lives_++;
        // TODO : update lives
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
            return; // nothing to do here
    }

    if(!map_.canMoveToCell(destination, isMovingLeftOrUp)) return;

    destination = map_.getDestination();
    pacman_.setCoordinates(destination);
    rect->x = destination.first;
    rect->y = destination.second;

    handleCollisionsWithEntities(direction, map_.getCellAtDestination(destination, isMovingLeftOrUp));
}

void Game::drawStaticEntities(SDL_Surface* plancheSprites, SDL_Surface* win_surf) {
    for(auto & cell : map_.getCellsWithActiveEntities())
    {
        Entity entity = cell.getEntity();
        SDL_Rect image = entity.getImage();
        SDL_Rect image_position = entity.getImagePosition();
        SDL_BlitScaled(plancheSprites, &image, win_surf, &image_position);
    }
}
