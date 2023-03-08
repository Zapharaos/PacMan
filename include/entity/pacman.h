//
// Created by matthieu on 28/02/2023.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include "movingEntity.h"
#include "../utils/timer.h"

class Pacman : MovingEntity {

private:
    bool superpower_ = false;
    Timer timer_ {};

public:
    Pacman(long time, const std::function<void(void)> &function, Sprite sprite, int speed, const pair<int, int> &coordinates,
           const vector<Sprite> &left, const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down);
    Pacman();

    void setSuperpower(bool superpower);
    [[nodiscard]] bool isSuperpower();

    [[nodiscard]] const pair<int, int> &getCoordinates() const override;
    [[nodiscard]] bool isLeftOrUp() const override;
    [[nodiscard]] Sprite getSprite() const override;
    [[nodiscard]] SDL_Rect getSpritePosition() const override;
    [[nodiscard]] const SDL_Rect &getSpriteImage() const override;

    [[nodiscard]] bool hasCollided(SDL_Rect e) const;
    Direction move(const Map& map, Direction continuous_direction, Direction try_direction);
    void move(const Map& map, Direction continuous_direction);
    void reset(pair<int, int> coordinates) override;
};


#endif //PACMAN_PACMAN_H
