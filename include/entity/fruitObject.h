//
// Created by mfrei on 09/03/2023.
//

#ifndef PACMAN_FRUITOBJECT_H
#define PACMAN_FRUITOBJECT_H

#include <utility>
#include <set>
#include <vector>
#include "../display/sprite.h"
#include "../display/animation.h"

using namespace std;

class FruitObject
{

private :

    /** Points awarded when the fruit is eaten. */
    int points_{};

    /** Levels at which the fruit can be displayed. */
    set<int> levels_{};

    /** Sprites to switch between when the fruit is displayed. */
    Animation animation_{};

public:

    /** Default FruitObject constructor. */
    FruitObject();

    /** FruitObject constructor.
     *
     * @param points Points awarded when the fruit is eaten.
     * @param levels Levels at which the fruit can be displayed.
     * @param levels Sprites to switch between when the fruit is displayed.
     */
    FruitObject(int points, const set<int> &levels,
                Animation animation);

    /** Getter : Points awarded when the fruit is eaten. */
    [[nodiscard]] int getPoints() const;

    /** Getter : Levels at which the fruit can be displayed. */
    [[nodiscard]] const set<int> &getLevels() const;

    /** Getter : Sprites to switch between when the fruit is displayed. */
    [[nodiscard]] const Animation &getAnimation() const;

    /** Executes the sprite switches when conditions are met.
     *
     * @see Animation::animate()
     *
     * @return The current sprite to be displayed.
     */
    const Sprite &animate();
};


#endif //PACMAN_FRUITOBJECT_H
