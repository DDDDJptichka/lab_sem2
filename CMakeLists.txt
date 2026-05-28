cmake_minimum_required(VERSION 3.16)

project(SEM2_LAB3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(googletest)

add_executable(a main.cpp)
add_executable(tests tests.cpp)

target_include_directories(a PRIVATE includes includes_lab4)
target_include_directories(tests PRIVATE includes includes_lab4)

target_link_libraries(tests gtest gtest_main)