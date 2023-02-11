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
    // coordinates
    pair<int, int> coordinates_;
    // name of sprite
    string name_ ;
public:
    void setCoordinates(pair<int, int> &coordinates);

public:
    pair<int, int> &getCoordinates();

public:
    Entity(const pair<int, int> &coordinates, string name);

    Entity();

};


#endif //PEC_MEN_ENTITY_H
