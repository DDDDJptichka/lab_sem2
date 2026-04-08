#pragma once

#include <string>
#include <exception>

class Exception : public std::exception{

    protected:

        std::string message;

    public:

        explicit Exception(const std::string &mssg) : message(mssg){}

        const char *what() const noexcept override{

            return message.c_str();

        }

};

class IndexOutOfRange : public Exception{};

class InvalidArgument : public Exception{};