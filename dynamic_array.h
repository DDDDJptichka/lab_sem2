#pragma once

#include "field_info.h"

typedef struct Dynamic_arr{

    void *data;
    size_t size;
    size_t capacity;
    const field_info_t* type;

} dynamic_arr_t;

//фции