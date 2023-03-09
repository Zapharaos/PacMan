//
// Created by matthieu on 28/02/2023.
//

#include "../../include/entity/pacman.h"

Pacman::Pacman() = default;

Pacman::Pacman(long time, const std::function<void(void)> &function, Sprite sprite, int speed, const pair<int, int> &coordinates,
               const vector<Sprite> &left, const vector<Sprite> &right, const vector<Sprite> &up, const vector<Sprite> &down,
               const vector<Sprite> &death) :
               timer_(time, function), MovingEntity(sprite, speed, coordinates, left, right, up, down), death_(death) {}

void Pacman::setSuperpower(bool superpower) {
    if(superpower) {
        timer_.kill(); // stop previous superpower if still running
        timer_.start();
    }
    superpower_ = superpower;
}

bool Pacman::isSuperpower() {
    timer_.setMutexLock(true);
    bool result = superpower_;
    timer_.setMutexLock(false);
    return result;
}

bool Pacman::isDead() const
{
    return dead_;
}

void Pacman::setDead(bool dead)
{
    Pacman::dead_ = dead;
    MovingEntity::setPreviousImagePosition({true, 0});
}

const pair<int, int> &Pacman::getCoordinates() const {
    return MovingEntity::getCoordinates();
}

bool Pacman::isLeftOrUp() const {
    return MovingEntity::isLeftOrUp();
}

Sprite Pacman::getSprite() const {
    return Entity::getSprite();
}

SDL_Rect Pacman::getSpritePosition() const {
    return MovingEntity::getSpritePosition();
}

const SDL_Rect &Pacman::getSpriteImage() const {
    return MovingEntity::getSpriteImage();
}

const pair<bool, int> &Pacman::getPreviousImagePosition() const
{
    return MovingEntity::getPreviousImagePosition();
}

void Pacman::setPreviousImagePosition(const pair<bool, int> &previousImagePosition)
{
    MovingEntity::setPreviousImagePosition(previousImagePosition);
}

bool Pacman::hasCollided(SDL_Rect e) const {
    auto p = this->getSpritePosition();

    bool left = (e.x <= p.x && p.x < e.x + e.w);
    bool right = (p.x <= e.x && e.x < p.x + p.w);
    bool up = (e.y <= p.y && p.y < e.y + e.h);
    bool down = (p.y <= e.y && e.y < p.y + p.h);

    bool horizontal = left || right;
    bool vertical = up || down;

    return horizontal && vertical;
}

Direction Pacman::move(const Map& map, Direction continuous_direction, Direction try_direction) {
    return MovingEntity::move(map, continuous_direction, try_direction);
}

void Pacman::move(const Map& map, Direction continuous_direction) {
    MovingEntity::move(map, continuous_direction);
}

void Pacman::reset(pair<int, int> coordinates) {
    MovingEntity::reset(coordinates);
    timer_.kill();
}

void Pacman::animateDeath() {

    std::pair<bool, int> position = getPreviousImagePosition();

    if(position.second == death_.size()) { // end of animation
        setDead(false);
        return;
    }

    Sprite sprite = death_.at(position.second);
    sprite.setCoordinates(getCoordinates());
    setSprite(sprite);

    position.second++;
    setPreviousImagePosition(position);
}
