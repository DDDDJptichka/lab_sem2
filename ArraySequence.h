#pragma once

#include "DynamicArray.h"
#include "Sequence.h"

template <class T> class ArraySequence : public Sequence<T>{

    protected:

        DynamicArray<T> *array;

        void append_internal(T item){

            size_t size = array->get_size() + 1;
            
            array->resize(size);
            array->set(size - 1, item);

        }

        void prepend_internal(T item){

            size_t size = array->get_size() + 1;

            array->resize(size);

            for (int i = size - 1; i > 0; --i){

                array->set(i, array->get(i - 1));

            }

            array->set(0, item);

        }

        void insert_at_internal(T item, int index){

            size_t size = array->get_size();

            if ((index < 0) || (index > size)){

                throw std::out_of_range("Index Out Of Range");

            }

            if (index == 0){

                prepend_internal(item);

                return;

            }

            if (index == size){

                append_internal(item);

                return;

            }

            array->resize(size + 1);

            for (int i = size; i > index; --i){

                array->set(i, array->get(i - 1));

            }

            array->set(index, item);

        }

    public:

        ArraySequence(T *items, size_t count){

            array = new DynamicArray<T>(items, count);

        }

        ArraySequence(){

            array = new DynamicArray<T>(0);

        }

        ArraySequence(size_t size){

            array = new DynamicArray<T>(size);

        }

        ArraySequence(const DynamicArray<T> &arr){

            size_t arr_size = arr.get_size();
            array = new DynamicArray<T>(arr_size);
            
            for (size_t i = 0; i < arr_size; ++i){

                array->set(i, arr.get(i));

            }

        }

        ArraySequence(const ArraySequence<T> &another){

            array = new DynamicArray<T>(*another.array);

        }

        ~ArraySequence() override{

            delete array;

        }

        T get_first() const override{

            if (array->get_size() == 0){

                throw std::out_of_range("Array is empty!");

            }

            return array->get(0);

        }

        T get_last() const override{

            if (array->get_size() == 0){

                throw std::out_of_range("Array is empty");

            }

            return array->get(array->get_size() - 1);

        }

        T get(int index) const override{

            if ((index < 0) || (index >= array->get_size())){

                throw std::out_of_range("index Out Of Range");

            }

            return array->get(index);

        }

        int get_length() const override{

            return array->get_size();

        }

        Sequence<T> *append(T item) override{

            append_internal(item);

            return this;

        }

        Sequence<T> *prepend(T item) override{

            prepend_internal(item);

            return this;

        }

        Sequence<T> *insert_at(T item, int index) override{

            insert_at_internal(item, index);

            return this;

        }

        Sequence<T> *get_sub_sequence(int start_index, int end_index) override{

            size_t size = array->get_size();

            if ((start_index < 0) || (end_index < 0) || (start_index >= size) || (end_index >= size)){

                throw std::out_of_range("Inde Out Of Range");

            }

            T *items = new T[abs(start_index - end_index) + 1];

            if (start_index <= end_index){

                for (size_t i = start_index; i <= end_index; ++i){

                    items[i - start_index] = array->get(i);

                }

            }
            else{

                for (int i = start_index; i >= end_index; --i){

                    items[abs(start_index - i)] = array->get(i);

                }

            }

            Sequence<T> *sub_sequence = new ArraySequence<T>(items, abs(end_index - start_index) + 1);
            delete[] items;

            return sub_sequence;

        }

        Sequence<T> *concat(Sequence<T> *sequence) override{

            if (sequence == nullptr){

                Sequence<T> *res_sequence = new ArraySequence<T>(*array);

                return res_sequence;

            }

            size_t seq_size = sequence->get_length();
            size_t this_size = this->get_length();

            DynamicArray<T> res_arr(*this->array);
            res_arr.resize(this_size + seq_size);

            for (size_t i = 0; i < seq_size; ++i){

                res_arr.set(this_size + i, sequence->get(i));

            }

            Sequence<T> *res_sequence = new ArraySequence<T>(res_arr);

            return res_sequence;

        }

        T operator[](size_t index){

            return array->get(index);

        }

};