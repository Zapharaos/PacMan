/**
 * @file movingEntity.h
 * @brief Defines the movingEntity class, an entity that can move across the map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 28/02/2023
*/

#ifndef PACMAN_MOVINGENTITY_H
#define PACMAN_MOVINGENTITY_H

#include <SDL.h>

#include <vector>

#include "entity.h"
#include "../map/map.h"
#include "../utils/direction.h"
#include "../display/animation.h"

/**
 * @brief An entity that can move across the map.
 * This class represents an entity that is capable of moving across the game board. It inherits from the Entity class and has
 * additional functionality for movement, speed and animations.
 * @extends Entity
*/
class MovingEntity : public Entity
{

private:

    /** Starting position / default position (in pixels). */
    Position start_ {};

    /** Speed per tick at which the entity is moving. */
    int speed_{};

    /** Animations when moving towards the left. */
    Animation left_{};

    /** Animations when moving towards the right. */
    Animation right_{};

    /** Animations when moving towards the top. */
    Animation up_{};

    /** Animations when moving towards the bottom. */
    Animation down_{};

    /** Previous direction. */
    Direction previous_direction_{};

    /** The direction the entity will take as it reach the next cell. */
    Direction next_direction_{};

    /** True if the entity is reversing direction as it reach the next cell. */
    bool direction_reverse_ {false};

    /** True if the entity is slowed inside a tunnel, otherwise false. */
    bool zone_tunnel_slow_ {false};

    /** True if the entity is sensible to the horizontal only zone, otherwise false. */
    bool zone_horizontal_only_ {false};

    /** True if the entity is allowed to pass through the ghost house door, otherwise false. */
    bool ghost_house_door_access_ {false};

    /** True if the entity has a boost, otherwise false. */
    bool speed_up_ {false};

    /** True if the entity is slowed, otherwise false. */
    bool speed_slow_ {false};

public:

    /**
     * @brief Default MovingEntity constructor.
     * This is the default constructor for the MovingEntity class.
     */
    MovingEntity();

    /**
     * @brief Constructs a MovingEntity object with the given position, enabled state, points, speed, and animations.
     * @details Mainly used as the ghost constructor.
     * @param position Raw position.
     * @param enabled If the entity is active.
     * @param points Points earned when entity is eaten.
     * @param speed Speed per tick at which the entity is moving.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    MovingEntity(const Position &position, bool enabled, int points, int speed,
                 Animation left, Animation right, Animation up, Animation down);

    /**
     * @brief Constructs a MovingEntity object with the given position, speed, and animations.
     * @details Mainly used as the pacman constructor.
     * @param position Raw position.
     * @param speed Speed per tick at which the entity is moving.
     * @param left Animations when moving towards the left.
     * @param right Animations when moving towards the right.
     * @param up Animations when moving towards the up.
     * @param down Animations when moving towards the down.
     */
    MovingEntity(const Position &position, int speed, Animation left,
                 Animation right, Animation up, Animation down);

    /**
     * @brief Gets the speed per tick at which the entity is moving.
     * @return speed per tick at which the entity is moving.
     */
    [[nodiscard]] int getSpeed() const;

    /**
     * @brief Handle the moving entity.
     * @param map The board with all the cells.
     * @param direction The direction the entity is moving towards.
     */
    void tick(const Map &map, Direction direction);

    /**
     * @brief Prepares the next move.
     * @param map The board with all the cells.
     * @param target The position the entity is targeting.
     * @return The direction to take in order to reach the target.
     */
    Direction prepare(const Map &map, std::optional<Position> target);

    /**
     * @brief Moves the entity in the given direction if it is a legal move.
     * @param map The board with all the cells.
     * @param direction The direction the entity is moving towards.
     * @return True if the move is legal, otherwise false.
     */
    bool move(const Map &map, Direction direction);

    /**
     * @brief Indicates the next direction while moving vertically.
     * @param map The board with all the cells.
     * @return The next direction to take.
     */
    Direction moveVertically(const Map &map);

    /**
     * @brief Switches between sprites depending on the direction of the current move.
     * Called when a move is legal.
     * Uses the Animation::animate() method to switch between the different animations.
     * @param direction The direction of the current move.
     */
    virtual void animate(const Direction &direction);

    /**
     * @brief Resets the entity to the given coordinates.
     */
    virtual void reset();

    /**
     * @brief Getter for the entity previous direction.
     * @return The previous direction taken by the entity.
     */
    [[nodiscard]] const Direction &getPreviousDirection() const;

    /**
     * Setter for the entity direction reversing.
     * @param directionReverse True if the entity is reversing direction as it reach the next cell.
     */
    void setDirectionReverse(bool directionReverse);

    /**
     * @brief Setter for the entity sensibility to tunnels.
     * @param zoneTunnelSlow True if the entity is slowed inside a tunnel, otherwise false.
     */
    void setZoneTunnelSlow(bool zoneTunnelSlow);

    /**
     * Getter for the entity sensibility inside a tunnel.
     * @return True if the entity is slowed inside a tunnel, otherwise false.
     */
    [[nodiscard]] bool isZoneTunnelSlow() const;

    /**
     * Setter for the horizontal only zone.
     * @param zoneHorizontalOnly True if the entity is sensible to the horizontal only zone, otherwise false.
     */
    void setZoneHorizontalOnly(bool zoneHorizontalOnly);

    /**
     * Setter for the accessibility to the ghost house door.
     * @param ghostHouseDoorAccess True if the entity is allowed to pass through the ghost house door, otherwise false.
     */
    void setGhostHouseDoorAccess(bool ghostHouseDoorAccess);

    /**
     * @brief Setter for the entity boost.
     * @param speedSlow True if the entity has a boost, otherwise false.
     */
    void setSpeedSlow(bool speedSlow);

    /**
     * Setter for the entity slow.
     * @param speedUp True if the entity is slowed, otherwise false.
     */
    void setSpeedUp(bool speedUp);

};


#endif //PACMAN_MOVINGENTITY_H
