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

        Sequence<T> *insert_at(int index, T item) override{

            ImmutableArraySequence<T> *copy = clone();
            copy->insert_at_internal(index, item);

            return copy;

        }

};