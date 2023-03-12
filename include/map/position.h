//
// Created by mfrei on 10/03/2023.
//

#ifndef PACMAN_POSITION_H
#define PACMAN_POSITION_H

#include <utility>
#include <cstdlib>
#include "../utils/direction.h"

using namespace std;

/** Position as abscissa and ordinate. */
class Position
{

private:

    /** Position as abscissa and ordinate. */
    pair<int, int> position_{};

public:

    /** Default position constructor */
    Position();

    /** Position constructor
     *
     * @param position Position as abscissa and ordinate.
     */
    explicit Position(const pair<int, int> &position);

    /** Indicates if both positions are equals. */
    bool operator==(const Position &rhs) const;

    /** Indicates if both positions are different. */
    bool operator!=(const Position &rhs) const;

    /** Getter : abscissa */
    [[nodiscard]] const int &getAbscissa() const;

    /** Getter : ordinate */
    [[nodiscard]] const int &getOrdinate() const;

    /** Indicates whether a position is out of bounds or not.
     *
     * @param width Width limit.
     * @param height Height limit.
     * @return true if the position is out of bounds, else false.
     */
    [[nodiscard]] bool isOutOfBounds(int width, int height) const;

    /** Indicates whether its between two positions or not.
     *
     * @param a The first position.
     * @param b The second position.
     * @return true if located between both positions, else false.
     */
    [[nodiscard]] bool isBetween(const Position &a, const Position &b) const;

    /** The distance on a single axis (horizontal or vertical).
     *
     * @pre Both positions must be either horizontally or vertically aligned.
     *
     * @param position The second position.
     * @return the distance between both positions.
     */
    [[nodiscard]] int getSingleAxisDistance(const Position &position) const;

    /** Scales the position.
     *
     * @param scale The scale.
     * @return Copy of the original object with its position scaled.
     */
    [[nodiscard]] Position getPositionScaled(int scale) const;

    /** Unscales the position.
     *
     * @param scale The scale.
     * @return Copy of the original object with its position unscaled.
     */
    [[nodiscard]] Position getPositionUnscaled(int scale) const;

    /** Indicates if two positions are neighbors.
     *
     * @param position Second position.
     * @return true if positions are neighbors, else false.
     */
    [[nodiscard]] bool isNeighbor(const Position &position) const;

    /** Position's neighbor in a specific direction.
     *
     * @param direction The direction.
     * @return the neighbor's position.
     */
    [[nodiscard]] Position getNeighbor(const Direction &direction) const;

    /** Moves into a direction.
     *
     * @param direction The direction of the movement.
     * @param distance The distance of the movement.
     * @return Copy of the original object with its position moved.
     */
    [[nodiscard]] Position moveIntoDirection(const Direction &direction, int distance) const;

    /**
     * [Debug] : Prints the position.
     */
    void print() const;
};


#endif //PACMAN_POSITION_H
