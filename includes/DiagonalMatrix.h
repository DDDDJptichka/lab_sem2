#pragma once

#include <concepts>

#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "Exception.h"

template <template <typename> class Container, typename T> concept MatrixContainer = requires(Container<T> c, T value, int i){

    {c.get(i)} -> std::convertible_to<T>;
    c.append(value);
    c[i];
    requires(requires {c.get_length();} || requires {c.get_size();});

};

template <template <typename> class Container, typename T> requires MatrixContainer<Container, T> class DiagonalMatrix{

    private:

        Container<T> buffer;
        size_t diag_count = 0;
        size_t matrix_size = 0;

    public:

        DiagonalMatrix(){}

        DiagonalMatrix(const Container<T> &container, size_t count, size_t d_count) :

            diag_count(d_count),
            matrix_size((((d_count - 1) / 2)*((d_count - 1) / 2) + ((d_count - 1) / 2) + count) / d_count),
            buffer(container){}
        
        DiagonalMatrix(const DiagonalMatrix<Container, T> &another) :

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