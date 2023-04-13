/**
 * @file ghost.h
 * @brief Defines the Ghost class, which is the second main entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 03/04/2023
*/

#ifndef PEC_MEN_GHOST_H
#define PEC_MEN_GHOST_H

#include "movingEntity.h"

enum class GhostType {
    kBlinky,
    kPinky,
    kInky,
    kClyde
};

/**
 * @brief Represents the Ghost entity in the game.
 * @extends MovingEntity
*/
template <GhostType T>
class Ghost : public MovingEntity
{

public:

    /**
     * @brief Default Ghost constructor.
     */
    Ghost();

    /**
     * @brief Constructs a Ghost entity with the given type and position.
     * @param position Raw position.
     * @param scatter_target The position the Ghost is targeting while in scatter mode.
     * @param house_target The position the Ghost is returning to when killed.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    Ghost(const Position &position, Position scatter_target,
          Position house_target, Animation left, Animation right, Animation up, Animation down);

    /**
     * @brief Handle the moving entity.
     * @param map The board with all the cells.
     */
    void tick(const Map &map);

    /**
     * @brief Kill entity.
     */
    void kill() override;

    /**
     * @brief Start the frightened mode.
     */
    void frightened();

    /**
     * @brief Quit the frightened mode.
     */
    void unfrightened();

    template <GhostType U = T, typename std::enable_if<U == GhostType::kBlinky, int>::type = 0>
    void chase(const Position &pacman);
    /**
     * @brief Resets the entity object.
     * @see MovingEntity::reset()
     */
    void reset() override;

private:

    GhostType type_ {T};

    enum class GhostStatus
    {
        kStart,
        kChase,
        kScatter,
        kFrightened,
        kFrightenedBlinking,
        kDead,
        kHouse
    };

    /** The current status. */
    GhostStatus status_ {GhostStatus::kStart};

    /** The previous status.
     * @details Used to save the status while in frightened mode. */
    GhostStatus previous_status_ {};

    /** The number of times the Ghost's status has changed.
     * @details Set as 1 since the 0 index is const for the frightened mode. */
    size_t status_changes_ = 1;

    /** Duration values for the statuses (in seconds) :
     * Index 0 is const for the frightened mode (not blinking!).
     * Index odd : scatter timers.
     * Index even : chase timers (infinite after last scatter).
     */
    inline static constexpr std::array<int, 8> status_timers {5, 7, 20, 7, 20, 5, 20, 5};

    /** Counts a number of frames between each statuses. */
    Counter counter_ {};

    /** The position the Ghost is targeting while in chase mode. */
    Position chase_target_ {};

    /** The position the Ghost is targeting while in scatter mode. */
    Position scatter_target_ {};

    /** The position the Ghost is returning to when killed. */
    Position house_target_ {};

    /** Animations when moving frightened (default). */
    Animation frightened_ {};

    /** Animations when moving frightened + blinking. */
    Animation frightened_blinking_ {};

    /** Animations when dead and moving towards the left. */
    Animation dead_left_{};

    /** Animations when dead and moving towards the right. */
    Animation dead_right_{};

    /** Animations when dead and moving towards the top. */
    Animation dead_up_{};

    /** Animations when dead and moving towards the bottom. */
    Animation dead_down_{};

    /**
     * @brief Indicates the current target, depending on the current status.
     * @param pacman The pacman position on the map.
     * @return The effective position target by the ghost.
     */
    std::optional<Position> getTarget();

    /**
     * @brief Checks whether or not the Ghost is currently in frightened mode.
     * @return True if the Ghost is frightened, false otherwise.
     */
    bool isFrightened();

    /**
     * @brief Handles the current status of the Ghost.
     * @details This method is called during each tick to determine the
     * appropriate behavior for the Ghost based on its current status.
     */
    void handleStatus() override;

    /**
     * @brief Handles a change in the Ghost's status.
     */
    void handleStatusChange();

    /**
     * @brief Animates the Ghost based on its current direction.
     * @param direction The direction the Ghost is moving to.
     * @see MovingEntity::animate()
     */
    void animate(const Direction &direction) override;

};


#endif //PEC_MEN_GHOST_H
