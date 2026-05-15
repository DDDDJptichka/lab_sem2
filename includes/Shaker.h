#include <cmath>
#include <algorithm>

#include <type_traits>
#include <random>
#include <chrono>

#include "Exception.h"

#include "DynamicArray.h"

template <typename Container> size_t get_size(const Container &container){

    if constexpr (requires {container.get_size();}){

        return container.get_size();

    }
    else if constexpr (requires {container.get_length();}){

        return container.get_length();

    }

}

template <typename Container> void shaker(Container &container, size_t k){

    size_t c_size = container.get_size();

    if ((c_size < k) || (k < 1)){

        return;

    }

    static std::mt19937 generator(std::chrono::steady_clock::now().time_since_epoch().count());
    size_t seg_size = c_size / k;
    size_t swaps = std::max(seg_size / 2, size_t(1));

    DynamicArray<size_t> seg_start(0);
    DynamicArray<size_t> seg_end(0);

    for (size_t i = 0; i < k; ++i){

        seg_start.append(i * seg_size);
        
        if (i == (k - 1)){

            seg_end.append(c_size - seg_start[i] + 1);

        }
        else{

            seg_end.append((i + 1) * seg_size);

        }

    }

}