//
// Created by matthieu on 08/02/2023.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include <iostream>
#include <fstream>
#include "map.h"
#include "movingEntity.h"
#include "ghost.h"
#include "Pacman.h"

class Game {
public:
    Game();
    Game(int width, int height, int cell_size, const char * file_path, int lives);

    [[nodiscard]] const Pacman &getPacman() const;

    void handleEntitiesCollisions();
    void move(directions direction);
    void drawStaticEntities(SDL_Surface* plancheSprites, SDL_Surface* win_surf);

private:
    Map map_;
    std::vector<Ghost> ghosts_;
    Pacman pacman_;

    // TODO : temp attributes
    bool powerup_ = false;
    int score_ = 0;
    int lives_ = 0;

    static std::vector<cell_type> getCellsTypeFromFile(const std::string &file_path);
};


#endif //PACMAN_GAME_H
