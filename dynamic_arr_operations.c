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

dynamic_arr_t* where(predicate_t predicate, dynamic_arr_t* arr){

    dynamic_arr_t* new_arr = create_arr(arr->capacity, arr->type);

    for (size_t i = 0; i < arr->size; ++i){

        void *elem = GET_ELEM(arr, i);

        if (predicate(elem)){

            add_to_arr(new_arr, elem);

        }

    }

    return new_arr;

}

void copy_arrs(dynamic_arr_t* result_arr, dynamic_arr_t* arr){

    for (size_t i = 0; i < arr->size; ++i){

        void *elem = GET_ELEM(arr, i);
        add_to_arr(result_arr, elem);

    }

}

dynamic_arr_t* concatenate(dynamic_arr_t* arr_1, dynamic_arr_t* arr_2){

    if (arr_1->type != arr_2->type){

        return NULL;

    }

    dynamic_arr_t* new_arr = create_arr((arr_1->size + arr_2->size), arr_1->type);

    copy_arrs(new_arr, arr_1);
    copy_arrs(new_arr, arr_2);

    return new_arr;

}