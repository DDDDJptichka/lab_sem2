#include <cstdio>
#include <iostream>

template <class T> class Node{

    public:

        T data;
        Node<T> *prev;
        Node<T> *next;

        Node(T value){

            data = value;
            prev = nullptr;
            next = nullptr;

        }
};

template <class T> class LinkedList{

    private:

        Node<T> *head;
        Node<T> *tail;
        int size;

    public:

        void AddToList(T value){

            Node<T> *new_node = new Node<T>;
            new_node->data = value;

            if (head == nullptr){

                head = new_node;
                tail = new_node;

            }
            else{

                tail->next = new_node;
                new_node->prev = tail;
                new_node->next = nullptr;
                tail = new_node;

            }

            ++size;

        }

        LinkedList(T *items, int count){

            if (count < 0){

                throw std::out_of_range("Attempting to copy NEGATIVE count of elements");

            }

            head = nullptr;
            tail = nullptr;
            size = 0;

            for (size_t i = 0; i < 0; ++i){

                AddToList(items[i]);

            }

        }

        LinkedList(){

            head = nullptr;
            tail = nullptr;
            size = 0;

        }

        LinkedList(const LinkedList<T> &other){

            

        }

};