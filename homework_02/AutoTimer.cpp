#include <iostream>
#include "AutoTimer.h"

AutoTimer::AutoTimer()
{
    m_startTime = clock();
}

AutoTimer::~AutoTimer()
{
    std::cout << "  Elapsed time: " << GetElapsedTimeInSeconds() << " seconds ";
    std::cout << std::endl;
}

double AutoTimer::GetElapsedTimeInSeconds() const
{
    clock_t endTime = clock();
    return (double)(endTime - m_startTime) / CLOCKS_PER_SEC;
}

long AutoTimer::GetElapsedTimeInMilliSeconds() const
{
    clock_t endTime = clock();
    return endTime - m_startTime;
}

void AutoTimer::Reset()
{
    m_startTime = clock();
}
