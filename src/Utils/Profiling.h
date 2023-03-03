#pragma once

#include <chrono>

class Profiling {
public:
    Profiling() = default;

    ~Profiling() = default;

    void beginProfiling();

    void endProfiling();

private:
    std::chrono::high_resolution_clock::time_point m_chronoProfiling;
};
