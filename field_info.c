#include "field_info.h"
#include "func.h"

static void copy_double(void *from, void *to){

    *(double*)to = *(double*)from;

}

static void copy_func(void *from, void *to){

    *(func_t*)to = *(func_t*)from;

}

static field_info_t DOUBLE_FIELD = {sizeof(double), copy_double};
static field_info_t FUNC_FIELD = {sizeof(func_t), copy_func};

const field_info_t* get_double_info(){

    return &DOUBLE_FIELD;

}

const field_info_t* get_func_info(){

    return &FUNC_FIELD;

}