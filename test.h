#pragma once

#include <stdbool.h>

#define TEST(test_name) \
    static void test_name(); \
    static void __attribute__((constructor)) \
    register_##test_name(){ \
        register_test(#test_name, test_name); \
    } \
    static void test_name()

#define TEST_ENTRY_POINT \
    int main(void){ \
        run_tests(); \
        return print_stats(); \
    }

typedef void (*test_func)(void);

typedef struct test{

    const char *name;
    test_func this_test;
    struct test_h *next_test;

} test_h;

void register_test(const char *name, test_func test);
void run_tests();

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

void test_create_arr_zero_capacity_DOUBLE();
void test_create_arr_zero_capacity_FUNC();
void test_create_arr_DOUBLE();
void test_create_arr_FUNC();
void test_add_to_arr_DOUBLE();
void test_add_to_arr_FUNC();
void test_wrong_get_from_arr_DOUBLE();
void test_wrong_get_from_arr_FUNC();
void test_try_to_brake_malloc_DOUBLE();
void test_try_to_brake_malloc_FUNC();
void test_try_to_brake_realloc_DOUBLE();
void test_try_to_brake_realloc_FUNC();
void test_map_DOUBLE();
void test_map_FUNC();
void test_where_DOUBLE();
void test_where_FUNC();
void test_concatenate_null_arr();
void test_concatenate_diff_types_arrays();
void test_concatenate_DOUBLE();
void test_concatenate_FUNC();