/**
 * @file game.h
 * @brief Implementation of the `Game` class, which represents the Pac-Man game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 08/02/2023
 */

#include "../include/game.h"

Game::Game() = default;

Game::Game(const Map &map, Window window) : map_(map), window_(std::move(window))
{
    pellets_total_ = map.getCellsWithEntities().size();
    lives_ = config::settings::kLives;
    fruit_ = Fruit{pellets_total_};
    // Pacman already done initialization.
    getLocalHighScore();

    // TODO : setup ghosts
}

void Game::tick(const Direction &direction)
{

    // Game is paused, nothing to do.
    if(status_ == StatusType::kPaused)
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

    // Points
    window_.writeHighScore();
    updateHighScore();
    window_.updateHighScore(high_score_);
    window_.updateScore(score_);

    //Fruits
    window_.updateFruits();

    //Lives
    window_.updateLives(lives_);



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
        if (cell->getType() == CellType::kEnergizer &&
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
        if (status_ == StatusType::kLevelUpAnimate)
            map_.animate();

        counter_.increment();
        return false;
    }

    // Game level up freeze is over.
    if (status_ == StatusType::kLevelUpFreeze)
    {
        // Start level up animation.
        status_ = StatusType::kLevelUpAnimate;
        counter_.start(config::settings::kDurationLevelupBlinking);
        // TODO : hide ghosts
        return false;
    }

    // Game level up animation is over.
    if (status_ == StatusType::kLevelUpAnimate)
    {
        //Fruits
        window_.addFruits(fruit_.getSpriteImage());
        levelUp();
        return false;
    }

    // Death freeze is over.
    if(status_ == StatusType::kDeathFreeze)
    {
        status_ = StatusType::kDeathAnimate;
        pacman_.setDead(true);
        // TODO : hide ghosts
        return false;
    }

    // Death animation is over.
    if(status_ == StatusType::kDeathAnimate && !pacman_.isDead())
    {
        lostLife();
        return false;
    }

    // Eating ghost animation is over.
    if(status_ == StatusType::kEatingGhost)
    {
        status_ = StatusType::kRunning;
        pacman_.show();
        return true;
    }

    // Game is not read to run yet.
    return (status_ == StatusType::kRunning);
}

void Game::handleEntitiesCollisions()
{
    bool lowScore = score_ < config::settings::kNewLifeAtPoints;

    // Get pacman sprite position.
    auto pacman = pacman_.getSpritePosition();

    // Get pacman current cell.
    auto pacman_position = Position{{pacman.x, pacman.y}};
    auto cell_position = pacman_position.getPositionUnscaled(
            map_.getCellSize());
    auto cell = map_.getCell(cell_position);
    std::shared_ptr<Entity> entity;

    // Cell has an active entity that collided with Pacman.
    if (cell && (entity = cell->getEntity()) && entity->isEnabled() &&
        SDL_HasIntersection(&pacman, &entity->getSpritePosition()))
    {
        // Disables entity.
        entity->setEnabled(false);
        score_ += entity->getPoints();

        // Freeze pacman.
        pacman_.count(config::settings::kDurationEatenPelletFreeze);

        // Updates fruit.
        ++pellets_eaten_;
        fruit_.update(pellets_eaten_, level_);

        // Updates game.
        if (pellets_eaten_ == pellets_total_) // Level up.
        {
            // Freeze game (60 frames) before the game level up animation.
            status_ = StatusType::kLevelUpFreeze;
            counter_.start(config::settings::kDurationLevelupFreeze);
        } else if (cell->getType() == CellType::kEnergizer) // Superpower.
        {
            pacman_.setSuperpower(true);
            // TODO : ghost scared (timer) into ghost blinking (ticks)
        }
    }

    // Fruit is active.
    if (fruit_.isEnabled())
    {
        // Collided with Pacman.
        if (SDL_HasIntersection(&pacman, &fruit_.getSpritePosition()))
        {
            // Disables fruit.
            fruit_.setEnabled(false);
            score_ += fruit_.getPoints();
            // Displays points earned.
            // TODO : display points sprite
        }
        fruit_.tick();
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
                status_ = StatusType::kDeathFreeze;
                counter_.start(config::settings::kDurationDeathFreeze);
                // TODO : ghosts status animate
                continue;
            }

            // Disables ghost & updates game.
            ghost.setEnabled(false);
            score_ += ghost.getPoints();

            // Eating animation.
            status_ = StatusType::kEatingGhost;
            counter_.start(config::settings::kDurationEatenGhostFreeze);
            pacman_.hide();

            // Display points sprite.
            // TODO : display points sprite

            // TODO : ghost going back to home
        }
    }

    if(pacman_.isSuperpower())
        pacman_.tick();

    // Check if the score has evolved up the new life's limit.
    if (lowScore && score_ >= config::settings::kNewLifeAtPoints)
        ++lives_;
}

void Game::togglePause()
{
    if(status_ == StatusType::kRunning)
        status_ = StatusType::kPaused;
    else if(status_ == StatusType::kPaused)
        status_ = StatusType::kRunning;
}

void Game::levelUp()
{
    // Update game settings.
    ++level_;
    pellets_eaten_ = 0;
    status_ = StatusType::kRunning;


    // Reset entities.
    map_.reset();
    pacman_.reset(
            Position{{config::positions::kPacmanX, config::positions::kPacmanY}});

    // TODO : ghosts reset
    // TODO : speed and timers : up
}

void Game::lostLife()
{
    if ((--lives_) == 0) // Game lost : reset the game settings
    {
        lives_ = config::settings::kLives; // temp
        score_ = 0;
        level_ = 1;
        pellets_eaten_ = 0;
        map_.reset();
    }

    // Reset the entities (might only lose a life).
    status_ = StatusType::kRunning;
    pacman_.reset(
            Position{{config::positions::kPacmanX, config::positions::kPacmanY}});

    // TODO : ghosts reset
    // TODO : speed and timers : reset
}

int Game::getLocalHighScore()
{
    high_score_ = stoi(getSavedHighScore());
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

void Game::quit() {
    window_.free();
}
