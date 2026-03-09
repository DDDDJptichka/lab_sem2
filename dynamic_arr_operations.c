#include <stdlib.h>
#include "dynamic_array.h"
#include "func.h"
#include "checker.h"

#define GET_ELEM(arr, i) ((char*)(arr)->data + (i) * (arr)->type->size)

dynamic_arr_t* map(func_t function, dynamic_arr_t* arr, error_code *error){

    if (error == NULL){

        return NULL;

    }
    
    if (arr == NULL){

        *error = ERROR_NULL;

        return NULL;

    }

    dynamic_arr_t* new_arr = create_arr(arr->capacity, arr->type, error);

    if (*error != OK){

        return NULL;

    }

    void *new_arr_member = malloc(arr->type->size);

    if (new_arr_member == NULL){

        *error = ERROR_MALLOC_FAILED;

        return NULL;

    }

    for (size_t i = 0; i < arr->size; ++i){

        void *elem = GET_ELEM(arr, i);        

        arr->type->copy(elem, new_arr_member);
        function(new_arr_member);
        add_to_arr(new_arr, new_arr_member, error);

        if (*error != OK){

            free(new_arr_member);

            return NULL;

        }

    }

    free(new_arr_member);
    
    *error = OK;

    return new_arr;

}

dynamic_arr_t* where(predicate_t predicate, dynamic_arr_t* arr, error_code *error){

    if (error == NULL){

        return NULL;

    }

    if (arr == NULL){

        *error = ERROR_NULL;

        return NULL;

    }

    dynamic_arr_t* new_arr = create_arr(arr->capacity, arr->type, error);

    if (*error != OK){

        return NULL;

    }

    for (size_t i = 0; i < arr->size; ++i){

        void *elem = GET_ELEM(arr, i);

        if (predicate(elem)){

            add_to_arr(new_arr, elem, error);

            if (*error != OK){

                return NULL;

            }


        }

    }

    *error = OK;

    return new_arr;

}

static void copy_arrs(dynamic_arr_t* result_arr, dynamic_arr_t* arr, error_code *error){

    if (error == NULL){

        return;

    }

    if (arr == NULL){

        *error = ERROR_NULL;

        return;

    }

    for (size_t i = 0; i < arr->size; ++i){

        void *elem = GET_ELEM(arr, i);
        add_to_arr(result_arr, elem, error);

        if (*error != OK){

            return;

        }

    }

    *error = OK;

}

dynamic_arr_t* concatenate(dynamic_arr_t* arr_1, dynamic_arr_t* arr_2, error_code *error){

    if (error == NULL){

        return NULL;

    }

    if ((arr_1 == NULL) || (arr_2 == NULL)){

        *error = ERROR_NULL;

        return NULL;

    }

    if (arr_1->type != arr_2->type){

        *error = ERROR_DIFF_TYPES;

        return NULL;

    }

    dynamic_arr_t* new_arr = create_arr((arr_1->size + arr_2->size), arr_1->type, error);

    if (*error != OK){

        return NULL;

    }

    copy_arrs(new_arr, arr_1, error);
    copy_arrs(new_arr, arr_2, error);

    if (*error != OK){

        return NULL;

    }

    *error = OK;

    return new_arr;

}