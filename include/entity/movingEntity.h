//
// Created by matthieu on 28/02/2023.
//

#ifndef PACMAN_MOVINGENTITY_H
#define PACMAN_MOVINGENTITY_H

#include <SDL.h>
#include <vector>
#include "entity.h"
#include "../map/map.h"
#include "../enums/direction.h"

class MovingEntity : public Entity{

private:
    int speed_ {};
    pair<int, int> coordinates_;
    std::vector<Sprite> left_ {};
    std::vector<Sprite> right_ {};
    std::vector<Sprite> up_ {};
    std::vector<Sprite> down_ {};
    Direction previous_direction_ {};
    std::pair<bool, int> previous_imagePosition_ {true, 0};
    bool isMovingLeftOrUp_ = false;
    int refreshAnimation_counter_ {};
    static const int refreshAnimation_rate_ = constants::ENTITY_REFRESH_RATE;

    [[nodiscard]] std::pair<int, int> getDestinationCoordinates(std::pair<int, int> origin, Direction direction) const;

public:
    MovingEntity();
    MovingEntity(Sprite sprite, int speed, const pair<int, int> &coordinates, const vector<Sprite> &left,
                 const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down);
    MovingEntity(Sprite sprite, int points, bool isDisabled, int speed, const pair<int, int> &coordinates, const vector<Sprite> &left,
                 const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down);

    [[nodiscard]] virtual const pair<int, int> &getCoordinates() const;
    void setCoordinates(const pair<int, int> &coordinates);
    [[nodiscard]] virtual bool isMovingLeftOrUp() const;
    [[nodiscard]] SDL_Rect getSpritePosition() const override;
    [[nodiscard]] const SDL_Rect &getSpriteImage() const override;

    virtual void move(Map map, Direction direction);
    virtual Direction move(Map map, Direction direction, Direction turn);
    void animate(Direction direction);
    std::pair<bool, int> getCurrentSprite(Direction direction, unsigned max_index);
};


#endif //PACMAN_MOVINGENTITY_H
