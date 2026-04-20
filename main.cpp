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

#include <gtest/gtest.h>

int main(int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}

//g++ tests.cpp googletest/googletest/src/gtest-all.cc googletest/googletest/src/gtest_main.cc -I googletest/googletest/include -I googletest/googletest -o test.exe -pthread