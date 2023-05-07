/**
 * @file timer.h
 * @brief Defines the Timer class which is an asynchronous timer that calls a function at expiration.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 05/03/2023
*/

#ifndef PACMAN_TIMER_H
#define PACMAN_TIMER_H

#include <iostream>
#include <chrono>
#include <functional>
#include <thread>
#include <mutex>

/**
 * @brief An asynchronous timer that calls a function at expiration.
*/
class Timer
{

private:

    /** Function executed as the timer expires. */
    std::function<void(void)> function_{};

    /** Time to wait for the timer to expire. */
    long time_{};

    /** Protects the variables used by the threads. */
    std::mutex mutex_;

    /** Indicates if the timer is running. */
    bool running_ = false;

    /** Indicates if the function should still be run when the timer expires. */
    bool killed_ = false;

public:

    /**
     * @brief Default constructor for the Timer class.
     */
    Timer();

    /**
     * @brief Copy constructor for the Timer class.
     * @param timer The timer to copy from.
     */
    Timer(const Timer &timer);

    /**
     * @brief Timer constructor.
     * @param time Time to wait for the timer to expire.
     */
    explicit Timer(long time);

    /**
     * @brief Timer constructor.
     * @param time Time to wait for the timer to expire.
     * @param function Function executed as the timer expires.
     */
    Timer(long time, std::function<void(void)> function);

    /**
     * @brief Copy assignment operator for the Timer class.
     * @param timer The timer to copy from.
     * @return The copied timer.
     */
    Timer &operator=(const Timer &timer);

    /**
     * @brief Locks or unlocks the mutex used by the Timer class.
     * @param lock If true, the mutex is locked. If false, the mutex is unlocked.
     */
    void setMutexLock(bool lock);

    /**
     * @brief Starts a new timer with the current function.
     */
    void start();


    /**
     * @brief Starts a new timer with a given function.
     * @param function The function to be executed when the timer expires.
     */
    void start(const std::function<void(void)> &function);

    /**
     * @brief Kills the current running timer.
     */
    void kill();
};


#endif //PACMAN_TIMER_H
