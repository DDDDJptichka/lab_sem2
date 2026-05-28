#pragma once

#include <cstddef>
#include <new>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "Exception.h"

template <class T> class Option{

    private:

        alignas(T) std::byte data[sizeof(T)];
        bool has_val = false;

        T* ptr();
        const T* ptr() const;
        void clean();

    public:

        Option(){}

        Option(const T& value){

            new (static_cast<void*>(data)) T(value);
            has_val = true;

        }
    
        Option(const Option& another){

            if (another.has_val == true){

                new (static_cast<void*>(data)) T(*another.ptr());
                has_val = true;
            
            }

        }

        ~Option(){

            clean();

        }

        void reset(){

            clean();

        }

        bool has_value() const{

            return has_val;

        }

        T& value(){

            if (has_val == false){

                throw empty_option("Option is empty");

            }

            return *ptr();

        }

        const T& value() const{

            if (has_val == false){

                throw empty_option("Option is empty");

            }

            return *ptr();

        }

        Option<T>& operator=(const Option<T>& another){

            if (this == &another){

                return *this;

            }

            clean();

            if (another.has_val){

                new (static_cast<void*>(data)) T(*(another.ptr()));
                has_val = true;

            }

            return *this;

        }

};

template <typename T> T* Option<T>::ptr(){

    return reinterpret_cast<T*>(data);

}

template <typename T> const T* Option<T>::ptr() const{

    return reinterpret_cast<const T*>(data);

}

template <typename T> void Option<T>::clean(){

    if (has_val == 1){

        ptr()->~T();
        has_val = false;

    }

}