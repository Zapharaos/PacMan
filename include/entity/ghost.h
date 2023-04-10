/**
 * @file ghost.h
 * @brief Defines the Ghost class, which is the second main entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 03/04/2023
*/

#ifndef PEC_MEN_GHOST_H
#define PEC_MEN_GHOST_H

#include "movingEntity.h"

/**
 * @brief Represents the Ghost entity in the game.
 * @extends MovingEntity
*/
class Ghost : public MovingEntity
{

public:

    /**
     * @brief Represents the different types of Ghosts.
     */
    enum class GhostType
    {
        kUndefined, /* Undefined Ghost type. */
        kBlinky, /* Blinky Ghost type. */
        kPinky, /* Pinky Ghost type. */
        kInky, /* Inky Ghost type. */
        kClyde /* Clyde Ghost type. */
    };

    /**
     * @brief Default Ghost constructor.
     */
    Ghost();

    /**
     * @brief Constructs a Ghost entity with the given type and position.
     * @param type Which type of ghosts.
     * @param position Raw position.
     * @param target The position the ghost is targeting while in scatter mode.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    Ghost(Ghost::GhostType type, const Position &position, Position target,
          Animation left, Animation right, Animation up, Animation down);

    /**
     * @brief Handle the moving entity.
     * @param map The board with all the cells.
     * @param pacman The position this entity is targeting.
     */
    void tick(const Map &map, const Position &pacman);

    /**
     * @brief Start the frightened mode.
     */
    void frightened();

    /**
     * @brief Quit the frightened mode.
     */
    void unfrightened();

    /**
     * @brief Resets the entity object.
     * @see MovingEntity::reset()
     */
    void reset() override;

private:

    /** The type of ghost. */
    GhostType type_ {GhostType::kUndefined};

    enum class GhostStatus
    {
        kStart,
        kChase,
        kScatter,
        kFrightened,
        kFrightenedBlinking
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

    /** The position the Ghost is targeting while in scatter mode. */
    Position target_ {};

    /** The direction the Ghost will take when he reach the next cell. */
    Direction next_direction_{};

    /** Whether or not the Ghost is reversing direction as he reach the next cell. */
    bool direction_reverse_ {false};

    /** Animations when moving frightened (default). */
    Animation frightened_ {};

    /** Animations when moving frightened + blinking. */
    Animation frightened_blinking_ {};

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

    /**
     * @brief Gets the next direction for the Ghost to move in.
     * @param map The game board.
     * @param pacman The position of Pac-Man.
     * @return The next direction for the Ghost to move to.
     */
    Direction getNextDirection(const Map &map, const Position &pacman);
};


#endif //PEC_MEN_GHOST_H
