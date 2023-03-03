#include <iostream>
#include "Profiling.h"

void Profiling::beginProfiling() {
    m_chronoProfiling = std::chrono::high_resolution_clock::now();
}

void Profiling::endProfiling() {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - m_chronoProfiling;
    std::cout << "Function execution time: " << elapsed.count() << " seconds\n";
}
