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

    size_t c_size = get_size(container);

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

            seg_end.append(c_size - 1);

        }
        else{

            seg_end.append((i + 1) * seg_size);

        }

    }

    auto swap = [&](size_t seg1_index, size_t seg2_index){

        for (size_t i = 0; i < swaps; ++i){

            std::uniform_int_distribution<size_t> dist_seg1(seg_start[seg1_index], seg_end[seg1_index]);
            std::uniform_int_distribution<size_t> dist_seg2(seg_start[seg2_index], seg_end[seg2_index]);

            size_t index1 = dist_seg1(generator);
            size_t index2 = dist_seg2(generator);

            std::swap(container[index1], container[index2]);

        }

    };

    for (size_t d = k / 2; d >= 1; --d){

        for (size_t i = 0; i + d < k; ++i){

            swap(i, i + d);

        }

    }

}