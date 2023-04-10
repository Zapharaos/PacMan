/**
 * @file position.h
 * @brief Defines the Position class representing a position on a 2D grid.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 10/02/2023
 */

#ifndef PACMAN_POSITION_H
#define PACMAN_POSITION_H

#include <utility>
#include <cstdlib>

#include "../utils/direction.h"

/**
 * @brief Represents a position on a 2D grid.
 */
class Position
{

private:

    /** Position as abscissa and ordinate. */
    std::pair<int, int> position_{};

public:

    /**
     * @brief Default constructor for the Position class.
     */
    Position();

    /**
     * @brief Constructor for the Position class.
     * @param position A pair representing the abscissa and ordinate of the position.
     */
    explicit Position(std::pair<int, int> position);

    /**
     * @brief Constructor for the Position class.
     * @param abscissa The abscissa of the position.
     * @param ordinate The ordinate of the position.
     */
    Position(int abscissa, int ordinate);

    /**
     * @brief Overloaded operator for the equality of two Position objects.
     * @param position The Position object to compare to.
     * @return True if both positions are equal, else false.
     */
    bool operator==(const Position &position) const;

    /**
     * @brief Overloaded operator for the inequality of two Position objects.
     * @param position The Position object to compare to.
     * @return True if both positions are different, else false.
     */
    bool operator!=(const Position &position) const;

    /**
     * @brief Getter for the abscissa of the position.
     * @return The abscissa of the position.
     */
    [[nodiscard]] const int &getAbscissa() const;

    /**
     * @brief Getter for the ordinate of the position.
     * @return The ordinate of the position.
     */
    [[nodiscard]] const int &getOrdinate() const;

    /**
     * @brief Gets the Euclidean distance between two positions.
     * @param position The second position.
     * @return The Euclidean distance between both positions.
     */
    [[nodiscard]] double getDistance(const Position& position) const;

    /**
     * @brief Indicates whether the position is out of bounds or not.
     * @param width The width limit of the grid.
     * @param height The height limit of the grid.
     * @return True if the position is out of bounds, else false.
     */
    [[nodiscard]] bool isOutOfBounds(int width, int height) const;

    /**
     * @brief Indicates whether the position is between two other positions or not.
     * @param a The first position.
     * @param b The second position.
     * @return True if the position is located between both positions, else false.
     */
    [[nodiscard]] bool isBetween(const Position &a, const Position &b) const;

    /**
     * @brief Gets the distance between two positions on a single axis (horizontal or vertical).
     * @pre Both positions must be either horizontally or vertically aligned.
     * @param position The second position.
     * @return The distance between both positions.
     */
    [[nodiscard]] int getSingleAxisDistance(const Position &position) const;

    /**
     * @brief Scales the position.
     * @param scale The scale factor.
     * @return A copy of the original object with its position scaled.
     */
    [[nodiscard]] Position getPositionScaled(int scale) const;

    /**
     * @brief Unscales the position.
     * @param scale The scale factor.
     * @return A copy of the original object with its position unscaled.
     */
    [[nodiscard]] Position getPositionUnscaled(int scale) const;

    /**
     * @brief Indicates if two positions are neighbors.
     * @param position Second position.
     * @return True if positions are neighbors, else false.
     */
    [[nodiscard]] bool isNeighbor(const Position &position) const;

    /**
     * @brief Gets the neighbor of the position in a specific direction.
     * @param direction The direction.
     * @return The neighbor's position.
     */
    [[nodiscard]] Position getNeighbor(const Direction &direction) const;

    /**
     * @brief Moves the position a certain distance into a direction.
     * @param direction The direction of the movement.
     * @param distance The distance of the movement.
     * @return Copy of the original object with its position moved.
     */
    [[nodiscard]] Position moveIntoDirection(const Direction &direction, int distance) const;

    /**
     * @brief Shifts the position by a certain amount.
     * @param x Distance on the abscissa axis.
     * @param y Distance on the ordinate axis.
     * @return The position shifted.
     */
    [[nodiscard]] Position shift(int x, int y) const;

    /**
     * @brief Gets the position's limit at the opposite.
     * @pre The position's origin must already be out of bounds.
     * @param width The maximum width.
     * @param height The maximum height.
     * @return The position at the opposite.
     */
    [[nodiscard]] Position getOpposite(int width, int height) const;

};


#endif //PACMAN_POSITION_H
