#pragma once

#include "Sequence.h"
#include "ArraySequence.h"

template <class T> class ImmutableArraySequence : public ArraySequence<T>{

    public:

        using ArraySequence<T>::ArraySequence;

        ImmutableArraySequence<T> *clone() const{

            ImmutableArraySequence<T> *copy = new ImmutableArraySequence<T>(*(this->array));

            return copy;

        }

        ImmutableArraySequence<T> *append(T item) override{

            ImmutableArraySequence<T> *copy = clone();
            copy->append_internal(item);
            
            return copy;

        }

        ImmutableArraySequence<T> *prepend(T item) override{

            ImmutableArraySequence<T> *copy = clone();
            copy->prepend_internal(item);

            return copy;

        }

        ImmutableArraySequence<T> *insert_at(T item, int index) override{

            ImmutableArraySequence<T> *copy = clone();
            copy->insert_at_internal(item, index);

            return copy;

        }

        T operator[](const size_t index) const{

            return this->get(index);

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