#include <cmath>
#include <algorithm>

#include <type_traits>
#include <random>
#include <chrono>

#include "Exception.h"

#include "DynamicArray.h"

struct Segment{

    size_t start;
    size_t end;

};

template <typename Container> size_t get_size(const Container &container){

    if constexpr (requires {container.get_size();}){

        return container.get_size();

    }
    else if constexpr (requires {container.get_length();}){

        return container.get_length();

    }

}

template <typename Container> concept IterableContainer = requires(Container &container){

    std::begin(container);
    std::end(container);

};

template <typename Iterator> concept SwapableIterator = requires(Iterator first, Iterator second){

    std::iter_swap(first, second);

};

template <typename Container> concept ShakerContainer = IterableContainer<Container> && SwapableIterator<decltype(std::begin(std::declval<Container&>()))>;

template <IterableContainer Container> auto make_iter_arr(Container &container){

    DynamicArray<decltype(std::begin(container))> iterators(0);

    for (auto it = std::begin(container); it != std::end(container); ++it){

        iterators.append(it);

    }

    return iterators;

}

auto make_segments(size_t c_size, size_t k){

    DynamicArray<Segment> segments;
    size_t seg_size = c_size / k;

    for (size_t i = 0; i < k; ++i){

        Segment seg;
        seg.start = i * seg_size;

        if (i == k - 1){

            seg.end = c_size - 1;

        }
        else{

            seg.end = (i + 1) * seg_size - 1;

        }

        segments.append(seg);

    }

    return segments;

}

template <SwapableIterator Iterator> void rand_swap_between_segs(DynamicArray<Iterator> &iterators, const Segment &first, const Segment &second, size_t swaps, std::mt19937 &gen){

    std::uniform_int_distribution<size_t> dist_firts(first.start, first.end);
    std::uniform_int_distribution<size_t> dist_second(second.start, second.end);

    for (size_t i = 0; i < swaps; ++i){

        size_t first_index = dist_firts(gen);
        size_t second_index = dist_second(gen);

        std::iter_swap(iterators[first_index], iterators[second_index]);

    }

}

template <ShakerContainer Container> void shaker(Container &container, size_t k){

    size_t c_size = get_size(container);

    if ((c_size < k) || (k < 1)){

        return;

    }

    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    size_t seg_size = c_size / k;
    size_t swaps = std::max(seg_size / 2, size_t(1));

    auto iterators = make_iter_arr(container);
    auto segments = make_segments(c_size, k);

    for (size_t distance = k / 2; distance >= 1; --distance){

        for (size_t i = 0; i + distance < k; ++i){

            const Segment &first = segments[i];
            const Segment &second = segments[i + distance];

            std::uniform_int_distribution<size_t> dist_firts(first.start, first.end);
            std::uniform_int_distribution<size_t> dist_second(second.start, second.end);

            for (size_t index = 0; index < swaps; ++index){

                size_t first_index = dist_firts(gen);
                size_t second_index = dist_second(gen);

                std::iter_swap(iterators[first_index], iterators[second_index]);

            }

        }

        if (distance == 1){

            break;

        }

    }

}