/**
 * @file timer.cpp
 * @brief Implementation of the Timer class which is an asynchronous timer that calls a function at expiration.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 05/03/2023
 */

#include "../../include/utils/timer.h"

#include <utility>

Timer::Timer() = default;

Timer::Timer(const Timer &timer)
{
    time_ = timer.time_;
    function_ = timer.function_;
    running_ = timer.running_;
    killed_ = timer.killed_;
}

Timer::Timer(long time) : time_(time)
{}

Timer::Timer(long time, std::function<void(void)> function) :
        time_(time), function_(std::move(function))
{}

Timer &Timer::operator=(const Timer &timer)
{
    time_ = timer.time_;
    function_ = timer.function_;
    running_ = timer.running_;
    killed_ = timer.killed_;
    return *this;
}

void Timer::setMutexLock(bool lock)
{
    if (lock)
        mutex_.lock();
    else
        mutex_.unlock();
}

void Timer::start()
{

    mutex_.lock();
    if (running_)
        killed_ = true;
    else
        running_ = true;
    mutex_.unlock();

    std::thread([&]() {
        std::this_thread::sleep_until(std::chrono::steady_clock::now() +
                                      std::chrono::milliseconds(time_));

        mutex_.lock();
        if (killed_)
        { // if the timer was killed during the wait
            killed_ = false;
            mutex_.unlock();
        } else
        {
            running_ = false;
            mutex_.unlock();
            function_();
        }
    }).detach();
}

void Timer::start(const std::function<void(void)> &function)
{
    function_ = function;
    start();
}

void Timer::kill()
{
    mutex_.lock();
    if (running_)
        killed_ = true;
    mutex_.unlock();
}
