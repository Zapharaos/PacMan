/**
 * @file fruitObject.h
 * @brief Contains the FruitObject class which represents the Fruit object in the Pacman game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 09/03/2023
*/

#ifndef PACMAN_FRUITOBJECT_H
#define PACMAN_FRUITOBJECT_H

#include <utility>
#include <set>
#include <vector>

#include "../config/config.h"
#include "../display/sprite.h"
#include "../display/animation.h"

/**
 * @brief The FruitObject class represents the fruit object in the Pacman game.
 * It holds information about the points awarded when the Fruit is eaten, the levels at which
 * the Fruit can be displayed, and the sprites to switch between when the Fruit is displayed.
*/

class FruitObject
{

private :

    /** Points awarded when the Fruit is eaten. */
    int points_{};

    /** Levels at which the Fruit can be displayed. */
    std::set<int> levels_{};

    /** Sprites to switch between when the Fruit is displayed. */
    Animation animation_{};

public:

    /**
     * @brief Default constructor for FruitObject.
     */
    inline FruitObject() = default;

    /**
     * @brief Constructs a FruitObject.
     * @param points Points awarded when the Fruit is eaten.
     * @param levels Levels at which the Fruit can be displayed.
     * @param animation Sprites to switch between when the Fruit is displayed.
    */
    inline FruitObject(int points, std::set<int> levels, Animation animation) :
            points_(points), levels_(std::move(levels)),
            animation_(std::move(animation))
    {}

    /**
     * @brief Getter function for points awarded when the Fruit is eaten.
     * @return Points awarded when the Fruit is eaten.
     */
    [[nodiscard]] inline int getPoints() const
    { return points_; }

    /**
     * @brief Getter function for levels at which the Fruit can be displayed.
     * @return Levels at which the Fruit can be displayed.
     */
    [[nodiscard]] inline const std::set<int> &getLevels() const
    { return levels_; }

    /**
     * @brief Getter function for the current sprite.
     * @return The current sprite to be displayed.
     */
    [[nodiscard]] inline const Sprite &getSprite()
    { return animation_.getSprite(); }

    /**
     * @brief Executes the sprite switches when conditions are met.
     * @see Animation::animate()
     * @return The current sprite to be displayed.
     */
    inline const Sprite &animate()
    { return animation_.animate(); }
};


#endif //PACMAN_FRUITOBJECT_H
