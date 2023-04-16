/**
 * @file ghostSpecial.h
 * @brief Defines the GhostSpecial class, which is an extended version of Ghost in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 13/04/2023
*/

#ifndef PACMAN_GHOSTSPECIAL_H
#define PACMAN_GHOSTSPECIAL_H

#include "ghost.h"

/** Represents the special types of Ghost. */
enum class GhostType {
    kBlinky,
    kPinky,
    kInky,
    kClyde
};

/**
 * @brief The GhostSpecial class is an extended version of the Ghost class, which is a game entity that chases the player in the game Pac-Man.
 * @tparam T The type of ghost to create.
 */
template <GhostType T>
class GhostSpecial : public Ghost
{

private:

    /** The type of the ghost. */
    GhostType type_ {T};

public:

    /**
    * @brief Default constructor for the GhostSpecial class.
    */
    GhostSpecial();

    /**
    * @brief Constructor for the GhostSpecial class.
    * @param position Raw position.
    * @param scatter_target The position the Ghost is targeting while in scatter mode.
    * @param house_target The position the Ghost is returning to when killed.
    * @param pellets The number amount of pellets to be eaten for the Ghost to leave the house.
    * @param left Animations when moving towards the left.
    * @param right Animations when moving towards the right.
    * @param up Animations when moving towards the up.
    * @param down Animations when moving towards the down.
    */
    GhostSpecial(const Position &position, const Position &scatterTarget,
                 const Position &houseTarget, unsigned long pellets,
                 const Animation &left, const Animation &right,
                 const Animation &up, const Animation &down);

    /**
     * @brief Chase method for the GhostSpecial class with behavior specific to Blinky.
     * @tparam U The type of the ghost (copy of T).
     * @param pacman The position of pacman.
     */
    template <GhostType U = T, typename std::enable_if<U == GhostType::kBlinky, int>::type = 0>
    void chase(const Position &pacman);

    /**
     * @brief Chase method for the GhostSpecial class with behavior specific to Pinky.
     * @tparam U The type of the ghost (copy of T).
     * @param pacman The position of pacman.
     * @param direction The current direction of pacman.
     */
    template <GhostType U = T, typename std::enable_if<U == GhostType::kPinky, int>::type = 0>
    void chase(const Position &pacman, const Direction &direction);

    /**
     * @brief Chase method for the GhostSpecial class with behavior specific to Inky.
     * @tparam U The type of the ghost (copy of T).
     * @param pacman The position of pacman.
     * @param direction The current direction of pacman.
     * @param blinky The position of Blinky.
     */
    template <GhostType U = T, typename std::enable_if<U == GhostType::kInky, int>::type = 0>
    void chase(const Position &pacman, const Direction &direction, const Position &blinky);

    /**
     * @brief Chase method for the GhostSpecial class with behavior specific to Clyde.
     * @tparam U The type of the ghost (copy of T).
     * @param pacman The position of pacman.
     */
    template <GhostType U = T, typename std::enable_if<U == GhostType::kClyde, int>::type = 0>
    void chase(const Position &pacman);

};


#endif //PACMAN_GHOSTSPECIAL_H
