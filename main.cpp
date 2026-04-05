#include <cstdio>
#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"

int main(){

    DynamicArray<int> array(3);
    ArraySequence<int> arr(3);

    array.set(0, 1);
    arr.insert_at(0, -10);

    std::cout << array[0] << "  " << arr[0];

    return 0;

}