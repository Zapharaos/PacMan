//
// Created by mfrei on 09/03/2023.
//

#include "../../include/entity/fruitObject.h"

#include <utility>

FruitObject::FruitObject() = default;

FruitObject::FruitObject(int points, const set<int> &levels,
                         Animation animation) :
        points_(points), levels_(levels), animation_(move(animation))
{}

int FruitObject::getPoints() const
{
    return points_;
}

const set<int> &FruitObject::getLevels() const
{
    return levels_;
}

const Animation &FruitObject::getAnimation() const
{
    return animation_;
}

const Sprite &FruitObject::animate()
{
    return animation_.animate();
}

