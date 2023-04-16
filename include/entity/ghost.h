/**
 * @file ghost.h
 * @brief Defines the Ghost class, which is the second main entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 03/04/2023
*/

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include "movingEntity.h"

/**
 * @brief Represents the Ghost entity in the game.
 * @extends MovingEntity
*/
class Ghost : public MovingEntity
{

public:

    /**
     * @brief Default Ghost constructor.
     */
    Ghost();

    /**
     * @brief Constructor for the Ghost class.
     * @param position Raw position.
     * @param scatter_target The position the Ghost is targeting while in scatter mode.
     * @param house_target The position the Ghost is returning to when killed.
     * @param pellets The number amount of pellets to be eaten for the Ghost to leave the house.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    Ghost(const Position &position, Position scatter_target, Position house_target,
          unsigned long pellets, Animation left, Animation right, Animation up, Animation down);

    /**
     * @brief Gets the position the Ghost is targeting while in scatter mode.
     * @return The scatter target.
     */
    [[nodiscard]] const Position &getScatterTarget() const;

    /**
     * @brief Sets the position the Ghost is targeting while in chase mode.
     * @param chaseTarget The new chase target.
     */
    void setChaseTarget(const Position &chaseTarget);

    /**
     * @brief Change the ghost statuses.
     * @details In some cases, it might not changed the current one, but the previous one.
     */
    void statusChange();

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
     * @param seconds Duration of the frightened status, without frightened blinking.
     */
    void frightened(unsigned long seconds);

    /**
     * @brief Quit the frightened mode.
     */
    void unfrightened();

    /**
     * @brief Animates the Ghost based on its current direction.
     * @param direction The direction the Ghost is moving to.
     * @see MovingEntity::animate()
     */
    void animate(const Direction &direction) override;

    /**
     * @brief Resets the entity object.
     * @see MovingEntity::reset()
     */
    void reset() override;

    /**
     * @brief Restarts the Ghost from the house, after pacman death.
     */
    void restartFromHouse();

    /**
     * @brief If authorized, force the ghost to exit the ghost house.
     * @return True if the Ghost has left the house, false otherwise.
     */
    bool exitHouse();

    /**
     * @brief Increments the pellet counter if the Ghost is in the house.
     * @return True if the Ghost is in the house and the pellet counter is active, false otherwise.
     */
    bool inHouseIncrementPelletCounter();

private:

    /** Represents the possible statuses of the Ghost. */
    enum class GhostStatus
    {
        kHouseWaiting, /* Waiting in the house. */
        kHouse, /* In the house but on his way out. */
        kChase, /* Chasing pacman. */
        kScatter, /* Scattering. */
        kFrightened, /* Scared. */
        kFrightenedBlinking, /* Scared with a blinking animation. */
        kDead /* Dead on his way back to the ghost house. */
    };

    /** The current status. */
    GhostStatus status_ {GhostStatus::kHouseWaiting};

    /** The previous status.
     * @details Used to save the status while in frightened mode. */
    GhostStatus previous_status_ {GhostStatus::kScatter};

    /** Counts a number of frames between each statuses. */
    Counter frigthened_counter_ {};

    /** Counts a number of pellets to be eaten for the Ghost to leave the house. */
    Counter pellet_counter_ {};

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
     * @brief Handles the current status of the Ghost.
     * @details This method is called during each tick to determine the
     * appropriate behavior for the Ghost based on its current status.
     */
    void handleStatus() override;

    /**
     * @brief Indicates the current target, depending on the current status.
     * @param pacman The pacman position on the map.
     * @return The effective position target by the ghost.
     */
    std::optional<Position> getTarget();

    /**
     * @brief The current cell the ghost is occupying.
     * @return The current cell the ghost is occupying.
     */
    Position getCurrentCellPosition();

};


#endif //PACMAN_GHOST_H
