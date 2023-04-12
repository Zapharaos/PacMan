/**
 * @file movingEntity.h
 * @brief Implements the movingEntity class, an entity that can move across the map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 28/02/2023
*/

#include "../../include/entity/movingEntity.h"

MovingEntity::MovingEntity() = default;

MovingEntity::MovingEntity(const Position &position, bool enabled, int points, int speed,
                           Animation left, Animation right, Animation up, Animation down) :
        Entity(position, left.getSprite(), enabled, points), start_(position), speed_(speed),
        left_(std::move(left)), right_(std::move(right)), up_(std::move(up)), down_(std::move(down))
{
    zone_tunnel_slow_ = true;
    zone_horizontal_only_ = true;
    dead_speed_up_ = true;
}

MovingEntity::MovingEntity(const Position &position, int speed, Animation left,
                           Animation right, Animation up, Animation down) :
        Entity(position, left.getSprite()), start_(position), speed_(speed),
        left_(std::move(left)), right_(std::move(right)), up_(std::move(up)), down_(std::move(down))
{}

int MovingEntity::getSpeed() const {
    if(speed_slow_)
        return speed_ / config::settings::kSpeedDownRatio;
    if(isDead() && dead_speed_up_)
        return speed_ * config::settings::kSpeedUpRatio;
    return speed_;
}

void MovingEntity::tick(const Map &map, Direction direction)
{
    // Handle status.
    handleStatus();

    if(move(map, direction)) // Move legal => animate.
        animate(previous_direction_);
}

void MovingEntity::handleStatus()
{
    // Changes ongoing.
    if(isCounterActive())
    {
        counterIncrement();
        return;
    }

    // Reset status : show entity.
    if(isHidden()) show();
}

Direction MovingEntity::prepare(const Map &map, std::optional<Position> target)
{
    auto current_unscaled = getPosition();
    auto current_position = current_unscaled.scaleDown(map.getCellSize());
    auto current_cell = map.getCell(current_position);

    // Default : next = current.
    auto next_position = current_position;
    auto next_cell = current_cell;

    if(!next_direction_.isUninitialized()) // only false at start or reset
    {
        // effective next cell
        auto next_unscaled = map.calculateDestination(current_unscaled, next_direction_, getSpeed(), isZoneTunnelSlow());
        next_position = next_unscaled.scaleDown(map.getCellSize());
        next_cell = map.getCell(next_position);

        if(current_cell == next_cell) // ignore : only update on cell change
            return next_direction_;

        if(direction_reverse_) // reverse
        {
            direction_reverse_ = false;
            next_position = current_position;
            next_direction_ = previous_direction_.reverse();
        }
    }

    if(next_position == target) // reached the target
        return next_direction_;

    auto current_direction = next_direction_; // local save before override
    next_direction_ = map.path(next_position, target, current_direction, zone_horizontal_only_, ghost_house_door_access_);

    if(current_direction.isUninitialized()) // only true at start or reset
    {
        previous_direction_.reset();
        return next_direction_;
    }

    // warping : move instantly towards the next direction
    if(next_direction_.isUninitialized() && current_cell->isWarp() || next_cell->isWarp())
        return next_direction_;

    // turning : move instantly towards the next direction
    if(current_direction.isTurn(next_direction_))
        return next_direction_;

    return current_direction;
}

bool MovingEntity::move(const Map &map, Direction direction)
{

    // Direction must be initialized.
    if (direction.isUninitialized())
    {
        if(previous_direction_.isUninitialized()) // No available movement.
            return false;
        direction = previous_direction_; // Repeat previous movement.
    }

    // Get positions as pixels.
    std::optional<Position> position;
    auto origin = getPosition();
    Position destination = map.calculateDestination(origin, previous_direction_, getSpeed(), isZoneTunnelSlow());

    // Direction change.
    if(direction.isTurn(previous_direction_))
    {
        position = map.turn(origin, destination, previous_direction_, direction, zone_horizontal_only_, ghost_house_door_access_);
        if(!position) // Turn is illegal.
            direction = previous_direction_; // Move into previous direction.
    }

    // Warping.
    if(map.isWarping(origin, destination) && direction == previous_direction_)
    {
        auto size = getSprite().getSize();
        auto corner = destination.shift(size.first, size.second);
        position = map.warp(destination, corner);
    }

    // No movements yet : move straight direction (or keeping same direction).
    if(!position)
    {
        position = map.move(origin, destination, direction, zone_horizontal_only_, ghost_house_door_access_);
        if (!position)
            return false; // Move is illegal.
    }

    // Move is legal : updates the entity.
    setPosition(position.value());
    previous_direction_ = direction;
    return true;
}

void MovingEntity::animate(const Direction &direction)
{
    // Nothing to animate yet.
    bool restart = previous_direction_ != direction;

    // Gets the new sprite.
    if (direction.isLeft())
        setSprite(left_.animate(restart));
    else if (direction.isRight())
        setSprite(right_.animate(restart));
    else if (direction.isUp())
        setSprite(up_.animate(restart));
    else if (direction.isDown())
        setSprite(down_.animate(restart));
}

void MovingEntity::reset()
{
    previous_direction_.reset();
    left_.reset();
    setSprite(left_.getSprite()); // default sprite
    setPosition(start_); // reset position
}

void MovingEntity::setZoneTunnelSlow(bool zoneTunnelSlow) {
    zone_tunnel_slow_ = zoneTunnelSlow;
}

void MovingEntity::setZoneHorizontalOnly(bool zoneHorizontalOnly) {
    zone_horizontal_only_ = zoneHorizontalOnly;
}

void MovingEntity::setGhostHouseDoorAccess(bool ghostHouseDoorAccess) {
    ghost_house_door_access_ = ghostHouseDoorAccess;
}

void MovingEntity::setSpeedSlow(bool speedSlow) {
    speed_slow_ = speedSlow;
}

void MovingEntity::setDirectionReverse(bool directionReverse) {
    direction_reverse_ = directionReverse;
}

void MovingEntity::resetNextDirection() {
    next_direction_.reset();
}

const Direction &MovingEntity::getPreviousDirection() const {
    return previous_direction_;
}

bool MovingEntity::isZoneTunnelSlow() const {
    return !speed_slow_ && zone_tunnel_slow_;
}
