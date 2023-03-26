/**
 * @file sprite.h
 * @brief Contains the FruitObject class which represents the fruit object in the Pacman game.
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
 * It holds information about the points awarded when the fruit is eaten, the levels at which
 * the fruit can be displayed, and the sprites to switch between when the fruit is displayed.
*/

class FruitObject
{

private :

    /** Copy elements from config files to make it easier to understand here. */
    static constexpr int kFruitsPerAnimation {config::settings::kFruitsMaximumPerAnimation};
    static constexpr int kLevelsPerFruit {config::settings::kLevelsMaximumPerFruit};

    /** Points awarded when the fruit is eaten. */
    int points_{};

    /** Levels at which the fruit can be displayed. */
    Container<int, kLevelsPerFruit> levels_{};

    /** Sprites to switch between when the fruit is displayed. */
    Animation<kFruitsPerAnimation> animation_{};

public:

    /**
     * @brief Default constructor for FruitObject.
     */
    inline FruitObject() = default;

    /**
     * @brief Constructs a FruitObject.
     * @param points Points awarded when the fruit is eaten.
     * @param levels Levels at which the fruit can be displayed.
     * @param animation Sprites to switch between when the fruit is displayed.
    */
    inline constexpr FruitObject(int points, Container<int, kLevelsPerFruit> levels,
                                 Animation<kFruitsPerAnimation> animation) :
            points_(points), levels_(levels), animation_(std::move(animation))
    {}

    /**
     * @brief Getter function for points awarded when the fruit is eaten.
     * @return Points awarded when the fruit is eaten.
     */
    [[nodiscard]] inline int getPoints() const
    { return points_; }

    /**
     * @brief Getter function for levels at which the fruit can be displayed.
     * @return Levels at which the fruit can be displayed.
     */
    [[nodiscard]] inline const Container<int, kLevelsPerFruit> &getLevels() const
    { return levels_; }

    /**
     * @brief Getter function for the current sprite.
     * @return The current sprite to be displayed.
     */
    [[nodiscard]] inline const Sprite & getSprite()
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
