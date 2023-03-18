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
#include "saveGame.h"
#include "utils/utils.h"
#include "display/window.h"

/** Indicates the game status. */
enum class StatusType
{
    STOPPED,
    RUNNING,
    PAUSED,
    LEVEL_UP_FREEZE,
    LEVEL_UP_ANIMATE,
    DEATH_FREEZE,
    DEATH_ANIMATE,
    EATING_GHOST
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
    vector<Ghost> ghosts_;

    /** Fruit entities. */
    Fruit fruit_;

    /** Current game status. */
    StatusType status_ = {StatusType::RUNNING};

    /** Counts a number of frames. */
    Counter counter_ {};

public:

    /** Default Game constructor. */
    Game();

    /** Game constructor.
     *
     * @param width Map's width.
     * @param height Map's height.
     * @param cell_size Size of a map's cell.
     * @param file_path Path to the map file.
     * @param lives Number of lives.
     */
    Game(int width, int height, int cell_size, const char *file_path,
         int lives);

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
    int getSavedHighScore();

    void setHighScore(int highScore);

    int getHighScore() const;

    void tick(const Direction &direction);

    void display();

    void quit();
};


#endif //PACMAN_GAME_H
