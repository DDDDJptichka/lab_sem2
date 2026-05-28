#pragma once

#include <algorithm>
#include <iostream>
#include <cstddef>

#include "Exception.h"
#include "LazySequence.h"

template <class T> struct OnlineStatistics{

    size_t count = 0;
    T min{};
    T max{};
    T sum{};
    double mean{};

};

template <typename T> OnlineStatistics<T> collect(LazySequence<T> &seq, size_t count){

    OnlineStatistics<T> stats;

    if (count == 0){

        return stats;

    }

    stats.min = seq[0];
    stats.max = seq[0];

    for (size_t i = 0; i < count; ++i){

        T val = seq[i];

        stats.min = std::min(stats.min, val);
        stats.max = std::max(stats.max, val);
        stats.sum += val;
        ++stats.count;
        stats.mean = static_cast<double>(stats.sum) / stats.count; 

    }

    return stats;

}

template <typename T> void print(OnlineStatistics<T> &stats){

    std::cout << "\ncount: " << stats.count;
    std::cout << "\nmin: " << stats.min;
    std::cout << "\nmax: " << stats.max;
    std::cout << "\nsum: " << stats.sum;
    std::cout << "\nmean: " << stats.mean;

}