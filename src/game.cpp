//
// Created by matthieu on 08/02/2023.
//

#include "../include/game.h"

Game::Game() = default;

Game::Game(int width, int height, int cell_size, const char *file_path,
           int lives)
{

    map_ = Map{width, height, cell_size, loadCellTypesFromFile(file_path)};
    window_ = Window{constants::WINDOW_MAP_WIDTH, constants::WINDOW_MAP_HEIGHT, "Pacman"};
    lives_ = lives;

    // Pacman
    pacman_ = Pacman(
            Position{{constants::WINDOW_PACMAN_X, constants::WINDOW_PACMAN_Y}},
            pacman_left.getSprite(), constants::PACMAN_SPEED, pacman_left,
            pacman_right, pacman_up, pacman_down, 5000, pacman_death);

    // Fruits
    vector<FruitObject> fruits = {
            {100, {1}, {{fruit_cherry_1, fruit_cherry_2}, false, 10}},
            {300, {2}, {{fruit_strawberry_1, fruit_strawberry_2}, false, 10}},
            {500, {3, 4}, {{fruit_orange_1, fruit_orange_2}, false, 10}},
            {700, {5, 6}, {{fruit_apple_1, fruit_apple_2}, false, 10}},
            {1000, {7,  8}, {{fruit_melon_1, fruit_melon_2}, false, 10}},
            {2000, {9,  10}, {{fruit_flagship_1, fruit_flagship_2}, false, 10}},
            {3000, {11, 12}, {{fruit_bell_1, fruit_bell_2}, false, 10}},
            {5000, {13}, {{fruit_key_1, fruit_key_2},  false, 10}}
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
    shared_ptr<Entity> entity;

    // Cell has an active entity that collided with Pacman.
    if (cell && (entity = cell->getEntity()) && entity->isEnabled() &&
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
