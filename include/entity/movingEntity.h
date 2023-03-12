//
// Created by matthieu on 28/02/2023.
//

#ifndef PACMAN_MOVINGENTITY_H
#define PACMAN_MOVINGENTITY_H

#include <SDL.h>
#include <vector>
#include "entity.h"
#include "../map/map.h"
#include "../utils/direction.h"

/** Entity that can move across the map.
 *
 * @see Entity class
 */
class MovingEntity : public Entity
{

private:

    /** Speed per tick at which the entity is moving. */
    int speed_{};

    /** Animations when moving towards the left. */
    vector<Sprite> left_{};

    /** Animations when moving towards the right. */
    vector<Sprite> right_{};

    /** Animations when moving towards the top. */
    vector<Sprite> up_{};

    /** Animations when moving towards the bottom. */
    vector<Sprite> down_{};

    /** Previous direction.
     * @details Used to determine a swap of animation. */
    Direction previousDirection_{};

    /** Previous sprite's index within an animation.
     * @details Used to determine the next sprite.
     * @param bool is moving from left to right.
     * @param int index of the sprite within the animation.
     */
    pair<bool, int> previousSpriteIndex_{true, 0};

    /** Counts the ticks since the last sprite change. */
    int ticksCount_ = 0;

    /** How many ticks between each sprite change. */
    static const int tickRate_ = constants::ENTITY_REFRESH_RATE;

public:

    /** Default MovingEntity constructor. */
    MovingEntity();

    /** MovingEntity constructor.
     *
     * @param position Raw position.
     * @param sprite Image when displayed.
     * @param enabled If the entity is active.
     * @param points Points earned when entity is eaten.
     * @param speed Speed per tick at which the entity is moving.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    MovingEntity(const Position &position, Sprite sprite, bool enabled,
                 int points, int speed, const vector<Sprite> &left,
                 const vector<Sprite> &right, const vector<Sprite> &up,
                 const vector<Sprite> &down);

    /** MovingEntity constructor.
     *
     * @param position Raw position.
     * @param sprite Image when displayed.
     * @param speed Speed per tick at which the entity is moving.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    MovingEntity(const Position &position, Sprite sprite, int speed,
                 const vector<Sprite> &left,
                 const vector<Sprite> &right, const vector<Sprite> &up,
                 const vector<Sprite> &down);

    /** Getter : Raw position.
     *
     * @see Entity::getPosition() override.
     */
    [[nodiscard]] const Position &getPosition() const override;

    /** Setter : Raw position.
     *
     * @see Entity::setPosition() override.
     */
    void setPosition(const Position &coordinates) override;

    /** Getter : Sprite's position on the bitmap.
     *
     * @see Entity::getSpriteImage() override.
     */
    [[nodiscard]] const SDL_Rect &getSpriteImage() const override;

    /** Getter : Sprite's position when displayed on the window.
     *
     * @see Entity::getSpritePosition() override.
     */
    [[nodiscard]] SDL_Rect getSpritePosition() override;

    /** Getter : Previous sprite's index within an animation. */
    [[nodiscard]] virtual const pair<bool, int> &getPreviousSpriteIndex() const;

    /** Setter : Previous sprite's index within an animation. */
    virtual void
    setPreviousSpriteIndex(const pair<bool, int> &previousSpriteIndex);

    /** If legal, moves into a given direction.
     *
     * @param map The board with all the cells.
     * @param direction The direction the entity is moving towards to.
     */
    virtual void move(Map map, Direction direction);

    /** If legal, turns towards a direction, else moves towards the original direction.
     *
     * @param map The board with all the cells.
     * @param direction The direction the entity is moving towards to.
     * @param turn The direction the entity wishes to move to.
     * @return turn if it could change direction, else direction.
     */
    virtual Direction move(Map map, Direction direction, Direction turn);

    /** Switches between sprites depending on the direction.
     *
     * @details Called when a move is legal.
     *
     * @param direction the direction of the current move.
     */
    void animate(Direction direction);

    /** Indicates the index of the current sprite.
     *
     * @see previousSpriteIndex_ member.
     *
     * @param direction the direction of the current move.
     * @param max_index Maximum number of sprites for the current animation.
     * @return temporary update of previousSpriteIndex_
     */
    pair<bool, int> getCurrentSprite(Direction direction, unsigned max_index);

    /**
     * Resets the entity object.
     */
    virtual void reset(Position coordinates);
};


#endif //PACMAN_MOVINGENTITY_H
