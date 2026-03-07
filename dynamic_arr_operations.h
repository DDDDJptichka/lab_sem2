#pragma once

#include "dynamic_array.h"
#include "func.h"

dynamic_arr_t* map(func_t function, dynamic_arr_t* arr);

dynamic_arr_t* where(predicate_t predicate, dynamic_arr_t* arr);

void copy_arrs(dynamic_arr_t* result_arr, dynamic_arr_t* arr);

dynamic_arr_t* concatenate(dynamic_arr_t* arr_1, dynamic_arr_t* arr_2);