//
// Created by mfrei on 05/03/2023.
//

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

Timer::Timer(long time, const function<void(void)> &function) :
        time_(time), function_(function)
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

    thread([&]() {
        auto delta = chrono::steady_clock::now() + chrono::milliseconds(time_);
        this_thread::sleep_until(delta);

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

void Timer::start(const function<void(void)> &function)
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
