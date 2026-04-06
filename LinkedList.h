#pragma once

#include <cstdio>
#include <iostream>
#include <memory>

template <class T> class LinkedList{

    private:

        struct Node{

            T data;
            std::unique_ptr<Node> next = nullptr;
            Node *prev = nullptr;

            Node(const T &value) : data(value), next(nullptr), prev(nullptr){}

        };

        std::unique_ptr<Node> head;
        Node *tail;
        size_t size;

    public:

        LinkedList(T *items, size_t count){

            head = nullptr;
            tail = nullptr;
            size = 0;

            for (size_t i = 0; i < count; ++i){

                append(items[i]);

            }

        }

        LinkedList(){

            head = nullptr;
            tail = nullptr;
            size = 0;

        }

        LinkedList(const LinkedList<T> &other){

            head = nullptr;
            tail = nullptr;
            size = 0;

            Node *curr = other.head.get();

            while (curr != nullptr){

                append(curr->data);
                curr = curr->next.get();

            }

        }

        ~LinkedList(){}

        T get_first() const{

            if (head == nullptr){

                throw std::out_of_range("It is not possible to get FIRST element, because LIST is empty!");

            }

            return head->data;

        }

        T get_last() const{

            if (tail == nullptr){

                throw std::out_of_range("It is not possible to get LAST element, because LIST is empty!");

            }

            return tail->data;

        }

        T get(int index) const{

            if ((index < 0) || (index >= size)){

                throw std::out_of_range("Index Out Of Range");

            }
            

            size_t curr_ind = 0;
            Node *curr_node = head.get();

            while (curr_ind != index){

                curr_node = curr_node->next.get();
                ++curr_ind;

            }

            return curr_node->data;

        }

        LinkedList<T> *get_sub_list(int start_index, int end_index){

            if ((start_index < 0) || (start_index >= size) || (end_index < 0) || (end_index >= size)){

                throw std::out_of_range("Index Out Of Range");

            }

            LinkedList<T> *list = new LinkedList<T>();

            if (start_index > end_index){

                Node *curr_node = tail;
                size_t curr_ind = size - 1;

                while (curr_ind >= end_index){

                    if (curr_ind <= start_index){
                        
                        list->append(curr_node->data);

                    }

                    curr_node = curr_node->prev;

                    if (curr_ind == 0){

                        break;

                    }

                    --curr_ind;

                }

            }
            else{

                Node *curr_node = head.get();
                size_t curr_ind = 0;

                while (curr_ind <= end_index){

                    if (curr_ind >= start_index){
                        
                        list->append(curr_node->data);

                    }

                    curr_node = curr_node->next.get();
                    ++curr_ind;

                }

            }

            return list;

        }

        size_t get_length() const{

            return size;

        }

        void append(T value){

            std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
            Node *ptr_new_node = new_node.get();

            if (head == nullptr){

                head = std::move(new_node);
                tail = ptr_new_node;

            }
            else{

                tail->next = std::move(new_node);
                ptr_new_node->prev = tail;
                tail = ptr_new_node;

            }

            ++size;

        }

        void prepend(T value){

            std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
            Node *ptr_new_node = new_node.get();

            if (head == nullptr){

                head = std::move(new_node);
                tail = ptr_new_node;

            }
            else{

                head->prev = ptr_new_node;
                new_node->next = std::move(head);
                head = std::move(new_node);

            }

            ++size;

        }

        void insert_at(T item, int index){

            if ((index < 0) || (index > size)){

                throw std::out_of_range("Index Out Of Range");

            }

            if (index == 0){

                this->prepend(item);
                return;

            }
            
            if (index == size){

                this->append(item);
                return;

            }

            Node *curr_node = head.get();
            size_t curr_ind = 0;

            while (curr_ind != index){

                curr_node = curr_node->next.get();
                ++curr_ind;

            }

            std::unique_ptr<Node> new_node = std::make_unique<Node>(item);
            Node *ptr_new_node = new_node.get();
            
            ptr_new_node->prev = curr_node->prev;
            ptr_new_node->next = std::move(curr_node->prev->next);
            ptr_new_node->next->prev = ptr_new_node;
            curr_node->prev->next = std::move(new_node);

            ++size;
        
        }

        LinkedList<T> *concat(LinkedList<T> *list){

            LinkedList<T> *res_list = new LinkedList<T>;
            Node *curr_node = this->head.get();
            
            while (curr_node != nullptr){

                res_list->append(curr_node->data);
                curr_node = curr_node->next.get();

            }

            if (list == nullptr){

                return res_list;

            }

            curr_node = list->head.get();

            while (curr_node != nullptr){

                res_list->append(curr_node->data);
                curr_node = curr_node->next.get();

            }

            return res_list;

        }

        T operator[](const size_t index) const{

            return get(index);

        }

};