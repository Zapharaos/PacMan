//
// Created by mfrei on 13/04/2023.
//

#include "../../include/entity/ghosts.h"

Ghosts::Ghosts()
{
    blinky_ = std::make_shared<Ghost<GhostType::kBlinky>>(
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
    pinky_ = std::make_shared<Ghost<GhostType::kPinky>>(
            Position{config::positions::entities::pinky::kDefaultX,
                        config::positions::entities::pinky::kDefaultY},
               Position{config::positions::entities::pinky::kTargetX,
                        config::positions::entities::pinky::kTargetY},
               Position{config::positions::entities::pinky::kHouseX,
                        config::positions::entities::pinky::kHouseY},
               visuals::ghosts::pinky::left::kAnimation,
               visuals::ghosts::pinky::right::kAnimation,
               visuals::ghosts::pinky::up::kAnimation,
               visuals::ghosts::pinky::down::kAnimation);
    inky_ = std::make_shared<Ghost<GhostType::kInky>>(
            Position{config::positions::entities::inky::kDefaultX,
                        config::positions::entities::inky::kDefaultY},
               Position{config::positions::entities::inky::kTargetX,
                        config::positions::entities::inky::kTargetY},
               Position{config::positions::entities::inky::kHouseX,
                        config::positions::entities::inky::kHouseY},
               visuals::ghosts::inky::left::kAnimation,
               visuals::ghosts::inky::right::kAnimation,
               visuals::ghosts::inky::up::kAnimation,
               visuals::ghosts::inky::down::kAnimation);
    clyde_ = std::make_shared<Ghost<GhostType::kClyde>>(
            Position{config::positions::entities::clyde::kDefaultX,
                        config::positions::entities::clyde::kDefaultY},
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

std::array<std::shared_ptr<Entity>, 4> Ghosts::getGhostsAsEntities()
{
    return ghosts_entities;
}

void Ghosts::tick(const Map& map, Position pacman, Direction pacman_direction)
{
    // Update chase targets.
    blinky_->chase(pacman);
    pinky_->chase(pacman, pacman_direction);
    inky_->chase(pacman, pacman_direction, blinky_->getPosition().scaleDown(config::dimensions::kWindowCellSize));
    clyde_->chase(pacman);

    // Handle ghosts.
    blinky_->tick(map);
    pinky_->tick(map);
    inky_->tick(map);
    clyde_->tick(map);
}

void Ghosts::show()
{
    for(auto &ghost : ghosts_entities)
        ghost->show();
}

void Ghosts::hide()
{
    for(auto &ghost : ghosts_entities)
        ghost->hide();
}

void Ghosts::unfrightened()
{
    blinky_->unfrightened();
    pinky_->unfrightened();
    inky_->unfrightened();
    clyde_->unfrightened();
}

void Ghosts::frightened()
{
    blinky_->frightened();
    pinky_->frightened();
    inky_->frightened();
    clyde_->frightened();
}

void Ghosts::reset()
{
    blinky_->reset();
    pinky_->reset();
    inky_->reset();
    clyde_->reset();
}
