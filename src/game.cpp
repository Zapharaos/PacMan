//
// Created by matthieu on 08/02/2023.
//

#include "../include/game.h"
#include "../include/sprite/extractor.h"

Game::Game() = default;

Game::Game(int width, int height, int cell_size, const char *file_path, int lives) {
    map_ = Map{width, height, cell_size, getCellsTypeFromFile(file_path)};

    // TODO : clean up

    // Pacman
    Sprite pacman_default {{ constants::BMP_PACMAN_START_X,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT }, {}};
    Sprite pacman_left_1 {{ 46,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT }, {}};
    Sprite pacman_left_2 {{ 63,constants::BMP_PACMAN_START_Y, 10,constants::BMP_ENTITY_GHOST_HEIGHT }, {6*2,0,10*2,0}};
    Sprite pacman_right_1 {{ 20,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT }, {}};
    Sprite pacman_right_2 {{ 35,constants::BMP_PACMAN_START_Y, 10,constants::BMP_ENTITY_GHOST_HEIGHT }, {0,0,10*2,0}};
    Sprite pacman_up_1 {{ 75,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT }, {}};
    Sprite pacman_up_2 {{ 92,94, constants::BMP_ENTITY_GHOST_WIDTH,10 }, {0,6*2,0,10*2}};
    Sprite pacman_down_1 {{ 109,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT }, {}};
    Sprite pacman_down_2 {{ 126,94, constants::BMP_ENTITY_GHOST_WIDTH,10 }, {0,0,0,10*2}};

    std::vector<Sprite> pacman_left {pacman_default, pacman_left_1, pacman_left_2};
    std::vector<Sprite> pacman_right {pacman_default, pacman_right_1, pacman_right_2};
    std::vector<Sprite> pacman_up {pacman_default, pacman_up_1, pacman_up_2};
    std::vector<Sprite> pacman_down {pacman_default, pacman_down_1, pacman_down_2};

    pacman_ = Pacman({constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y}, cell_size, pacman_left.at(1),
                     constants::PACMAN_SPEED, pacman_left, pacman_right, pacman_up, pacman_down);

    // Fruits
    const std::function<void(void)> &function = [&](){ fruits_.setIsDisabled(true); };
    fruits_ = {{constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y}, cell_size, {}, 9500, function};

    fruits_.appendFruit(100, {1}, {
        Sprite({ 290,238, 12,12 }, {2*2, 2*2, 12*2, 12*2}),
        Sprite({ 290,258, 12,12 }, {2*2, 2*2, 12*2, 12*2})
        });
    fruits_.appendFruit(300, {2}, {
        Sprite({ 307,238, 11,12 }, {2*2, 2*2, 11*2, 12*2}),
        Sprite({ 307,258, 11,12 }, {2*2, 2*2, 11*2, 12*2})
        });
    fruits_.appendFruit(500, {3, 4}, {
        Sprite({ 322,238, 12,12 }, {2*2, 2*2, 12*2, 12*2}),
        Sprite({ 322,258, 12,12 }, {2*2, 2*2, 12*2, 12*2})
        });
    fruits_.appendFruit(700, {5, 6}, {
        Sprite({ 338,238, 12,12 }, {2*2, 2*2, 12*2, 12*2}),
        Sprite({ 338,258, 12,12 }, {2*2, 2*2, 12*2, 12*2})
        });
    fruits_.appendFruit(1000, {7, 8}, {
        Sprite({ 355,236, 11,14 }, {2*2, 1*2, 11*2, 14*2}),
        Sprite({ 355,256, 11,14 }, {2*2, 1*2, 11*2, 14*2})
        });
    fruits_.appendFruit(2000, {9, 10}, {
        Sprite({ 371,239, 11,11 }, {2*2, 2*2, 11*2, 11*2}),
        Sprite({ 371,259, 11,11 }, {2*2, 2*2, 11*2, 11*2})
        });
    fruits_.appendFruit(3000, {11, 12}, {
        Sprite({ 387,237, 12,13 }, {2*2, 1*2, 12*2, 13*2}),
        Sprite({ 387,257, 12,13 }, {2*2, 1*2, 12*2, 13*2})
        });
    fruits_.appendFruit(5000, {13}, {
        Sprite({ 405,237, 7,13 }, {4*2, 1*2, 7*2, 13*2}),
        Sprite({ 405,257, 7,13 }, {4*2, 1*2, 7*2, 13*2})
        });

    // TODO : setup ghosts
    lives_ = lives; // TODO : temp, waiting for the scoreboard
}

const Pacman &Game::getPacman() const {
    return pacman_;
}

std::vector<CellType> Game::getCellsTypeFromFile(const std::string& file_path) {
    std::vector<CellType> cell_types;
    std::ifstream file; // indata is like cin
    char value; // variable for input value

    file.open(file_path); // opens the file
    if(!file) { // file couldn't be opened
        std::cerr << "Error: file could not be opened" << std::endl;
        exit(1);
    }
    file >> value;
    while ( !file.eof() ) { // keep reading until end-of-file
        cell_types.emplace_back((CellType) strtol(&value, nullptr, 10));
        file >> value; // sets EOF flag if no value found
    }
    file.close();
    return cell_types;
}

Direction Game::move(Direction continuous_direction, Direction try_direction) {
    Direction result = pacman_.move(map_, continuous_direction, try_direction);
    handleEntitiesCollisions();
    return result;
}

void Game::move(Direction continuous_direction) {
    pacman_.move(map_, continuous_direction);
    handleEntitiesCollisions();
}

void Game::handleEntitiesCollisions() {
    bool lowPoints = score_ < constants::NEW_UP_POINTS_CAP;

    Cell& cell = map_.getCellFromCoordinates(pacman_.getCoordinates(), pacman_.isMovingLeftOrUp());
    Entity entity = cell.getEntity();
    if(!entity.isDisabled() && pacman_.hasCollided(entity))
    {
        entity.setIsDisabled(true);
        cell.setEntity(entity);
        score_ += entity.getPoints();
        fruits_.incrementClearedPellets(level_);

        if(cell.getType() == CellType::ENERGIZER)
        {
            powerup_ = true;
            // TODO : handle power ups
        }
        // TODO : goodies => freeze 1/60s + point animation
    }

    if(!fruits_.isDisabled() && pacman_.hasCollided(fruits_))
    {
        score_ += fruits_.getPoints();
        fruits_.setIsDisabled(true);
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
                // TODO : freeze 1/60s + point animation
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
        const Entity& entity = cell.getEntity();
        SDL_Rect image = entity.getSprite().getImage();
        SDL_Rect image_position = entity.getImagePosition();
        SDL_BlitScaled(plancheSprites, &image, win_surf, &image_position);
    }

    if(!fruits_.isDisabled()) {
        SDL_Rect image = fruits_.getSprite().getImage();
        SDL_Rect image_position = fruits_.getImagePosition();
        SDL_BlitScaled(plancheSprites, &image, win_surf, &image_position);
    }

}
