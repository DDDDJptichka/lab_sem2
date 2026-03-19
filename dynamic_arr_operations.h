#pragma once

#include "dynamic_array.h"
#include "func.h"
#include "checker.h"

dynamic_arr_t* map(func_t function, dynamic_arr_t* arr, error_code* error);

dynamic_arr_t* where(predicate_t predicate, dynamic_arr_t* arr, error_code* error);

dynamic_arr_t* concatenate(dynamic_arr_t* arr_1, dynamic_arr_t* arr_2, error_code* error);