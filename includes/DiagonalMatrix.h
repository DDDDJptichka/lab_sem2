#pragma once

#include <algorithm>
#include <concepts>
#include <type_traits>

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

        size_t get_buff_size() const{

            return matrix_size + ((matrix_size - 1) + (matrix_size - ((diag_count - 1) / 2))) * ((diag_count - 1) / 2);

        }

        size_t index(int row_index, int column_index) const{

            int diff = column_index - row_index;
            size_t start_shift = (diag_count - 1) / 2;
            size_t buff_index = 0;
            
            if (diff >= 0){

                for (int shift = start_shift; shift > diff; --shift){

                    buff_index += matrix_size - shift;

                }

                buff_index += row_index;

            }
            else{

                for (int shift = start_shift; shift >= 0; --shift){

                    buff_index += matrix_size - shift;

                }

                for (size_t shift = 1; shift < abs(diff); ++shift){

                    buff_index += matrix_size - shift;

                }

                buff_index += column_index;

            }

            return buff_index;

        }

        void copy_to_container(Container<T> &another_buff, size_t copy_size, size_t another_size){

            for(size_t i = 0; i < copy_size; ++i){

                buffer[i] = another_buff[i];

            }

            for(size_t i = copy_size; i < another_size; ++i){

                buffer.append(another_buff[i]);

            }

        }

    public:

        DiagonalMatrix(){}

        DiagonalMatrix(const Container<T> &container, size_t count, size_t d_count) :

            diag_count(d_count),
            matrix_size((((d_count - 1) / 2)*((d_count - 1) / 2) + ((d_count - 1) / 2) + count) / d_count){

            for (size_t i = 0; i < count; ++i){

                buffer.append(container[i]);

            }

        }
        
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

        T get(int row_index, int column_index) const{

            if ((row_index < 0) || (column_index < 0) || (row_index >= matrix_size) || (column_index >= matrix_size)){

                throw index_out_of_range("Index Out Of Range");

            }

            if (abs(row_index - column_index) > ((diag_count - 1) / 2)){

                return 0;

            }

            return buffer[index(row_index, column_index)];

        }
    
        void set(int row_index, int column_index, T item){

            if ((row_index < 0) || (column_index < 0) || (row_index >= matrix_size) || (column_index >= matrix_size)){

                throw index_out_of_range("Index Out Of Range");

            }

            if (abs(row_index - column_index) > ((diag_count - 1) / 2)){

                throw index_out_of_range("Index Out Of Range");

            }

            buffer[index(row_index, column_index)] = item;

        }

        template <class A> requires requires(T t, A a){{t * a} -> std::convertible_to<T>;} void multiply_by_scalar(A scalar){
            
            size_t buff_size = get_buff_size();

            for (size_t i = 0; i < buff_size; ++i){

                buffer[i] = buffer[i] * scalar;

            }

        }

        template <class A> requires requires(T t, A a){{t + a} -> std::convertible_to<T>;} void summary_with_scalar(A scalar){
            
            size_t buff_size = get_buff_size();

            for (size_t i = 0; i < buff_size; ++i){

                buffer[i] = buffer[i] + scalar;

            }

        }

        void summary_with_matrix(DiagonalMatrix<Container, T> &another){

            if (this->matrix_size != another.matrix_size){

                throw different_matrix_size("Different matrix size");

            }

            size_t this_size = get_buff_size();
            size_t another_size = another.get_buff_size();
            size_t diff = abs((int)this_size - (int)another_size) / 2;
            Container<T> new_buff;

            if (this_size >= another_size){

                for (size_t i = 0; i < diff; ++i){

                    new_buff.append(buffer[i]);

                }

                for (size_t i = 0; i < another_size; ++i){

                    new_buff.append(buffer[i + diff] + another.buffer[i]);

                }

                for (size_t i = another_size + diff; i < this_size; ++i){

                    new_buff.append(buffer[i]);

                }

                copy_to_container(new_buff, another_size, this_size);

            }
            else{

                for (size_t i = 0; i < diff; ++i){

                    new_buff.append(another.buffer[i]);

                }

                for (size_t i = 0; i < this_size; ++i){

                    new_buff.append(another.buffer[i + diff] + buffer[i]);

                }

                for (size_t i = this_size + diff; i < another_size; ++i){

                    new_buff.append(another.buffer[i]);

                }

                diag_count = another.diag_count;
                copy_to_container(new_buff, this_size, another_size);

            }

        }

};