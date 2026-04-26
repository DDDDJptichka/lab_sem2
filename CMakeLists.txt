cmake_minimum_required(VERSION 3.16)
project(Sequences)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

add_executable(a main.cpp tests.cpp SequenceInterface.cpp)

target_link_libraries(a gtest)