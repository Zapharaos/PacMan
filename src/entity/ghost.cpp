/**
 * @file ghost.cpp
 * @brief Implements the Ghost class, which is the second entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 03/04/2023
*/

#include "../../include/entity/ghost.h"

#include <utility>

template <GhostType T>
Ghost<T>::Ghost() = default;

template <GhostType T>
Ghost<T>::Ghost(const Position &position, Position scatter_target,
             Position house_target, Animation left, Animation right, Animation up, Animation down) :
    scatter_target_(std::move(scatter_target)), house_target_(std::move(house_target)),
    MovingEntity(position, true, static_cast<int>(Score::kGhost), config::settings::kSpeedGhost,
                 std::move(left), std::move(right), std::move(up), std::move(down))
{
    frightened_ = visuals::ghosts::frightened::kAnimation;
    frightened_blinking_ = visuals::ghosts::frightened_blinking::kAnimation;
    dead_left_ = visuals::ghosts::dead::left::kAnimation;
    dead_right_ = visuals::ghosts::dead::right::kAnimation;
    dead_up_ = visuals::ghosts::dead::up::kAnimation;
    dead_down_ = visuals::ghosts::dead::down::kAnimation;
}

template <GhostType T>
std::optional<Position> Ghost<T>::getTarget()
{
    switch(status_)
    {
        case GhostStatus::kChase:
            return chase_target_;
        case GhostStatus::kScatter:
            return scatter_target_;
        case GhostStatus::kDead:
            return house_target_;
        default:
            return std::nullopt;
    }
}

template <GhostType T>
bool Ghost<T>::isFrightened()
{
    return (status_ == GhostStatus::kFrightened || status_ == GhostStatus::kFrightenedBlinking);
}

template <GhostType T>
void Ghost<T>::handleStatus()
{
    // Handle ghost status.
    if(counter_.isActive())
        counter_.increment();
    else
        handleStatusChange();

    // Handle parent moving entity status.
    MovingEntity::handleStatus();
}

template <GhostType T>
void Ghost<T>::handleStatusChange() {

    if(!isEnabled())
    {
        if(isDead()) // Death.
        {
            if (house_target_ == getPosition().scaleDown(config::dimensions::kWindowCellSize))
            {
                setEnabled(true);
                counter_.loadSave();
                status_ = previous_status_;
                resetNextDirection();
                setZoneTunnelSlow(true);
                setZoneHorizontalOnly(true);
                setGhostHouseDoorAccess(false);
                show();
            }
        }
        else if(status_ == GhostStatus::kHouse)// Ghost house.
        {
            // TODO : ghost house status
        }
        return;
    }

    if (status_ == GhostStatus::kFrightened)
    {
        status_ = GhostStatus::kFrightenedBlinking;
        return;
    }

    if(status_changes_ > config::settings::kGhostStatusChangesBeforeInfiniteChase)
        return;

    switch(status_)
    {
        case GhostStatus::kChase:
            status_changes_++;
            setDirectionReverse(true);
        case GhostStatus::kStart:
            status_ = GhostStatus::kScatter;
            counter_.start(status_timers.at(status_changes_) * config::settings::kFramesPerSecond);
            return;
        case GhostStatus::kScatter:
            status_changes_++;
            status_ = GhostStatus::kChase;
            setDirectionReverse(true);
            if(status_changes_ < config::settings::kGhostStatusChangesBeforeInfiniteChase)
                counter_.start(status_timers.at(status_changes_) * config::settings::kFramesPerSecond);
            return;
        default: // unreachable
            return;
    }
}

template <GhostType T>
void Ghost<T>::animate(const Direction &direction)
{
    // Override MovingEntity::animate() in special cases.
    if(status_ == GhostStatus::kFrightened)
        setSprite(frightened_.animate());
    else if(status_ == GhostStatus::kFrightenedBlinking)
        setSprite(frightened_blinking_.animate());
    else if(!isDead())
        MovingEntity::animate(direction);
    else
    {
        if(direction.isLeft())
            setSprite(dead_left_.animate());
        else if(direction.isRight())
            setSprite(dead_right_.animate());
        else if(direction.isUp())
            setSprite(dead_up_.animate());
        else if(direction.isDown())
            setSprite(dead_down_.animate());
    }
}

template <GhostType T>
void Ghost<T>::tick(const Map &map) {

    handleStatus();

    // Current direction and prepare next move.
    Direction direction = prepare(map, getTarget());

    if(move(map, direction)) // Move legal => animate.
        animate(getPreviousDirection());
}

template <GhostType T>
void Ghost<T>::kill() {
    if(!isFrightened())
    {
        previous_status_ = status_;
        counter_.save();
    }
    status_ = GhostStatus::kDead;
    counter_.stop();
    resetNextDirection();
    setZoneTunnelSlow(false);
    setZoneHorizontalOnly(false);
    setGhostHouseDoorAccess(true);
    setDirectionReverse(false);
    setSpeedSlow(false);
    Entity::kill();
}

template <GhostType T>
void Ghost<T>::frightened()
{
    if(isDead() || status_ == GhostStatus::kHouse)
        return;

    if(!isFrightened())
    {
        previous_status_ = status_;
        setDirectionReverse(true);
        setZoneHorizontalOnly(false);
        setSpeedSlow(true);
    }

    if(status_timers.at(1) == 0)
        status_ = GhostStatus::kFrightenedBlinking;
    else {
        status_ = GhostStatus::kFrightened;
        counter_.save();
        counter_.start(status_timers.at(0)*config::settings::kFramesPerSecond);
    }
}

template <GhostType T>
void Ghost<T>::unfrightened()
{
    if(!isFrightened())
        return;
    if(status_ == GhostStatus::kFrightened && counter_.isActive())
        counter_.loadSave();
    status_ = previous_status_;
    resetNextDirection();
    setZoneHorizontalOnly(true);
    setSpeedSlow(false);
}

template <GhostType T>
void Ghost<T>::reset()
{
    MovingEntity::reset();
    status_ = GhostStatus::kStart;
    counter_.stop();
    status_changes_ = 1;
    resetNextDirection();
    setZoneTunnelSlow(false);
    setZoneHorizontalOnly(false);
    setGhostHouseDoorAccess(true);
    setSpeedSlow(false);
}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kBlinky, int>::type>
void Ghost<T>::chase(const Position &pacman)
{
    if(status_ != GhostStatus::kChase) return;

    chase_target_ = pacman;
}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kPinky, int>::type>
void Ghost<T>::chase(const Position &pacman, const Direction &direction)
{
    if(status_ != GhostStatus::kChase) return;

    chase_target_ = pacman.moveIntoDirection(direction, config::settings::kPinkyOffsetToPacman);
}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kInky, int>::type>
void Ghost<T>::chase(const Position &pacman, const Direction &direction, const Position &blinky)
{
    if(status_ != GhostStatus::kChase) return;

    auto offset_position = pacman.moveIntoDirection(direction, config::settings::kInkyOffsetToPacman);
    auto difference = blinky.getDistance2D(offset_position);
    chase_target_ = offset_position.shift(difference.getAbscissa(), difference.getOrdinate());
}

template <GhostType T>
template <GhostType U, typename std::enable_if<U == GhostType::kClyde, int>::type>
void Ghost<T>::chase(const Position &pacman)
{
    if(status_ != GhostStatus::kChase) return;

    auto current_cell_position = getPosition().scaleDown(config::dimensions::kWindowCellSize);
    if(current_cell_position.getDistance(pacman) >= config::settings::kClydeDistanceFromPacman)
        chase_target_ = pacman;
    else
        chase_target_ = scatter_target_;
}
