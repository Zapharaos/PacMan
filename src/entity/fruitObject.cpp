//
// Created by mfrei on 09/03/2023.
//

#include "../../include/entity/fruitObject.h"

FruitObject::FruitObject() = default;

FruitObject::FruitObject(int points, const set<int> &levels,
                         const vector<Sprite> &sprites) :
        points_(points), levels_(levels), sprites_(sprites)
{}

int FruitObject::getPoints() const
{
    return points_;
}

const set<int> &FruitObject::getLevels() const
{
    return levels_;
}

const vector<Sprite> &FruitObject::getSprites() const
{
    return sprites_;
}
