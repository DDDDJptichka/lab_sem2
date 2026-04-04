#pragma once

#include "Dynamic_array.h"
#include "Linked_list.h"
#include "Sequence.h"

template <class T> class Array_sequence : public Sequence<T>{

    private:

        Dynamic_array<T> *array;

    public:

        Array_sequence(T *items, size_t count){

            array = new Dynamic_array<T>(items, count);

        }

        Array_sequence(){

            array = new Dynamic_array<T>(0);

        }

        Array_sequence(const Dynamic_array<T> &arr){

            size_t arr_size = arr.get_size();
            array = new Dynamic_array<T>(arr_size);
            
            for (size_t i = 0; i < arr_size; ++i){

                array->set(i, arr.get(i));

            }

        }

        ~Array_sequence() override{

            delete array;

        }

        T get_first() const override{

            if (array->get_size() == 0){

                throw std::out_of_range("Array is empty!");

            }

            return array->get(0);

        }

        T get_last() const override{

            if (array->get_size() == 0){

                throw std::out_of_range("Array is empty");

            }

            return array->get(array->get_size() - 1);

        }

        T get(int index) const override{

            if ((index < 0) || (index >= array->get_size())){

                throw std::out_of_range("index Out Of Range");

            }

            return array->get(index);

        }

        int get_length() const override{

            return array->get_size();

        }

        Sequence<T> *append(T item) override{

            size_t size = array->get_size() + 1;
            
            array->resize(size);
            array->set(size - 1, item);

            return this;

        }

        Sequence<T> *prepend(T item) override{

            size_t size = array->get_size() + 1;

            array->resize(size);

            for (int i = size - 1; i > 0; --i){

                array->set(i, array->get(i - 1))

            }

            array->set(0, item);

            return this;

        }

        Sequence<T> *insert_at(T item, int index) override{

            size_t size = array->get_size();

            if ((index < 0) || (index > size)){

                throw std::out_of_range("Index Out Of Range");

            }

            if (index == 0){

                return this->prepend(item);

            }
            
            if (index == size){

                return this->append(item);

            }

            array->resize(size + 1);

            for (int i = size; i > index; --i){

                array->set(i, array->get(i - 1));

            }

            array->set(index, item);

            return this;

        }

        Sequence<T> *get_sub_sequence(int start_index, int end_index) override{

            size_t size = array->get_size();

            if ((start_index < 0) || (end_index < 0) || (start_index >= size) || (end_index >= size)){

                throw std::out_of_range("Inde Out Of Range");

            }

            T *items = new T[abs(start_index - end_index) + 1];

            if (start_index <= end_index){

                for (size_t i = start_index; i <= end_index; ++i){

                    items[i - start_index] = array->get(i);

                }

            }
            else{

                for (int i = end_index; i >= start_index; --i){

                    items[abs(i - end_index)] = array->get(i);

                }

            }

            Sequence<T> *sub_sequence = new Array_sequence<T>(items, abs(end_index - start_index) + 1);
            delete[] items;

            return sub_sequence;

        }

        Sequence<T> *concat(Sequence<T> *list) override{

            if (list == nullptr){

                Sequence<T> *res_sequence = new Array_sequence<T>(*array);

                return res_sequence;

            }

            size_t list_size = list->get_length();
            size_t this_size = this->get_length();

            Dynamic_array<T> res_arr(*this->array);
            res_arr.resize(this_size + list_size);

            for (size_t i = 0; i < list_size; ++i){

                res_arr.set(this_size + i, list->get(i));

            }

            Sequence<T> *res_sequence = new Array_sequence<T>(res_arr);

            return res_sequence;

        }

};