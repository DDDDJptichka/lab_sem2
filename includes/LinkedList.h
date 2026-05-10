#pragma once

#include <memory>

#include "Exception.h"

template <class T> class LinkedList{

    private:

        struct Node{

            T data;
            std::shared_ptr<Node> next;
            std::weak_ptr<Node> prev;

            Node(const T &value) : data(value){}

        };

        std::shared_ptr<Node> head;
        std::weak_ptr<Node> tail;
        size_t size;

    public:

        class Iterator{

            private:

                Node *node;

            public:

                Iterator(Node *curr) : node(curr){}

                T& operator*() const{

                    return node->data;

                }
                
                T* operator->() const{

                    return &(node->data);

                }

                Iterator& operator++(){

                    node = node->next.get();

                    return *this;

                }

                Iterator operator++(int){

                    Iterator res = *this;
                    ++(*this);

                    return res;

                }

                bool operator==(const Iterator &another) const{

                    return node == another.node;

                }

                bool operator!=(const Iterator &another) const{

                    return !(*this == another);

                }

        };

        class CIterator{

            private:

                const Node *node;

            public:

                CIterator(const Node *curr) : node(curr){}
                CIterator(const Iterator &iter) : node(iter.operator->()){}

                const T& operator*() const{

                    return node->data;

                }
                
                const T* operator->() const{

                    return &(node->data);

                }

                CIterator& operator++(){

                    node = node->next.get();

                    return *this;

                }

                CIterator operator++(int){

                    CIterator res = *this;
                    ++(*this);

                    return res;

                }

                bool operator==(const CIterator &another) const{

                    return node == another.node;

                }

                bool operator!=(const CIterator &another) const{

                    return !(*this == another);

                }

        };

        LinkedList(T *items, size_t count){

            head = nullptr;
            tail.reset();
            size = 0;

            for (size_t i = 0; i < count; ++i){

                append(items[i]);

            }

        }

        LinkedList(){

            head = nullptr;
            tail.reset();
            size = 0;

        }

        LinkedList(const LinkedList<T> &other){

            head = nullptr;
            tail.reset();
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

                throw empty_container("It is not possible to get FIRST element, because LIST is empty!");

            }

            return head->data;

        }

        T get_last() const{

            std::shared_ptr<Node> locked_tail = tail.lock();

            if (locked_tail == nullptr){

                throw empty_container("It is not possible to get LAST element, because LIST is empty!");

            }

            return locked_tail->data;

        }

        void set(int index, T item){

            if ((index < 0) || (index >= size)){

                throw index_out_of_range("Index Out Of Range");

            }
            
            Node *curr = head.get();

            for (size_t i = 0; i < index; ++i){

                curr = curr->next.get();

            }

            curr->data = item;

        }

        T& get(int index){

            if ((index < 0) || (index >= size)){

                throw index_out_of_range("Index Out Of Range");

            }
            

            size_t curr_ind = 0;
            Node *curr_node = head.get();

            while (curr_ind != index){

                curr_node = curr_node->next.get();
                ++curr_ind;

            }

            return curr_node->data;

        }

        const T& get(int index) const{

            if ((index < 0) || (index >= size)){

                throw index_out_of_range("Index Out Of Range");

            }
            

            size_t curr_ind = 0;
            Node *curr_node = head.get();

            while (curr_ind != index){

                curr_node = curr_node->next.get();
                ++curr_ind;

            }

            return curr_node->data;

        }

        LinkedList<T> *get_sub_list(int start_index, int end_index) const{

            if ((start_index < 0) || (start_index >= size) || (end_index < 0) || (end_index >= size)){

                throw index_out_of_range("Index Out Of Range");

            }

            LinkedList<T> *list = new LinkedList<T>();

            if (start_index > end_index){

                Node *curr_node = tail.lock().get();
                size_t curr_ind = size - 1;

                while (curr_ind >= end_index){

                    if (curr_ind <= start_index){
                        
                        list->append(curr_node->data);

                    }

                    curr_node = curr_node->prev.lock().get();

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

            std::shared_ptr<Node> new_node = std::make_shared<Node>(value);

            if (head == nullptr){

                head = new_node;
                tail = new_node;

            }
            else{

                std::shared_ptr<Node> locked_tail = tail.lock();

                locked_tail->next = new_node;
                new_node->prev = locked_tail;
                tail = new_node;

            }

            ++size;

        }

        void prepend(T value){

            std::shared_ptr<Node> new_node = std::make_shared<Node>(value);

            if (head == nullptr){

                head = new_node;
                tail = new_node;

            }
            else{

                head->prev = new_node;
                new_node->next = head;
                head = new_node;

            }

            ++size;

        }

        void insert_at(T item, int index){

            if ((index < 0) || (index > size)){

                throw index_out_of_range("Index Out Of Range");

            }

            if (index == 0){

                this->prepend(item);
                return;

            }
            
            if (index == size){

                this->append(item);
                return;

            }

            std::shared_ptr<Node> curr_node = head;
            size_t curr_ind = 0;

            while (curr_ind != index){

                curr_node = curr_node->next;
                ++curr_ind;

            }

            std::shared_ptr<Node> new_node = std::make_shared<Node>(item);
            std::shared_ptr<Node> locked_prev = curr_node->prev.lock();
            
            new_node->prev = locked_prev;
            new_node->next = curr_node;
            new_node->next->prev = new_node;
            locked_prev->next = new_node;
            
            ++size;
        
        }

        LinkedList<T> *concat(LinkedList<T> *list) const{

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

        T& operator[](const int index){

            return get(index);

        }

        const T& operator[](int index) const{

            return get(index);

        }

        LinkedList<T> &operator=(const LinkedList<T> &other){

            if (this == &other){

                return *this;

            }

            head = nullptr;
            tail.reset();
            size = 0;

            Node *curr_node = other.head.get();

            while (curr_node != nullptr){

                append(curr_node->data);
                curr_node = curr_node->next.get();

            }

            return *this;

        }

        LinkedList<T> operator+(const LinkedList<T> &other) const{

            LinkedList<T> res_list(*this);
            Node *curr_node = other.head.get();

            while (curr_node != nullptr){

                res_list.append(curr_node->data);
                curr_node = curr_node->next.get();

            }

            return res_list;

        }

};