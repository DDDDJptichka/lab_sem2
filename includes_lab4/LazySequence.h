#pragma once

#include "Exception.h"

#include "ArraySequence.h"
#include "Sequence.h"

#include "Option.h"
#include "Generator.h"

template <class T> class LazySequence : public Sequence<T>{

    private:

        mutable Generator<T> generator;
        mutable ArraySequence<T> cache;
        bool inf = false;
        size_t length = 0;

        void materialize_to(size_t index) const;

    public:

        LazySequence(){}

        LazySequence(T *items, int count) : cache(items, count), length(count){}

        LazySequence(Sequence<T> &seq){

            length = seq.get_length();

            for (size_t i = 0; i < length; ++i){

                cache.append(seq.get(i));

            }

        }

        LazySequence(Generator<T> generator) : generator(generator), inf(true), length(0){}

        LazySequence(Generator<T> generator, size_t count) : generator(generator), length(count){}

        ~LazySequence(){}

        size_t materialised_size(){

            return cache.get_length();

        }

        T get_first() const override{

            if ((inf == false) && (length == 0)){

                throw empty_container("Sequence is empty");

            }

            materialize_to(0);

            return cache[0];

        }

        T get_last() const override{

            if (inf == true){

                throw not_usable("There is no last element, because sequence is infinite");

            }

            if (length == 0){

                throw empty_container("Sequence is empty");

            }

            materialize_to(length - 1);

            return cache[length - 1];

        }

        T& get(int index) override{

            if (index < cache.get_length()){

                return cache[index];

            }

            materialize_to(index);

            return cache[index];
        }

        size_t get_length() const override{

            return length;

        }

        Sequence<T> *append(T item) override{

            if (inf == true){

                throw not_usable("Can`t append smth, because sequence is infinite");

            }

            if (length > 0){

                materialize_to(length - 1);

            }

            cache.append(item);
            ++length;

            return this;

        }

        Sequence<T> *prepend(T item) override{

            cache.prepend(item);

            if (inf == false){
                
                ++length;

            }

            return this;

        }

        Sequence<T> *insert_at(T item, int index) override{

            if (index < 0){

                throw index_out_of_range("Index Out Of Range");

            }

            if (inf == true){

                materialize_to(index);
                cache.insert_at(item, index);

                return this;

            }

            if (index > length){

                throw index_out_of_range("Index Out Of Range");

            }

            if (length > 0){

                materialize_to(length - 1);

            }

            cache.insert_at(item, index);
            ++length;

            return this;

        }

        Sequence<T> *get_sub_sequence(int start_index, int end_index) const override{

            if ((inf == false) && (length <= std::max(start_index, end_index))){

                throw index_out_of_range("Index Out Of Range");

            }

            materialize_to(std::max(start_index, end_index));

            return cache.get_sub_sequence(start_index, end_index);

        }

        Sequence<T> *concat(Sequence<T> *sequence) const override{

            if (inf == true){

                throw not_usable("Can`t use concat, because sequence is infinite");

            }

            if (length > 0){

                materialize_to(length - 1);

            }

            return cache.concat(sequence);

        }

        T& operator[](int index){

            return get(index);

        }

        const T& operator[](int index) const{

            return get(index);

        }

};

template <typename T> void LazySequence<T>::materialize_to(size_t index) const{

    if ((inf == 0) && (index >= length)){

        throw index_out_of_range("Index Out Of Range");

    }

    size_t cache_len = cache.get_length();

    for (size_t i = cache_len; i <= index; ++i){

        if (generator.has_next() == false){

            throw index_out_of_range("Generator hasn`t next element");

        }

        cache.append(generator.get_next());

    }

};