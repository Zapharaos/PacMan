/**
 * @file game.h
 * @brief Implementation of the `Game` class, which represents the Pac-Man game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 08/02/2023
 */

#include "../include/game.h"

Game::Game() = default;

Game::Game(const Map &map, Window window, unsigned long high_score) : map_(map), window_(std::move(window)), high_score_(high_score)
{
    pellets_total_ = map.getCellsWithEntities().size();
    lives_ = config::settings::kLives;
    status_ = StatusType::kGameStartFreeze;
    fruit_ = Fruit{pellets_total_};
    // Pacman and ghosts already done at compilation (default).
}

void Game::tick(const Direction &direction) {
    // Display Welcome screen
    if (status_ == StatusType::kWelcomeScreen) {
        displayWelcomeScreen();
    }
    // Game is paused, nothing to do.
    if (status_ == StatusType::kPaused)
        return;

    // Handle status.
    bool running = handleStatus();

    if (!running && pacman_.isDead()) // Death animation still ongoing.
    {
        pacman_.death();
    }
    else if (running)
    {
        // Get pacman sprite position.
        auto pacman = pacman_.getSprite().getPosition();
        auto pacman_previous_direction = pacman_.getPreviousDirection();
        auto pacman_cell_position = pacman_.getPosition().scaleDown(map_.getCellSize());

        // Tick entities.
        fruit_.tick();
        pacman_.tick(map_, direction);
        ghosts_.tick(map_, pacman_cell_position, pacman_previous_direction);

        // Handle collisions.
        handleEntitiesCollisions(pacman);
    }

    // Update game visuals.
    display();
}

void Game::display() {
    window_.clear();
    // Map.
    window_.draw(map_, config::dimensions::kScoreBoardHeight);

    // Points
    window_.writeHighScore();
    updateHighScore();
    window_.updateHighScore(high_score_);
    window_.updateScore(score_);

    //Fruits
    window_.updateFruits();

    //Lives
    window_.updateLives(lives_);

    // Pellets
    for (auto &cell: map_.getCellsWithEntities()) {
        auto entity = cell->getEntity();

        // Blinking energizer (homogenize counter even if disabled)
        if (cell->getType() == CellType::kEnergizer &&
            !entity->tickVisibility())
            continue;

        // Entity disabled
        if (!entity->isEnabled())
            continue;

        // Display entity
        window_.draw(*entity, config::dimensions::kScoreBoardHeight);
    }

    // Fruit
    if (fruit_.isEnabled()) {
        // Display entity
        window_.draw(fruit_, config::dimensions::kScoreBoardHeight);
    } else if (fruit_.isCounterActive()) {
        fruit_.counterIncrement();
        //TODO better way to center
        if (fruit_.getPoints() >= 1000) {
            window_.writeScorePoints(1000, config::positions::entities::kFruitPointsX+5, config::positions::entities::kFruitPointsY + config::dimensions::kScoreBoardHeight,
                                     visuals::fruit::kScale, colours::kPink);
        } else {
            window_.writeScorePoints(fruit_.getPoints(), config::positions::entities::kFruitPointsX,
                                     config::positions::entities::kFruitPointsY + config::dimensions::kScoreBoardHeight,
                                     visuals::fruit::kScale, colours::kPink);
        }
    }

    // Ghosts
    /*for(auto &ghost : ghosts_)
        if(!ghost.isHidden())
            window_.draw(ghost, config::dimensions::kScoreBoardHeight);*/
    for(auto &ghost : ghosts_.getGhostsAsEntities())
    {
        if(!ghost->isHidden())
            window_.draw(ghost, config::dimensions::kScoreBoardHeight);
    }

    // Pacman
    if (!pacman_.isHidden())
        window_.draw(pacman_, config::dimensions::kScoreBoardHeight);

    if (status_ == StatusType::kGameStartAnimate) {
        window_.writeWord("READY!", 280, 615, 2, 3, colours::kYellow);
        if (counter_.getCount() <= config::settings::kDurationGameStartFreeze && counter_.isActive()) {
            window_.writeWord("PLAYER ONE", 229, 453, 2, 2.9, colours::kCyan);
        }
    }

    window_.update();
}

bool Game::handleStatus() {
    // Processing animations.
    if (counter_.isActive()) {

        counter_.increment();

        // Superpower active
        if(status_ == StatusType::kSuperpower)
            return true;

        // Map blinking
        if (status_ == StatusType::kLevelUpAnimate)
            map_.animate();

        if (status_ == StatusType::kGameStartAnimate) {
            if (counter_.getCount() >= config::settings::kDurationGameStartFreeze) {
                pacman_.show();
                ghosts_.show();
            } else {
                pacman_.hide();
                ghosts_.hide();
            }
        }

        return false;
    }

    // Game level up freeze is over.
    if (status_ == StatusType::kLevelUpFreeze) {
        // Start level up animation.
        status_ = StatusType::kLevelUpAnimate;
        counter_.start(config::settings::kDurationLevelupBlinking);
        // TODO : hide ghosts
        return false;
    }

    // Game is begining freeze
    if (status_ == StatusType::kGameStartFreeze) {
        // Draw pacman and ghosts
        status_ = StatusType::kGameStartAnimate;
        // Start level up animation.
        counter_.start(config::settings::kDurationGameStartFreeze * 2);
        return false;
    }

    if (status_ == StatusType::kGameStartAnimate && !counter_.isActive()) {
        status_ = StatusType::kRunning;
    }

    // Game level up animation is over.
    if (status_ == StatusType::kLevelUpAnimate) {
        //Fruits
        window_.addFruits(fruit_.getSprite().getImage());
        levelUp();
        return false;
    }

    // Death freeze is over.
    if (status_ == StatusType::kDeathFreeze) {
        status_ = StatusType::kDeathAnimate;
        pacman_.kill();
        // TODO : hide ghosts
        return false;
    }

    // Death animation is over.
    if (status_ == StatusType::kDeathAnimate)
    {
        if (!pacman_.isDead())
            lostLife();
        return false;
    }

    // Eating ghost animation is over.
    if (status_ == StatusType::kEatingGhost) {
        pacman_.show();
        counter_.loadSaveWithDifference();
        status_ = counter_.isActive() ? StatusType::kSuperpower : StatusType::kRunning;
        return true;
    }

    if(status_ == StatusType::kSuperpower)
    {
        status_ = StatusType::kRunning;
        ghosts_.unfrightened();
    }

    // Game is not ready to run yet.
    return (status_ == StatusType::kRunning);
}

void Game::handleEntitiesCollisions(const SDL_Rect &pacman) {
    bool lowScore = score_ < config::settings::kNewLifeAtPoints;

    // Get pacman current cell.
    auto pacman_position = Position{pacman.x, pacman.y};
    auto cell_position = pacman_position.scaleDown(map_.getCellSize());
    auto cell = map_.getCell(cell_position);
    std::shared_ptr<Entity> entity;

    // Cell has an active entity that collided with Pacman.
    if (cell && (entity = cell->getEntity()) && entity->isEnabled() &&
        SDL_HasIntersection(&pacman, &entity->getSprite().getPosition())) {
        // Disables entity.
        entity->setEnabled(false);
        score_ += entity->getPoints();

        // Freeze pacman.
        pacman_.freeze();
        pacman_.count(config::settings::kDurationEatenPelletFreeze);

        // Updates fruit.
        ++pellets_eaten_;
        fruit_.update(pellets_eaten_, level_);

        // Updates game.
        if (pellets_eaten_ == pellets_total_) // Level up.
        {
            // Freeze game before the game level up animation.
            status_ = StatusType::kLevelUpFreeze;
            counter_.start(config::settings::kDurationLevelupFreeze);
        } else if (cell->getType() == CellType::kEnergizer) // Superpower.
        {
            // Freeze pacman.
            pacman_.freeze();
            pacman_.count(config::settings::kDurationEatenEnergizerFreeze);

            status_ = StatusType::kSuperpower;
            counter_.start(config::settings::kDurationSuperpower);
            ghosts_eaten = 0;
            ghosts_.frightened();
        }
    }

    // Fruit is active.
    if (fruit_.isEnabled()) {
        // Collided with Pacman.
        if (SDL_HasIntersection(&pacman, &fruit_.getSprite().getPosition())) {
            // Disables fruit.
            fruit_.setEnabled(false);
            fruit_.count(config::settings::kDurationFruitPoints);
            score_ += fruit_.getPoints();
        }
    }

    for (auto &ghost : ghosts_.getGhostsAsEntities())
    {
        // Ghost is active and collided with Pacman.
        if (ghost->isEnabled() &&
            SDL_HasIntersection(&pacman, &ghost->getSprite().getPosition()))
        {
            // Not dead yet && superpower disabled : death.
            if (!pacman_.isDead() && status_ != StatusType::kSuperpower)
            {
                // Freeze game (60 frames) before the death animation.
                status_ = StatusType::kDeathFreeze;
                counter_.start(config::settings::kDurationDeathFreeze);
                // TODO : ghosts status animate
            } else
            {
                // Disables ghost & updates game.
                ghost->setEnabled(false);
                ghost->kill();
                auto value = (1 << (ghosts_eaten++));
                score_ += ghost->getPoints() * value;

                // Eating animation.
                status_ = StatusType::kEatingGhost;
                counter_.save();
                counter_.start(config::settings::kDurationEatenGhostFreeze);
                pacman_.hide();

                // Display points sprite.
                // TODO : display points sprite
            }
        }
    }

    // Check if the score has evolved up the new life's limit.
    if (lowScore && score_ >= config::settings::kNewLifeAtPoints)
        ++lives_;
}

void Game::togglePause() {
    if (status_ == StatusType::kRunning)
        status_ = StatusType::kPaused;
    else if (status_ == StatusType::kPaused)
        status_ = StatusType::kRunning;
}

void Game::levelUp() {
    // Update game settings.
    ++level_;
    pellets_eaten_ = 0;
    status_ = StatusType::kRunning;

    // Reset entities.
    map_.reset();
    pacman_.reset();
    ghosts_.reset();

    // TODO : speed and timers : up
}

void Game::lostLife() {
    if ((--lives_) == 0) // Game lost : reset the game settings
    {
        lives_ = config::settings::kLives; // temp
        score_ = 0;
        level_ = 1;
        pellets_eaten_ = 0;
        map_.reset();
    }

    status_ = StatusType::kRunning;
    pacman_.reset();
    ghosts_.reset();

    // TODO : speed and timers : reset
}

bool Game::updateHighScore() {
    if (score_ > high_score_) {
        high_score_ = score_;
        return true;
    }
    return false;

}

void Game::displayWelcomeScreen() {

    int scale = 3;
    int pos_x = 0;
    int pos_y = 5;
    window_.writeWord("1UP    HIGH SCORE    2UP", pos_x, pos_y, 1, scale);


    pos_x = 100;
    pos_y = 50;
    window_.writeWord("CHARACTER  /  NICKNAME ", pos_x, pos_y, 1, scale);

    pos_x = 10;
    pos_y += constants::BMP_CHARACTER_WIDTH * scale + 5;

    //Draw blinky
    SDL_Rect dst;
    dst.x = pos_x;
    dst.y = pos_y;
    dst.h = window_.getGhostBlinkyR().h * scale;
    dst.w = window_.getGhostBlinkyR().w * scale;
    drawObject(window_.getRenderer(), window_.getTexture(), window_.getGhostBlinkyR(), dst, 1);

    pos_x = 100;
    window_.writeWord("- SHADOW     ' BLINKY ' ", pos_x, dst.y, 1, scale, colours::kRed);

    //Draw pinky
    dst.y += dst.h + 4;
    drawObject(window_.getRenderer(), window_.getTexture(), window_.getGhostPinkyR(), dst, 1);
    window_.writeWord("- SPEEDY     ' PINKY ' ", pos_x, dst.y, 1, scale, colours::kPink);

    //Draw inky
    dst.y += dst.h + 4;
    drawObject(window_.getRenderer(), window_.getTexture(), window_.getGhostInkyR(), dst, 1);
    window_.writeWord("- BASHFUL     ' INKY  ' ", pos_x, dst.y, 1, scale, colours::kCyan);

    //Draw clyde
    dst.y += dst.h + 4;
    drawObject(window_.getRenderer(), window_.getTexture(), window_.getGhostClydeR(), dst, 1);
    window_.writeWord("- POKEY     ' CLYDE ' ", pos_x + 10, dst.y, 1, scale, colours::kOrange);
    window_.update();

}

//TODO
void Game::quit() {
    window_.clear();
}

unsigned long Game::getHighScore() const {
    return high_score_;
}

int Game::getLevel() const {
    return level_;
}


