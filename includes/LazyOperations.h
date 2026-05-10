#pragma once

#include <iterator>

#include <cstdio>
#include <iostream>

#include "Exception.h"

#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Sequence.h"
#include "DiagonalMatrix.h"


template <typename Container, typename function> class MapV{

    private:

        const Container &container;
        function f;

    public:
    
        using ContainerIterator = decltype(container.begin());

        MapV(const Container &cont, function func) : container(cont), f(func){}

        class Iterator{

            private:

                ContainerIterator curr;
                function f;

            public:

                using iterator_category = std::forward_iterator_tag;
                using value_type = decltype(std::declval<function>()(*std::declval<ContainerIterator>()));
                using difference_type = std::ptrdiff_t;
                using pointer = value_type*;
                using reference = value_type;

                Iterator(ContainerIterator start, function func) : curr(start), f(func){}

                auto operator*() const{return f(*curr);};

                Iterator& operator++(){

                    ++curr;

                    return *this;

                }

                Iterator operator++(int){

                    Iterator res = *this;
                    ++curr;

                    return res;

                }

                bool operator==(const Iterator &another) const{return curr == another.curr;}
                bool operator!=(const Iterator &another) const{return curr != another.curr;}

        };

        Iterator begin() const{return Iterator(container.begin(), f);}
        Iterator end() const{return Iterator(container.end(), f);}

};

template <typename Container, typename function> auto map(const Container &container, function f){

    return MapV<Container, function>(container, f);

}