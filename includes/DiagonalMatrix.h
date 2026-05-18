#pragma once

#include <complex>
#include <cmath>

#include <algorithm>
#include <concepts>
#include <type_traits>

#include "Exception.h"

template <template <typename> class Container, typename T> concept MatrixContainer = requires(Container<T> c, const Container<T> another, T value, int i){

    {c = another} -> std::same_as<Container<T>&>;
    {c.get(i)} -> std::convertible_to<T>;
    c.append(value);
    c[i];

};

template <template <typename> class Container, typename T> requires MatrixContainer<Container, T> class DiagonalMatrix{

    template <template <typename> class B, typename C> requires MatrixContainer<B, C> friend class DiagonalMatrix;

    private:

        Container<T> buffer;
        size_t diag_count = 0;
        size_t matrix_size = 0;
        bool diagonal_flag = 1;

        Container<T> make_minor(const Container<T> &container, size_t row, size_t column, size_t size) const{

            Container<T> minor;

            for (size_t i = 0; i < size; ++i){

                for (size_t j = 0; j < size; ++j){

                    if ((i != row) && (j != column)){

                        minor.append(container[i * size + j]);

                    }

                }

            }

            return minor;

        }

        T get_det(const Container<T> &container, size_t size) const{

            if (size == 1){

                return container[0];

            }

            T res = 0;

            for (size_t i = 0; i < size; ++i){

                Container<T> minor(make_minor(container, 0, i, size));
                
                if (i % 2 == 0){

                    res += container[i] * get_det(minor, size - 1);

                }
                else{

                    res += (-1) * container[i] * get_det(minor, size - 1);

                }

            }

            return res;

        }

        void convert(){

            if (diagonal_flag == 0){

                return;

            }

            Container<T> new_buff;

            for (size_t i = 0; i < matrix_size; ++i){

                for (size_t j = 0; j < matrix_size; ++j){

                    new_buff.append(get(i, j));

                }

            }

            buffer = new_buff;
            diagonal_flag = 0;
            diag_count = 2 * matrix_size - 1;

        }

        size_t get_buff_size() const{

            if (diagonal_flag == 1){
                
                return matrix_size + ((matrix_size - 1) + (matrix_size - ((diag_count - 1) / 2))) * ((diag_count - 1) / 2);
            
            }
            else{

                return matrix_size * matrix_size;

            }

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

    public:

        class MatrixCIterator{

            private:

                const DiagonalMatrix &matrix;
                size_t row_index;
                size_t column_index;

            public:

                using iterator_category = std::forward_iterator_tag;
                using value_type = T;
                using difference_type = std::ptrdiff_t;
                using pointer = const T*;
                using reference = T;
            
                MatrixCIterator(const DiagonalMatrix &mat, size_t row_ind, size_t column_ind) : matrix(mat), row_index(row_ind), column_index(column_ind){}

                T operator*() const{

                    return matrix.get(row_index, column_index);

                }

                MatrixCIterator& operator++(){

                    if (column_index + 1 < matrix.get_matrix_size()){

                        ++column_index;

                    }
                    else{

                        column_index = 0;
                        ++row_index;

                    }

                    return *this;

                }

                MatrixCIterator operator++(int){

                    MatrixCIterator res = *this;
                    ++(*this);
                    
                    return res;

                }

                bool operator==(const MatrixCIterator &another) const{

                    return ((row_index == another.row_index) && (column_index == another.column_index));

                }

                bool operator!=(const MatrixCIterator &another) const{

                    return !(*this == another);

                }

        };

        MatrixCIterator begin() const{return MatrixCIterator(*this, 0, 0);}
        MatrixCIterator end() const{return MatrixCIterator(*this, get_matrix_size(), 0);}

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
            buffer(another.buffer),
            diagonal_flag(another.diagonal_flag){}
        
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
            
            if (diagonal_flag == 0){

                return buffer[matrix_size * row_index + column_index];

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

            if (diagonal_flag == 0){

                buffer[matrix_size * row_index + column_index] = item;

                return;

            }

            if (abs(row_index - column_index) > ((diag_count - 1) / 2)){

                convert();
                buffer[matrix_size * row_index + column_index] = item;

                return;

            }

            buffer[index(row_index, column_index)] = item;

        }

        template <class A> auto multiply_by_scalar(A scalar) const{
            
            using res_type = decltype(T{} * scalar);
            Container<res_type> new_buffer;

            for (auto item : buffer){

                new_buffer.append(item * scalar);

            }

            if (diagonal_flag == 1){
            
                DiagonalMatrix<Container, res_type> res(new_buffer, get_buff_size(), diag_count);
            
                return res;

            }
            else{

                DiagonalMatrix<Container, res_type> res;
                res.buffer = new_buffer;
                res.diag_count = 2 * matrix_size - 1;
                res.diagonal_flag = 0;
                res.matrix_size = matrix_size;

                return res;
                
            }

        }

        template <class A> auto summary_with_scalar(A scalar) const{
            
            using res_type = decltype(T{} + scalar);
            Container<res_type> new_buffer;

            for (size_t i = 0; i < matrix_size; ++i){

                for (size_t j = 0; j < matrix_size; ++j){

                    new_buffer.append(get(i, j) + scalar);

                }

            }

            DiagonalMatrix<Container, res_type> res;
            res.buffer = new_buffer;
            res.diag_count = 2 * matrix_size - 1;
            res.diagonal_flag = 0;
            res.matrix_size = matrix_size;

            return res;

        }

        void summary_with_matrix(DiagonalMatrix<Container, T> &another){//todo: не забыть тоже сделать иммутбл

            if (this->matrix_size != another.matrix_size){

                throw different_matrix_size("Different matrix size");

            }

            if ((diagonal_flag && another.diagonal_flag) == 1){

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

                    buffer = new_buff;

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
                    buffer = new_buff;

                }

            }
            else{

                convert();

                for (size_t i = 0; i < matrix_size; ++i){

                    for (size_t j = 0; j < matrix_size; ++j){

                        buffer[i * matrix_size + j] = buffer[i * matrix_size + j] + another.get(i, j);

                    }

                }

            }

        }

        double frobenius_norm() const{

            double res = 0;
            
            for (auto itemm : buffer){

                double re = std::real(itemm);
                double im = std::imag(itemm);

                res += re * re + im * im;

            }

            return std::sqrt(res);

        }

        auto get_inverse_matrix() const{

            DiagonalMatrix<Container, T> res_matrix(*this);
            DiagonalMatrix<Container, T> tmp(*this);
            res_matrix.convert();
            tmp.convert();

            T det = get_det(res_matrix.buffer, matrix_size);

            if (det == T{}){

                throw zero_determinant("Matrix can`t be inversed, because det == 0");

            }

            if (matrix_size == 1){

                res_matrix.set(0, 0, T{1});
                
                return res_matrix.multiply_by_scalar(1.0 / det);

            }

            for (size_t i = 0; i < matrix_size; ++i){

                for (size_t j = 0; j < matrix_size; ++j){

                    if ((i + j) % 2 == 0){

                        res_matrix.set(j, i, get_det(make_minor(tmp.buffer, i, j, matrix_size), matrix_size - 1));

                    }
                    else{

                        res_matrix.set(j, i, (-1) * get_det(make_minor(tmp.buffer, i, j, matrix_size), matrix_size - 1));                        

                    }

                }

            }

            return res_matrix.multiply_by_scalar(1.0 / det);

        }

        auto &operator=(const DiagonalMatrix<Container, T> &another){

            if (this == &another){

                return *this;

            }

            buffer = another.buffer;
            matrix_size = another.matrix_size;
            diag_count = another.diag_count;
            diagonal_flag = another.diagonal_flag;

            return *this;

        }

};