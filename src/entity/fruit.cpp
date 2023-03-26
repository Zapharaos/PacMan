/**
 * @file fruit.cpp
 * @brief Implements the Fruit class which represents a fruit that occasionally appears on the board.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 12/03/2023
*/

#include "../../include/entity/fruit.h"

Fruit::Fruit() = default;

Fruit::Fruit(unsigned long total_pellets) : Entity(Position{{config::positions::kFruitX, config::positions::kFruitY}})
{
    timer_ = Timer(config::settings::kDurationFruit);
    for(auto &percentage : config::settings::kFruitsPercentages)
        pellets_cap_.emplace(total_pellets * percentage / 100);

    fruits_ = visuals::fruit::kFruits;
}

void Fruit::update(int pellets_eaten, int level)
{
    // if a fruit should be displayed
    if (pellets_cap_.contains(pellets_eaten))
    {
        timer_.kill(); // just in case : disable previous fruit timer

        index_ = 0;
        for (auto &fruit: fruits_) // find fruit corresponding to level
        {
            if (fruit.getLevels().contains(level))
                break;
            ++index_;
        }

        setEnabled(true); // enables the entity
        setPoints(fruits_.at(index_).getPoints()); // update points
        setSprite(fruits_.at(index_).getSprite()); // update sprite

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
