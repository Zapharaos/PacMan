/**
 * @file game.h
 * @brief Contains the declaration of the `Game` class, which represents the Pac-Man game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 08/02/2023
 */

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include <iostream>
#include <fstream>

#include "map/map.h"
#include "entity/movingEntity.h"
#include "entity/ghosts.h"
#include "entity/pacman.h"
#include "entity/fruit.h"
#include "utils/utils.h"
#include "display/window.h"
#include "config/visuals.h"

/**
 * @brief Represents the Pac-Man game.
 *
 * The `Game` class manages the game state, entities, and mechanics, and interacts with the user
 * through a `Window` object. It contains methods for updating the game state, handling user input,
 * and rendering the game objects on the window.
*/
class Game
{

private:

    /**
     * @brief Enumerates the possible statuses of the game.
     */
    enum class StatusType
    {
        kStopped, /* The game is not running. */
        kRunning, /* The game is running normally. */
        kPaused, /* The game is paused. */
        kLevelUpFreeze, /* The game is freezing before level up. */
        kLevelUpAnimate, /* The game is animating level up. */
        kDeathFreeze, /* The game is freezing before death. */
        kDeathAnimate, /* The game is animating death. */
        kEatingGhost, /* Pacman is eating a ghost. */
        kWelcomeScreen, /*Initial Screen with animations */
        kGameStartFreeze, /* The game is frozen before starting*/
        kGameStartAnimate,
        kSuperpower, /* The pacman ate an energizer. */
    };

    /** The map object. */
    Map map_;

    /** The window object. */
    Window window_;

    /** The number of lives. */
    int lives_ = 0;

    /** The current score. */
    unsigned long score_ = 0;

    /** The highest score stored locally. */
    unsigned long high_score_ = 0 ;

    /** The current level. */
    int level_ = 1;

    /** The current number of ghosts eaten while in superpower mode. */
    int ghosts_eaten = 0;

    /** The current number of pellets eaten. */
    int pellets_eaten_ = 0;

    /** The total number of pellets. */
    unsigned long pellets_total_ = 0;

    /** The pacman entity. */
    Pacman pacman_;

    /** The ghost entities. */
    Ghosts ghosts_;

    /** The fruit entity. */
    Fruit fruit_;

    /** The current game status. */
    StatusType status_ = {StatusType::kRunning};

    /** The counter used to count frames. */
    Counter counter_ {};

public:

    /**
     * @brief Default constructor for the Game class.
     */
    Game();

    /**
     * @brief Constructor for the Game class.
     * @param map The map object.
     * @param window The window object.
     * @param high_score The local saved high score.
     */
    Game(const Map &map, Window window, unsigned long high_score);

    /**
     * @brief Executes a game tick.
     * @param direction The user's input direction for pacman.
     */
    void tick(const Direction &direction);

    /**
     * @brief Draws all objects onto the window.
     */
    void display();

    /**
     * @brief Handles the game status.
     * @return True if the game is still running, false otherwise.
     */
    bool handleStatus();

    /**
     * @brief Handles collisions between entities.
     * @param pacman Pacman position (in pixels).
     */
    void handleEntitiesCollisions(const SDL_Rect &pacman);

    /**
     * @brief Toggles the game's pause status.
     */
    void togglePause();

    /**
     * @brief Levels the game up.
     */
    void levelUp();

    /**
     * @brief Handles the player losing a life.
     */
    void lostLife();

    bool updateHighScore() ;

    /**
     * getSavedHighScore
     * Gets the high score set locally from the save.json file
     * @return high_score_
     */
    int getLocalHighScore();

    unsigned long getHighScore() const;

    int getLevel() const;

    void displayWelcomeScreen();

    /**
     * @brief Quits the game by setting the game status to kStopped.
     */
    void quit();
};


#endif //PACMAN_GAME_H
