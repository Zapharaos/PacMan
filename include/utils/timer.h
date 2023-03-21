//
// Created by mfrei on 05/03/2023.
//

#ifndef PACMAN_TIMER_H
#define PACMAN_TIMER_H

#include <iostream>
#include <chrono>
#include <functional>
#include <thread>
#include <mutex>

/** Asynchronous timer that calls a function at expiration. */
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

    /** Default Fruit constructor. */
    Timer();

    /** Copy constructor
     *
     * @param timer The timer to copy from.
     */
    Timer(const Timer &timer);

    /** Timer constructor.
     *
     * @param time Time to wait for the timer to expire.
     */
    explicit Timer(long time);

    /** Timer constructor.
     *
     * @param time Time to wait for the timer to expire.
     * @param function Function executed as the timer expires.
     */
    Timer(long time, std::function<void(void)> function);

    /** Copy assignment operator.
     *
     * @param timer The timer to copy from.
     * @return The copied timer.
     */
    Timer &operator=(const Timer &timer);

    /** Locks/unlocks the mutex. */
    void setMutexLock(bool lock);

    /** Starts a new timer. */
    void start();

    /** Starts a new timer.
     *
     * @param function Function executed as the timer expires.
     */
    void start(const std::function<void(void)> &function);

    /** Kills the current running timer. */
    void kill();
};


#endif //PACMAN_TIMER_H
