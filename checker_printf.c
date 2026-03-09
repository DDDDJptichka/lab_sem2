#include "checker.h"

const char* err_printf(error_code error){

    switch (error){

        case OK:
            return "OK";

        case ERROR_DIFF_TYPES:
            return "different types error";

        case ERROR_MALLOC_FAILED:
            return "malloc failed";

        case ERROR_NOT_AN_ERROR_TYPE:
            return "wrong type of error (not an 'error_code' argument)";

        case ERROR_NULL:
            return "null ptr error";

        case ERROR_REALLOC_FAILED:
            return "realloc failed";

        case ERROR_ZERO_CAPACITY:
            return "zero capacity error";

        case ERROR_GET_ELEM_OUT_OF_RANGE:
            return "try to get element out of array range";

        default:
            return "GG";
    }

}