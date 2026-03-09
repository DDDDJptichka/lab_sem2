#pragma once

typedef enum{

    OK = 0,
    ERROR_ZERO_CAPACITY,
    ERROR_NULL,
    ERROR_MALLOC_FAILED,
    ERROR_REALLOC_FAILED,
    ERROR_DIFF_TYPES,
    ERROR_NOT_AN_ERROR_TYPE,
    ERROR_GET_ELEM_OUT_OF_RANGE

} error_code;

const char* err_printf(error_code error);