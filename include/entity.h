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
    // name of sprite
    string name_ ;
    //number of points won if eaten
    int points ;
public:
    Entity(const pair<int, int> &coordinates, string name, int points);

    Entity();

    [[nodiscard]] const pair<int, int> &getCoordinates() const;

    void setCoordinates(const pair<int, int> &coordinates);

    [[nodiscard]] const string &getName() const;

    void setName(const string &name);

    int getPoints() const;

    void setPoints(int points_);

    virtual ~Entity();

    Entity(const pair<int, int> &coordinates, string name);

    Entity(string name, int points);
};

#endif //PEC_MEN_ENTITY_H
