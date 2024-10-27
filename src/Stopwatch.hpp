#pragma once

#include <chrono>

class Stopwatch {
    using time_point = std::chrono::steady_clock::time_point;
    time_point _start;
    time_point _prevLap;

    public:
        void start();
        long long lap(const char* label);
        long long stop(const char* label);
};