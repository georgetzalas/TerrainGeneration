#include <core/timer.h>

std::chrono::steady_clock::time_point Core::Timer::start;

void Core::Timer::Start()
{
    start = std::chrono::steady_clock::now();
}

double Core::Timer::Elapsed()
{
    return std::chrono::duration<double, std::milli>(
        std::chrono::steady_clock::now() - start
    ).count();
}

void Core::Timer::Elapsed(double& elapsed)
{
    elapsed = std::chrono::duration<double, std::milli>(
        std::chrono::steady_clock::now() - start
    ).count();
}