#pragma once

template <class T> class Sequence{

    public:

        virtual T get_first() const = 0;
        virtual T get_last() const = 0;
        virtual T get(int index) const = 0;
        virtual size_t get_length() const = 0;
        virtual Sequence<T> *append(T item) = 0;
        virtual Sequence<T> *prepend(T item) = 0;
        virtual Sequence<T> *insert_at(T item, int index) = 0;
        virtual Sequence<T> *get_sub_sequence(int start_index, int end_index) = 0;
        virtual Sequence<T> *concat(Sequence<T> *sequence) = 0;
        
        virtual ~Sequence(){}

};