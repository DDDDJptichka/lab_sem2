#include <cstdio>
#include <iostream>

#include "Exception.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"
#include "SequenceInterface.h"

#include <gtest/gtest.h>

int main(int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);

    int check = RUN_ALL_TESTS();
    std::cout << "\n\n";
    
    Sequence<double> *seq = choose_seq();
    do_operations(seq);

    delete seq;

}

//g++ main.cpp SequenceInterface.cpp tests.cpp googletest/googletest/src/gtest-all.cc -I googletest/googletest/include -I googletest/googletest -o a.exe -pthread