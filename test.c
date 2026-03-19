#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "test.h"
#include "func.h"
#include "dynamic_array.h"
#include "checker.h"
#include "dynamic_arr_operations.h"
#include "field_info.h"
#include "assertions.h"

void num_plus_322(void *arg){

    double *x = arg;
    *x = (*x) + 322.00000000000;

}

void num_negative(void *arg){

    double *x = arg;
    *x = (*x) * (-1.000000000000);

}

void num_minus_2(void *arg){

    double *x = arg;
    *x = (*x) - 2.000000000000;

}

void square_square(void *arg){

    double *x = arg;
    *x = ((*x) * (*x)) * ((*x) * (*x));

}

void square(void *arg){

    double *x = arg;
    *x = (*x) * (*x);

}

void do_nothing(void *f){}

void to_square_func(void *f){

    func_t *func = f;

    if (*func != square){

        *func = square;

    }

}

void to_square_square_func(void *f){

    func_t *func = f;

    if (*func != square_square){

        *func = square_square;

    }

}

void to_num_negative_func(void *f){

    func_t *func = f;

    if (*func != num_negative){

        *func = num_negative;

    }

}

void to_num_minus_2_func(void *f){

    func_t *func = f;

    if (*func != num_minus_2){

        *func = num_minus_2;

    }

}

bool is_square_square(void *f){

    func_t *func = f;

    return (*func == square_square);

}

bool perfect_man_height(void *height){

    double *h = height;

    return (*h == 1.71);

}

bool is_square(void *f){

    func_t *func = f;

    return (*func == square);

}

bool is_less_than_ten(void *num){
    
    double *h = num;

    return ((*h - 10.0) < 0);

}

bool is_more_than_ten(void *num){

    double *h = num;

    return ((*h - 10.0) > 0);

}

TEST(test_create_arr_zero_capacity_DOUBLE){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(0, get_double_info(), &error);

    ASSERT_NULL(arr);
    ASSERT_EQ(error, ERROR_ZERO_CAPACITY);
    
}

TEST(test_create_arr_zero_capacity_FUNC){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(0, get_func_info(), &error);

    ASSERT_NULL(arr);
    ASSERT_EQ(error, ERROR_ZERO_CAPACITY);

}

TEST(test_create_arr_DOUBLE){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(3, get_double_info(), &error);

    ASSERT_NOT_NULL(arr);
    ASSERT_EQ(error, OK);
    
}

TEST(test_create_arr_FUNC){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(3, get_func_info(), &error);

    ASSERT_NOT_NULL(arr);
    ASSERT_EQ(error, OK);
    
}

TEST(test_add_to_arr_DOUBLE){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(1, get_double_info(), &error);

    double x, res;

    x = 0.6372;
    
    add_to_arr(arr, &x, &error);

    ASSERT_EQ(error, OK);

    res = *(double*)get_elem(arr, 0, &error);

    ASSERT_EQ(error, OK);
    ASSERT_DOUBLE_EQ(res, x);

}

TEST(test_add_to_arr_FUNC){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(1, get_func_info(), &error);

    func_t f1, f_check; 
    double x;
    
    x = 2.2;
    f1 = square;

    add_to_arr(arr, &f1, &error);

    ASSERT_EQ(error, OK);

    f_check = *(func_t*)get_elem(arr, 0, &error);

    ASSERT_EQ(error, OK);
    ASSERT_EQ(f_check, square);
    
}

TEST(test_wrong_get_from_arr_DOUBLE){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(1, get_double_info(), &error);

    double x, elem_check;
    x = 0.6372;
    
    add_to_arr(arr, &x, &error);
    void *ptr = get_elem(arr, 1, &error);

    ASSERT_EQ(error, ERROR_GET_ELEM_OUT_OF_RANGE);

}

TEST(test_wrong_get_from_arr_FUNC){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(1, get_func_info(), &error);

    func_t f1; 
    double x;
    
    x = 2.2;
    f1 = square;

    add_to_arr(arr, &f1, &error);

    void *ptr = get_elem(arr, 1, &error);
    
    ASSERT_EQ(error, ERROR_GET_ELEM_OUT_OF_RANGE);
    
}

TEST(test_try_to_brake_malloc_DOUBLE){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(999999999, get_double_info(), &error);

    ASSERT_EQ(error, ERROR_MALLOC_FAILED);
    
}

TEST(test_try_to_brake_malloc_FUNC){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(999999999, get_func_info(), &error);

    ASSERT_EQ(error, ERROR_MALLOC_FAILED);
    
}

TEST(test_try_to_brake_realloc_DOUBLE){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(1, get_double_info(), &error);

    double x;
    x = 1.23;  

    for (int i = 0; i < 999999999; ++i){

        add_to_arr(arr, &x, &error);

        if (error != OK){

            ASSERT_EQ(error, ERROR_REALLOC_FAILED);
            return;

        }

    }

    ASSERT(0);

}

TEST(test_try_to_brake_realloc_FUNC){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(1, get_func_info(), &error);

    func_t f1;
    f1 = square;

    for (int i = 0; i < 999999999; ++i){

        add_to_arr(arr, &f1, &error);

        if (error != OK){

            ASSERT_EQ(error, ERROR_REALLOC_FAILED);
            return;

        }

    }
    
    ASSERT(0);

}

TEST(test_map_DOUBLE){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(3, get_double_info(), &error);

    double x, y, z;
    func_t f1; 

    x = 1.12;
    y = 2.23;
    z = 3.34;

    f1 = square;

    add_to_arr(arr, &x, &error);
    add_to_arr(arr, &y, &error);
    add_to_arr(arr, &z, &error);

    dynamic_arr_t *res_arr = map(f1, arr, &error);
    
    ASSERT_EQ(error, OK);

    for (size_t i = 0; i < res_arr->size; ++i){

        double res =  *(double*)get_elem(res_arr, i, &error);
        double curr = *(double*)get_elem(arr, i, &error);

        ASSERT_EQ(error, OK);
        ASSERT_DOUBLE_EQ(res, curr * curr);

    }

}

TEST(test_map_FUNC){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(1, get_func_info(), &error);

    double x;
    func_t f1, check; 

    x = 2.5;

    f1 = square;

    add_to_arr(arr, &f1, &error);

    dynamic_arr_t *res_arr = map(do_nothing, arr, &error);

    ASSERT_EQ(error, OK);

    check = *(func_t*)get_elem(res_arr, 0, &error);
    
    check(&x);
    check(&x);
    
    ASSERT_EQ(error, OK);
    ASSERT_DOUBLE_EQ(x, 2.5*2.5*2.5*2.5);

}

TEST(test_where_DOUBLE){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(3, get_double_info(), &error);

    double x, y, z;
    predicate_t pred; 

    pred = perfect_man_height;

    x = 2.01;
    y = 1.71;
    z = 1.76;

    add_to_arr(arr, &x, &error);
    add_to_arr(arr, &y, &error);
    add_to_arr(arr, &z, &error);

    dynamic_arr_t *res_arr = where(pred, arr, &error);

    ASSERT_EQ(error, OK);

    double curr = *(double*)get_elem(res_arr, 0, &error);
    ASSERT_DOUBLE_EQ(curr, 1.71);

}

TEST(test_where_FUNC){

    error_code error = OK;

    dynamic_arr_t *arr = create_arr(3, get_func_info(), &error);

    predicate_t pred;
    func_t f1, f2, f3, f_check;

    f1 = square; 
    f2 = do_nothing;
    f3 = square;

    pred = is_square;

    add_to_arr(arr, &f1, &error);
    add_to_arr(arr, &f2, &error);
    add_to_arr(arr, &f3, &error);

    dynamic_arr_t *res_arr = where(pred, arr, &error);

    ASSERT_EQ(error, OK);

    f_check = *(func_t*)get_elem(res_arr, 0, &error);
    ASSERT_EQ(f_check, square);

    f_check = *(func_t*)get_elem(res_arr, 1, &error);
    ASSERT_EQ(f_check, square);

}

TEST(test_concatenate_null_arr){

    error_code error = OK;

    dynamic_arr_t *arr1, *arr2;

    arr1 = NULL;
    arr2 = NULL;

    dynamic_arr_t *res_arr = concatenate(arr1, arr2, &error);
    ASSERT_EQ(error, ERROR_NULL);

}

TEST(test_concatenate_diff_types_arrays){

    error_code error = OK;

    dynamic_arr_t *arr1 = create_arr(10, get_double_info(), &error);
    dynamic_arr_t *arr2 = create_arr(10, get_func_info(), &error);

    dynamic_arr_t *res_arr = concatenate(arr1, arr2, &error);
    ASSERT_EQ(error, ERROR_DIFF_TYPES);

}

TEST(test_concatenate_DOUBLE){

    error_code error = OK;

    dynamic_arr_t *arr1 = create_arr(2, get_double_info(), &error);
    dynamic_arr_t *arr2 = create_arr(3, get_double_info(), &error);

    double a, b, x, y, z;

    a = 1.1;
    b = 2.2;
    x = 3.3;
    y = 4.4;
    z = 5.5;

    add_to_arr(arr1, &a, &error);
    add_to_arr(arr1, &b, &error);
    add_to_arr(arr2, &x, &error);
    add_to_arr(arr2, &y, &error);
    add_to_arr(arr2, &z, &error);

    dynamic_arr_t *res_arr = concatenate(arr1, arr2, &error);
    ASSERT_EQ(error, OK);

    double curr = *(double*)get_elem(res_arr, 0, &error);
    ASSERT_DOUBLE_EQ(curr, a);

    curr = *(double*)get_elem(res_arr, 1, &error);
    ASSERT_DOUBLE_EQ(curr, b);

    curr = *(double*)get_elem(res_arr, 2, &error);
    ASSERT_DOUBLE_EQ(curr, x);

    curr = *(double*)get_elem(res_arr, 3, &error);
    ASSERT_DOUBLE_EQ(curr, y);

    curr = *(double*)get_elem(res_arr, 4, &error);
    ASSERT_DOUBLE_EQ(curr, z);

}

TEST(test_concatenate_FUNC){

    error_code error = OK;

    dynamic_arr_t *arr1 = create_arr(2, get_func_info(), &error);
    dynamic_arr_t *arr2 = create_arr(3, get_func_info(), &error);

    func_t f1, f2, f3, f4, f5, f_check;

    f1 = square;
    f2 = square_square;
    f3 = num_negative;
    f4 = num_minus_2;
    f5 = num_plus_322;

    add_to_arr(arr1, &f1, &error);
    add_to_arr(arr1, &f2, &error);
    add_to_arr(arr2, &f3, &error);
    add_to_arr(arr2, &f4, &error);
    add_to_arr(arr2, &f5, &error);

    dynamic_arr_t *res_arr = concatenate(arr1, arr2, &error);
    ASSERT_EQ(error, OK);

    f_check = *(func_t*)get_elem(res_arr, 0, &error);
    ASSERT_EQ(f_check, square);

    f_check = *(func_t*)get_elem(res_arr, 1, &error);
    ASSERT_EQ(f_check, square_square);

    f_check = *(func_t*)get_elem(res_arr, 2, &error);
    ASSERT_EQ(f_check, num_negative);

    f_check = *(func_t*)get_elem(res_arr, 3, &error);
    ASSERT_EQ(f_check, num_minus_2);

    f_check = *(func_t*)get_elem(res_arr, 4, &error);
    ASSERT_EQ(f_check, num_plus_322);

}

static test_t *head = NULL;
static test_t *tail = NULL;

void register_test(const char *name, test_func test)
{
    test_t *tmp = malloc(sizeof(test_t));
    
    tmp->name = name;
    tmp->this_test = test;
    tmp->next_test = NULL;
    
    if (head == NULL && tail == NULL){
        
        head = tmp;
        tail = tmp;
        
        return;
    }
    
    tail->next_test = tmp;
    tail = tmp;
}

void run_tests(){

    int failed_tests, all_tests;

    failed_tests = 0;
    all_tests = 0;

    for (test_t *t = head; t != NULL; t = t->next_test){

        t->this_test();
        ++all_tests;

        int fail = fail_result();

        if (fail > 0){

            ++failed_tests;

        }

    }

    if (failed_tests > 0){

        printf("FAILED TESTS :  %d      PASSED TESTS :  %d\n", failed_tests, all_tests - failed_tests);

    }
    else{

        printf("ALL %d TESTS PASSED :)\n", all_tests);

    }

}

TEST_ENTRY_POINT