//
// Created by omar on 12/02/23.
//

#include "../../include/entity/fruit.h"

Fruit::Fruit() = default;

Fruit::Fruit(Position position, long time, set<int> pelletsCap,
             vector<FruitObject> fruits) :
        Entity(position), timer_(time), pelletsCap_(move(pelletsCap)),
        fruits_(move(fruits))
{}

void Fruit::update(int pelletsEaten, int level)
{
    // if a fruit should be displayed
    if (pelletsCap_.find(pelletsEaten) != pelletsCap_.end())
    {
        timer_.kill(); // just in case : disable previous fruit timer

        FruitObject &current = fruits_.back(); // set as default fruit object
        for (auto &fruit: fruits_) // find object corresponding to level
        {
            set<int> levels = fruit.getLevels();
            if (levels.find(level) != levels.end())
                current = fruit;
        }

        sprite_index_ = 0; // reset animation counter
        setEnabled(true); // enables the entity
        setPoints(current.getPoints()); // update the points
        setSprite(current.getSprites().at(sprite_index_)); // update sprite

        timer_.start([&]() {
            setEnabled(false);
        }); // only showing fruit for a specific time
    }
}

bool Fruit::isEnabled()
{
    // protecting access : as timer_ expires, it disables the entity
    timer_.setMutexLock(true);
    bool result = Entity::isEnabled();
    timer_.setMutexLock(false);
    return result;
}

void Fruit::reset()
{
    timer_.kill(); // stop the timer
}
