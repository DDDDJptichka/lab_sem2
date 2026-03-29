#include <cstdio>
#include <iostream>

template <class T> class DynamicArray{

    private: 

        int size;
        T *data;

    public:

        DynamicArray(T *items, int count){

            if (count < 0){

                throw std::out_of_range("Attempting to copy NEGATIVE count of elements");

            }
            
            size = count;
            data = new T[size];

            for (size_t i = 0; i < count; ++i){

                data[i] = items[i];

            }

        }

        DynamicArray(int size){

            if (size < 0){

                throw std::out_of_range("Attempting to create DynamicArray with NEGATIVE size");

            }

            this->size = size;
            this->data = new T[size];

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

        T Get(int index){

            if ((index < 0) || (index >= size)){

                throw std::out_of_range("Index Out Of Range");

            }

            return data[index];

        }

        int GetSize(){

            return size;

        }

        void Set(int index, T value){

            if ((index < 0) || (index >= size)){

                throw std::out_of_range("Index Out Of Range");

            }

            data[index] = value;

        }

        void Resize(int new_size){

            if (new_size < 0){

                throw std::out_of_range("Index Out Of Range");

            }

            T *new_data = new T[new_size];

            for (size_t i = 0; i < min(size, new_size); ++i){

                new_data[i] = data[i];

            }

            delete[] data;
            data = new_data;
            size = new_size;

        }

};