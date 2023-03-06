//
// Created by omar on 12/02/23.
//

#include "../../include/entity/fruit.h"

Fruits::Fruit::Fruit() = default;

Fruits::Fruit::Fruit(int points, const set<int> &levels, const vector<Sprite> &animations) :
    points_(points), levels_(levels), animations_(animations) {}

int Fruits::Fruit::getPoints() const {
    return points_;
}

const set<int> &Fruits::Fruit::getLevels() const {
    return levels_;
}

const vector<Sprite> &Fruits::Fruit::getAnimations() const {
    return animations_;
}

Fruits::Fruits() = default;

Fruits::Fruits(const pair<int, int> &coordinates, int size, Sprite sprite,
             long time, const std::function<void(void)> &function) :
        Entity(coordinates, size, sprite), timer_(time, function) {}

void Fruits::appendFruit(int points, const std::set<int>& levels, const std::vector<Sprite>& animations) {
    fruits_.emplace_back(Fruit{points, levels, animations});
}

void Fruits::incrementClearedPellets(int level)
{
    clearedPellets_++;
    if(pelletsCap_.find(clearedPellets_) != pelletsCap_.end())
    {
        timer_.setMutexLock(true);
        if(timer_.isRunning())
            timer_.setKilled(true);
        timer_.setMutexLock(false);

        Fruit &current = fruits_.back();
        for(auto & fruit : fruits_) {
            std::set<int> levels = fruit.getLevels();
            if(levels.find(level) != levels.end())
                current = fruit;
        }

        sprite_index = 0;
        setIsDisabled(false);
        setPoints(current.getPoints());
        Sprite sprite = current.getAnimations().at(sprite_index);
        setSprite(sprite);
        // TODO : set coordinates from current sprite
        timer_.start();
    }
}
