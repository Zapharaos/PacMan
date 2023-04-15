/**
 * @file fruit.h
 * @brief Defines the Fruit class which represents a Fruit that occasionally appears on the board.
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
#include "../entity/fruitObject.h"
#include "../config/config.h"
#include "../config/visuals.h"

/**
 * @brief Represents a Fruit that occasionally appears on the board.
 * @extends Entity
*/
class Fruit : public Entity
{

private:

    /** List of values at which the Fruit will be displayed. */
    std::set<unsigned long> pellets_cap_{};

    /** List of Fruits that can be displayed.
     * @see Fruit::FruitObject class */
    std::vector<FruitObject> fruits_{};

    /** Index of the current FruitObject.
     * @details Used to access and animate the Fruit. */
    int index_{};

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
     * @brief Update the Fruit only if specific conditions are met.
     * @param pellets_eaten Current number of pellets eaten.
     * @param level Current level of the game.
     * @note pellets_eaten must belong to pellets_cap_ for the Fruit to be displayed.
     */
    void update(int pellets_eaten, int level);

    /**
     * @brief Executes the sprite switches when conditions are met.
     * @see FruitObject::animate()
     */
    void animate();

    /**
     * @brief Update the Fruit counter and disable it when it's over.
     */
    void tick() override;
};


#endif //PEC_MEN_POWERUP_H
