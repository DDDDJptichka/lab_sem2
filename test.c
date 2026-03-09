#include <stdio.h>
#include <stdbool.h>
#include "func.h"
#include "dynamic_array.h"
#include "checker.h"
#include "dynamic_arr_operations.h"
#include "field_info.h"

void num_plus_322(void *arg){

    double *x = arg;
    *x = (*x) + 322;

}

void num_negative(void *arg){

    double *x = arg;
    *x = (*x) * (-1);

}

void num_minus_2(void *arg){

    double *x = arg;
    *x = (*x) - 2;

}

void square_square(void *arg){

    double *x = arg;
    *x = ((*x) * (*x)) * ((*x) * (*x));

}

void square(void *arg){

    double *x = arg;
    *x = (*x) * (*x);

}

void do_nothing(void *f){

    func_t *func = f;

}

bool perfect_man_height(void *height){

    double *h = height;

    return (*h == 1.71);

}

bool is_square(void *arg){

    func_t *f = arg;

    return (*f == square);

}

error_code error;

void test_create_arr_zero_capacity_DOUBLE(){

    dynamic_arr_t *arr = create_arr(0, get_double_info(), &error);

    printf("%s\n", err_printf(error));
    
}

void test_create_arr_zero_capacity_FUNC(){

    dynamic_arr_t *arr = create_arr(0, get_func_info(), &error);

    printf("%s\n\n", err_printf(error));
    
}

void test_create_arr_DOUBLE(){

    dynamic_arr_t *arr = create_arr(3, get_double_info(), &error);

    printf("%s\n", err_printf(error));
    
}

void test_create_arr_FUNC(){

    dynamic_arr_t *arr = create_arr(3, get_func_info(), &error);

    printf("%s\n\n", err_printf(error));
    
}

void test_add_to_arr_DOUBLE(){

    dynamic_arr_t *arr = create_arr(1, get_double_info(), &error);

    double x;

    x = 0.6372;
    
    add_to_arr(arr, &x, &error);

    printf("double get:   %f %s\n", *(double*)get_elem(arr, 0, &error), err_printf(error));

}

void test_add_to_arr_FUNC(){

    dynamic_arr_t *arr = create_arr(1, get_func_info(), &error);

    func_t f1, f_check; 
    double x;
    
    x = 2.2;
    f1 = square;

    add_to_arr(arr, &f1, &error);

    f_check = *(func_t*)get_elem(arr, 0, &error);
    f_check(&x);

    printf("func_get:   (2.2)**2 = %.3f %s\n\n", x, err_printf(error));
    
}

void test_wrong_get_from_arr_DOUBLE(){

    dynamic_arr_t *arr = create_arr(1, get_double_info(), &error);

    double x, elem_check;
    x = 0.6372;
    
    add_to_arr(arr, &x, &error);
    void *ptr = get_elem(arr, 1, &error);

    printf("%s\n", err_printf(error));

}

void test_wrong_get_from_arr_FUNC(){

    dynamic_arr_t *arr = create_arr(1, get_func_info(), &error);

    func_t f1; 
    double x;
    
    x = 2.2;
    f1 = square;

    add_to_arr(arr, &f1, &error);

    void *ptr = get_elem(arr, 1, &error);
    
    printf("%s\n\n", err_printf(error));
    
}

void test_try_to_brake_malloc_DOUBLE(){

    dynamic_arr_t *arr = create_arr(999999999, get_double_info(), &error);

    printf("%s\n", err_printf(error));
    
}

void test_try_to_brake_malloc_FUNC(){

    dynamic_arr_t *arr = create_arr(999999999, get_func_info(), &error);

    printf("%s\n\n", err_printf(error));
    
}

void test_try_to_brake_realloc_DOUBLE(){

    dynamic_arr_t *arr = create_arr(1, get_double_info(), &error);

    double x;
    x = 1.23;  

    for (int i = 0; i < 999999999; ++i){

        add_to_arr(arr, &x, &error);

        if (error == ERROR_REALLOC_FAILED){

            printf("%s\n", err_printf(error));

            return;

        }

    }
    
}

void test_try_to_brake_realloc_FUNC(){

    dynamic_arr_t *arr = create_arr(1, get_func_info(), &error);

    func_t f1;
    f1 = square;

    for (int i = 0; i < 999999999; ++i){

        add_to_arr(arr, &f1, &error);

        if (error == ERROR_REALLOC_FAILED){

            printf("%s\n\n", err_printf(error));

            return;

        }

    }
    
}

void test_map_DOUBLE(){

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

    for (size_t i = 0; i < res_arr->size; ++i){

        printf("double map:   %d:  %f %s\n", i, *(double*)get_elem(res_arr, i, &error), err_printf(error));

    }

}

void test_map_FUNC(){

    dynamic_arr_t *arr = create_arr(1, get_func_info(), &error);

    double x;
    func_t f1, check; 

    x = 2.5;

    f1 = square;

    add_to_arr(arr, &f1, &error);

    dynamic_arr_t *res_arr = map(do_nothing, arr, &error);

    check = *(func_t*)get_elem(res_arr, 0, &error);
    
    check(&x);
    check(&x);
    
    printf("func map:   (2.5)**4 = %f %s\n\n", x, err_printf(error));

}

void test_where_DOUBLE(){

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

    printf("double where:   %.2f %s\n", *(double*)get_elem(res_arr, 0, &error), err_printf(error));

}

void test_where_FUNC(){

    dynamic_arr_t *arr = create_arr(3, get_func_info(), &error);

    double x;
    predicate_t pred;
    func_t f1, f2, f3, f_check;

    x = 2.5;
    f1 = square; 
    f2 = do_nothing;
    f3 = square;

    pred = is_square;

    add_to_arr(arr, &f1, &error);
    add_to_arr(arr, &f2, &error);
    add_to_arr(arr, &f3, &error);

    dynamic_arr_t *res_arr = where(pred, arr, &error);

    f_check = *(func_t*)get_elem(res_arr, 0, &error);
    f_check(&x);
    printf("func where:   0: %f %s\n", x, err_printf(error));

    x = 2.5;

    f_check = *(func_t*)get_elem(res_arr, 1, &error);
    f_check(&x);
    printf("func where:   1: %f %s\n\n", x, err_printf(error));

}

void test_concatenate_null_arr(){

    dynamic_arr_t *arr1, *arr2;

    arr1 = NULL;
    arr2 = NULL;

    dynamic_arr_t *res_arr = concatenate(arr1, arr2, &error);

    printf("%s\n\n", err_printf(error));

}

void test_concatenate_diff_types_arrays(){

    dynamic_arr_t *arr1 = create_arr(10, get_double_info(), &error);
    dynamic_arr_t *arr2 = create_arr(10, get_func_info(), &error);

    dynamic_arr_t *res_arr = concatenate(arr1, arr2, &error);

    printf("%s\n\n", err_printf(error));

}

void test_concatenate_DOUBLE(){

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
    add_to_arr(arr1, &x, &error);
    add_to_arr(arr1, &y, &error);
    add_to_arr(arr1, &z, &error);

    dynamic_arr_t *res_arr = concatenate(arr1, arr2, &error);

    for (size_t i = 0; i < res_arr->size; ++i){

        printf("double concatenate:   %d:  %f %s\n", i, *(double*)get_elem(res_arr, i, &error), err_printf(error));

    }

}

void test_concatenate_FUNC(){

    dynamic_arr_t *arr1 = create_arr(2, get_func_info(), &error);
    dynamic_arr_t *arr2 = create_arr(3, get_func_info(), &error);

    func_t f1, f2, f3, f4, f5, f_check;
    double x;

    x = 3.3;

    f1 = square;
    f2 = square_square;
    f3 = num_negative;
    f4 = num_minus_2;
    f5 = num_plus_322;

    add_to_arr(arr1, &f1, &error);
    add_to_arr(arr1, &f2, &error);
    add_to_arr(arr1, &f3, &error);
    add_to_arr(arr1, &f4, &error);
    add_to_arr(arr1, &f5, &error);

    dynamic_arr_t *res_arr = concatenate(arr1, arr2, &error);

    for (size_t i = 0; i < res_arr->size; ++i){

        f_check = *(func_t*)get_elem(res_arr, i, &error);
        f_check(&x);
        printf("func concatenate:   %d:  %f %s\n", i, x, err_printf(error));

        x = 3.3;

    }

    printf("\n");

}