#pragma once

#include "dynamic_array.h"
#include "func.h"

#define GET_ELEM(arr, i) ((char*)(arr)->data + (i) * (arr)->type->size)

dynamic_arr_t* map(func_t function, dynamic_arr_t* arr){

    dynamic_arr_t* new_arr = create_arr(arr->capacity, arr->type);

    void *new_arr_member = malloc(arr->type->size);

    for (size_t i = 0; i < arr->size; ++i){

        void *elem = GET_ELEM(arr, i);

        arr->type->copy(elem, new_arr_member);
        
        function(new_arr_member);
        add_to_arr(new_arr, new_arr_member);

    }

    free(new_arr_member);

    return new_arr;

}

dynamic_arr_t* where(func_t h, dynamic_arr_t* arr){



}


dynamic_arr_t* concatination(dynamic_arr_t* arr_1, dynamic_arr_t* arr_2){

    

}