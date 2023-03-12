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
#include "../entity/fruitObject.h"

/** Fruit that occasionally appears on the board.
 *
 * @see Entity class
 */
class Fruit : public Entity
{

private:

    /** Timer that disables the fruit at expiration. */
    Timer timer_{};

    /** List of values at which the fruit will be displayed. */
    set<int> pelletsCap_{};

    /** List of fruits that can be displayed.
     * @see Fruit::FruitObject class */
    vector<FruitObject> fruits_{};

    // TODO : sprite_index_ : animation ?

    /** Index of the current fruit's sprite */
    int sprite_index_{};

public:

    /** Default Fruit constructor. */
    Fruit();

    /** Fruit constructor.
     *
     * @param position Raw position when displayed.
     * @param time Time before the timer expires and disables the fruit.
     * @param pelletsCap List of values at which the fruit will be displayed.
     * @param fruits List of fruits that can be displayed.
     */
    Fruit(Position position, long time, set<int> pelletsCap,
          vector<FruitObject> fruits);

    /** Getter : Tells if the fruit is enabled (i.e. displayed).
     *
     * @see Entity::isEnabled() override.
     */
    [[nodiscard]] bool isEnabled();

    /**
     * Update the fruit only if specific conditions are met.
     *
     * @note pelletsEaten must belong to pelletsCap_ for the fruit to be displayed.
     *
     * @param pelletsEaten Current number of pellets eaten.
     * @param level Current level of the game.
     */
    void update(int pelletsEaten, int level);

    /**
     * Resets the fruit object.
     */
    void reset();
};


#endif //PEC_MEN_POWERUP_H
