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
class Pacman : MovingEntity
{

private:

    /** Superpower mode is activated. */
    bool superpower_ = false;

    /** Timer that disables the superpower mode at expiration. */
    Timer timer_{};

    /** Has died. */
    bool dead_ = false;

    /** Animations when has died. */
    vector<Sprite> death_{};

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
    Pacman(const Position &position, Sprite sprite, int speed,
           const vector<Sprite> &left, const vector<Sprite> &right,
           const vector<Sprite> &up, const vector<Sprite> &down,
           long time, const vector<Sprite> &death);

    /** Setter : Superpower mode is activated. */
    void setSuperpower(bool superpower);

    /** Getter : Superpower mode is activated. */
    [[nodiscard]] bool isSuperpower();

    /** Getter : Has died. */
    [[nodiscard]] bool isDead() const;

    /** Setter : Has died. */
    void setDead(bool dead);

    /** Getter : Raw position.
     *
     * @see MovingEntity::getPosition() override.
     */
    [[nodiscard]] const Position &getPosition() const override;

    /** Getter : Image when displayed.
     *
     * @see Entity::getSpriteImage() override.
     */
    [[nodiscard]] Sprite getSprite() const override;

    /** Getter : Sprite's position on the bitmap.
     *
     * @see MovingEntity::getSpriteImage() override.
     */
    [[nodiscard]] const SDL_Rect &getSpriteImage() const override;

    /** Getter : Sprite's position when displayed on the window.
     *
     * @see MovingEntity::getSpritePosition() override.
     */
    [[nodiscard]] SDL_Rect getSpritePosition() override;

    /** Getter : Previous sprite's index within an animation.
     *
     * @see MovingEntity::getPreviousSpriteIndex() override.
     */
    [[nodiscard]] const pair<bool, int> &
    getPreviousSpriteIndex() const override;

    /** Getter : Setter : Previous sprite's index within an animation.
     *
     * @see MovingEntity::setPreviousSpriteIndex() override.
     */
    void
    setPreviousSpriteIndex(const pair<bool, int> &previousSpriteIndex) override;

    /** Indicates whether two entities have collided.
     *
     * @param e The second entity's sprite's position.
     * @return true if collision, else false.
     */
    [[nodiscard]] bool collides(SDL_Rect e);

    /** If legal, moves into a given direction.
     *
     * @see MovingEntity::move(Map map, Direction direction)
     *
     * @param map The board with all the cells.
     * @param direction The direction the entity is moving towards to.
     */
    void move(const Map &map, Direction continuous_direction);

    /** If legal, turns towards a direction, else moves towards the original direction.
     *
     * @see MovingEntity::move(Map map, Direction direction, Direction turn)
     *
     * @param map The board with all the cells.
     * @param continuous_direction The direction the entity is moving towards to.
     * @param try_direction The direction the entity wishes to move to.
     * @return turn if it could change direction, else direction.
     */
    Direction move(const Map &map, Direction continuous_direction,
                   Direction try_direction);

    /** Executes the death animation. */
    void animateDeath();

    /**
     * Resets the entity object.
     * @see MovingEntity::reset()
     */
    void reset(Position coordinates) override;
};


#endif //PACMAN_PACMAN_H
