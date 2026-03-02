#pragma once

#include "field_info.h"

typedef struct Dynamic_arr{

    void *data;
    size_t size;
    size_t capacity;
    const field_info_t* type;

} dynamic_arr_t;

dynamic_arr_t* create_arr(size_t capacity, const field_info_t *info);

int add_to_arr(dynamic_arr_t *arr, void *elem);