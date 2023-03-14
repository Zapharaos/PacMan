//
// Created by matthieu on 08/02/2023.
//

#include "../include/game.h"
#include "../include/display/extractor.h"
#include "../include/utils/utils.h"

Game::Game() = default;

Game::Game(int width, int height, int cell_size, const char *file_path,
           int lives)
{

    map_ = Map{width, height, cell_size, loadCellTypesFromFile(file_path)};
    lives_ = lives;

    // TODO : clean up

    // Pacman
    Sprite pacman_default{{constants::BMP_PACMAN_START_X, constants::BMP_PACMAN_START_Y, 14, 14},
                          {1 * 2,                         1 * 2},
                          {14 * 2,                        14 * 2}};
    Sprite pacman_left_1{{48,     constants::BMP_PACMAN_START_Y, 13, 14},
                         {2 * 2,  1 * 2},
                         {13 * 2, 14 * 2}};
    Sprite pacman_left_2{{64,    constants::BMP_PACMAN_START_Y, 9, 14},
                         {7 * 2, 1 * 2},
                         {9 * 2, 14 * 2}};
    Sprite pacman_right_1{{21,     constants::BMP_PACMAN_START_Y, 13, 14},
                          {1 * 2,  1 * 2},
                          {13 * 2, 14 * 2}};
    Sprite pacman_right_2{{36,    constants::BMP_PACMAN_START_Y, 9, 14},
                          {1 * 2, 1 * 2},
                          {9 * 2, 14 * 2}};
    Sprite pacman_up_1{{76,     91, 14, 13},
                       {1 * 2,  2 * 2},
                       {14 * 2, 13 * 2}};
    Sprite pacman_up_2{{93,     95, 14, 9},
                       {1 * 2,  7 * 2},
                       {14 * 2, 9 * 2}};
    Sprite pacman_down_1{{110,    91, 14, 13},
                         {1 * 2,  1 * 2},
                         {14 * 2, 13 * 2}};
    Sprite pacman_down_2{{127,    95, 14, 9},
                         {1 * 2,  1 * 2},
                         {14 * 2, 9 * 2}};

    Sprite pacman_death_1{{4,      111, 16, 8},
                          {0,      0 * 2},
                          {16 * 2, 8 * 2}};
    Sprite pacman_death_2{{23,     113, 16, 6},
                          {0,      2 * 2},
                          {16 * 2, 6 * 2}};
    Sprite pacman_death_3{{42,     114, 16, 5},
                          {0,      3 * 2},
                          {16 * 2, 5 * 2}};
    Sprite pacman_death_4{{61,     114, 16, 5},
                          {0,      4 * 2},
                          {16 * 2, 5 * 2}};
    Sprite pacman_death_5{{80,     113, 16, 6},
                          {0,      4 * 2},
                          {16 * 2, 6 * 2}};
    Sprite pacman_death_6{{99,     112, 14, 6},
                          {1 * 2,  4 * 2},
                          {14 * 2, 6 * 2}};
    Sprite pacman_death_7{{116,    112, 10, 7},
                          {3 * 2,  4 * 2},
                          {10 * 2, 7 * 2}};
    Sprite pacman_death_8{{129,   112, 6, 7},
                          {5 * 2, 4 * 2},
                          {6 * 2, 7 * 2}};
    Sprite pacman_death_9{{138,   112, 2, 7},
                          {7 * 2, 4 * 2},
                          {2 * 2, 7 * 2}};
    Sprite pacman_death_10{{143,    109, 11, 10},
                           {3 * 2,  3 * 2},
                           {11 * 2, 10 * 2}};

    Animation pacman_left{{pacman_default, pacman_left_1, pacman_left_2}, true, constants::ENTITY_REFRESH_RATE};
    Animation pacman_right{{pacman_default, pacman_right_1, pacman_right_2}, true, constants::ENTITY_REFRESH_RATE};
    Animation pacman_up{{pacman_default, pacman_up_1, pacman_up_2}, true, constants::ENTITY_REFRESH_RATE};
    Animation pacman_down{{pacman_default, pacman_down_1, pacman_down_2}, true, constants::ENTITY_REFRESH_RATE};

    Animation pacman_death{{pacman_death_1, pacman_death_2,
                                     pacman_death_3, pacman_death_4,
                                     pacman_death_5,
                                     pacman_death_6, pacman_death_7,
                                     pacman_death_8, pacman_death_9,
                                     pacman_death_10}, false, 7};

    pacman_ = Pacman(
            Position{{constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y}},
            pacman_left.getSprite(), constants::PACMAN_SPEED, pacman_left,
            pacman_right, pacman_up, pacman_down, 5000, pacman_death);

    // Fruits
    vector<FruitObject> fruits = {
            {100,  {1}, {{
                                  Sprite({290, 238, 12, 12}, {2 * 2, 2 * 2},
                                         {12 * 2, 12 * 2}),
                                  Sprite({290, 258, 12, 12}, {1 * 2, 1 * 2},
                                         {14 * 2, 14 * 2})}, false, 10}
            },
            {300,  {2}, {{
                                   Sprite({307, 238, 11, 12}, {2 * 2, 2 * 2},
                                          {11 * 2, 12 * 2}),
                                   Sprite({307, 258, 11, 12}, {1 * 2, 1 * 2},
                                          {13 * 2, 14 * 2})}, false, 10}
            },
            {500,  {3,  4}, {{
                                       Sprite({322, 238, 12, 12}, {2 * 2, 2 * 2},
                                              {12 * 2, 12 * 2}),
                                       Sprite({322, 258, 12, 12}, {1 * 2, 1 * 2},
                                              {13 * 2, 14 * 2})}, false, 10}
            },
            {700,  {5,  6}, {{
                                     Sprite({338, 238, 12, 12}, {2 * 2, 2 * 2},
                                            {12 * 2, 12 * 2}),
                                     Sprite({338, 258, 12, 12}, {1 * 2, 1 * 2},
                                            {13 * 2, 14 * 2})}, false, 10}
            },
            {1000, {7,  8}, {{
                                     Sprite({355, 236, 11, 14}, {2 * 2, 1 * 2},
                                            {11 * 2, 14 * 2}),
                                     Sprite({355, 256, 11, 14}, {1 * 2, 0},
                                            {13 * 2, 15 * 2})}, false, 10}
            },
            {2000, {9,  10}, {{
                                      Sprite({371, 239, 11, 11}, {2 * 2, 2 * 2},
                                             {11 * 2, 11 * 2}),
                                      Sprite({371, 259, 11, 11}, {1 * 2, 1 * 2},
                                             {13 * 2, 13 * 2})}, false, 10}
            },
            {3000, {11, 12}, {{
                                      Sprite({387, 237, 12, 13}, {2 * 2, 1 * 2},
                                             {12 * 2, 13 * 2}),
                                      Sprite({387, 257, 12, 13}, {1 * 2, 0},
                                             {14 * 2, 15 * 2})}, false, 10}
            },
            {5000, {13}, {{
                                  Sprite({405, 237, 7, 13}, {4 * 2, 1 * 2},
                                         {7 * 2, 13 * 2}),
                                  Sprite({405, 257, 7, 13}, {3 * 2, 0},
                                         {9 * 2, 15 * 2})}, false, 10}
            }
    };
    Position fruit_coordinates{
            {constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y - 5 * 32}};
    fruit_ = {fruit_coordinates, 9500, {56, 136}, fruits};

    // TODO : setup ghosts
}


int Game::getScore() const
{
    return score_;
}

const Pacman &Game::getPacman() const
{
    return pacman_;
}

void Game::setPacman(const Pacman &pacman)
{
    pacman_ = pacman;
}

const StatusType &Game::getStatus() const
{
    return status_;
}

void Game::setStatus(const StatusType &status)
{
    status_ = status;
}

void Game::move(const Direction &continuous_direction)
{
    pacman_.move(map_, continuous_direction);
    handleEntitiesCollisions();
}

Direction Game::move(const Direction &continuous_direction, const Direction &try_direction)
{
    Direction result = pacman_.move(map_, continuous_direction, try_direction);
    handleEntitiesCollisions();
    return result;
}

void Game::handleEntitiesCollisions()
{
    bool lowScore = score_ < constants::NEW_UP_POINTS_CAP;

    status_ = StatusType::RUNNING;

    // Get pacman sprite position.
    auto pacman = pacman_.getSpritePosition();

    // Get pacman current cell.
    auto pacman_position = Position{{pacman.x, pacman.y}};
    auto cell_position = pacman_position.getPositionUnscaled(map_.getCellSize());
    auto cell = map_.getCell(cell_position);
    auto entity = cell->getEntity();

    // DEATH TEST : at cell (7, 10)
    if(cell->getPositionScaled() == Position{{7*32, 10*32}})
    {
        status_ = StatusType::LOST_LIFE;
        pacman_.setDead(true);
        return;
    }

    // Cell has an active entity that collided with Pacman.
    if (cell && entity && entity->isEnabled() && SDL_HasIntersection(&pacman, &entity->getSpritePosition()))
    {
        // Disables entity.
        entity->setEnabled(false);
        score_ += entity->getPoints();

        // Freeze pacman.
        pacman_.count(1);

        // Updates fruit.
        pelletsEaten_++;
        fruit_.update(pelletsEaten_, level_);

        // Updates game.
        if (pelletsEaten_ == pelletsTotal_) // Level up.
        {
            status_ = StatusType::LEVEL_UP;

            // TODO : level up animation
            // Freeze pacman & ghosts.
            // After freeze : Map blinking => pacman shown & ghosts hidden.

        }
        else if (cell->getType() == CellType::ENERGIZER) // Superpower.
        {
            pacman_.setSuperpower(true);
            // TODO : ghost scared (timer) into ghost blinking (ticks)
        }
    }

    // Fruit is active and collided with Pacman.
    if (fruit_.isEnabled() && SDL_HasIntersection(&pacman, &fruit_.getSpritePosition()))
    {
        // Disables fruit.
        fruit_.setEnabled(false);
        score_ += fruit_.getPoints();
        // TODO : display points sprite
        status_ = StatusType::INTERRUPTED;
    }

    for (auto &ghost: ghosts_)
    {
        // Ghost is active and collided with Pacman.
        if (ghost.isEnabled() && SDL_HasIntersection(&pacman, &ghost.getSpritePosition()))
        {
            if (!pacman_.isSuperpower()) // Superpower disabled : death.
            {
                status_ = StatusType::LOST_LIFE;
                pacman_.setDead(true);

                // TODO : death animation
                // Freeze pacman + Freeze ghosts but still animate them.
                // After freeze => pacman animateDeath & hide ghosts.
                // After animateDeath => restart.

                continue;
            }

            // Disables ghost & updates game.
            ghost.setEnabled(false);
            score_ += ghost.getPoints();
            status_ = StatusType::INTERRUPTED;

            // TODO : eating animation
            // Freeze pacman & hide.
            // Freeze ghosts.
            // Display points sprite.

            // TODO : ghost going back to home
        }
    }

    // Check if the score has evolved up the new life's limit.
    if (lowScore && score_ >= constants::NEW_UP_POINTS_CAP)
        lives_++;
}

void Game::levelUp()
{
    // Update game settings.
    level_++;
    pelletsEaten_ = 0;
    status_ = StatusType::RUNNING;

    // Reset entities.
    map_.reset();
    fruit_.reset();
    pacman_.reset(
            Position{{constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y}});

    // TODO : ghosts reset
    // TODO : speed and timers : up
}

void Game::lostLife()
{
    if ((--lives_) == 0) // Game lost : reset the game settings
    {
        lives_ = 3; // temp
        score_ = 0;
        level_ = 1;
        pelletsEaten_ = 0;
        map_.reset();
    }

    // Reset the entities (might only lose a life).
    status_ = StatusType::RUNNING;
    fruit_.reset();
    pacman_.reset(
            Position{{constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y}});

    // TODO : ghosts reset
    // TODO : speed and timers : reset
}

void

Game::drawStaticEntities(std::shared_ptr<SDL_Renderer> render,
                         std::shared_ptr<SDL_Texture> texture)
{

    // Pellets
    for (auto &cell: map_.getCellsWithEntities())
    {
        auto entity = cell->getEntity();

        // Blinking energizer
        if (cell->getType() == CellType::ENERGIZER && entity->countLowerHalf())
            continue;

        // Entity disabled
        if (!entity->isEnabled())
            continue;

        // Display entity
        SDL_Rect image = entity->getSpriteImage();
        SDL_Rect position = entity->getSpritePosition();
        drawObject(render,texture,image,position);

    }

    // Fruit
    if (fruit_.isEnabled())
    {
        // Display entity
        fruit_.animate();
        SDL_Rect image = fruit_.getSpriteImage();
        SDL_Rect position = fruit_.getSpritePosition();
        drawObject(render,texture,image,position);
    }
}

int Game::getSavedHighScore() {
    high_score_ = stoi(SaveGame::getHighScore());
    return high_score_ ;
}

bool Game::updateHighScore() {
    if (score_>high_score_){
        high_score_ = score_;
        return true ;
    }
    return false ;

}

int Game::getHighScore() const {
    return high_score_;
}

void Game::setHighScore(int highScore) {
    high_score_ = highScore;
}
