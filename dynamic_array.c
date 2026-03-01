#include "dynamic_array.h"
#include "field_info.h"
#include <stdio.h>

dynamic_arr_t* create_arr(size_t capacity, const field_info_t *info){
    
    if (capacity <= 0){

        return NULL;

    }

    dynamic_arr_t *arr = malloc(sizeof(dynamic_arr_t));
    arr->data = malloc(capacity * info->size);
    arr->size = 0;
    arr->capacity = capacity;
    arr->type = info;

    return arr;
}

void add_to_arr(dynamic_arr_t *arr, void *elem){

    

}

void ning(){

    
}