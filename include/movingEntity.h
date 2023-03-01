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
    std::vector<Sprite> left_ {};
    std::vector<Sprite> right_ {};
    std::vector<Sprite> up_ {};
    std::vector<Sprite> down_ {};
    directions previous_direction_ {};
    std::pair<bool, int> previous_imagePosition_ {true, 0};
    bool isMovingLeftOrUp_ = false;
    int refreshAnimation_counter_ {};
    static const int refreshAnimation_rate_ = constants::ENTITY_REFRESH_RATE;

    std::pair<int, int> getDestination(directions direction);

public:
    MovingEntity();
    MovingEntity(const pair<int, int> &coordinates, int size, Sprite sprite, int speed, const vector<Sprite> &left,
                 const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down);
    MovingEntity(const pair<int, int> &coordinates, int size, Sprite sprite, int points, bool isDisabled, int speed, const vector<Sprite> &left,
                 const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down);

    [[nodiscard]] directions getPreviousDirection() const;
    [[nodiscard]] virtual bool isMovingLeftOrUp() const;

    virtual bool move(Map map, directions direction);
    void animate(directions direction);
    std::pair<bool, int> updateImagePosition(directions direction, unsigned max_index);
};


#endif //PACMAN_MOVINGENTITY_H
