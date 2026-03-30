#include <cstdio>
#include <iostream>

template <class T> struct Node{

    T data;
    Node *next;
    Node *prev;

};

template <class T> class Linked_list{

    private:

        Node<T> *head;
        Node<T> *tail;
        size_t size;

    public:

        Linked_list(T *items, size_t count){

            head = nullptr;
            tail = nullptr;
            size = 0;

            for (size_t i = 0; i < 0; ++i){

                append(items[i]);

            }

        }

        Linked_list(){

            head = nullptr;
            tail = nullptr;
            size = 0;

        }

        Linked_list(const linked_list<T> &other){

            head = nullptr;
            tail = nullptr;
            size = 0;

            Node<T> *curr = other.head;

            while (curr != nullptr){

                append(curr->data);
                curr = curr->next;

            }

        }

        ~Linked_list(){

            Node<T> *curr_node = head;

            while (curr_node != nullptr){

                Node<T> *next_node = curr_node->next;
                delete curr_node;
                curr_node = next_node;

            }

        }

        T get_first(){

            if (head == nullptr){

                throw std::out_of_range("It is not possible to get FIRST element, because LIST is empty!");

            }

            return head->data;

        }

        T get_last(){

            if (tail == nullptr){

                throw std::out_of_range("It is not possible to get LAST element, because LIST is empty!");

            }

            return tail->data;

        }

        T get(int index){

            if ((index < 0) || (index >= size)){

                throw std::out_of_range("Index Out Of Range");

            }
            

            size_t curr_ind = 0;
            Node<T> *curr_node = head;

            while (curr_ind != index){

                curr_node = curr_node->next;
                ++curr_ind;

            }

            return curr_node->data;

        }

        Linked_list<T> *get_sub_list(int start_index, int end_index){

            if ((start_index < 0) || (start_index >= size) || (end_index < 0) || (end_index >= size)){

                throw std::out_of_range("Index Out Of Range");

            }

            Linked_list<T> *list = new Linked_list<T>();

            if (start_index > end_index){

                Node<T> *curr_node = tail;
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

                Node<T> *curr_node = head;
                size_t curr_ind = 0;

                while (curr_ind <= end_index){

                    if (curr_ind >= start_index){
                        
                        list->append(curr_node->data);

                    }

                    curr_node = curr_node->next;
                    ++curr_ind;

                }

            }

            return list;

        }

        size_t get_lenght(){

            return size;

        }

        void append(T value){

            Node<T> *new_node = new Node<T>;
            new_node->data = value;
            new_node->next = nullptr;
            new_node->prev = nullptr;

            if (head == nullptr){

                head = new_node;
                tail = new_node;

            }
            else{

                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;

            }

            ++size;

        }

        void prepend(T value){

            Node<T> *new_node = new Node<T>;
            new_node->data = value;
            new_node->next = nullptr;
            new_node->prev = nullptr;

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

            Node<T> *new_node = new Node<T>;
            Node<T> *curr_node = head;
            size_t curr_ind = 0;

            while (curr_ind != index){

                curr_node = curr_node->next;
                ++curr_ind;

            }


            curr_node->prev->next = new_node;
            new_node->prev = curr_node->prev;
            new_node->next = curr_node;
            curr_node->prev = new_node;

            new_node->data = item;
            ++size;
        
        }

        Linked_list<T> *concat(Linked_list<T> *list){

            Linked_list<T> *res_list = new Linked_list<T>;
            Node<T> *curr_node = this->head;
            
            while (curr_node != nullptr){

                res_list->append(curr_node->data);
                curr_node = curr_node->next;

            }

            if (list == nullptr){

                return res_list;

            }

            curr_node = list->head;

            while (curr_node != nullptr){

                res_list->append(curr_node->data);
                curr_node = curr_node->next;

            }

            return res_list;

        }

};