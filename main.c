#include <stdlib.h>
#include <stdio.h>
#include "test.h"
#include "checker.h"
#include "dynamic_arr_operations.h"
#include "dynamic_array.h"
#include "func.h"

int main(){

    test_create_arr_zero_capacity_DOUBLE();
    test_create_arr_zero_capacity_FUNC();
    test_create_arr_DOUBLE();
    test_create_arr_FUNC();
    test_add_to_arr_DOUBLE();
    test_add_to_arr_FUNC();
    test_wrong_get_from_arr_DOUBLE();
    test_wrong_get_from_arr_FUNC();
    test_try_to_brake_malloc_DOUBLE();
    test_try_to_brake_malloc_FUNC();
    test_try_to_brake_realloc_DOUBLE();
    test_try_to_brake_realloc_FUNC();
    test_map_DOUBLE();
    test_map_FUNC();
    test_where_DOUBLE();
    test_where_FUNC();
    test_concatenate_null_arr();
    test_concatenate_diff_types_arrays();
    test_concatenate_DOUBLE();
    test_concatenate_FUNC();

    return 0;
}