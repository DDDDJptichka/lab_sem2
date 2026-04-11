#pragma once

#include <string>
#include <exception>

class exception : public std::exception{

    protected:

        std::string message;

    public:

        explicit exception(const std::string &msg) : message(msg){}

        const char *what() const noexcept override{

            return message.c_str();

        }

};

class index_out_of_range : public exception{

    public:

        explicit index_out_of_range(const std::string &msg) : exception(msg){}

};

class empty_container : public exception{

    public:

        explicit empty_container(const std::string &msg) : exception(msg){}

};