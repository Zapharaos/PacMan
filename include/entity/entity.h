//
// Created by omar on 08/02/23.
//

#ifndef PEC_MEN_ENTITY_H
#define PEC_MEN_ENTITY_H
#include <SDL.h>
#include <string>
#include <iostream>
#include <utility>
#include "../utils/constants.h"
#include "../sprite/sprite.h"

using namespace std;

class Entity{

private:
    int points_{};
    bool isDisabled_ = true;
    Sprite sprite_{};

public:

    virtual ~Entity();
    Entity();
    Entity(Sprite sprite, int points, bool isDisabled);
    explicit Entity(Sprite sprite);

    [[nodiscard]] int getPoints() const;
    void setPoints(int points);
    [[nodiscard]] bool isDisabled() const;
    void setIsDisabled(bool isDisabled);
    [[nodiscard]] virtual Sprite getSprite() const;
    void setSprite(const Sprite &sprite);

    [[nodiscard]] virtual SDL_Rect getSpritePosition() const;
    [[nodiscard]] virtual SDL_Rect getSpritePosition(std::pair<int, int> coordinates) const;
    [[nodiscard]] virtual const SDL_Rect &getSpriteImage() const;

    void print() const;

};

#endif //PEC_MEN_ENTITY_H
