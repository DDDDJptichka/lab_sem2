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

        ArraySequence<uint32_t> *array;
        size_t bit_count;

        void append_bit(const bool bit){

            size_t block, offset;
            uint32_t curr;

            block = bit_count / UINT_SIZE;
            offset = bit_count % UINT_SIZE;

            if (bit_count % UINT_SIZE == 0){

                array->append(0);

            }

            curr = array->get(block);

            if (bit == 1){

                curr |= (1U << offset);

            }
            else{

                curr &= ~(1U << offset);

            }

            array->set(block, curr);
            ++bit_count;

        }

        void append_bytes(unsigned char byte){

            for (int i = 7; i >= 0; --i){

                append_bit((byte >> i) & 1);

            }

        }

        template <class T> void append_internal(const T &value){

            const unsigned char *bytes = reinterpret_cast<const unsigned char*>(&value);

            for (size_t i = 0; i < sizeof(T); ++i){

                append_bytes(bytes[i]);

            }

        }

    public:

        NormalBitSequence(){

            array = new ArraySequence<uint32_t>(0);
            bit_count = 0;

        }

        NormalBitSequence(size_t size){

            array = new ArraySequence<uint32_t>((size / UINT_SIZE) + ((size % UINT_SIZE) > 0));
            bit_count = UINT_SIZE * ((size / UINT_SIZE) + ((size % UINT_SIZE) > 0));

        }

        //NormalBitSequence(const NormalBitSequence &another){}

        /*template <class T> NormalBitSequence(const DynamicArray<T> &arr){

            for (size_t i = 0; i < arr.get_size(); ++i){

                

            }

        }*/

        //template <class T> NormalBitSequence(const ArraySequence<T> &arr){}

        //template <class T> NormalBitSequence(const LinkedList<T> &arr){}

        //template <class T> NormalBitSequence(const ListSequence<T> &arr){}
 
        ~NormalBitSequence(){

            delete array;

        }

        int get(size_t index) const{

            if (index >= bit_count){

                throw index_out_of_range("Index Out Of Range");

            }

            size_t block, offset;   
            
            block = index / UINT_SIZE;
            offset = index % UINT_SIZE;

            uint32_t curr = array->get(block);

            return (curr >> offset) & 1U;

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

        template <class T> NormalBitSequence *append(const T &value){

            append_internal(value);

            return this;

        }

        template <class T> NormalBitSequence *prepend(const T &value){

            NormalBitSequence *res = new NormalBitSequence();

            res->append(value);

            for (size_t i = 0; i < bit_count; ++i){

                res->append_bit(get(i));

            }

            return res;

        }

        NormalBitSequence *insert_at(const bool bit, int index){

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

            NormalBitSequence *res = new NormalBitSequence();

            for (size_t i = 0; i < index; ++i){

                res->append_bit(get(i));

            }

            res->append_bit(bit);

            for (size_t i = index; i < bit_count; ++i){

                res->append_bit(get(i));

            }

            return res;

        }

};