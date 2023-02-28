//
// Created by omar on 08/02/23.
//

#ifndef PEC_MEN_ENTITY_H
#define PEC_MEN_ENTITY_H
#include <SDL.h>
#include <string>
#include <iostream>
#include <utility>
#include "constants.h"

using namespace std;

class Entity{

private:
    pair<int, int> coordinates_;
    int size_{};
    int points_{} ;
    bool isDisabled_ = true;
    SDL_Rect image_{};

public:

    virtual ~Entity();
    Entity();
    Entity(const pair<int, int> &coordinates, int size, int points, bool isDisabled, SDL_Rect image);
    Entity(const pair<int, int> &coordinates, int size, int points); // TODO : temp

    [[nodiscard]] int getPoints() const;
    [[nodiscard]] const pair<int, int> &getCoordinates() const;
    void setCoordinates(const pair<int, int> &coordinates);
    [[nodiscard]] bool isDisabled() const;
    void setIsDisabled(bool isDisabled);
    [[nodiscard]] SDL_Rect getImage() const;

    [[nodiscard]] bool hasCollided(directions direction, const Entity& entity) const;
    [[nodiscard]] SDL_Rect getImagePosition() const;
    void print() const;

};

#endif //PEC_MEN_ENTITY_H
