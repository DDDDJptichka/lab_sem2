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

template <typename Container, typename function> class WhereV{

    private:

        const Container &container;
        function f;

    public:

        using ContainerIterator = decltype(container.begin());

        WhereV(const Container &cont, function func) : container(cont), f(func){}

        class Iterator{

            private:

                ContainerIterator curr;
                ContainerIterator curr_end;
                function f;

                void skip(){

                    while ((curr != curr_end) && (f(*curr) == 0)){++curr;}

                }

            public:

                using iterator_category = std::forward_iterator_tag;
                using value_type = decltype(std::declval<function>()(*std::declval<ContainerIterator>()));
                using difference_type = std::ptrdiff_t;
                using pointer = const value_type*;
                using reference = const value_type&;

                Iterator(ContainerIterator c_start, ContainerIterator c_end, function func) : curr(c_start), curr_end(c_end), f(func){skip();}

                auto operator*() const{return *curr;}

                Iterator& operator++(){

                    ++curr;
                    skip();

                    return *this;

                }

                Iterator operator++(int){

                    Iterator res = *this;
                    ++(*this);

                    return res;

                }

                bool operator==(const Iterator &another) const{return curr == another.curr;}
                bool operator!=(const Iterator &another) const{return curr != another.curr;}

        };

        Iterator begin() const{return Iterator(container.begin(), container.end(), f);}
        Iterator end() const{return Iterator(container.end(), container.end(), f);}

};

template <typename Container, typename function> auto where(const Container &container, function f){

    return WhereV<Container, function>(container, f);

}

template <typename Container, typename function, typename T> auto reduce(const Container &container, function f, const T c){

    auto iter = container.begin();

    if (iter == container.end()){

        return c;

    }

    auto res = f(*(iter), c);
    ++iter;

    for (; iter != container.end(); ++iter){

        res = f(res, *iter);

    }

    return res;

}