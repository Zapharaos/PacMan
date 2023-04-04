/**
 * @file animation.cpp
 * @brief Implements the Animation class, an entity that can move across the map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 28/02/2023
*/

#include "../../include/display/animation.h"

Animation::Animation() = default;

Animation::Animation(std::vector<Sprite> animation, bool reverse, long ticks_cap) :
    animation_(std::move(animation)), reverse_(reverse), ticks_cap_(ticks_cap) {}

const Sprite &Animation::animate(bool restart)
{
    if(restart) reset();

    if(!counter_.isActive()) // if enough frames
    {
        // Restart counter.
        counter_.start(ticks_cap_);

        // Handle reverse.
        if((reverse_ && index_ == animation_.size() - 1) || (!to_right_ && index_ == 0))
            to_right_ = !to_right_;

        // Animation is over
        if((!reverse_ && index_ == animation_.size() - 1) || (!to_right_ && index_ == 0))
            over_ = true;

        // Update index.
        if(!reverse_ && index_ == animation_.size() - 1)
            index_ = 0;
        else if(to_right_)
            ++index_;
        else
            --index_;
    }
    counter_.increment(); // increment number of frames
    return animation_.at(index_);
}

const Sprite &Animation::getSprite()
{ return animation_.at(index_); }

bool Animation::isOver() const
{ return over_; }

void Animation::reset()
{
    index_ = 0;
    to_right_ = true;
    over_ = false;
    counter_.start(ticks_cap_);
}
