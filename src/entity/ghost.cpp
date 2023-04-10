/**
 * @file ghost.cpp
 * @brief Implements the Ghost class, which is the second entity in the game.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 03/04/2023
*/

#include "../../include/entity/ghost.h"

#include <utility>

Ghost::Ghost() = default;

Ghost::Ghost(Ghost::GhostType type, const Position &position, Position scatter_target,
             Position house_target, Animation left, Animation right, Animation up, Animation down) :
    type_(type), scatter_target_(std::move(scatter_target)), house_target_(std::move(house_target)),
    MovingEntity(position, true, static_cast<int>(Score::kGhost), config::settings::kSpeedGhost,
                 std::move(left), std::move(right), std::move(up), std::move(down))
{
    frightened_ = visuals::ghosts::frightened::kAnimation;
    frightened_blinking_ = visuals::ghosts::frightened_blinking::kAnimation;
}

void Ghost::tick(const Map &map, const Position &pacman) {

    handleStatus();

    if(move(map, getNextDirection(map, pacman))) // Move legal.
        animate(next_direction_);
}

void Ghost::frightened()
{
    if(status_ == GhostStatus::kDead || status_ == GhostStatus::kHouse)
        return;

    if(!isFrightened())
    {
        previous_status_ = status_;
        direction_reverse_ = true;
    }

    if(status_timers.at(1) == 0)
        status_ = GhostStatus::kFrightenedBlinking;
    else {
        status_ = GhostStatus::kFrightened;
        counter_.save();
        counter_.start(status_timers.at(0)*config::settings::kFramesPerSecond);
    }
}

void Ghost::unfrightened()
{
    if(!isFrightened())
        return;
    if(status_ == GhostStatus::kFrightened && counter_.isActive())
        counter_.loadSave();
    status_ = previous_status_;
    next_direction_.reset();
}

void Ghost::reset()
{
    MovingEntity::reset();
    status_ = GhostStatus::kStart;
    counter_.stop();
    status_changes_ = 1;
    next_direction_.reset();
}

bool Ghost::isFrightened()
{
    return (status_ == GhostStatus::kFrightened || status_ == GhostStatus::kFrightenedBlinking);
}

void Ghost::handleStatus()
{
    // Handle ghost status.
    if(counter_.isActive())
        counter_.increment();
    else
        handleStatusChange();

    // Handle parent moving entity status.
    MovingEntity::handleStatus();
}

void Ghost::handleStatusChange() {

    if(!isEnabled())
    {
        if(status_ == GhostStatus::kDead) // Death.
        {
            if (getPosition() == house_target_)
            {
                setEnabled(true);
                counter_.loadSave();
                status_ = previous_status_;
                next_direction_.reset();
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
            direction_reverse_ = true;
        case GhostStatus::kStart:
            status_ = GhostStatus::kScatter;
            counter_.start(status_timers.at(status_changes_) * config::settings::kFramesPerSecond);
            return;
        case GhostStatus::kScatter:
            status_changes_++;
            status_ = GhostStatus::kChase;
            direction_reverse_ = true;
            if(status_changes_ < config::settings::kGhostStatusChangesBeforeInfiniteChase)
                counter_.start(status_timers.at(status_changes_) * config::settings::kFramesPerSecond);
            return;
        default: // unreachable
            return;
    }
}

void Ghost::animate(const Direction &direction)
{
    // Override MovingEntity::animate() in special cases.
    if(status_ == GhostStatus::kFrightened)
        setSprite(frightened_.animate());
    else if(status_ == GhostStatus::kFrightenedBlinking)
        setSprite(frightened_blinking_.animate());
    else
        MovingEntity::animate(direction);
}

Direction Ghost::getNextDirection(const Map &map, const Position &pacman)
{
    auto current_unscaled = getPosition();
    auto current_position = current_unscaled.getPositionUnscaled(map.getCellSize());
    auto current_cell = map.getCell(current_position);

    // default, next = current
    auto next_position = current_position;
    auto next_cell = current_cell;

    Direction reverse = next_direction_.reverse();

    if(!next_direction_.isUninitialized()) // only false at start or reset
    {
        // effective next cell
        auto next_unscaled = map.calculateDestination(current_unscaled, next_direction_, isTunnelSlow(), getSpeed());
        next_position = next_unscaled.getPositionUnscaled(map.getCellSize());
        next_cell = map.getCell(next_position);

        if(current_cell == next_cell) // ignore : only update on cell change
            return next_direction_;

        if(direction_reverse_) // reverse
        {
            next_position = current_position;
            next_direction_ = reverse;
        }
    }

    bool forbid_ghost_vertical = false;

    if(current_position.getAbscissa() == 11 && current_position.getOrdinate() == 10)
        forbid_ghost_vertical = false;

    if(!isFrightened() && status_ != GhostStatus::kDead)
        forbid_ghost_vertical = current_cell->isGhostHorizontal() && next_cell->isGhostHorizontal();
    auto directions = map.getAvailableDirections(next_position, next_direction_, status_ == GhostStatus::kDead, forbid_ghost_vertical);

    if(directions.empty()) // nothing available
    {
        if(current_cell->isWarp() || next_cell->isWarp())
            return next_direction_;
        next_direction_ = reverse;
    }
    else if(directions.size() == 1) // one way
    {
        next_direction_ = *(directions.begin());
    }
    else if(isFrightened()) // intersection : random
    {
        next_direction_ = Direction{getRandomElementFromSet(directions)};
    }
    else // intersection : pathfinding
    {
        Position target;
        switch(status_)
        {
            case GhostStatus::kChase:
                target = pacman; // TODO : get pacman target per ghost
                break;
            case GhostStatus::kScatter:
                target = scatter_target_;
                break;
            case GhostStatus::kDead:
            default:
                target = house_target_;
                break;
        }
        double min_distance = std::numeric_limits<double>::max();

        for(auto &element : directions)
        {
            auto position_scaled = next_position.getNeighbor(Direction{element});
            auto position = position_scaled.getPositionScaled(map.getCellSize());
            double distance = target.getDistance(position);
            if(distance < min_distance)
            {
                min_distance = distance;
                next_direction_ = Direction{element};
            }
        }
    }

    if(direction_reverse_) // reverse
    {
        direction_reverse_ = false;
        return reverse;
    }

    return next_direction_;
}

void Ghost::kill() {
    if(!isFrightened())
    {
        previous_status_ = status_;
        counter_.save();
    }
    status_ = GhostStatus::kDead;
    counter_.stop();
    next_direction_.reset();
    Entity::kill();
}
