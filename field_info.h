#pragma once

#include <stdio.h>

typedef struct field_info{

    size_t size;
    void (*copy)(void*, void*);

} field_info_t;

const field_info_t* get_double_info();

const field_info_t* get_func_info();