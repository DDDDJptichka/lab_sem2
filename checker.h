#pragma once

typedef enum{

    OK = 0,
    ERROR_ZERO_CAPACITY,
    ERROR_NULL,
    ERROR_MALLOC_FAILED,
    ERROR_REALLOC_FAILED,
    ERROR_DIFF_TYPES,
    ERROR_NOT_AN_ERROR_TYPE

} error_code;
