#include "dynamic_array.h"
#include "field_info.h"
#include <stdlib.h>
#include "checker.h"

dynamic_arr_t* create_arr(size_t capacity, const field_info_t *info, error_code *error){
    
    if (capacity == 0){

        *error = ERROR_ZERO_CAPACITY;

        return NULL;

    }

    dynamic_arr_t *arr = malloc(sizeof(dynamic_arr_t));

    if (arr == NULL){

        *error = ERROR_MALLOC_FAILED;
        
        return NULL;

    }

    arr->data = malloc(capacity * info->size);

    if (arr->data == NULL){

        free(arr);
        
        *error = ERROR_MALLOC_FAILED;

        return NULL;

    }

    arr->size = 0;
    arr->capacity = capacity;
    arr->type = info;

    *error = OK;

    return arr;
}

int add_to_arr(dynamic_arr_t *arr, void *elem, error_code *error){

    if (arr->size >= arr->capacity){

        size_t curr_capacity = arr->size + arr->capacity;
        void *new_arr = realloc(arr->data, curr_capacity * arr->type->size);
        
        if (new_arr == NULL){

            *error = ERROR_REALLOC_FAILED;

            return 1;

        }

        arr->data = new_arr;
        arr->capacity = curr_capacity;

    }

    void *curr_ptr = (char*)arr->data + arr->size * (arr->type->size);
    arr->type->copy(elem, curr_ptr);
    arr->size++;
    
    *error = OK;

    return 0;
}