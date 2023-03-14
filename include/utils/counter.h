//
// Created by matthieu on 13/03/2023.
//

#ifndef PACMAN_COUNTER_H
#define PACMAN_COUNTER_H


class Counter {

private:

    bool active_ = false;
    long count_ = 0;
    long cap_ = 0;

public:

    Counter() = default;

    [[nodiscard]] bool isActive() const { return active_; }

    void start(long cap) {
        active_ = true;
        count_ = 0;
        cap_ = cap;
    }

    void increment() {
        if((++count_) < cap_) return;
        active_ = false;
        count_ = 0;
    }

    bool incrementLowerHalf() {
        auto isLowerHalf = (count_ < cap_/2);
        increment();
        return isLowerHalf;
    }

};


#endif //PACMAN_COUNTER_H
