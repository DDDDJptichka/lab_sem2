#pragma once

#include "field_info.h"
#include "checker.h"

typedef struct Dynamic_arr{

    void *data;
    size_t size;
    size_t capacity;
    const field_info_t* type;

} dynamic_arr_t;

dynamic_arr_t* create_arr(size_t capacity, const field_info_t *info, error_code *error);

int add_to_arr(dynamic_arr_t *arr, void *elem, error_code *error);

void* get_elem(dynamic_arr_t *arr, size_t index, error_code *error);