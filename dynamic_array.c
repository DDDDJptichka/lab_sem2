#include "dynamic_array.h"
#include "field_info.h"
#include <stdlib.h>

dynamic_arr_t* create_arr(size_t capacity, const field_info_t *info){
    
    if (capacity == 0){

        return NULL;

    }

    dynamic_arr_t *arr = malloc(sizeof(dynamic_arr_t));
    arr->data = malloc(capacity * info->size);
    arr->size = 0;
    arr->capacity = capacity;
    arr->type = info;

    return arr;
}

int add_to_arr(dynamic_arr_t *arr, void *elem){

    if (arr->size >= arr->capacity){

        size_t curr_capacity = arr->size + arr->capacity;
        void *new_arr = realloc(arr->data, curr_capacity * arr->type->size);
        
        if (new_arr == NULL){

            return 1;

        }

        arr->data = new_arr;
        arr->capacity = curr_capacity;

    }

    void *curr_ptr = (char*)arr->data + arr->size * (arr->type->size);
    arr->type->copy(elem, curr_ptr);
    arr->size++;
    
    return 0;
}