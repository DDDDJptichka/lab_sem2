#pragma once

#include <cstdio>
#include <iostream>
#include <algorithm>

#include "Exception.h"

template <class T> class DynamicArray{

    private: 

        size_t size;
        T *data;

    public:

        DynamicArray(T *items, size_t count){

            size = count;
            data = new T[size]();

            for (size_t i = 0; i < count; ++i){

                data[i] = items[i];

            }

        }

        DynamicArray(size_t size){

            this->size = size;
            this->data = new T[size]();

        }

        DynamicArray(const DynamicArray<T> &other){

            size = other.size;
            data = new T[size];

            for (size_t i = 0; i < size; ++i){

                data[i] = other.data[i];

            }

        }

        ~DynamicArray(){

            delete[] data;

        }

        T& get(int index){

            if ((index < 0) || (index >= size)){

                throw index_out_of_range("Index Out Of Range");

            }

            return data[index];

        }

        const T& get(int index) const{

            if ((index < 0) || (index >= size)){

                throw index_out_of_range("Index Out Of Range");

            }

            return data[index];

        }

        size_t get_size() const{

            return size;

        }

        void set(int index, T value){

            if ((index < 0) || (index >= size)){

                throw index_out_of_range("Index Out Of Range");

            }

            data[index] = value;

        }

        void resize(size_t new_size){

            if (new_size == size){

                return;

            }

            T *new_data = new T[new_size]();

            for (size_t i = 0; i < std::min(size, new_size); ++i){

                new_data[i] = data[i];

            }

            delete[] data;
            data = new_data;
            size = new_size;

        }

        void append(T value){

            resize(size + 1);
            
            data[size - 1] = value;

        }

        T& operator[](const int index){

            return get(index);

        }

        const T& operator[](int index) const{

            return get(index);

        }

        DynamicArray<T> &operator=(const DynamicArray<T> &other){

            if (this == &other){

                return *this;

            }

            size_t new_size = other.get_size();
            T *new_data = new T[new_size];

            for (size_t i = 0; i < new_size; ++i){

                new_data[i] = other.data[i];

            }

            delete[] data;

            data = new_data;
            size = new_size;

            return *this;

        }

        DynamicArray<T> operator+(const DynamicArray<T> &other) const{

            DynamicArray<T> res_arr(*this);
            size_t new_size = size + other.get_size();

            res_arr.resize(new_size);

            for (size_t i = size; i < new_size; ++i){

                res_arr.data[i] = other.data[i - size];

            }

            return res_arr;

        }

};