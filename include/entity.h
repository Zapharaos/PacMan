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
    Entity(const pair<int, int> &coordinates, int size, SDL_Rect image, int points, bool isDisabled);
    Entity(const pair<int, int> &coordinates, int size, SDL_Rect image);

    [[nodiscard]] int getPoints() const;
    [[nodiscard]] virtual const pair<int, int> &getCoordinates() const;
    void setCoordinates(const pair<int, int> &coordinates);
    [[nodiscard]] bool isDisabled() const;
    void setIsDisabled(bool isDisabled);
    [[nodiscard]] virtual SDL_Rect getImage() const;
    void setImage(const SDL_Rect &image);
    [[nodiscard]] int getSize() const;

    [[nodiscard]] virtual SDL_Rect getImagePosition() const;
    void print() const;

};

#endif //PEC_MEN_ENTITY_H
