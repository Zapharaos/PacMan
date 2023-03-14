//
// Created by matthieu on 28/02/2023.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include "movingEntity.h"
#include "../utils/timer.h"

/** Main entity.
 *
 * @see MovingEntity class
 */
class Pacman : public MovingEntity
{

private:

    /** Superpower mode is activated. */
    bool superpower_ = false;

    /** Timer that disables the superpower mode at expiration. */
    Timer timer_{};

    /** Has died. */
    bool dead_ = false;

    /** Animations when has died. */
    Animation death_{};

public:

    /** Default Pacman constructor. */
    Pacman();

    /** Pacman constructor.
     *
     * @param position Raw position.
     * @param sprite Image when displayed.
     * @param speed Speed per tick at which the entity is moving.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     * @param time Time before the timer expires and disables the superpower.
     * @param death Animations when has died.
     */
    Pacman(const Position &position, const Sprite &sprite, int speed,
           const Animation &left, const Animation &right,
           const Animation &up, const Animation &down,
           long time, Animation death);

    /** Setter : Superpower mode is activated. */
    void setSuperpower(bool superpower);

    /** Getter : Superpower mode is activated. */
    [[nodiscard]] bool isSuperpower();

    /** Getter : Has died. */
    [[nodiscard]] bool isDead() const;

    /** Setter : Has died. */
    void setDead(bool dead);

    /** Executes the death animation. */
    void animateDeath();

    /**
     * Resets the entity object.
     * @see MovingEntity::reset()
     */
    void reset(const Position &coordinates) override;
};


#endif //PACMAN_PACMAN_H
