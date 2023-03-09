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

enum class StatusType {
    STOPPED,
    RUNNING,
    PAUSED,
    INTERRUPTED,
    LEVEL_UP,
    LOST_LIFE,
};

class Game {
public:
    Game();
    Game(int width, int height, int cell_size, const char * file_path, int lives);

    [[nodiscard]] const Pacman &getPacman() const;

    void setPacman(const Pacman &pacman);

    [[nodiscard]] StatusType getStatus() const;
    void setStatus(StatusType status);

    Direction move(Direction continuous_direction, Direction try_direction);
    void move(Direction continuous_direction);
    void handleEntitiesCollisions();
    void drawStaticEntities(SDL_Surface* plancheSprites, SDL_Surface* win_surf, bool displayEnergizers);

    void levelUp();
    void lostLife();

    int getScore() const;

private:
    Map map_;
    int lives_ = 0;
    int score_ = 0;
    int level_ = 1;
    int pelletsEaten_ = 0;
    static const int pelletsTotal_ = 192;
    std::vector<Ghost> ghosts_;
    Pacman pacman_;
    Fruits fruits_;
    StatusType status_ = {StatusType::RUNNING};

    static std::vector<CellType> getCellsTypeFromFile(const std::string &file_path);
};


#endif //PACMAN_GAME_H
