#include <cstdio>
#include <iostream>

#include "includes/Exception.h"

#include "includes/DynamicArray.h"
#include "includes/LinkedList.h"
#include "includes/ArraySequence.h"
#include "includes/ListSequence.h"
#include "includes/Sequence.h"
#include "includes/DiagonalMatrix.h"

#include "includes_lab4/Option.h"
#include "includes_lab4/Generator.h"
#include "includes_lab4/LazySequence.h"
#include "includes_lab4/OnlineStatistics.h"

int main(){

    Generator<int> gen([](size_t i){return static_cast<int>(i * i);});
    LazySequence<int> seq(gen);

    size_t count;

    std::cout << "Enter count: ";
    std::cin >> count;

    OnlineStatistics<int> stats = collect(seq, count);

    print(stats);

    std::cout << "\n\nMaterialised: " << seq.materialised_size();

    return 0;

}
// rmdir /s /q build
// cmake -S . -B build -G "MinGW Makefiles"
// cmake --build build