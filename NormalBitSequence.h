#pragma once

#include <type_traits>
#include <iostream>
#include <string>
#include <algorithm>

#include "Sequence.h"
#include "ArraySequence.h"
#include "LinkedList.h"
#include "ListSequence.h"

template <class T> class NormalBitSequence{

    static_assert(std::is_integral_v<T> && std::is_unsigned_v<T>, "Wrong buffer type");

    private:

        ArraySequence<T> array;
        size_t bit_count = 0;
        size_t block_size = sizeof(T) * 8;
        

        void append_bit(const bool bit){

            size_t block, offset;
            T curr;

            block = bit_count / block_size;
            offset = bit_count % block_size;

            if (bit_count % block_size == 0){

                array.append(0);

            }

            curr = array.get(block);

            if (bit){

                curr |= (static_cast<T>(1) << offset);

            }
            else{

                curr &= ~(static_cast<T>(1) << offset);

            }

            array.set(block, curr);
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

        void prepend_bit(const bool bit){

            NormalBitSequence<T> res;
            res.append_bit(bit);

            for (size_t i = 0; i < bit_count; ++i){

                res.append_bit(get(i));

            }

            *this = res;

        }

    public:

        NormalBitSequence() = default;

        NormalBitSequence(const NormalBitSequence<T> &another) = default;

        template <class A> NormalBitSequence(A *items, int size){

            bit_count = 0;

            for (size_t i = 0; i < size; ++i){

                append_internal(items[i]);

            }

        }

        template <class A> NormalBitSequence(const Sequence<A> &seq){

            bit_count = 0;

            size_t seq_length = seq.get_length();

            for (size_t i = 0; i < seq_length; ++i){

                append_internal(seq.get(i));

            }

        }

        template <class A> NormalBitSequence(const DynamicArray<A> &arr){

            bit_count = 0;

            size_t arr_size = arr.get_size();

            for (size_t i = 0; i < arr_size; ++ i){

                append_internal(arr.get(i));

            }

        }

        template <class A> NormalBitSequence(const LinkedList<A> &list){

            bit_count = 0;

            size_t list_size = list.get_length();

            for (size_t i = 0; i < list_size; ++i){

                append_internal(list.get(i));

            }

        }
 
        ~NormalBitSequence(){}

        void set(bool bit, int index){

            if ((index < 0) || (index  > bit_count)){

                throw index_out_of_range("Index Out Of Range");

            }
            else if (index == bit_count){

                this->append_bit(bit);
                return;

            }
            
            size_t block_index = index / block_size;
            size_t offset = index % block_size;
            T block = array.get(block_index);

            if (bit == 1){

                block |= (T(1) << offset);

            }
            else{

                block &= ~(T(1) << offset);

            }

            array.set(block_index, block);

        }

        int get(size_t index) const{

            if (index >= bit_count){

                throw index_out_of_range("Index Out Of Range");

            }

            size_t block, offset;   
            
            block = index / block_size;
            offset = index % block_size;

            T curr = array.get(block);

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

       template <class A> NormalBitSequence<T> *insert_at(const A &value, int block_index){

            if ((block_index < 0) || (block_index * block_size > bit_count)){

                throw index_out_of_range("Index Out Of Range");

            }
            else if (block_index == 0){

                this->prepend(value);

                return this;

            }
            else if (block_index * block_size == bit_count){

                this->append(value);

                return this;

            }

            NormalBitSequence<T> res;

            for (size_t i = 0; i < block_index * block_size; ++i){

                res.append_bit(get(i));

            }

            res.append(value);

            for (size_t i = (block_index * block_size); i < bit_count; ++i){

                res.append_bit(get(i));

            }

            *this = res;

            return this;

        }

        NormalBitSequence<T> *get_sub_sequence(int start_index, int end_index) const{

            if ((start_index < 0) || (end_index < 0) || (start_index + 1 > bit_count) || (end_index + 1> bit_count)){

                throw index_out_of_range("Index Out Of Range");

            }
            
            NormalBitSequence<T> *res = new NormalBitSequence<T>();

            if (start_index >= end_index){

                for (int i = start_index; i >= end_index; --i){

                    res->append_bit(this->get(i));

                }

            }
            else{

                for (size_t i = start_index; i <= end_index; ++i){

                    res->append_bit(this->get(i));

                }    

            }

            return res;
        }

        NormalBitSequence<T> *concat(const NormalBitSequence<T> *another) const{

            if (another == nullptr){

                throw nullptr_argument("Argument is nullptr");

            }

            size_t another_length = another->get_length();
            NormalBitSequence<T> *res = new NormalBitSequence<T>(*this);

            for (size_t i = 0; i < another_length; ++i){

                res->append_bit(another->get(i));

            }

            return res;

        }

        NormalBitSequence<T> *AND(const NormalBitSequence<T> *another){

            if (another == nullptr){

                throw nullptr_argument("Argument is nullptr");

            }

            size_t another_length = another->get_length();

            for (size_t i = 0; i < bit_count; ++i){

                if (i >= another_length){

                    this->set(0, i);                    

                }
                else{

                    this->set(this->get(i) && another->get(i), i);

                }

            }

            return this;

        }

        NormalBitSequence<T> *OR(const NormalBitSequence<T> *another){

            if (another == nullptr){

                throw nullptr_argument("Argument is nullptr");

            }

            size_t another_length = another->get_length();
            size_t finish = std::min(bit_count, another_length);

            for (size_t i = 0; i < finish; ++i){

                this->set(this->get(i) || another->get(i), i);

            }

            return this;

        }

        NormalBitSequence<T> *NOT(){

            for (size_t i = 0; i < bit_count; ++i){

                this->set(!(this->get(i)), i);

            }

            return this;

        }

        NormalBitSequence<T> *XOR(const NormalBitSequence<T> *another){

            if (another == nullptr){

                throw nullptr_argument("Argument is nullptr");

            }

            size_t another_length = another->get_length();
            size_t finish = std::min(bit_count, another_length);

            for (size_t i = 0; i < finish; ++i){

                this->set(this->get(i) ^ another->get(i), i);

            }

            return this;

        }

        NormalBitSequence<T> &operator=(const NormalBitSequence<T> &another){

            if (this == &another){

                return *this;

            }

            array = another.array;
            bit_count = another.bit_count;

            return *this;

        }
  
};

template <class T> const bool operator==(const NormalBitSequence<T> &seq1, const NormalBitSequence<T> &seq2){

    if (seq1.get_length() != seq2.get_length()){

        return false;

    }

    size_t length = seq1.get_length();

    for (size_t i = 0; i < length; ++i){

        if (seq1.get(i) != seq2.get(i)){

            return false;

        }

    }

    return true;

}