//
// Created by omar on 12/02/23.
//

#ifndef PEC_MEN_POWERUP_H
#define PEC_MEN_POWERUP_H
#include <SDL.h>
#include <utility>
#include <set>
#include <vector>
#include "entity.h"
#include "../utils/constants.h"
#include "../utils/timer.h"

class Fruits : public Entity{

private:

    class Fruit {
    private :
        int points_ {};
        std::set<int> levels_ {};
        std::vector<Sprite> animations_ {};
    public:
        [[nodiscard]] int getPoints() const;
        [[nodiscard]] const set<int> &getLevels() const;
        [[nodiscard]] const vector<Sprite> &getAnimations() const;
        Fruit();
        Fruit(int points, const set<int> &levels, const vector<Sprite> &animations);
    };

    Timer timer_;
    std::set<int> pelletsCap_ {56, 136};
    std::vector<Fruit> fruits_ {};
    int sprite_index {};

public:
    Fruits();
    Fruits(long time, const std::function<void(void)> &function);

    void appendFruit(int points, const set<int>& levels, const vector<Sprite>& animations);
    void updateSprite(int eaten, int level);
};


#endif //PEC_MEN_POWERUP_H
