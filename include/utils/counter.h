/**
 * @file counter.h
 * @brief Contains the Counter class which counts until a certain value is reached.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 13/03/2023
*/

#ifndef PACMAN_COUNTER_H
#define PACMAN_COUNTER_H

/**
 * @class Counter
 * @brief A class that counts until a certain value is reached.
 */
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
    inline Counter() = default;

    /**
    * @brief Getter for the active state of the counter.
    * @return True if the counter is still running, false otherwise.
    */
    [[nodiscard]] inline bool isActive() const
    { return active_; };

    /**
     * @brief Starts the counter with a given value to reach.
     * @param cap The value to reach.
     */
    inline void start(long cap)
    {
        active_ = true;
        count_ = 0;
        cap_ = cap;
    };

    /**
     * @brief Increments the counter.
     * @details Stops counting if the value to reach has been reached.
     */
    inline void increment()
    {
        if(count_ == 0)
            active_ = true;
        if((++count_) < cap_)
            return;
        stop();
    };

    /**
     * @brief Getter for the current count value.
     * @return The current count value.
     */
    [[nodiscard]] inline long getCount() const
    { return count_;};

    /**
     * Stops the current count.
     */
    inline void stop()
    {
        active_ = false;
        count_ = 0;
    }

};


#endif //PACMAN_COUNTER_H
