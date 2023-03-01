//
// Created by matthieu on 28/02/2023.
//

#ifndef PACMAN_MOVINGENTITY_H
#define PACMAN_MOVINGENTITY_H

#include <SDL.h>
#include <vector>
#include "entity.h"
#include "map.h"

class MovingEntity : public Entity{

private:
    int speed_ {};
    std::vector<SDL_Rect> left_ {};
    std::vector<SDL_Rect> right_ {};
    std::vector<SDL_Rect> up_ {};
    std::vector<SDL_Rect> down_ {};
    directions previous_direction_ {};
    std::pair<bool, int> previous_imagePosition_ {true, 0};
    bool isMovingLeftOrUp_ = false;
    int refreshAnimation_counter_ {};
    static const int refreshAnimation_rate_ = constants::ENTITY_REFRESH_RATE;

public:
    MovingEntity();
    MovingEntity(const pair<int, int> &coordinates, int size, const SDL_Rect &image, int speed);
    MovingEntity(const pair<int, int> &coordinates, int size, SDL_Rect image, int speed, const vector<SDL_Rect> &left,
                 const vector<SDL_Rect> &right, const vector<SDL_Rect> &up, const vector<SDL_Rect> &down);
    MovingEntity(const pair<int, int> &coordinates, int size, SDL_Rect image, int points, bool isDisabled, int speed, const vector<SDL_Rect> &left,
                 const vector<SDL_Rect> &right, const vector<SDL_Rect> &up, const vector<SDL_Rect> &down);

    [[nodiscard]] directions getPreviousDirection() const;
    [[nodiscard]] virtual bool isMovingLeftOrUp() const;

    virtual void move(Map map, directions direction);
    std::pair<bool, int> updateImagePosition(directions direction, unsigned max_index);
};


#endif //PACMAN_MOVINGENTITY_H
