#pragma

#include <chrono>

namespace Core{
    class Timer
    {
    public:
        static void Start();
        static double Elapsed();
        static void Elapsed(double& elapsed);

    private:
        static std::chrono::steady_clock::time_point start;
    };
};