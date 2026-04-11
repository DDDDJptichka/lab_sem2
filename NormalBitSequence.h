#pragma once

#include <type_traits>
#include <iostream>
#include <string>

#include "Sequence.h"
#include "ArraySequence.h"
#include "LinkedList.h"
#include "ListSequence.h"

#define UINT_SIZE 32 

class NormalBitSequence{

    private:

        DynamicArray<uint32_t> *array;
        size_t bit_count;

    public:

        NormalBitSequence(){

            array = new DynamicArray<uint32_t>(0);
            bit_count = 0;

        }

        NormalBitSequence(size_t size){

            array = new DynamicArray<uint32_t>(size);
            bit_count = UINT_SIZE * size;

        }

        NormalBitSequence(const NormalBitSequence &another){}

        template <class T> NormalBitSequence(const DynamicArray<T> &arr){}

        template <class T> NormalBitSequence(const ArraySequence<T> &arr){}

        template <class T> NormalBitSequence(const LinkedList<T> &arr){}

        template <class T> NormalBitSequence(const ListSequence<T> &arr){}

        ~NormalBitSequence(){}

};