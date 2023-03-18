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
    window_ = Window{constants::WINDOW_MAP_WIDTH, constants::WINDOW_MAP_HEIGHT, "Pacman"};
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

    Animation pacman_left{{pacman_default, pacman_left_1, pacman_left_2}, true,
                          constants::ENTITY_REFRESH_RATE};
    Animation pacman_right{{pacman_default, pacman_right_1, pacman_right_2},
                           true, constants::ENTITY_REFRESH_RATE};
    Animation pacman_up{{pacman_default, pacman_up_1, pacman_up_2}, true,
                        constants::ENTITY_REFRESH_RATE};
    Animation pacman_down{{pacman_default, pacman_down_1, pacman_down_2}, true,
                          constants::ENTITY_REFRESH_RATE};

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
            {100,  {1},      {{
                                      Sprite({290, 238, 12, 12}, {2 * 2, 2 * 2},
                                             {12 * 2, 12 * 2}),
                                      Sprite({290, 258, 12, 12}, {1 * 2, 1 * 2},
                                             {14 * 2, 14 * 2})}, false, 10}
            },
            {300,  {2},      {{
                                      Sprite({307, 238, 11, 12}, {2 * 2, 2 * 2},
                                             {11 * 2, 12 * 2}),
                                      Sprite({307, 258, 11, 12}, {1 * 2, 1 * 2},
                                             {13 * 2, 14 * 2})}, false, 10}
            },
            {500,  {3,  4},  {{
                                      Sprite({322, 238, 12, 12}, {2 * 2, 2 * 2},
                                             {12 * 2, 12 * 2}),
                                      Sprite({322, 258, 12, 12}, {1 * 2, 1 * 2},
                                             {13 * 2, 14 * 2})}, false, 10}
            },
            {700,  {5,  6},  {{
                                      Sprite({338, 238, 12, 12}, {2 * 2, 2 * 2},
                                             {12 * 2, 12 * 2}),
                                      Sprite({338, 258, 12, 12}, {1 * 2, 1 * 2},
                                             {13 * 2, 14 * 2})}, false, 10}
            },
            {1000, {7,  8},  {{
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
            {5000, {13},     {{
                                      Sprite({405, 237, 7, 13}, {4 * 2, 1 * 2},
                                             {7 * 2, 13 * 2}),
                                      Sprite({405, 257, 7, 13}, {3 * 2, 0},
                                             {9 * 2, 15 * 2})},  false, 10}
            }
    };
    Position fruit_coordinates{
            {constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y - 5 * 32}};
    fruit_ = {fruit_coordinates, 9500, {56, 136}, fruits};

    // TODO : setup ghosts
}

void Game::togglePause()
{
    if(status_ == StatusType::RUNNING)
        status_ = StatusType::PAUSED;
    else if(status_ == StatusType::PAUSED)
        status_ = StatusType::RUNNING;
}

void Game::tick(const Direction &direction)
{

    // Game is paused, nothing to do.
    if(status_ == StatusType::PAUSED)
        return;

    // Handle status.
    if(handleStatus())
    {
        // Move entities and handle collisions.
        pacman_.move(map_, direction);
        // TODO : move ghosts
        handleEntitiesCollisions();
    }

    // Update game visuals.
    display();
}

void Game::display()
{
    // couleur transparente
    //SDL_SetColorKey(plancheSprites_, true, 0);
    //TODO Changer transparence avec SDL2

    window_.clear();

    // TODO : scores

    // Map.
    window_.draw(map_);

    // Pacman
    if(pacman_.isDead()) // death animation
        pacman_.animateDeath();
    if(pacman_.isVisible())
        window_.draw(pacman_);

    // TODO : ghosts

    // Pellets
    for (auto &cell: map_.getCellsWithEntities())
    {
        auto entity = cell->getEntity();

        // Blinking energizer (homogenize counter even if disabled)
        if (cell->getType() == CellType::ENERGIZER &&
            !entity->tickVisibility())
            continue;

        // Entity disabled
        if (!entity->isEnabled())
            continue;

        // Display entity
        window_.draw(*entity);
    }

    // Fruit
    if (fruit_.isEnabled())
    {
        // Display entity
        fruit_.animate();
        window_.draw(fruit_);
    }

    window_.update();
}

bool Game::handleStatus()
{
    // Processing animations.
    if (counter_.isActive())
    {
        // Map blinking
        if (status_ == StatusType::LEVEL_UP_ANIMATE)
            map_.animate();

        counter_.increment();
        return false;
    }

    // Game level up freeze is over.
    if (status_ == StatusType::LEVEL_UP_FREEZE)
    {
        // Start level up animation.
        status_ = StatusType::LEVEL_UP_ANIMATE;
        counter_.start(240);
        // TODO : hide ghosts
        return false;
    }

    // Game level up animation is over.
    if (status_ == StatusType::LEVEL_UP_ANIMATE)
    {
        levelUp();
        return false;
    }

    // Death freeze is over.
    if(status_ == StatusType::DEATH_FREEZE)
    {
        status_ = StatusType::DEATH_ANIMATE;
        pacman_.setDead(true);
        // TODO : hide ghosts
        return false;
    }

    // Death animation is over.
    if(status_ == StatusType::DEATH_ANIMATE && !pacman_.isDead())
    {
        lostLife();
        return false;
    }

    // Eating ghost animation is over.
    if(status_ == StatusType::EATING_GHOST)
    {
        status_ = StatusType::RUNNING;
        pacman_.show();
        return true;
    }

    // Game is not read to run yet.
    return (status_ == StatusType::RUNNING);
}

void Game::handleEntitiesCollisions()
{
    bool lowScore = score_ < constants::NEW_UP_POINTS_CAP;

    // Get pacman sprite position.
    auto pacman = pacman_.getSpritePosition();

    // Get pacman current cell.
    auto pacman_position = Position{{pacman.x, pacman.y}};
    auto cell_position = pacman_position.getPositionUnscaled(
            map_.getCellSize());
    auto cell = map_.getCell(cell_position);
    auto entity = cell->getEntity();

    // Cell has an active entity that collided with Pacman.
    if (cell && entity && entity->isEnabled() &&
        SDL_HasIntersection(&pacman, &entity->getSpritePosition()))
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
            // Freeze game (60 frames) before the game level up animation.
            status_ = StatusType::LEVEL_UP_FREEZE;
            counter_.start(60);
        } else if (cell->getType() == CellType::ENERGIZER) // Superpower.
        {
            pacman_.setSuperpower(true);
            // TODO : ghost scared (timer) into ghost blinking (ticks)
        }
    }

    // Fruit is active and collided with Pacman.
    if (fruit_.isEnabled() &&
        SDL_HasIntersection(&pacman, &fruit_.getSpritePosition()))
    {
        // Disables fruit.
        fruit_.setEnabled(false);
        score_ += fruit_.getPoints();
        // Displays points earned.
        // TODO : display points sprite
    }

    for (auto &ghost: ghosts_)
    {
        // Ghost is active and collided with Pacman.
        if (ghost.isEnabled() &&
            SDL_HasIntersection(&pacman, &ghost.getSpritePosition()))
        {
            if (!pacman_.isSuperpower()) // Superpower disabled : death.
            {
                // Freeze game (60 frames) before the death animation.
                status_ = StatusType::DEATH_FREEZE;
                counter_.start(60);
                // TODO : ghosts status animate
                continue;
            }

            // Disables ghost & updates game.
            ghost.setEnabled(false);
            score_ += ghost.getPoints();

            // Eating animation.
            status_ = StatusType::EATING_GHOST;
            counter_.start(60);
            pacman_.hide();

            // Display points sprite.
            // TODO : display points sprite

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

int Game::getSavedHighScore()
{
    high_score_ = stoi(SaveGame::getHighScore());
    return high_score_;
}

bool Game::updateHighScore()
{
    if (score_ > high_score_)
    {
        high_score_ = score_;
        return true;
    }
    return false;

}

int Game::getHighScore() const
{
    return high_score_;
}

void Game::setHighScore(int highScore)
{
    high_score_ = highScore;
}

void Game::quit() {
    window_.free();
}
