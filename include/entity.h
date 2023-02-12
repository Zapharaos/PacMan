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
public:
    Entity(const pair<int, int> &coordinates, const string &name);

    Entity();

    [[nodiscard]] const pair<int, int> &getCoordinates() const;

    void setCoordinates(const pair<int, int> &coordinates);

    [[nodiscard]] const string &getName() const;

    void setName(const string &name);

    virtual ~Entity();

};

Entity::~Entity() = default;


#endif //PEC_MEN_ENTITY_H
