/**
 * @file fruit.h
 * @brief Defines the Fruit class which represents a fruit that occasionally appears on the board.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 12/03/2023
*/

#ifndef PEC_MEN_POWERUP_H
#define PEC_MEN_POWERUP_H

#include <SDL.h>

#include <utility>
#include <set>
#include <vector>

#include "entity.h"
#include "../utils/timer.h"
#include "../entity/fruitObject.h"
#include "../config/config.h"
#include "../config/visuals.h"

/**
 * @brief Represents a fruit that occasionally appears on the board.
 * @see Entity
*/
class Fruit : public Entity
{

private:

    /** Timer that disables the fruit at expiration. */
    Timer timer_{};

    /** List of values at which the fruit will be displayed. */
    Container<unsigned long, config::settings::kFruitsPerLevel> pellets_cap_{};

    /** List of fruits that can be displayed.
     * @see Fruit::FruitObject class */
    Container<FruitObject, visuals::fruit::kFruitsSize> fruits_{};

    /** Index of the current FruitObject.
     * @details Used to access and animate the fruit. */
    int index_ {};

public:

    /**
     * @brief Default Fruit constructor.
     */
    Fruit();

    /**
     * @brief Fruit constructor.
     * @param total_pellets Total number of pellets.
     */
    explicit Fruit(unsigned long total_pellets);

    /**
     * @brief Tells if the fruit is enabled (i.e. displayed).
     * @details Overrides the isEnabled() method in the Entity class.
     * @return True if the fruit is enabled, false otherwise.
     */
    [[nodiscard]] bool isEnabled();

    /**
     * @brief Update the fruit only if specific conditions are met.
     * @note pelletsEaten must belong to pelletsCap_ for the fruit to be displayed.
     * @param pellets_eaten Current number of pellets eaten.
     * @param level Current level of the game.
     */
    void update(int pellets_eaten, int level);

    /**
     * @brief Executes the sprite switches when conditions are met.
     * @see FruitObject::animate()
     */
    void animate();

    /**
     * @brief Resets the fruit object.
     */
    void reset();
};


#endif //PEC_MEN_POWERUP_H
