#pragma once

#include <cstdio>
#include <iostream>

template <class T> class Dynamic_array{

    private: 

        size_t size;
        T *data;

    public:

        Dynamic_array(T *items, size_t count){

            size = count;
            data = new T[size];

            for (size_t i = 0; i < count; ++i){

                data[i] = items[i];

            }

        }

        Dynamic_array(size_t size){

            this->size = size;
            this->data = new T[size];

        }

        Dynamic_array(const Dynamic_array<T> &other){

            size = other.size;
            data = new T[size];

            for (size_t i = 0; i < size; ++i){

                data[i] = other.data[i];

            }

        }

        ~Dynamic_array(){

            delete[] data;

        }

        T get(int index) const{

            if ((index < 0) || (index >= size)){

                throw std::out_of_range("Index Out Of Range");

            }

            return data[index];

        }

        size_t get_size() const{

            return size;

        }

        void set(int index, T value){

            if ((index < 0) || (index >= size)){

                throw std::out_of_range("Index Out Of Range");

            }

            data[index] = value;

        }

        void resize(size_t new_size){

            T *new_data = new T[new_size];

            for (size_t i = 0; i < std::min(size, new_size); ++i){

                new_data[i] = data[i];

            }

            delete[] data;
            data = new_data;
            size = new_size;

        }

};