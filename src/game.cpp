/**
 * @file game.h
 * @brief Implementation of the `Game` class, which represents the Pac-Man game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 08/02/2023
 */

#include "../include/game.h"


Game::Game() = default;

Game::Game(const Map &map, Window window, unsigned long high_score) :
        map_(map), window_(std::move(window)), high_score_(high_score)
{
    //TODOS GET SAVED HIGHSCORE
    pellets_total_ = map.getCellsWithEntities().size();
    lives_ = config::settings::kLives;
    counter_.start(config::settings::kWelcomeScreen);
    status_ = StatusType::kWelcomeScreen;
    fruit_ = Fruit{pellets_total_};
    // Pacman and ghosts already initialized with the default constructors.
}

void Game::tick(const Direction &direction)
{

    // Game is paused, nothing to do.
    if (status_ == StatusType::kPaused)
        return;

    // Handle status.
    bool running = handleStatus();

    if (!running && pacman_.isDead()) // Death animation still ongoing.
    {
        pacman_.death();
        ghosts_.animate();
    } else if (running)
    {
        // Get pacman sprite position.
        auto pacman = pacman_.getSprite().getPosition();
        auto pacman_previous_direction = pacman_.getPreviousDirection();
        auto pacman_cell_position = pacman_.getPosition().scaleDown(
                map_.getCellSize());

        // Tick entities.
        fruit_.tick();
        pacman_.tick(map_, direction);
        ghosts_.tick(map_, pacman_cell_position, pacman_previous_direction);
        for (auto &cell: map_.getCellsWithEntities())
            cell->getEntity()->tick();

        // Handle collisions.
        handleEntitiesCollisions(pacman);

        // Update high score
        if (score_ > high_score_)
            high_score_ = score_;
    }

    // Update game visuals.
    display();
}

void Game::display()
{

    window_.clear();

    // Points
    window_.writeHighScore();
    window_.updateHighScore(high_score_);
    window_.updateScore(score_);

    if (status_ == StatusType::kWelcomeScreen)
    {
        displayWelcomeScreen();
        return;
    }

    // Map.
    window_.draw(map_, config::dimensions::kScoreBoardHeight);

    //Fruits
    window_.updateFruits();

    //Lives
    window_.updateLives(lives_);

    // Pellets
    for (auto &cell: map_.getCellsWithEntities())
    {
        // Entity disabled or hidden
        if (!cell->getEntity()->isEnabled() || cell->getEntity()->isHidden())
            continue;

        // Display entity
        window_.draw(cell->getEntity(), config::dimensions::kScoreBoardHeight);
    }

    // Fruit
    if (fruit_.isEnabled())
    {
        // Display entity
        window_.draw(fruit_, config::dimensions::kScoreBoardHeight);
    }

    displayPoints();

    // Ghosts
    for (auto &ghost: ghosts_.getGhosts())
        if (!ghost->isHidden())
            window_.draw(ghost, config::dimensions::kScoreBoardHeight);

    // Pacman
    if (!pacman_.isHidden())
        window_.draw(pacman_, config::dimensions::kScoreBoardHeight);

    if (status_ == StatusType::kGameStartAnimate)
    {
        window_.writeWord("READY!", display::game_messages::kReadyTextX,
                          display::game_messages::kReadyTextY,
                          offsets::kReady, scales::kReadyTextScale,
                          colours::kYellow);

        if (counter_.getCount() <= config::settings::kDurationGameStartFreeze &&
            counter_.isActive())
        {
            window_.writeWord("PLAYER ONE",
                              display::game_messages::kPlayerOneTextX,
                              display::game_messages::kPlayerOneTextY,
                              offsets::kPlayerOne, scales::kPlayerOneText,
                              colours::kCyan);
        }
    }

    if (status_ == StatusType::kDeathAnimate_2)
    {
        window_.writeWord("READY!", display::game_messages::kReadyTextX,
                          display::game_messages::kReadyTextY,
                          offsets::kReady, scales::kReadyTextScale,
                          colours::kYellow);

    }
    if (status_ == StatusType::kGameOver)
    {
        window_.writeWord("GAME  OVER",
                          display::game_messages::kGameOverTextX,
                          display::game_messages::kGameOverTextY,
                          offsets::kGameOverText,
                          scales::kGameOverText, colours::kRed);

        window_.writeWord("CREDIT 0", display::game_messages::kCreditTextX,
                          display::game_messages::kCreditTextY,
                          offsets::kCreditText, scales::kCreditText);

    }


    window_.update();
}

bool Game::handleStatus()
{
    // Processing animations.
    if (counter_.isActive())
    {
        counter_.increment();

        // Superpower active
        if (status_ == StatusType::kSuperpower)
            return true;

        // Map blinking
        if (status_ == StatusType::kLevelUpAnimate)
            map_.animate();

        // Game frozen : pacman death
        if (status_ == StatusType::kDeathFreeze)
            ghosts_.animate();

        //Game Frozen : starting game
        if (status_ == StatusType::kGameStartAnimate)
        {
            if (counter_.getCount() >=
                config::settings::kDurationGameStartFreeze)
            {
                pacman_.show();
                for (auto &ghost: ghosts_.getGhosts())
                    ghost->show();
            } else
            {
                pacman_.hide();
                for (auto &ghost: ghosts_.getGhosts())
                    ghost->hide();
            }
        }
        if (status_ == StatusType::kDeathAnimate_2)
        {
            pacman_.show();
            for (auto &ghost: ghosts_.getGhosts())
                ghost->show();
        }
        return false;
    }

    // Game level up freeze is over.
    if (status_ == StatusType::kLevelUpFreeze)
    {
        // Start level up animation.
        status_ = StatusType::kLevelUpAnimate;
        counter_.start(config::settings::kDurationLevelupBlinking * 2);
        for (auto &ghost: ghosts_.getGhosts())
            ghost->hide();
        return false;
    }

    // Game is begining freeze
    if (status_ == StatusType::kGameStartFreeze)
    {
        if (lives_ == 0)
        {
            resetGame();
        }
        // Draw pacman and ghosts
        status_ = StatusType::kGameStartAnimate;
        // Start level up animation.
        counter_.start(config::settings::kDurationGameStartFreeze * 2);
        return false;
    }

    // Game start animation is done
    if (status_ == StatusType::kGameStartAnimate)
        status_ = StatusType::kRunning;

    // Welcome screen is done
    if (status_ == StatusType::kWelcomeScreen)
        status_ = StatusType::kGameStartFreeze;


    // Game level up animation is over.
    if (status_ == StatusType::kLevelUpAnimate)
    {
        levelUp();
        return false;
    }

    // Death freeze is over.
    if (status_ == StatusType::kDeathFreeze)
    {
        status_ = StatusType::kDeathAnimate;
        pacman_.kill();
        for (auto &ghost: ghosts_.getGhosts())
            ghost->hide();
        return false;
    }

    //Second part of death animation is done
    if (status_ == StatusType::kDeathAnimate_2)
    {
        status_ = StatusType::kRunning;
        return false;
    }

    // Game over animation is done
    if (status_ == StatusType::kGameOver)
    {
        resetGame();
        return false;
    }

    // Death animation is over.
    if (status_ == StatusType::kDeathAnimate && !pacman_.isDead())
    {
        lostLife();
        counter_.start(config::settings::kDurationTextDeathFreeze);
        if (lives_ == 0)
        {
            status_ = StatusType::kGameOver;
        } else
        {
            for (auto &ghost: ghosts_.getGhosts())
                ghost->show();
            status_ = StatusType::kDeathAnimate_2;
        }
    }
    // Eating ghost animation is over.
    if (status_ == StatusType::kEatingGhost)
    {
        pacman_.show();
        counter_.loadSaveWithDifference();
        status_ = counter_.isActive() ? StatusType::kSuperpower
                                      : StatusType::kRunning;
        return true;
    }

    if (status_ == StatusType::kSuperpower)
    {
        status_ = StatusType::kRunning;
        for (auto &ghost: ghosts_.getGhosts())
            ghost->unfrightened();
    }
    // Game is not ready to run yet.
    return (status_ == StatusType::kRunning);
}

void Game::handleEntitiesCollisions(const SDL_Rect &pacman)
{
    bool lowScore = score_ < config::settings::kNewLifeAtPoints;

    // Get pacman current cell.
    auto pacman_position = Position{pacman.x, pacman.y};
    auto cell_position = pacman_position.scaleDown(map_.getCellSize());
    auto cell = map_.getCell(cell_position);
    std::shared_ptr<Entity> entity;

    // Cell has an active entity that collided with Pacman.
    if (cell && (entity = cell->getEntity()) && entity->isEnabled() &&
        SDL_HasIntersection(&pacman, &entity->getSprite().getPosition()))
    {
        // Disables entity.
        entity->setEnabled(false);
        score_ += entity->getPoints();

        // Freeze pacman.
        pacman_.freeze(config::settings::kDurationEatenPelletFreeze);

        // Updates fruit.
        ++pellets_eaten_;
        fruit_.update(pellets_eaten_, level_);

        // Free ghost from house if special conditions are met.
        ghosts_.pelletEaten();

        // Updates game.
        if (pellets_eaten_ == pellets_total_) // Level up.
        {
            // Freeze game before the game level up animation.
            status_ = StatusType::kLevelUpFreeze;
            counter_.start(config::settings::kDurationLevelupFreeze);
        } else if (cell->getType() == CellType::kEnergizer) // Superpower.
        {
            // Freeze pacman.
            pacman_.freeze(config::settings::kDurationEatenEnergizerFreeze);

            // Start superpower.
            status_ = StatusType::kSuperpower;
            counter_.start(config::settings::kDurationSuperpower);
            ghosts_eaten = 0;
            ghosts_.frightened();
        }
    }

    // Fruit is active and collided with pacman.
    if (fruit_.isEnabled() &&
        SDL_HasIntersection(&pacman, &fruit_.getSprite().getPosition()))
    {
        // Disables fruit.
        fruit_.setEnabled(false);
        score_ += fruit_.getPoints();
        addPointsToDisplay(fruit_.getPoints(), visuals::fruit::kScale,
                           colours::kPink,
                           config::positions::entities::kFruitPointsX,
                           config::positions::entities::kFruitPointsY);
    }

    for (auto &ghost: ghosts_.getGhosts())
    {
        // Ghost is active and collided with Pacman.
        if (ghost->isEnabled() &&
            SDL_HasIntersection(&pacman, &ghost->getSprite().getPosition()))
        {
            // Ghost not frightened : death.
            if (!ghost->isFrightened())
            {
                // Freeze game (60 frames) before the death animation.
                status_ = StatusType::kDeathFreeze;
                counter_.start(config::settings::kDurationDeathFreeze);
                break;
            }

            auto points = ghost->getPoints() * (1 << (ghosts_eaten++));

            // Disables ghost & updates game.
            score_ += points;
            ghost->kill();
            pacman_.hide();

            // Eating animation.
            status_ = StatusType::kEatingGhost;
            counter_.save();
            counter_.start(config::settings::kDurationEatenGhostFreeze);

            // Display points sprite.
            addPointsToDisplay(points, visuals::ghosts::kScale,
                               colours::kCyan,
                               ghost->getPosition().getAbscissa() +
                               offsets::kGhostPointsX,
                               ghost->getPosition().getOrdinate() +
                               offsets::kGhostPointsY);
        }
    }

    // Check if the score has evolved up the new life's limit.
    if (lowScore && score_ >= config::settings::kNewLifeAtPoints)
        ++lives_;
}

void Game::togglePause()
{
    if (status_ == StatusType::kRunning)
        status_ = StatusType::kPaused;
    else if (status_ == StatusType::kPaused)
        status_ = StatusType::kRunning;
}

void Game::levelUp()
{
    window_.addFruits(fruit_.getSprite().getImage());

    // Update game settings.
    ++level_;
    pellets_eaten_ = 0;
    status_ = StatusType::kRunning;

    // Reset entities.
    map_.reset();
    fruit_.reset();
    pacman_.reset();
    ghosts_.levelUp();
}

void Game::lostLife()
{
    status_ = StatusType::kRunning;
    pacman_.reset();

    if ((--lives_) == 0) // Game lost : reset the game settings
    {
        status_ = StatusType::kGameStartFreeze;
        fruit_.reset();
    }

    status_ = StatusType::kRunning;
    pacman_.reset();
    ghosts_.restartFromHouse();
    points_.clear();
}

void Game::resetGame()
{
    //Reset game parameters and variables
    lives_ = config::settings::kLives;
    score_ = 0;
    level_ = 1;
    pellets_eaten_ = 0;
    map_.reset();
    pacman_.reset();
    fruit_.reset();
    ghosts_.reset();
    points_.clear();

    for (auto &ghost: ghosts_.getGhosts())
        ghost->hide();

    fruit_.reset();
    counter_.start(config::settings::kWelcomeScreen);
    status_ = StatusType::kWelcomeScreen;
}


void Game::displayWelcomeScreen()
{
    SDL_Rect dst;

    window_.writeWord("CHARACTER / NICKNAME ",
                      display::welcome_screen::text::kCharaterNicknameX,
                      display::welcome_screen::text::kCharaterNicknameY,
                      display::welcome_screen::text::kCharaterNicknameOffset,
                      display::welcome_screen::text::kCharaterNicknameScale);


    dst.x = display::welcome_screen::ghosts::blinky::kWelcomeScreenX;
    dst.y = display::welcome_screen::ghosts::blinky::kWelcomeScreenY;
    dst.h = (int) display::welcome_screen::ghosts::kSpriteHeight ;
    dst.w = (int) display::welcome_screen::ghosts::kSpriteWidth ;

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 2)
    {
        //Blinky
        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::ghosts::blinky::right::sprite_1::kSprite.getImage(),
                   dst);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 3)
    {
        window_.writeWord("- SHADOW",
                          display::welcome_screen::ghosts::blinky::kNameX,
                          display::welcome_screen::ghosts::blinky::kNameY,
                          display::welcome_screen::text::kCharaterNicknameOffset,
                          display::welcome_screen::ghosts::kNameScale,
                          colours::kRed);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 4)
    {
        window_.writeWord("'BLINKY' ",
                          display::welcome_screen::ghosts::blinky::kNickNameX,
                          display::welcome_screen::ghosts::blinky::kNickNameY,
                          display::welcome_screen::text::kCharaterNicknameOffset,
                          display::welcome_screen::ghosts::kNameScale, colours::kRed);
    }


    dst.y = display::welcome_screen::ghosts::pinky::kWelcomeScreenY;
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 5)
    {
        //Pinky
        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::ghosts::pinky::right::sprite_1::kSprite.getImage(),
                   dst);
    }

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 6)
    {
        window_.writeWord("- SPEEDY",
                          display::welcome_screen::ghosts::pinky::kNameX,
                          display::welcome_screen::ghosts::pinky::kNameY,
                          display::welcome_screen::text::kCharaterNicknameOffset,
                          display::welcome_screen::ghosts::kNameScale, colours::kPink);
    }

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 7)
    {
        window_.writeWord("'PINKY' ",
                display::welcome_screen::ghosts::pinky::kNickNameX,
                display::welcome_screen::ghosts::pinky::kNickNameY,
                display::welcome_screen::text::kCharaterNicknameOffset,
                display::welcome_screen::ghosts::kNameScale, colours::kPink);
    }


    dst.y = display::welcome_screen::ghosts::inky::kWelcomeScreenY;

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 8)
    {
        //Inky
        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::ghosts::inky::right::sprite_1::kSprite.getImage(),
                   dst);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 9)
    {
        window_.writeWord("- BASHFUL",
                          display::welcome_screen::ghosts::inky::kNameX,
                          display::welcome_screen::ghosts::inky::kNameY,
                          display::welcome_screen::text::kCharaterNicknameOffset,
                          display::welcome_screen::ghosts::kNameScale, colours::kCyan);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 10)
    {
        window_.writeWord("'INKY' ",
                          display::welcome_screen::ghosts::inky::kNickNameX,
                          display::welcome_screen::ghosts::inky::kNickNameY,
                          display::welcome_screen::text::kCharaterNicknameOffset,
                          display::welcome_screen::ghosts::kNameScale,colours::kCyan);
    }


    dst.y = display::welcome_screen::ghosts::clyde::kWelcomeScreenY;
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 11)
    {
        //Clyde
        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::ghosts::clyde::right::sprite_1::kSprite.getImage(),
                   dst);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 12)
    {
        window_.writeWord("- POKEY",
                          display::welcome_screen::ghosts::clyde::kNameX,
                          display::welcome_screen::ghosts::clyde::kNameY,
                          display::welcome_screen::text::kCharaterNicknameOffset,
                          display::welcome_screen::ghosts::kNameScale, colours::kOrange);
    }
    if (counter_.getCount() >= config::settings::kFramesPerSecond * 13)
    {
        window_.writeWord("'CLYDE' ",
                          display::welcome_screen::ghosts::clyde::kNickNameX,
                          display::welcome_screen::ghosts::clyde::kNickNameY,
                          display::welcome_screen::text::kCharaterNicknameOffset,
                          display::welcome_screen::ghosts::kNameScale,colours::kOrange);
    }

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 14)
    {
        //small pellet
        dst.x = display::welcome_screen::pellet::kPosX;
        dst.y = display::welcome_screen::pellet::kPosY;
        dst.h = (int) display::welcome_screen::pellet::kSpriteHeight ;
        dst.w = (int) display::welcome_screen::pellet::kSpriteWidth ;

        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::pellet::kSprite.getImage(), dst);

        window_.writeWord("10",
                          display::welcome_screen::pellet::kPointsTextPosX,
                          display::welcome_screen::pellet::kPointsTextPosY,
                          display::welcome_screen::pellet::kOffset,
                          display::welcome_screen::pellet::kPointsTextscale);

        dst.x = display::welcome_screen::pellet::kPointsPosX;
        dst.y = display::welcome_screen::pellet::kPointsPosY;
        dst.h = (int) display::welcome_screen::pellet::kPointsSpriteHeight ;
        dst.w = (int) display::welcome_screen::pellet::kPointsSpriteWidth ;


        //pts for 10
        drawObject(window_.getRenderer(), window_.getTexture(),
                   characters::special::points::kSprite.getImage(),
                   dst);




        // big Pellet
        dst.x = display::welcome_screen::energizer::kPosX;
        dst.y = display::welcome_screen::energizer::kPosY;
        dst.h = (int) display::welcome_screen::energizer::kSpriteHeight ;
        dst.w = (int) display::welcome_screen::energizer::kSpriteWidth ;

        drawObject(window_.getRenderer(), window_.getTexture(),
                   visuals::energizer::kSprite.getImage(), dst);


        window_.writeWord("50",
                display::welcome_screen::energizer::kPointsTextPosX,
                display::welcome_screen::energizer::kPointsTextPosY,
                display::welcome_screen::energizer::kOffset,
                display::welcome_screen::energizer::kPointsTextscale);


        dst.x = display::welcome_screen::energizer::kPointsPosX;
        dst.y = display::welcome_screen::energizer::kPointsPosY;
        dst.h = (int) display::welcome_screen::energizer::kPointsSpriteHeight ;
        dst.w = (int) display::welcome_screen::energizer::kPointsSpriteWidth ;
        //pts for 50
        drawObject(window_.getRenderer(), window_.getTexture(),
                   characters::special::points::kSprite.getImage(),
                   dst);
    }

    if (counter_.getCount() >= config::settings::kFramesPerSecond * 15)
    {
        window_.writeWord("` 1980 MIDWAY MFG. CO.",
                          display::welcome_screen::text::kMidwayX,
                    display::welcome_screen::text::kMidwayY,
                          display::welcome_screen::text::kMidwayOffset,
                    display::welcome_screen::text::kMidwayScale,
                    colours::kPink);
    }

    window_.writeWord("CREDIT 0",
                      display::scoreboard::kCreditPosX,
                      display::scoreboard::kCreditPosY,
                      offsets::kCreditText,
                      scales::kCreditText);
    window_.update();

}

void Game::displayPoints()
{

    for (auto s = points_.begin(); s != points_.end();)
    {
        //If counter is still active
        if (std::get<2>(*s).isActive())
        {
            //Change colour
            SDL_SetTextureColorMod(window_.getTexture().get(),
                                   std::get<0>(std::get<3>(*s)),
                                   std::get<1>(std::get<3>(*s)),
                                   std::get<2>(std::get<3>(*s)));


            drawObject(window_.getRenderer(), window_.getTexture(),
                       std::get<0>(*s), std::get<1>(*s));

            std::get<2>(*s).increment();
            //Switch back to original colour
            SDL_SetTextureColorMod(window_.getTexture().get(),
                                   std::get<0>(colours::kWhite),
                                   std::get<1>(colours::kWhite),
                                   std::get<2>(colours::kWhite));
        } else
        {
            //Erase object to display from the vector
            points_.erase(s);
            return;
        }
        ++s;
    }
}

void Game::addPointsToDisplay(unsigned long points, float scale,
                              std::tuple<int, int, int> colour, int x, int y)
{

    auto found = window_.getPointsMap().find(points);
    //Check so no crashes happen in case unrecognised value is passed
    if (points == 0 || (found == window_.getPointsMap().end()))
    {
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

void Game::quit()
{
    // Save high score.
    saveGameState(high_score_, level_);

    // Quit the window.
    window_.quit();
}
