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

        Sequence<T> *append(T item) override{

            ImmutableListSequence<T> *copy = clone();
            copy->append_internal(item);
            
            return copy;

        }

        Sequence<T> *prepend(T item) override{

            ImmutableListSequence<T> *copy = clone();
            copy->prepend_internal(item);

            return copy;

        }

        Sequence<T> *insert_at(T item, int index) override{

            ImmutableListSequence<T> *copy = clone();
            copy->insert_at_internal(item, index);

            return copy;

        }

};