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
class Counter
{

private:

    /** Indicates if the counter is running. */
    bool active_ = false;

    /** Current value. */
    unsigned long count_ = 0;

    /** Value to reach. */
    unsigned long cap_ = 0;

    bool save_ = false;

    unsigned long count_difference_ = 0;

    /** Save current value. */
    unsigned long count_save_ = 0;

    /** Save value to reach/ */
    unsigned long cap_save_ = 0;

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
     * @brief Getter for the current count value.
     * @return The current count value.
     */
    [[nodiscard]] inline unsigned long getCount() const
    { return count_; };

    /**
     * @brief Starts the counter with a given value to reach.
     * @param cap The value to reach.
     */
    inline void start(unsigned long cap)
    {
        if (cap == 0) return;
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
        if (count_ == 0)
            active_ = true;
        if (save_)
            ++count_difference_;
        if ((++count_) < cap_)
            return;
        stop();
    };

    /**
     * Stops the current count.
     */
    inline void stop()
    {
        active_ = false;
        count_ = 0;
    }

    /**
     * @brief Restarts the counter.
     * @pre cap must have been set beforehand.
     */
    inline void restart()
    {
        active_ = true;
        count_ = 0;
    };

    /**
     * @brief Saves the current counter state.
     */
    inline void save()
    {
        count_save_ = count_;
        cap_save_ = cap_;
        count_difference_ = 0;
        save_ = true;
    }

    /**
     * @brief Loads the saved values as the current ones.
     * @param Optional : time difference added to the saved counter.
     */
    inline void loadSave(unsigned long difference = 0)
    {
        active_ = true;
        count_ = count_save_ + difference; // Time saved + time difference
        cap_ = cap_save_;
        save_ = false;
        if (count_ >= cap_)
            stop();
    }

    /**
     * @brief Loads the saved values as the current ones
     * (with active time difference, aka time elapsed since the save).
     */
    inline void loadSaveWithDifference()
    {
        loadSave(count_difference_);
    }

};


#endif //PACMAN_COUNTER_H
