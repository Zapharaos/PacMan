//
// Created by omar on 08/02/23.
//

#ifndef PEC_MEN_ENTITY_H
#define PEC_MEN_ENTITY_H

#include <SDL.h>
#include <string>
#include <iostream>
#include <utility>
#include "../utils/constants.h"
#include "../sprite/sprite.h"

using namespace std;

/** An object located on the map. */
class Entity
{

private:

    /** Raw position. */
    Position position_{};

    /** Image when displayed. */
    Sprite sprite_{};

    /** If the entity is active. */
    bool enabled_ = false;

    /** Points earned when entity is eaten. */
    int points_{};

public:

    /** Default Entity constructor. */
    Entity();

    /** Entity constructor
     *
     * @param position Raw position.
     * @param sprite Image when displayed.
     * @param enabled If the entity is active.
     * @param points Points earned when entity is eaten.
     */
    Entity(Position position, Sprite sprite, bool enabled, int points);

    /** Entity constructor
     *
     * @param position Raw position.
     * @param sprite Image when displayed.
     */
    Entity(Position position, Sprite sprite);

    /** Entity constructor
     *
     * @param position Raw position.
     */
    explicit Entity(Position position);

    /** Getter : Raw position. */
    [[nodiscard]] virtual const Position &getPosition() const;

    /** Setter : Raw position. */
    virtual void setPosition(const Position &position);

    /** Getter : Image when displayed. */
    [[nodiscard]] virtual const Sprite &getSprite() const;

    /** Setter : Image when displayed. */
    void setSprite(const Sprite &sprite);

    /** Getter : Points earned when entity is eaten. */
    [[nodiscard]] int getPoints() const;

    /** Setter : Points earned when entity is eaten. */
    void setPoints(int points);

    /** Getter : If the entity is active. */
    [[nodiscard]] bool isEnabled() const;

    /** Setter : If the entity is active. */
    void setEnabled(bool enabled);

    /** Getter : Sprite's position on the bitmap.
     *
     * @see Sprite::getImage().
     */
    [[nodiscard]] virtual const SDL_Rect &getSpriteImage() const;

    /** Getter : Sprite's position when displayed on the window.
     *
     * @see Sprite::getPosition().
     */
    [[nodiscard]] virtual const SDL_Rect &getSpritePosition();

    /** [Debug] : Prints the entity's members. */
    void print() const;
};

#endif //PEC_MEN_ENTITY_H
