#pragma once

#include <cstddef>

template <class T> class Sequence{

    public:

        virtual T get_first() const = 0;
        virtual T get_last() const = 0;
        virtual T get(int index) const = 0;
        virtual size_t get_length() const = 0;
        virtual Sequence<T> *append(T item) = 0;
        virtual Sequence<T> *prepend(T item) = 0;
        virtual Sequence<T> *insert_at(T item, int index) = 0;
        virtual Sequence<T> *get_sub_sequence(int start_index, int end_index) const = 0;
        virtual Sequence<T> *concat(Sequence<T> *sequence) const = 0;
        
        T operator[](const int index) const{

            return get(index);

        }

        virtual ~Sequence(){}

};

template <class T> const bool operator==(const Sequence<T> &seq1, const Sequence<T> &seq2){

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