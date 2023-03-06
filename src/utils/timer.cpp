//
// Created by mfrei on 05/03/2023.
//

#include "../../include/utils/timer.h"

Timer::Timer() = default;

Timer::Timer(long time, const std::function<void(void)> &function) :
        time_(time), function_(function) {}

Timer& Timer::operator = (const Timer& other) {
    time_ = other.time_;
    function_ = other.function_;
    return *this;
}

void Timer::setTime(const long &time) {
    time_ = time;
}

bool Timer::isRunning() const {
    return running_;
}

void Timer::setKilled(bool killed) {
    killed_ = killed;
}

void Timer::setMutexLock(bool lock) {
    if(lock)
        mutex_.lock();
    else
        mutex_.unlock();
}

void Timer::start() {

    mutex_.lock();
    if(running_)
        killed_ = true;
    else
        running_ = true;
    mutex_.unlock();

    thread_ = std::thread([&]() {
        auto delta = std::chrono::steady_clock::now() + std::chrono::milliseconds(time_);
        std::this_thread::sleep_until(delta);

        mutex_.lock();
        if(killed_) {
            killed_ = false;
            mutex_.unlock();
        } else {
            running_ = false;
            mutex_.unlock();
            function_();
        }
    });
    thread_.detach();
}
