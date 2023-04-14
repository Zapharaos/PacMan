//
// Created by mfrei on 13/04/2023.
//

#include "../../include/entity/ghostSpecial.h"


template<GhostType T>
GhostSpecial<T>::GhostSpecial() = default;

template<GhostType T>
GhostSpecial<T>::GhostSpecial(const Position &position,
                              const Position &scatterTarget,
                              const Position &houseTarget,
                              const Animation &left, const Animation &right,
                              const Animation &up, const Animation &down):Ghost(
        position, scatterTarget, houseTarget, left, right, up, down)
{}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kBlinky, int>::type>
void GhostSpecial<T>::chase(const Position &pacman)
{
    setChaseTarget(pacman);
}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kPinky, int>::type>
void GhostSpecial<T>::chase(const Position &pacman, const Direction &direction)
{
    setChaseTarget(pacman.moveIntoDirection(direction, config::settings::kPinkyOffsetToPacman));
}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kInky, int>::type>
void GhostSpecial<T>::chase(const Position &pacman, const Direction &direction, const Position &blinky)
{
    auto offset_position = pacman.moveIntoDirection(direction, config::settings::kInkyOffsetToPacman);
    auto difference = blinky.getDistance2D(offset_position);
    setChaseTarget(offset_position.shift(difference.getAbscissa(), difference.getOrdinate()));
}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kClyde, int>::type>
void GhostSpecial<T>::chase(const Position &pacman)
{
    auto current_cell_position = getPosition().scaleDown(config::dimensions::kWindowCellSize);
    auto distance = current_cell_position.getDistance(pacman);
    if(distance >= config::settings::kClydeDistanceFromPacman)
        setChaseTarget(pacman);
    else
        setChaseTarget(getScatterTarget());
}