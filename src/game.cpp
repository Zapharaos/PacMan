//
// Created by matthieu on 08/02/2023.
//

#include "../include/game.h"
#include "../include/sprite/extractor.h"

Game::Game() = default;

Game::Game(int width, int height, int cell_size, const char *file_path, int lives) {
    map_ = Map{width, height, cell_size, getCellsTypeFromFile(file_path)};
    lives_ = lives;

    // TODO : clean up

    // Pacman
    Sprite pacman_default {{ constants::BMP_PACMAN_START_X,constants::BMP_PACMAN_START_Y, 14,14 }, {1*2, 1*2}, {14*2, 14*2}};
    Sprite pacman_left_1 {{ 48,constants::BMP_PACMAN_START_Y, 13,14 }, {2*2, 1*2}, {13*2, 14*2}};
    Sprite pacman_left_2 {{ 64,constants::BMP_PACMAN_START_Y, 9,14 }, {7*2,1*2}, {9*2,14*2}};
    Sprite pacman_right_1 {{ 21,constants::BMP_PACMAN_START_Y, 13,14 }, {1*2, 1*2}, {13*2, 14*2}};
    Sprite pacman_right_2 {{ 36,constants::BMP_PACMAN_START_Y, 9,14 }, {1*2,1*2},{9*2,14*2}};
    Sprite pacman_up_1 {{ 76,91, 14,13 }, {1*2, 2*2}, {14*2, 13*2}};
    Sprite pacman_up_2 {{ 93,95, 14,9 }, {1*2,7*2},{14*2,9*2}};
    Sprite pacman_down_1 {{ 110,91, 14,13 }, {1*2, 1*2}, {14*2, 13*2}};
    Sprite pacman_down_2 {{ 127,95, 14,9 }, {1*2,1*2},{14*2,9*2}};

    std::vector<Sprite> pacman_left {pacman_default, pacman_left_1, pacman_left_2};
    std::vector<Sprite> pacman_right {pacman_default, pacman_right_1, pacman_right_2};
    std::vector<Sprite> pacman_up {pacman_default, pacman_up_1, pacman_up_2};
    std::vector<Sprite> pacman_down {pacman_default, pacman_down_1, pacman_down_2};

    pacman_ = Pacman(5000, [&](){ pacman_.setSuperpower(false); }, pacman_left.at(1), constants::PACMAN_SPEED, {constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y}, pacman_left, pacman_right, pacman_up, pacman_down);

    // Fruits
    fruits_ = {9500, [&](){ fruits_.setIsDisabled(true); }};
    std::pair<int, int> fruit_coordinates = {constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y};
    fruits_.appendFruit(100, {1}, {
        Sprite({ 290,238, 12,12 }, {2*2, 2*2}, {12*2, 12*2}, fruit_coordinates),
        Sprite({ 290,258, 12,12 }, {2*2, 2*2}, {12*2, 12*2}, fruit_coordinates)});
    fruits_.appendFruit(300, {2}, {
        Sprite({ 307,238, 11,12 }, {2*2, 2*2}, {11*2, 12*2}, fruit_coordinates),
        Sprite({ 307,258, 11,12 }, {2*2, 2*2}, {11*2, 12*2}, fruit_coordinates)});
    fruits_.appendFruit(500, {3, 4}, {
        Sprite({ 322,238, 12,12 }, {2*2, 2*2}, {12*2, 12*2}, fruit_coordinates),
        Sprite({ 322,258, 12,12 }, {2*2, 2*2}, {12*2, 12*2}, fruit_coordinates)});
    fruits_.appendFruit(700, {5, 6}, {
        Sprite({ 338,238, 12,12 }, {2*2, 2*2}, {12*2, 12*2}, fruit_coordinates),
        Sprite({ 338,258, 12,12 }, {2*2, 2*2}, {12*2, 12*2}, fruit_coordinates)});
    fruits_.appendFruit(1000, {7, 8}, {
        Sprite({ 355,236, 11,14 }, {2*2, 1*2}, {11*2, 14*2}, fruit_coordinates),
        Sprite({ 355,256, 11,14 }, {2*2, 1*2}, {11*2, 14*2}, fruit_coordinates)});
    fruits_.appendFruit(2000, {9, 10}, {
        Sprite({ 371,239, 11,11 }, {2*2, 2*2}, {11*2, 11*2}, fruit_coordinates),
        Sprite({ 371,259, 11,11 }, {2*2, 2*2}, {11*2, 11*2}, fruit_coordinates)});
    fruits_.appendFruit(3000, {11, 12}, {
        Sprite({ 387,237, 12,13 }, {2*2, 1*2}, {12*2, 13*2}, fruit_coordinates),
        Sprite({ 387,257, 12,13 }, {2*2, 1*2}, {12*2, 13*2}, fruit_coordinates)});
    fruits_.appendFruit(5000, {13}, {
        Sprite({ 405,237, 7,13 }, {4*2, 1*2}, {7*2, 13*2}, fruit_coordinates),
        Sprite({ 405,257, 7,13 }, {4*2, 1*2}, {7*2, 13*2}, fruit_coordinates)});

    // TODO : setup ghosts
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

    Cell& cell = map_.getCellFromCoordinates(pacman_.getCoordinates(), pacman_.isLeftOrUp());
    Entity entity = cell.getEntity();
    if(!entity.isDisabled() && pacman_.hasCollided(entity.getSpritePosition()))
    {
        cell.setIsDisabled(true);
        score_ += entity.getPoints();
        fruits_.updateSprite((eaten_++), level_);

        if(cell.getType() == CellType::ENERGIZER)
            pacman_.setSuperpower(true);
        // TODO : goodies => freeze 1/60s + point animation
    }

    if(!fruits_.isDisabled() && pacman_.hasCollided(fruits_.getSpritePosition()))
    {
        score_ += fruits_.getPoints();
        fruits_.setIsDisabled(true);
        // TODO : freeze 1/60s + point animation
    }

    for(auto & ghost : ghosts_)
    {
        if(!ghost.isDisabled() && pacman_.hasCollided(ghost.getSpritePosition()))
        {
            if(!pacman_.isSuperpower()) {
                lives_--;
                break;
            }
            score_ += ghost.getPoints();
            ghost.setIsDisabled(true);
            break;
            // TODO : hide Pacman & show points earned
            // TODO : freeze 1/60s + point animation
        }
    }

    if(lowPoints && score_ >= constants::NEW_UP_POINTS_CAP)
        lives_++;
}

void Game::drawStaticEntities(SDL_Surface* plancheSprites, SDL_Surface* win_surf) {
    for(auto & cell : map_.getCellsWithActiveEntities())
    {
        Entity entity = cell.getEntity();
        SDL_Rect image = entity.getSpriteImage();
        SDL_Rect position = entity.getSpritePosition();
        SDL_BlitScaled(plancheSprites, &image, win_surf, &position);
    }

    if(!fruits_.isDisabled()) {
        SDL_Rect image = fruits_.getSpriteImage();
        SDL_Rect position = fruits_.getSpritePosition();
        SDL_BlitScaled(plancheSprites, &image, win_surf, &position);
    }
}

bool Game::levelChange() {
    if(eaten_ != pellets_) return false;

    level_++;
    eaten_ = 0;

    map_.reset();
    pacman_.reset({constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y});

    // TODO : ghosts reset

    return true;

}

int Game::getScore() const {
    return score_;
}
