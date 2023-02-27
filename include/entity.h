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
protected:

// coordinates
    pair<int, int> coordinates_;
    int size_;
    // name of sprite
    string name_ ;
    //number of points won if eaten
    int points_{} ;
public:
    [[nodiscard]] int getPoints() const;

public:
    Entity(const pair<int, int> &coordinates, int size, string name, int points);

    Entity(const pair<int, int> &coordinates, string name);

    Entity(string name, int points);

    Entity();

    virtual ~Entity();

    [[nodiscard]] const pair<int, int> &getCoordinates() const;

    void setCoordinates(const pair<int, int> &coordinates);

    [[nodiscard]] bool hasCollided(const Entity& entity) const;

    void print() const;

};

#endif //PEC_MEN_ENTITY_H
