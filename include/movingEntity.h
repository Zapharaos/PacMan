//
// Created by matthieu on 28/02/2023.
//

#ifndef PACMAN_MOVINGENTITY_H
#define PACMAN_MOVINGENTITY_H

#include <SDL.h>
#include <vector>
#include "entity.h"
#include "map.h"

class movingEntity : public Entity{

private:
    int speed_;
    std::vector<SDL_Rect> left_ {};
    std::vector<SDL_Rect> right_ {};
    std::vector<SDL_Rect> up_ {};
    std::vector<SDL_Rect> down_ {};
    directions previous_direction_ {};
    std::pair<bool, int> previous_imagePosition_ {true, 0};

public:
    movingEntity(const pair<int, int> &coordinates, int size, int speed, const vector<SDL_Rect> &left,
                 const vector<SDL_Rect> &right, const vector<SDL_Rect> &up, const vector<SDL_Rect> &down);
    movingEntity(const pair<int, int> &coordinates, int size, int points, bool isDisabled, int speed, const vector<SDL_Rect> &left,
                 const vector<SDL_Rect> &right, const vector<SDL_Rect> &up, const vector<SDL_Rect> &down);

    void move(Map map, directions direction);
    std::pair<bool, int> updateNextImage(directions direction, unsigned last_index);
};


#endif //PACMAN_MOVINGENTITY_H
