#pragma once

#include <functional>
#include <cstddef>

#include "Exception.h"
#include "Option.h"

template <class T> class Generator{

    private:

        std::function<T(size_t)> rule = nullptr;
        size_t index = 0;
        size_t count = 0;
        bool inf = false;

    public:

        class Iterator{

            private:

                std::function<T(size_t)> rule = nullptr;
                size_t index = 0;
                size_t count = 0;

            public:

                Iterator(){}

                Iterator(std::function<T(size_t)> rule, size_t index, size_t count) : rule(rule), index(index), count(count){}

                T operator*() const{

                    return rule(index);

                }

                Iterator& operator++(){

                    ++index;
                    return *this;

                }

                Iterator operator++(int){

                    Iterator tmp = *this;
                    ++(*this);
                    return tmp;

                }

                bool operator==(const Iterator& another) const{

                    return (index == another.index);

                }

                bool operator!=(const Iterator& another) const{

                    return !(*this == another);

                }

        };

        Iterator begin() const{

            if (inf == true){

                throw not_usable("Generator is infinite, there is no begin");

            }

            return Iterator(rule, 0, count);

        }

        Iterator end() const{

            if (inf == true){

                throw not_usable("Generator is infinite, there is no end");

            }

            return Iterator(rule, count, count);

        }

        Generator(){}

        Generator(std::function<T(size_t)> rule) : rule(rule), inf(true){}

        Generator(std::function<T(size_t)> rule, size_t count) : rule(rule), count(count), inf(false){}

        ~Generator(){}

        bool has_next() const{

            return ((rule != nullptr) && (inf || index < count));

        }

        T get_next(){

            if (has_next() == false){

                throw index_out_of_range("Generator hasn`t next element");

            }

            T elem = rule(index);
            ++index;

            return elem;

        }

        Option<T> try_get_next(){

            if (has_next() == false){

                return Option<T>();

            }

            return Option<T>(get_next());

        }

        size_t get_position() const{

            return index;

        }

};