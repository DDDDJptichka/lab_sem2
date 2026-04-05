#pragma once

#include "LinkedList.h"
#include "Sequence.h"

template <class T> class ListSequence : public Sequence<T>{

    private:

        Linked_list<T> *list;

    public:

        ListSequence(T *items, size_t count){

            list = new Linked_list<T>(items, count);

        }
        
        ListSequence(){

            list = new Linked_list<T>();

        }

        ListSequence(const Linked_list<T> &another_list){

            size_t size = another_list.get_length();
            list = new Linked_list<T>();
            
            for (size_t i = 0; i < size; ++i){

                list->append(another_list.get(i));

            }

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

        T get(int index) const override{

            return list->get(index);

        }

        int get_length() const override{

            return list->get_length();

        }

        Sequence<T> *append(T item) override{

            this->list->append(item);

            return this;

        }

        Sequence<T> *prepend(T item) override{

            this->list->prepend(item);

            return this;

        }

        Sequence<T> *insert_at(T item, int index) override{

            this->list->insert_at(item, index);

            return this;

        }

        Sequence<T> *get_sub_sequence(int start_index, int end_idnex) override{

            Linked_list<T> *res_list = list->get_sub_list(start_index, end_idnex);
            Sequence<T> *res_sequence = new ListSequence<T>(*res_list);

            delete res_list;

            return res_sequence;

        }

        Sequence<T> *concat(Sequence<T> *another_list) override{

            if (another_list == nullptr){

                Sequence<T> *res_sequence = new ListSequence<T>(*list);

                return res_sequence;

            }

            Linked_list<T> *l_list = new Linked_list<T>();
            size_t size = another_list->get_length();

            for (size_t i = 0; i < size ; ++i){

                l_list->append(another_list->get(i));

            }

            Linked_list<T> *concatenated_list = list->concat(l_list);
            Sequence<T> *res_sequence = new ListSequence<T>(*concatenated_list);
            
            delete l_list;
            delete concatenated_list;

            return res_sequence;

        }

};