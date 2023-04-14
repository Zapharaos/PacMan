/**
 * @file game.h
 * @brief Implementation of the `Game` class, which represents the Pac-Man game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 08/02/2023
 */

#include "../include/game.h"

Game::Game() = default;

Game::Game(const Map &map, Window window, unsigned long high_score) : map_(map), window_(std::move(window)),
                                                                      high_score_(high_score) {

    pellets_total_ = map.getCellsWithEntities().size();
    lives_ = config::settings::kLives;
    status_ = StatusType::kGameStartFreeze;

    // Pacman already done at compilation (default).
    fruit_ = Fruit{pellets_total_};
    ghosts_.emplace_back(Ghost{Ghost::GhostType::kBlinky,
                               Position{config::positions::entities::blinky::kDefaultX,
                                        config::positions::entities::blinky::kDefaultY},
                               Position{config::positions::entities::blinky::kTargetX,
                                        config::positions::entities::blinky::kTargetY},
                               visuals::ghosts::blinky::left::kAnimation,
                               visuals::ghosts::blinky::right::kAnimation,
                               visuals::ghosts::blinky::up::kAnimation,
                               visuals::ghosts::blinky::down::kAnimation});
    ghosts_.emplace_back(Ghost{Ghost::GhostType::kPinky,
                               Position{config::positions::entities::blinky::kDefaultX,
                                        config::positions::entities::blinky::kDefaultY},
                               Position{config::positions::entities::pinky::kTargetX,
                                        config::positions::entities::pinky::kTargetY},
                               visuals::ghosts::pinky::left::kAnimation,
                               visuals::ghosts::pinky::right::kAnimation,
                               visuals::ghosts::pinky::up::kAnimation,
                               visuals::ghosts::pinky::down::kAnimation});
    ghosts_.emplace_back(Ghost{Ghost::GhostType::kInky,
                               Position{config::positions::entities::blinky::kDefaultX,
                                        config::positions::entities::blinky::kDefaultY},
                               Position{config::positions::entities::inky::kTargetX,
                                        config::positions::entities::inky::kTargetY},
                               visuals::ghosts::inky::left::kAnimation,
                               visuals::ghosts::inky::right::kAnimation,
                               visuals::ghosts::inky::up::kAnimation,
                               visuals::ghosts::inky::down::kAnimation});
    ghosts_.emplace_back(Ghost{Ghost::GhostType::kClyde,
                               Position{config::positions::entities::blinky::kDefaultX,
                                        config::positions::entities::blinky::kDefaultY},
                               Position{config::positions::entities::clyde::kTargetX,
                                        config::positions::entities::clyde::kTargetY},
                               visuals::ghosts::clyde::left::kAnimation,
                               visuals::ghosts::clyde::right::kAnimation,
                               visuals::ghosts::clyde::up::kAnimation,
                               visuals::ghosts::clyde::down::kAnimation});
}

void Game::tick(const Direction &direction) {
    // Game is paused, nothing to do.
    if (status_ == StatusType::kPaused)
        return;

    // Handle status.
    bool running = handleStatus();

    if (!running && pacman_.isDead()) // Death animation still ongoing.
    {
        pacman_.death();
    } else if (running) {
        // Get pacman sprite position.
        auto pacman = pacman_.getSprite().getPosition();

        // Tick entities.
        fruit_.tick();
        pacman_.tick(map_, direction);
        auto pacman_position = pacman_.getPosition().getPositionUnscaled(map_.getCellSize());
        for (auto &ghost: ghosts_)
            ghost.tick(map_, pacman_position);

        // Handle collisions.
        handleEntitiesCollisions(pacman);
        //Update high score
        updateHighScore();
    }

    // Update game visuals.

    display();
}


void Game::display() {

    window_.clear();


    // Points
    window_.writeHighScore();
    updateHighScore();

    window_.updateHighScore(high_score_);
    window_.updateScore(score_);

    if (status_ == StatusType::kWelcomeScreen) {
        displayWelcomeScreen();
        return;
    }

    window_.updateHighScore(high_score_);

    // Map.
    window_.draw(map_, config::dimensions::kScoreBoardHeight);

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
        //TODO better way to center
        fruit_.counterIncrement();

    }

    displayPoints();

    // Ghosts
    for (auto &ghost: ghosts_)
        if (!ghost.isHidden())
            window_.draw(ghost, config::dimensions::kScoreBoardHeight);

    // Pacman
    if (!pacman_.isHidden())
        window_.draw(pacman_, config::dimensions::kScoreBoardHeight);

    if (status_ == StatusType::kGameStartAnimate) {
        window_.writeWord("READY!", config::positions::display::kReadyTextX,
                          config::positions::display::kReadyTextY,
                          config::positions::offsets::kReady, 3, colours::kYellow);
        if (counter_.getCount() <= config::settings::kDurationGameStartFreeze && counter_.isActive()) {
            window_.writeWord("PLAYER ONE", config::positions::display::kPlayerOneTextX,
                              config::positions::display::kPlayerOneTextY,
                              config::positions::offsets::kPlayerOne, 2.9, colours::kCyan);
        }
    }

    window_.update();
}

bool Game::handleStatus() {
    // Processing animations.
    if (counter_.isActive()) {

        counter_.increment();

        // Superpower active
        if (status_ == StatusType::kSuperpower)
            return true;

        // Map blinking
        if (status_ == StatusType::kLevelUpAnimate)
            map_.animate();

        if (status_ == StatusType::kGameStartAnimate) {
            if (counter_.getCount() >= config::settings::kDurationGameStartFreeze) {
                pacman_.show();
                for (auto &ghost: ghosts_)
                    ghost.show();
            } else {
                pacman_.hide();
                for (auto &ghost: ghosts_)
                    ghost.hide();

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

    if (status_ == StatusType::kGameStartAnimate) {
        status_ = StatusType::kRunning;
    }

    if (status_ == StatusType::kWelcomeScreen) {
        status_ = StatusType::kGameStartFreeze;
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
    if (status_ == StatusType::kDeathAnimate) {
        if (!pacman_.isDead())
            lostLife();
        return false;
    }

    // Eating ghost animation is over.
    if (status_ == StatusType::kEatingGhost) {
        pacman_.show();
        for (auto &ghost: ghosts_) {
            if (ghost.isHidden()) {
                ghost.show();
            }
        }

        counter_.loadSaveWithDifference();
        status_ = counter_.isActive() ? StatusType::kSuperpower : StatusType::kRunning;
        return true;
    }

    if (status_ == StatusType::kSuperpower) {
        status_ = StatusType::kRunning;
        for (auto &ghost: ghosts_)
            ghost.unfrightened();
    }

    // Game is not ready to run yet.
    return (status_ == StatusType::kRunning);
}

void Game::handleEntitiesCollisions(const SDL_Rect &pacman) {
    bool lowScore = score_ < config::settings::kNewLifeAtPoints;

    // Get pacman current cell.
    auto pacman_position = Position{pacman.x, pacman.y};
    auto cell_position = pacman_position.getPositionUnscaled(
            map_.getCellSize());
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
            for (auto &ghost: ghosts_)
                ghost.frightened();
        }
    }

    // Fruit is active.
    if (fruit_.isEnabled()) {
        // Collided with Pacman.
        if (SDL_HasIntersection(&pacman, &fruit_.getSprite().getPosition())) {
            // Disables fruit.
            fruit_.setEnabled(false);
            fruit_.count(config::settings::kFramesPerSecond);
            addPointsToDisplay(fruit_.getPoints(), visuals::fruit::kScale, colours::kPink,
                               config::positions::entities::kFruitPointsX,
                               config::positions::entities::kFruitPointsY);
            score_ += fruit_.getPoints();
        }
    }

    for (auto &ghost: ghosts_) {
        // Ghost is active and collided with Pacman.
        if (ghost.isEnabled() &&
            SDL_HasIntersection(&pacman, &ghost.getSprite().getPosition())) {
            // Not dead yet && superpower disabled : death.
            if (!pacman_.isDead() && status_ != StatusType::kSuperpower) {
                // Freeze game (60 frames) before the death animation.
                status_ = StatusType::kDeathFreeze;
                counter_.start(config::settings::kDurationDeathFreeze);
                // TODO : ghosts status animate
                break;
            }

            // Disables ghost & updates game.
            ghost.setEnabled(false);
            unsigned long points_won = ghost.getPoints() * (1 << (ghosts_eaten++));
            score_ += points_won;

            // Eating animation.
            status_ = StatusType::kEatingGhost;
            counter_.save();
            counter_.start(config::settings::kDurationEatenGhostFreeze);
            pacman_.hide();
            ghost.hide();
            // Display points sprite.
            addPointsToDisplay(points_won, visuals::ghosts::kScale,
                               colours::kCyan,
                               ghost.getPosition().getAbscissa() + config::positions::offsets::kGhostPointsX,
                               ghost.getPosition().getOrdinate() + config::positions::offsets::kGhostPointsY);
            // TODO : ghost going back to home
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
    for (auto &ghost: ghosts_)
        ghost.reset();

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
        for (auto &ghost: ghosts_)
            ghost.reset();
    }

    status_ = StatusType::kRunning;
    pacman_.reset();

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


    float scale = 2.75;
    int pos_x = 0;
    int pos_y = 5;


    window_.writeWord("CHARACTER / NICKNAME ", config::positions::display::kCharaterNicknameX,
                      config::positions::display::kCharaterNicknameY, 1, 2.75);
    SDL_Rect dst;
    /* dst.x = config::positions::kGhostsX;
     dst.y = config::positions::kBlinkyY;*/

    dst.x = 60;
    dst.y = 170;
    dst.h = visuals::ghosts::blinky::right::sprite_1::kBitmapHeight * 2.75;
    dst.w = visuals::ghosts::blinky::right::sprite_1::kBitmapWidth * 2.75;

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 2) {
        //Blinky
        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::ghosts::blinky::right::sprite_1::kSprite.getImage(), dst);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 3) {
        window_.writeWord("- SHADOW", config::positions::display::kCharaterNicknameX,
                          180, 1, 2.75, colours::kRed);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 4) {
        window_.writeWord("'BLINKY' ", 360,
                          180, 1, 2.75, colours::kRed);
    }


    dst.y = 240;
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 5) {
        //Pinky
        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::ghosts::pinky::right::sprite_1::kSprite.getImage(), dst);
    }

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 6) {
        window_.writeWord("- SPEEDY", config::positions::display::kCharaterNicknameX,
                          250, 1, 2.75, colours::kPink);
    }

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 7) {
        window_.writeWord("'PINKY' ", 360,
                          250, 1, 2.75, colours::kPink);
    }


    dst.y = 310;

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 8) {
        //Inky
        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::ghosts::inky::right::sprite_1::kSprite.getImage(), dst);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 9) {
        window_.writeWord("- BASHFUL", config::positions::display::kCharaterNicknameX,
                          320, 1, 2.75, colours::kCyan);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 10) {
        window_.writeWord("'INKY' ", 360,
                          320, 1, 2.75, colours::kCyan);
    }


    dst.y = 380;
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 11) {
        //Clyde
        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::ghosts::clyde::right::sprite_1::kSprite.getImage(), dst);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 12) {
        window_.writeWord("- POKEY", config::positions::display::kCharaterNicknameX,
                          390, 1, 2.75, colours::kOrange);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 13) {
        window_.writeWord("'CLYDE' ", 360,
                          390, 1, 2.75, colours::kOrange);
    }

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 14) {
        //small pellet
        dst.x = 250;
        dst.y = 500;
        dst.h = visuals::pellet::kBitmapHeight * 3;
        dst.w = visuals::pellet::kBitmapWidth * 3;

        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::pellet::kSprite.getImage(), dst);
        dst.x = 280;
        dst.y = 495;
        window_.writeWord("10", dst.x, dst.y, 1, 2.2);


        dst.h = visuals::energizer::kBitmapHeight * 3;
        dst.w = visuals::energizer::kBitmapWidth * 3;
        dst.x = 242;
        dst.y = 520;
        // big Pellet
        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::energizer::kSprite.getImage(), dst);


        dst.x = 280;
        dst.y = 522;
        window_.writeWord("50", dst.x, dst.y, 1, 2.2);


        dst.h = characters::special::points::kBitmapHeight * 2.7;
        dst.w = characters::special::points::kBitmapWidth * 2.7;
        dst.x = 320;
        dst.y = 500;


        //pts for 10
        drawObject(window_.getRenderer(), window_.getTexture(),
                   characters::special::points::kSprite.getImage(),
                   dst);
        dst.y = 525;
        //pts for 50
        drawObject(window_.getRenderer(), window_.getTexture(),
                   characters::special::points::kSprite.getImage(),
                   dst);
    }

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 15) {
        dst.x = 70;
        dst.y = 600;
        window_.writeWord("` 1980 MIDWAY MFG. CO.", dst.x,
                          dst.y, 1, 2.75, colours::kPink);
    }


    //TODO ANIMATION
    dst.x = 60;
    dst.y = config::dimensions::kWindowHeight - 50;
    window_.writeWord("CREDIT 0", dst.x,
                      dst.y, 1, 2.75);
    //TODO ADD credit field  ?
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


void Game::displayPoints() {

    for (auto s = points_.begin(); s != points_.end();) {
        //If counter is still active
        if (std::get<2>(*s).isActive()) {
            //Change colour
            SDL_SetTextureColorMod(window_.getTexture().get(),
                                   std::get<0>(std::get<3>(*s)),
                                   std::get<1>(std::get<3>(*s)),
                                   std::get<2>(std::get<3>(*s)));


            drawObject(window_.getRenderer(), window_.getTexture(), std::get<0>(*s), std::get<1>(*s));

            std::get<2>(*s).increment();
            //Switch back to original colour
            SDL_SetTextureColorMod(window_.getTexture().get(),
                                   std::get<0>(colours::kWhite),
                                   std::get<1>(colours::kWhite),
                                   std::get<2>(colours::kWhite));
        } else {
            //Erase object to display from the vector
            points_.erase(s);
            return;
        }
        ++s;
    }
}

void Game::addPointsToDisplay(unsigned long points, float scale, std::tuple<int, int, int> colour, int x, int y) {

    auto found = window_.getPointsMap().find(points);
    //Check so no crashes happen in case unrecognised value is passed
    if (points == 0 || (found == window_.getPointsMap().end())) {
        return;
    }
    //setting up the sprite
    SDL_Rect src = window_.getPointsMap().at(points);
    SDL_Rect dest;
    dest.x = Window::centerImage(src, x);
    dest.y = y;
    dest.w = (int) ((float) src.w * scale);
    dest.h = (int) ((float) src.h * scale);
    //Adding Counter to the sprite to display
    Counter counter = *new Counter();
    counter.start(config::settings::kDurationPoints);
    //Adding the sprite and counter to the vector
    points_.emplace_back(src, dest, counter, colour);
}