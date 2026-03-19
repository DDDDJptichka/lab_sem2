#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include "test.h"
#include "checker.h"
#include "dynamic_arr_operations.h"
#include "dynamic_array.h"
#include "func.h"
#include "console_interface.h"

#define TEST(test_name) \
    static void test_name(); \
    static void __attribute__((constructor)) \
    register_##test_name(){ \
        register_test(#test_name, test_name); \
    } \
    static void test_name()

#define TEST_ENTRY_POINT \
    int main(void){ \
        SetConsoleOutputCP(1251); \
        SetConsoleCP(1251); \
        setlocale(LC_ALL, "Russian"); \
        run_tests(); \
        dynamic_arr_t *arr = do_interface(); \
        return 0; \
    } \

typedef void (*test_func)(void);

typedef struct test{

    const char *name;
    test_func this_test;
    struct test *next_test;

} test_t;

void num_plus_322(void *arg);
void num_negative(void *arg);
void num_minus_2(void *arg);
void square_square(void *arg);
void square(void *arg);

void do_nothing(void *f);
void to_square_func(void *f);
void to_num_negative_func(void *f);
void to_num_minus_2_func(void *f);

bool is_square_square(void *f);
bool is_square(void *f);

bool is_less_than_ten(void *num);
bool perfect_man_height(void *height);
bool is_more_than_ten(void *num);

void register_test(const char *name, test_func test);
void run_tests();