#pragma once

#include <type_traits>
#include <iostream>
#include <string>

#include "Sequence.h"
#include "ArraySequence.h"
#include "LinkedList.h"
#include "ListSequence.h"

template <class T> class NormalBitSequence{

    private:

        ArraySequence<T> *array;
        size_t bit_count;
        size_t block_size = sizeof(T) * 8;
    

        void append_bit(const bool bit){

            size_t block, offset;
            T curr;

            block = bit_count / block_size;
            offset = bit_count % block_size;

            if (bit_count % block_size == 0){

                array->append(0);

            }

            curr = array->get(block);

            if (bit == 1){

                curr |= (T(1) << offset);

            }
            else{

                curr &= ~(T(1) << offset);

            }

            array->set(block, curr);
            ++bit_count;

        }

        void append_bytes(unsigned char byte){

            for (int i = 7; i >= 0; --i){

                append_bit((byte >> i) & 1);

            }

        }

        template <class A> void append_internal(const A &value){

            const unsigned char *bytes = reinterpret_cast<const unsigned char*>(&value);

            for (size_t i = 0; i < sizeof(A); ++i){

                append_bytes(bytes[i]);

            }

        }

    public:

        NormalBitSequence(){

            array = new ArraySequence<T>(0);
            bit_count = 0;

        }

        NormalBitSequence(const NormalBitSequence &another){

            array = new ArraySequence<T>(*another.array);
            bit_count = another.bit_count;

        }

        template <class A> NormalBitSequence(const DynamicArray<A> &arr){

            array = new ArraySequence<T>(0);
            bit_count = 0;

            size_t arr_size = arr.get_size();

            for (size_t i = 0; i < arr_size; ++ i){

                append_internal(arr.get(i));

            }

        }

        template <class A> NormalBitSequence(const ArraySequence<A> &arr){

            array = new ArraySequence<T>(0);
            bit_count = 0;

            size_t arr_size = arr.get_length();

            for (size_t i = 0; i < arr_size; ++i){

                append_internal(arr.get(i));

            }

        }

        template <class A> NormalBitSequence(const LinkedList<A> &list){

            array = new ArraySequence<T>(0);
            bit_count = 0;

            size_t list_size = list.get_length();

            for (size_t i = 0; i < list_size; ++i){

                append_internal(list.get(i));

            }

        }

        template <class A> NormalBitSequence(const ListSequence<A> &list){

            array = new ArraySequence<T>(0);
            bit_count = 0;

            size_t list_size = list.get_length();

            for (size_t i = 0; i < list_size; ++i){

                append_internal(list.get(i));

            }         

        }
 
        ~NormalBitSequence(){

            delete array;

        }

        int get(size_t index) const{

            if (index >= bit_count){

                throw index_out_of_range("Index Out Of Range");

            }

            size_t block, offset;   
            
            block = index / block_size;
            offset = index % block_size;

            T curr = array->get(block);

            return (curr >> offset) & T(1);

        }
        
        int get_first() const{

            if (bit_count == 0){

                throw empty_container("Sequence is empty");

            }

            return get(0);

        }

        int get_last() const{

            if (bit_count == 0){

                throw empty_container("Sequence is empty");

            }

            return get(bit_count - 1);

        }

        size_t get_length() const{

            return bit_count;

        }

        template <class A> NormalBitSequence<T> *append(const A &value){

            append_internal(value);

            return this;

        }

        template <class A> NormalBitSequence<T> *prepend(const A &value){

            NormalBitSequence<T> res;

            res.append(value);

            for (size_t i = 0; i < bit_count; ++i){

                res.append_bit(get(i));

            }

            *this = res;

            return this;

        }

        NormalBitSequence<T> *insert_at(const bool bit, int index){

            if ((index < 0) || (index > bit_count)){

                throw index_out_of_range("Index Out Of Range");

            }
            else if (index == 0){

                return this->prepend(bit);

            }
            else if (index == bit_count){

                this->append_bit(bit);

                return this;

            }

            NormalBitSequence<T> res;

            for (size_t i = 0; i < index; ++i){

                res.append_bit(get(i));

            }

            res.append_bit(bit);

            for (size_t i = index; i < bit_count; ++i){

                res.append_bit(get(i));

            }

            *this = res;

            return this;

        }

        //NormalBitSequence<T> *get_sub_sequence(int start_index, int end_index){


            
        //}

        NormalBitSequence<T> &operator=(const NormalBitSequence<T> &another){

            if (this == &another){

                return *this;

            }

            delete array;
            array = new ArraySequence<T>(*another.array);
            bit_count = another.bit_count;

            return *this;

        }

};