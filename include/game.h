//
// Created by matthieu on 08/02/2023.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include <iostream>
#include <fstream>

#include "map/map.h"
#include "entity/movingEntity.h"
#include "entity/ghost.h"
#include "entity/pacman.h"
#include "entity/fruit.h"
#include "utils/utils.h"
#include "display/window.h"

/** Indicates the game status. */
enum class StatusType
{
    kStopped,
    kRunning,
    kPaused,
    kLevelUpFreeze,
    kLevelUpAnimate,
    kDeathFreeze,
    kDeathAnimate,
    kEatingGhost
};

/** Game object. */
class Game
{

private:

    /** Map. */
    Map map_;

    /** Window. */
    Window window_;

    /** Number of lives. */
    int lives_ = 0;

    /** Current score. */
    int score_ = 0;

    /** Highest score set locally*/
    int high_score_ = 0 ;

    /** Current level. */
    int level_ = 1;

    /** Current number of pellets eaten. */
    int pelletsEaten_ = 0;

    /** Total number of pellets. */
    static const int pelletsTotal_ = 192;

    /** Pacman. */
    Pacman pacman_;

    /** Ghost entities. */
    std::vector<Ghost> ghosts_;

    /** Fruit entities. */
    Fruit fruit_;

    /** Current game status. */
    StatusType status_ = {StatusType::kRunning};

    /** Counts a number of frames. */
    Counter counter_ {};

public:

    /** Default Game constructor. */
    Game();

    /** Game constructor.
     *
     * @param map Map.
     * @param window Window.
     * @param lives Number of lives.
     */
    Game(Map map, Window window, int lives);

    /** Pause/Resume the game. */
    void togglePause();

    /** Handles status. */
    bool handleStatus();

    /** Handles collisions. */
    void handleEntitiesCollisions();

    /** Level's the game up. */
    void levelUp();

    /** Player died. */
    void lostLife();

    bool updateHighScore() ;

    /**
 * getSavedHighScore
 * Gets the high score set locally from the save.json file
 * @return high_score_
 */
    int getLocalHighScore();

    void tick(const Direction &direction);

    void display();

    void quit();
};


#endif //PACMAN_GAME_H
