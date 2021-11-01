#pragma once
#include <functional>
#include <chrono>
using namespace std;
using namespace std::chrono;

long long measure_nanoseconds(function<void()> f) {
    auto clock = high_resolution_clock();
    auto start = clock.now();
    f();
    auto stop =  clock.now();
    return duration_cast<nanoseconds>(stop - start).count();
}