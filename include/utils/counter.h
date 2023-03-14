//
// Created by matthieu on 13/03/2023.
//

#ifndef PACMAN_COUNTER_H
#define PACMAN_COUNTER_H

/** Count until a certain value is reached. */
class Counter {

private:

    /** Indicates if the counter is running. */
    bool active_ = false;

    /** Current value. */
    long count_ = 0;

    /** Value to reach. */
    long cap_ = 0;

public:

    /** Default Counter constructor. */
    Counter() = default;

    /** Getter : Indicates if the counter is running.
     * @return true if counter still running, else false.
     */
    [[nodiscard]] bool isActive() const { return active_; }

    /** Starts counting.
     * @param cap Value to reach.
     */
    void start(long cap) {
        active_ = true;
        count_ = 0;
        cap_ = cap;
    }

    /** Increments the counter.
     * @details Stops counting if conditions are met.
     */
    void increment() {
        if((++count_) < cap_) return;
        active_ = false;
        count_ = 0;
    }

    /** Increments and indicate if the current count is low.
     * @see increment()
     * @return true if less than half of the value was reached, else false.
     */
    bool incrementLowerHalf() {
        auto isLowerHalf = (count_ < cap_/2);
        increment();
        return isLowerHalf;
    }

};


#endif //PACMAN_COUNTER_H
