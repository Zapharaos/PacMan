/**
 * @file ghostSpecial.cpp
 * @brief Implements the GhostSpecial class, which is an extended version of Ghost in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 13/04/2023
*/

#include "../../include/entity/ghostSpecial.h"

template<GhostType T>
GhostSpecial<T>::GhostSpecial() = default;

template<GhostType T>
GhostSpecial<T>::GhostSpecial(const Position &position,
                              const Position &scatterTarget,
                              const Position &houseTarget,
                              unsigned long pellets,
                              const Animation &left, const Animation &right,
                              const Animation &up, const Animation &down):Ghost(
        position, scatterTarget, houseTarget, pellets, left, right, up, down)
{}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kBlinky, int>::type>
void GhostSpecial<T>::chase(const Position &pacman)
{
    // Simply targeting the current cell of pacman.
    setChaseTarget(pacman);
}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kPinky, int>::type>
void GhostSpecial<T>::chase(const Position &pacman, const Direction &direction)
{
    // Targeting the current cell of pacman with a specific offset in a specific direction.
    setChaseTarget(pacman.shift(direction, config::settings::kPinkyOffsetToPacman));
}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kInky, int>::type>
void GhostSpecial<T>::chase(const Position &pacman, const Direction &direction, const Position &blinky)
{
    // Get the current cell of pacman with a specific offset in a specific direction.
    auto offset_position = pacman.shift(direction, config::settings::kInkyOffsetToPacman);
    // Get the distance between this new cell and blinky's current cell.
    auto difference = blinky.getDistance2D(offset_position);
    // Apply the difference to the newly calculated cell.
    setChaseTarget(offset_position.shift(difference.getAbscissa(), difference.getOrdinate()));
}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kClyde, int>::type>
void GhostSpecial<T>::chase(const Position &pacman)
{
    // Changes the target depending on how far/close it is from pacman's current cell.
    auto current_cell_position = getPosition().scaleDown(config::dimensions::kWindowCellSize);
    auto distance = current_cell_position.getDistance(pacman);
    if(distance >= config::settings::kClydeDistanceFromPacman) // Too far.
        setChaseTarget(pacman); // Target pacman.
    else // Too close.
        setChaseTarget(getScatterTarget()); // Scatter target.
}