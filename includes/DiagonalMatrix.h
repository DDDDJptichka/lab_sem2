#pragma once

#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "Exception.h"

template <class T> class DiagonalMatrix{

    private:

        ArraySequence<T> buffer;
        size_t diag_count = 0;
        size_t matrix_size = 0;

    public:

        DiagonalMatrix(){}

        DiagonalMatrix(T *items, size_t count, size_t d_count) : 

            diag_count(d_count),
            matrix_size((((d_count - 1) / 2)*((d_count - 1) / 2) + ((d_count - 1) / 2) + count) / d_count),
            buffer(items, count){}

        DiagonalMatrix(const Sequence<T> &seq, size_t count, size_t d_count) :

            diag_count(d_count),
            matrix_size((((d_count - 1) / 2)*((d_count - 1) / 2) + ((d_count - 1) / 2) + count) / d_count),
            buffer(count){

            for (int i = 0; i < count; ++i){

                buffer[i] = seq.get(i);

            }
        }
        

        DiagonalMatrix(const LinkedList<T> &list, size_t count, size_t d_count) : 

            diag_count(d_count),
            matrix_size((((d_count - 1) / 2)*((d_count - 1) / 2) + ((d_count - 1) / 2) + count) / d_count),
            buffer(count){

            for (int i = 0; i < count; ++i){

                buffer[i] = list[i];

            }

        }

        DiagonalMatrix(const DynamicArray<T> &arr, size_t count, size_t d_count) :

            diag_count(d_count),
            matrix_size((((d_count - 1) / 2)*((d_count - 1) / 2) + ((d_count - 1) / 2) + count) / d_count),
            buffer(count){

            for (int i = 0; i < count; ++i){

                buffer[i] = arr[i];

            }

        }

        DiagonalMatrix(const DiagonalMatrix<T> &another) :

            diag_count(another.diag_count),
            matrix_size(another.matrix_size),
            buffer(another.buffer){}
        
        ~DiagonalMatrix(){}

    size_t get_diag_count() const{

        return diag_count;

    }

    size_t get_matrix_size() const{

        return matrix_size;

    }

    T get(int index) const{

        return buffer.get(index);

    }
    
};