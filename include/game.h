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

class Game {
public:
    Game();
    Game(int width, int height, int cell_size, const char * file_path, int lives);

    [[nodiscard]] const Pacman &getPacman() const;

    void handleEntitiesCollisions();
    Direction move(Direction continuous_direction, Direction try_direction);
    void move(Direction continuous_direction);
    void drawStaticEntities(SDL_Surface* plancheSprites, SDL_Surface* win_surf);
    bool levelChange();

    int getScore() const;

private:
    Map map_;
    int lives_ = 0;
    int score_ = 0;
    int level_ = 1;
    int eaten_ = 0;
    static const int pellets_ = 192;
    std::vector<Ghost> ghosts_;
    Pacman pacman_;
    Fruits fruits_;

    // TODO : temp attributes
    bool powerup_ = false;

    static std::vector<CellType> getCellsTypeFromFile(const std::string &file_path);
};


#endif //PACMAN_GAME_H
