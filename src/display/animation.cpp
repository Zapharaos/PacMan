//
// Created by matthieu on 13/03/2023.
//

#include "../../include/display/animation.h"

Animation::Animation() = default;

Animation::Animation(const vector<Sprite> &animation, bool reverse, long ticksCap) : animation_(animation),
                                                                                     reverse_(reverse),
                                                                                     ticksCap_(ticksCap) {}

const Sprite &Animation::animate(bool restart) {

    if(restart) reset();

    if(!counter_.isActive()) // if enough frames
    {
        // Restart counter.
        counter_.start(ticksCap_);

        // Handle reverse.
        if((reverse_ && index_ == animation_.size() - 1) || (!toRight_ && index_ == 0))
            toRight_ = !toRight_;

        // Animation is over
        if((!reverse_ && index_ == animation_.size() - 1) || (!toRight_ && index_ == 0))
            over_ = true;

        // Update index.
        if(!reverse_ && index_ == animation_.size() - 1)
            index_ = 0;
        else if(toRight_)
            index_++;
        else
            index_--;
    }
    counter_.increment(); // increment number of frames
    return animation_.at(index_);
}

const Sprite & Animation::getSprite() const {
    return animation_.at(index_);
}

void Animation::reset() {
    index_ = 0;
    toRight_ = true;
    over_ = false;
    counter_.start(ticksCap_);
}

bool Animation::isOver() const {
    return over_;
}
