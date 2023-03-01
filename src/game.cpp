//
// Created by matthieu on 08/02/2023.
//

#include "../include/game.h"
#include "../include/extractor.h"

Game::Game() = default;

Game::Game(int width, int height, int cell_size, const char *file_path, int lives) {
    map_ = Map{width, height, cell_size, getCellsTypeFromFile(file_path)};

    // TODO : clean up
    SDL_Rect pacman_default { constants::BMP_PACMAN_START_X,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };

    std::vector<SDL_Rect> pacman_left {pacman_default,
                                       { 46,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT },
                                       { 63,constants::BMP_PACMAN_START_Y, 10,constants::BMP_ENTITY_GHOST_HEIGHT }};
    std::vector<SDL_Rect> pacman_right {pacman_default,
                                        { 20,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT },
                                        { 35,constants::BMP_PACMAN_START_Y, 10,constants::BMP_ENTITY_GHOST_HEIGHT }};
    std::vector<SDL_Rect> pacman_up {pacman_default,
                                     { 75,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT },
                                     { 92,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT }};
    std::vector<SDL_Rect> pacman_down {pacman_default,
                                       { 109,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT },
                                       { 126,94, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT }};

    pacman_ = Pacman({constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y}, cell_size, pacman_left.at(0),
                     constants::PACMAN_SPEED, pacman_left, pacman_right, pacman_up, pacman_down);

    // TODO : setup ghosts
    lives_ = lives; // TODO : temp, waiting for the scoreboard
}

const Pacman &Game::getPacman() const {
    return pacman_;
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

void Game::move(directions direction) {
    pacman_.move(map_, direction);
    handleEntitiesCollisions();
}

void Game::handleEntitiesCollisions() {
    bool lowPoints = score_ < constants::NEW_UP_POINTS_CAP;

    Cell& cell = map_.getCellAtDestination(pacman_.getCoordinates(), pacman_.isMovingLeftOrUp());
    Entity entity = cell.getEntity();
    if(!entity.isDisabled() && pacman_.hasCollided(entity))
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
        if(!ghost.isDisabled() && pacman_.hasCollided(ghost))
        {
            if(powerup_)
            {
                score_ += ghost.getPoints();
                ghost.setIsDisabled(true);
                // TODO : hide Pacman & show points earned
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

void Game::drawStaticEntities(SDL_Surface* plancheSprites, SDL_Surface* win_surf) {
    for(auto & cell : map_.getCellsWithActiveEntities())
    {
        Entity entity = cell.getEntity();
        SDL_Rect image = entity.getImage();
        SDL_Rect image_position = entity.getImagePosition();
        SDL_BlitScaled(plancheSprites, &image, win_surf, &image_position);
    }

}
