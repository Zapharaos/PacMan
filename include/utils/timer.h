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

class Timer
{

private:
    long time_ = 10000;
    std::mutex mutex_;
    std::thread thread_ {};
    std::function<void(void)> function_ {};
    bool running_ = false;
    bool killed_ = false;

public:
    Timer();
    Timer(const Timer& other);
    Timer(long time, std::function<void(void)> function);

    Timer& operator = (const Timer& other);

    void setTime(const long &time);
    [[nodiscard]] bool isRunning() const;
    void setKilled(bool killed);
    void setMutexLock(bool lock);

    void start();
    void kill();
};


#endif //PACMAN_TIMER_H
