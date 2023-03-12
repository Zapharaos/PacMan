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

/** Indicates the game status. */
enum class StatusType
{
    STOPPED,
    RUNNING,
    PAUSED,
    INTERRUPTED,
    LEVEL_UP,
    LOST_LIFE,
};

/** Game object. */
class Game
{

private:

    /** Map. */
    Map map_;

    /** Number of lives. */
    int lives_ = 0;

    /** Current score. */
    int score_ = 0;

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
    StatusType status_ = {StatusType::RUNNING};

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

    /** Getter : Current score. */
    [[nodiscard]] int getScore() const;

    /** Getter : Pacman. */
    [[nodiscard]] const Pacman &getPacman() const;

    /** Setter : Pacman. */
    void setPacman(const Pacman &pacman);

    /** Getter : Current game status. */
    [[nodiscard]] StatusType getStatus() const;

    /** Setter : Current game status. */
    void setStatus(StatusType status);

    /** Pacman tries to move & handle collisions.
     *
     * @param continuous_direction The direction pacman is moving towards to.
     */
    void move(Direction continuous_direction);

    /** Pacman tries to turn & handle collisions.
     *
     * @param continuous_direction The direction pacman is moving towards to.
     * @param try_direction he direction pacman wishes to move to.
     * @return try_direction if it could change direction, else continuous_direction.
     */
    Direction move(Direction continuous_direction, Direction try_direction);

    /** Handles collisions. */
    void handleEntitiesCollisions();

    /** Level's the game up. */
    void levelUp();

    /** Player died. */
    void lostLife();

    /** Displays all static entities. */
    void drawStaticEntities(SDL_Surface *plancheSprites, SDL_Surface *win_surf,
                            bool displayEnergizers);

};


#endif //PACMAN_GAME_H
