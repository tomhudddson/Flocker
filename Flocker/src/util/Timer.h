#pragma once

#include <chrono>

namespace flock
{

typedef long long timerCount_t;

class Timer
{
public:
    // Default 
    Timer() {  }

    inline static timerCount_t GetMilliSeconds()
    {
        using namespace std::chrono;
        auto now = high_resolution_clock::now().time_since_epoch();
        return duration_cast<milliseconds>(now).count();
    }

    inline static timerCount_t GetNanoSeconds()
    {
        using namespace std::chrono;
        auto now = high_resolution_clock::now().time_since_epoch();
        return duration_cast<nanoseconds>(now).count();
    }

    inline static timerCount_t Duration(const timerCount_t t1, const timerCount_t t2)
    {
        return t2 - t1;
    }

private:

};

}