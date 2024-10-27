#include "Stopwatch.hpp"

#include <iostream>

void Stopwatch::start() {
    _start = _prevLap = std::chrono::steady_clock::now();
}

long long Stopwatch::lap(const char* label) {
    const time_point now = std::chrono::steady_clock::now();
    const long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _prevLap).count();
    _prevLap = now;

    std::cout << label << ": " << elapsed << "ms" << std::endl;
    return elapsed;
}

long long Stopwatch::stop(const char* label) {
    const time_point now = std::chrono::steady_clock::now();
    const long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start).count();

    std::cout << label << ": " << elapsed << "ms" << std::endl;
    return elapsed;
}