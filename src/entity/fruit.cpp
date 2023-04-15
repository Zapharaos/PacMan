/**
 * @file fruit.cpp
 * @brief Implements the Fruit class which represents a Fruit that occasionally appears on the board.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 12/03/2023
*/

#include "../../include/entity/fruit.h"

Fruit::Fruit() = default;

Fruit::Fruit(unsigned long total_pellets) : Entity({config::positions::entities::kFruitX, config::positions::entities::kFruitY})
{
    for(auto &percentage : config::settings::kFruitsPercentages)
        pellets_cap_.emplace(total_pellets * percentage / 100);

    fruits_ = visuals::fruit::kFruits;
}

void Fruit::update(int pellets_eaten, int level)
{
    // if a fruit should be displayed
    if (pellets_cap_.contains(pellets_eaten))
    {
        index_ = 0;
        for (auto &fruit: fruits_) // find fruit corresponding to level
        {
            if (fruit.getLevels().contains(level))
                break;
            ++index_;
        }

        setPoints(fruits_.at(index_).getPoints()); // update points
        setSprite(fruits_.at(index_).getSprite()); // update sprite
        showTimed(config::settings::kDurationFruit);
    }
}

void Fruit::tick()
{
    Entity::tick();
    if(isEnabled())
        animate();
}

void Fruit::animate() {
    setSprite(fruits_.at(index_).animate());
}
