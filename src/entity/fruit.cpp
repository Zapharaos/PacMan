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

        index_ = 0;
        for (auto &fruit: fruits_) // find fruit corresponding to level
        {
            set<int> levels = fruit.getLevels();
            if (levels.find(level) != levels.end())
                break;
            index_++;
        }

        setEnabled(true); // enables the entity
        setPoints(fruits_.at(index_).getPoints()); // update points
        setSprite(fruits_.at(index_).getAnimation().getSprite()); // update sprite

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

void Fruit::animate() {
    setSprite(fruits_.at(index_).animate());
}
