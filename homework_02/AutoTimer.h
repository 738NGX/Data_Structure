#pragma once
#include <ctime>

class AutoTimer
{
    public:
    AutoTimer();
    ~AutoTimer();

    double GetElapsedTimeInSeconds() const;
    long GetElapsedTimeInMilliSeconds() const;

    void Reset();

    private:
    clock_t m_startTime;
};
