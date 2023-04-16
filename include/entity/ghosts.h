/**
 * @file ghosts.cpp
 * @brief Defines the Ghosts class, which contains all Ghost entities in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 13/04/2023
*/

#ifndef PACMAN_GHOSTS_H
#define PACMAN_GHOSTS_H

#include "../../src/entity/ghostSpecial.cpp"

/**
 * @brief Class representing all the Ghost entities in the game.
 */
class Ghosts
{

private:

    /** The Ghost entities. */
    std::shared_ptr<GhostSpecial<GhostType::kBlinky>> blinky_ {};
    std::shared_ptr<GhostSpecial<GhostType::kPinky>> pinky_ {};
    std::shared_ptr<GhostSpecial<GhostType::kInky>> inky_ {};
    std::shared_ptr<GhostSpecial<GhostType::kClyde>> clyde_ {};
    std::array<std::shared_ptr<Ghost>, 4> ghosts_entities {};

    /** Counts a number of frames between each statuses. */
    Counter status_counter_ {};

    /** The number of times the Ghost's status has changed. */
    size_t status_changes_ {};

    /** Counts a number of pellets after restartFromHouse() is called. */
    Counter pellet_counter_ {};

    /** True if counting for pellets, otherwise false. */
    bool pellet_counting_ {false};

public:

    /**
     * @brief Default Ghosts constructor.
     */
    Ghosts();

    /**
     * @brief Returns an array containing all the Ghost entities.
     * @return An array containing all the Ghost entities.
     */
    std::array<std::shared_ptr<Ghost>, 4> getGhosts();

    /**
     * @brief Updates the state of the Ghost entities based on the player's position and direction.
     * @param map The board with all the cells.
     * @param position The current position of the pacman.
     * @param direction The current direction of the pacman.
     */
    void tick(const Map& map, Position position, Direction direction);

    /**
     * @brief Sets all Ghost entities into frightened mode.
     */
    void frightened();

    /**
     * @brief Resets the state of all Ghost entities.
     */
    void reset();

    /**
     * @brief Increases the level of all Ghost entities.
     */
    void levelUp();

    /**
     * @brief Restarts all Ghost entities from the house.
     */
    void restartFromHouse();

    /**
     * @brief Notifies the Ghost entities that a pellet has been eaten.
     */
    void pelletEaten();

    /**
     * @brief Animates all Ghost entities.
     */
    void animate();
};


#endif //PACMAN_GHOSTS_H
