#pragma once

#include "Sequence.h"
#include "ListSequence.h"

template <class T> class ImmutableListSequence : public ListSequence<T>{

    public:

        using ListSequence<T>::ListSequence;

        ImmutableListSequence<T> *clone() const{

            ImmutableListSequence<T> *copy = new ImmutableListSequence<T>(*(this->list));

            return copy;

        }

        ImmutableListSequence<T> *append(T item) override{

            ImmutableListSequence<T> *copy = clone();
            copy->append_internal(item);
            
            return copy;

        }

        ImmutableListSequence<T> *prepend(T item) override{

            ImmutableListSequence<T> *copy = clone();
            copy->prepend_internal(item);

            return copy;

        }

        ImmutableListSequence<T> *insert_at(T item, int index) override{

            ImmutableListSequence<T> *copy = clone();
            copy->insert_at_internal(item, index);

            return copy;

        }

        T operator[](const size_t index) const{

            return this->get(index);

        }

        ImmutableListSequence<T> &operator=(const ImmutableListSequence<T> &other){

            if (this == &other){

                return *this;

            }

            *this->list = *other.list;

            return *this;

        }

        ImmutableListSequence<T> operator+(const ImmutableListSequence<T> &other) const{

            ImmutableListSequence<T> new_im_seq(*this->list + *other.list);

            return new_im_seq;

        }

};