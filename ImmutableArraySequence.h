#pragma once

#include "Sequence.h"
#include "ArraySequence.h"

template <class T> class ImmutableArraySequence : public ArraySequence<T>{

    private:

        ImmutableArraySequence<T> *clone() const{

            ImmutableArraySequence<T> *copy = new ImmutableArraySequence<T>(*(this->array));

            return copy;

        }      

    public:

        using ArraySequence<T>::ArraySequence;

        Sequence<T> *append(T item) override{

            ImmutableArraySequence<T> *copy = clone();
            copy->append_internal(item);
            
            return copy;

        }

        Sequence<T> *prepend(T item) override{

            ImmutableArraySequence<T> *copy = clone();
            copy->prepend_internal(item);

            return copy;

        }

        Sequence<T> *insert_at(T item, int index) override{

            ImmutableArraySequence<T> *copy = clone();
            copy->insert_at_internal(item, index);

            return copy;

        }

        ImmutableArraySequence<T> &operator=(const ImmutableArraySequence<T> &other){

            if (this == &other){

                return *this;

            }

            *this->array = *other.array;

            return *this;

        }

        ImmutableArraySequence<T> operator+(const ImmutableArraySequence<T> &other) const{

            ImmutableArraySequence<T> new_im_seq(*this->array + *other.array);

            return new_im_seq;

        }

};