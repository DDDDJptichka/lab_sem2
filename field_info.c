#include "field_info.h"

static void copy_double(void *from, void *to){

    *(double*)from = *(double*)to;

}

static void copy_func(void *from, void *to){

    *(int*)from = *(int*)to;

}

static field_info_t DOUBLE_FIELD = {sizeof(double), copy_double};

const field_info_t* get_double_info(){

    return &DOUBLE_FIELD;

}

