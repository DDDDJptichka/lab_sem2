#pragma once

#include "LinkedList.h"
#include "Sequence.h"

template <class T> class ListSequence : public Sequence<T>{

    protected:

        LinkedList<T> *list;

        void append_internal(T item){

            this->list->append(item);

        }

        void prepend_internal(T item){

            this->list->prepend(item);

        }

        void insert_at_internal(T item, int index){

            this->list->insert_at(item, index);

        }

    public:

        ListSequence(T *items, size_t count){

            list = new LinkedList<T>(items, count);

        }
        
        ListSequence(){

            list = new LinkedList<T>();

        }

        ListSequence(const LinkedList<T> &another_list){

            size_t size = another_list.get_length();
            list = new LinkedList<T>();
            
            for (size_t i = 0; i < size; ++i){

                list->append(another_list.get(i));

            }

        }

        ListSequence(const ListSequence<T> &another){

            list = new LinkedList<T>(*another.list);

        }

        ~ListSequence() override{

            delete list;

        }

        T get_first() const override{

            return list->get_first();

        }

        T get_last() const override{

            return list->get_last();

        }

        void set(int index, T item){

            list->set(index, item);

        }

        T get(int index) const override{

            return list->get(index);

        }

        size_t get_length() const override{

            return list->get_length();

        }

        Sequence<T> *append(T item) override{

            append_internal(item);

            return this;

        }

        Sequence<T> *prepend(T item) override{

            prepend_internal(item);

            return this;

        }

        Sequence<T> *insert_at(T item, int index) override{

            insert_at_internal(item, index);

            return this;

        }

        Sequence<T> *get_sub_sequence(int start_index, int end_idnex) const override{

            LinkedList<T> *res_list = list->get_sub_list(start_index, end_idnex);
            Sequence<T> *res_sequence = new ListSequence<T>(*res_list);

            delete res_list;

            return res_sequence;

        }

        Sequence<T> *concat(Sequence<T> *sequence) const override{

            if (sequence == nullptr){

                Sequence<T> *res_sequence = new ListSequence<T>(*list);

                return res_sequence;

            }

            LinkedList<T> *l_list = new LinkedList<T>();
            size_t size = sequence->get_length();

            for (size_t i = 0; i < size ; ++i){

                l_list->append(sequence->get(i));

            }

            LinkedList<T> *concatenated_list = list->concat(l_list);
            Sequence<T> *res_sequence = new ListSequence<T>(*concatenated_list);
            
            delete l_list;
            delete concatenated_list;

            return res_sequence;

        }

        T operator[](const size_t index) const{

            return get(index);

        }

        ListSequence<T> &operator=(const ListSequence<T> &other){

            if (this == &other){

                return *this;

            }

            *list = *other.list;

            return *this;

        }

        ListSequence<T> operator+(const ListSequence<T> &other) const{

            ListSequence<T> new_seq(*list + *other.list);

            return new_seq;

        }

};