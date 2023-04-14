//
// Created by mfrei on 13/04/2023.
//

#include "../../include/entity/ghosts.h"

Ghosts::Ghosts()
{
    blinky_ = std::make_shared<GhostSpecial<GhostType::kBlinky>>(
            Position{config::positions::entities::blinky::kDefaultX,
                        config::positions::entities::blinky::kDefaultY},
               Position{config::positions::entities::blinky::kTargetX,
                        config::positions::entities::blinky::kTargetY},
               Position{config::positions::entities::blinky::kHouseX,
                        config::positions::entities::blinky::kHouseY},
               visuals::ghosts::blinky::left::kAnimation,
               visuals::ghosts::blinky::right::kAnimation,
               visuals::ghosts::blinky::up::kAnimation,
               visuals::ghosts::blinky::down::kAnimation);
    pinky_ = std::make_shared<GhostSpecial<GhostType::kPinky>>(
            Position{config::positions::entities::blinky::kDefaultX,
                        config::positions::entities::blinky::kDefaultY},
               Position{config::positions::entities::pinky::kTargetX,
                        config::positions::entities::pinky::kTargetY},
               Position{config::positions::entities::pinky::kHouseX,
                        config::positions::entities::pinky::kHouseY},
               visuals::ghosts::pinky::left::kAnimation,
               visuals::ghosts::pinky::right::kAnimation,
               visuals::ghosts::pinky::up::kAnimation,
               visuals::ghosts::pinky::down::kAnimation);
    inky_ = std::make_shared<GhostSpecial<GhostType::kInky>>(
            Position{config::positions::entities::blinky::kDefaultX,
                        config::positions::entities::blinky::kDefaultY},
               Position{config::positions::entities::inky::kTargetX,
                        config::positions::entities::inky::kTargetY},
               Position{config::positions::entities::inky::kHouseX,
                        config::positions::entities::inky::kHouseY},
               visuals::ghosts::inky::left::kAnimation,
               visuals::ghosts::inky::right::kAnimation,
               visuals::ghosts::inky::up::kAnimation,
               visuals::ghosts::inky::down::kAnimation);
    clyde_ = std::make_shared<GhostSpecial<GhostType::kClyde>>(
            Position{config::positions::entities::blinky::kDefaultX,
                        config::positions::entities::blinky::kDefaultY},
               Position{config::positions::entities::clyde::kTargetX,
                        config::positions::entities::clyde::kTargetY},
               Position{config::positions::entities::clyde::kHouseX,
                        config::positions::entities::clyde::kHouseY},
               visuals::ghosts::clyde::left::kAnimation,
               visuals::ghosts::clyde::right::kAnimation,
               visuals::ghosts::clyde::up::kAnimation,
               visuals::ghosts::clyde::down::kAnimation);
    ghosts_entities = {blinky_, pinky_, inky_, clyde_};
}

std::array<std::shared_ptr<Ghost>, 4> Ghosts::getGhosts()
{
    return ghosts_entities;
}

void Ghosts::tick(const Map& map, Position pacman, Direction pacman_direction)
{

    if(status_counter_.isActive())
    {
        status_counter_.increment();
    }
    else if(status_changes_ < status_timers.size())
    {
        for(auto &ghost : ghosts_entities)
            ghost->statusChange();
        if((++status_changes_) < status_timers.size())
            status_counter_.start(status_timers.at(status_changes_) * config::settings::kFramesPerSecond);
    }

    // Update chase targets.
    blinky_->chase(pacman);
    pinky_->chase(pacman, pacman_direction);
    inky_->chase(pacman, pacman_direction, blinky_->getPosition().scaleDown(config::dimensions::kWindowCellSize));
    clyde_->chase(pacman);

    // Tick ghosts.
    for(auto &ghost : ghosts_entities)
        ghost->tick(map);
}

void Ghosts::frightened()
{
    for(auto &ghost : ghosts_entities)
        ghost->frightened(status_timers.at(0));
}

void Ghosts::reset()
{
    status_changes_ = 0;
    status_counter_.stop();
    for(auto &ghost : ghosts_entities)
        ghost->reset();
}
