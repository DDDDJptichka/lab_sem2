#include <stdlib.h>
#include <stdio.h>
#include "checker.h"
#include "dynamic_array.h"
#include "dynamic_arr_operations.h"
#include "field_info.h"
#include "func.h"
#include "math.h"
#include "test.h"

int choose_action(){

    int flag, a;

    flag = 0;

    printf("=============================\n"
            "0 - Создать массив\n1 - Применить map\n2 - Применить where\n3 - Применить concatenate\n4 - Выход\n\n"
            "-----------------------------\n"
            "Введите номер действия: ");

    int check_scanf = scanf("%d", &flag);

    while ((check_scanf != 1) || ((flag != 0) && (flag != 1) && (flag != 2) && (flag != 3) && (flag != 4))){
        
        printf("\n\nНЕКОРРЕКТНЫЙ ВВОД\n\n=============================\n"
                "0 - Создать массив\n1 - Применить map\n2 - Применить where\n3 - Применить concatenate\n4 - Выход\n\n"
                "-----------------------------\n"
                "Введите номер действия: ");

        check_scanf = scanf("%d", &flag);
        while ((a = getchar()) != '\n');

    }
    
    return flag;
}

int choose_array_type(){

    int flag, a;

    printf("\n\nКакого типа массив хотите создать?\n\n0 - функциональный\n1 - вещественный\n\nВведите номер действия: ");
    int check_scanf = scanf("%d", &flag);

    while ((check_scanf != 1) || ((flag != 0) && (flag != 1))){

        printf("\n\nНЕКОРРЕКТНЫЙ ВВОД\n\n=============================\n"
                "Какого типа массив хотите создать?\n\n0 - функциональный\n1 - вещественный\n\nВведите номер действия: ");

        check_scanf = scanf("%d", &flag);
        while ((a = getchar()) != '\n');

    }

    return flag;

}

dynamic_arr_t* create_double_array_console(){

    double element;
    int flag, a;
    error_code error;
    dynamic_arr_t *arr = create_arr(1, get_double_info(), &error);

    printf("\n\nХотите добавить элемент?\n\n0 - да\n1 - нет\n\nВведите номер действия: ");

    int check_scanf = scanf("%d", &flag);
    while ((a = getchar()) != '\n');

    while (flag != 1){
        
        while (check_scanf != 1){

            printf("\n\nНЕКОРРЕКТНЫЙ ВВОД\n\n==========================\n");
            printf("\n\nХотите добавить элемент?\n\n0 - да\n1 - нет\n\nВведите номер действия: ");

            check_scanf = scanf("%d", &flag);
            while ((a = getchar()) != '\n');

        }

        if (flag == 0){

            printf("\n\nВведите элемент:   ");
            check_scanf = scanf("%lf", &element);

            while (check_scanf != 1){

                printf("\n\nНЕКОРРЕКТНЫЙ ВВОД\n\n=============================\n");
                printf("\n\nВведите элемент:   ");

                check_scanf = scanf("%lf", &element);
                while ((a = getchar()) != '\n');

            }       

            add_to_arr(arr, &element, &error);

            if (error == OK){
            
                printf("\n\nЭлемент успешно добавлен\n\n");

            }
            else{

                printf("\n\nПроизошла подозрительно удивительная ошибка при добавлении элеменета в массив\n\n");

                return NULL;
            }
        }

        printf("\n\nХотите добавить элемент?\n\n0 - да\n1 - нет\n\nВведите номер действия: ");

        check_scanf = scanf("%d", &flag);
        while ((a = getchar()) != '\n');
    }

    printf("\n\nТекущий массив: [ ");

    for (size_t i = 0; i < arr->size; ++i){

        if (i != arr->size - 1){

            printf("%.9f; ", *(double*)get_elem(arr, i, &error));

        }
        else{

            printf("%.9f", *(double*)get_elem(arr, i, &error));

        }

    }

    printf(" ]\n\n");       

    return arr;
}

dynamic_arr_t* create_func_array_console(){

    int flag, a;
    error_code error;
    dynamic_arr_t *arr = create_arr(1, get_func_info(), &error);

    printf("\n\nХотите добавить функцию?\n\n0 - да\n1 - нет\n\nВведите номер действия: ");

    int check_scanf = scanf("%d", &flag);
    while ((a = getchar()) != '\n');

    while (flag != 1){

        while (check_scanf != 1){

            printf("\n\nНЕКОРРЕКТНЫЙ ВВОД\n\n=============================\n");
            printf("\n\nХотите добавить функцию?\n\n0 - да\n1 - нет\n\nВведите номер действия: ");

            check_scanf = scanf("%d", &flag);
            while ((a = getchar()) != '\n');

        }

        printf("\n\nСписок доступных функций(выберите, какую хотите добавить):\n\n0 - num_plus_322\n1 - num_negative\n2 - num_minus_2\n3 - square\n4 - square_square\n5 - do_nothing\n\nВведите номер действия: ");
        
        check_scanf = scanf("%d", &flag);
        while ((a = getchar()) != '\n');

        while ((check_scanf != 1) || ((flag != 0) && (flag != 1) && (flag != 2) && (flag != 3) && (flag != 4) && (flag != 5))){

            printf("\n\nНЕКОРРЕКТНЫЙ ВВОД\n\n=============================\n");
            printf("\n\nСписок доступных функций(выберите, какую хотите добавить):\n\n0 - num_plus_322\n1 - num_negative\n2 - num_minus_2\n3 - square\n4 - square_square\n5 - do_nothing\n\nВведите номер действия: ");

            check_scanf = scanf("%d", &flag);
            while ((a = getchar()) != '\n');

        }

        switch (flag){

            case 0:
                add_to_arr(arr, &num_plus_322, &error);
                break;

            case 1:
                add_to_arr(arr, &num_negative, &error);
                break;

            case 2:
                add_to_arr(arr, &num_minus_2, &error);
                break;
            
            case 3:
                add_to_arr(arr, &square, &error);
                break;

            case 4:
                add_to_arr(arr, &square_square, &error);
                break;

            case 5:
                add_to_arr(arr, &do_nothing, &error);
                break;
            
            default:
                error = ERROR_NULL;
                break;
        }

        if (error == OK){
            
            printf("\n\nЭлемент успешно добавлен\n\n");

        }
        else{

            printf("\n\nПроизошла подозрительно удивительная ошибка при добавлении функции в массив\n\n");

            return NULL;
        }

        printf("\n\nХотите добавить функцию?\n\n0 - да\n1 - нет\n\nВведите номер действия: ");

        check_scanf = scanf("%d", &flag);
        while ((a = getchar()) != '\n');

    }

    return arr;

}

dynamic_arr_t* do_map_console(dynamic_arr_t *arr){

    int flag, a;
    error_code error;
    dynamic_arr_t *new_arr = NULL;

    if (arr == NULL){

        printf("\n\nПрименить MAP невозможно, массив еще не создан\n\n");

        return NULL;
    }

    if (arr->type == get_double_info()){

        printf("\n\nВыберите функцию, которую хотите применить к массиву\n\n0 - num_plus_322\n1 - num_negative\n2 - num_minus_2\n3 - square\n4 - square_square\n\nВведите номер действия: ");

        int check_scanf = scanf("%d", &flag);
        while ((a = getchar()) != '\n');
        
        while ((check_scanf != 1) || ((flag != 0) && (flag != 1) && (flag != 2) && (flag != 3) && (flag != 4))){

            printf("\n\nНЕКОРРЕКТНЫЙ ВВОД\n\n=============================\n");
            printf("\n\nВыберите функцию, которую хотите применить к массиву\n\n0 - num_plus_322\n1 - num_negative\n2 - num_minus_2\n3 - square\n4 - square_square\n\nВведите номер действия: ");

            check_scanf = scanf("%d", &flag);
            while ((a = getchar()) != '\n');

        }

        switch (flag){

            case 0:
                new_arr = map(num_plus_322, arr, &error);
                break;
        
            case 1:
                new_arr = map(num_negative, arr, &error);
                break;

            case 2:
                new_arr = map(num_minus_2, arr, &error);
                break;

            case 3:
                new_arr = map(square, arr, &error);
                break;

            case 4:
                new_arr = map(square_square, arr, &error);
                break;

            default:
                break;
        }

        printf("\n\nТекущий массив: [ ");

        for (size_t i = 0; i < new_arr->size; ++i){

            if (i != new_arr->size - 1){

                printf("%.9f; ", *(double*)get_elem(new_arr, i, &error));

            }
            else{

                printf("%.9f ]", *(double*)get_elem(new_arr, i, &error));

            }

        }

        printf(" ]\n\n");       

    }
    else if (arr->type == get_func_info()){

        printf("\n\nВыберите функцию, которую хотите применить к массиву\n\n0 - do_nothing\n1 - to_square_func\n2 - to_num_negative_func\n3 - to_num_minus_2_func\n\nВведите номер действия: ");

        int check_scanf = scanf("%d", &flag);
        while ((a = getchar()) != '\n');
        
        while ((check_scanf != 1) || ((flag != 0) && (flag != 1) && (flag != 2) && (flag != 3))){

            printf("\n\nНЕКОРРЕКТНЫЙ ВВОД\n\n=============================\n");
            printf("\n\nВыберите функцию, которую хотите применить к массиву\n\n0 - do_nothing\n1 - to_square_func\n2 - to_num_negative_func\n3 - to_num_minus_2_func\n\nВведите номер действия: ");

            check_scanf = scanf("%d", &flag);
            while ((a = getchar()) != '\n');

        }

        switch (flag){

            case 0:
                new_arr = map(do_nothing, arr, &error);
                break;
        
            case 1:
                new_arr = map(to_square_func, arr, &error);
                break;

            case 2:
                new_arr = map(to_num_negative_func, arr, &error);
                break;

            case 3:
                new_arr = map(to_num_minus_2_func, arr, &error);
                break;

            default:
                break;
        }        
    }
    else{

        printf("\n\nМассив неизвестного типа, MAP не была применена\n\n");
        return NULL;

    }

    if (error == OK){
        
        printf("\n\nMAP успешно применена\n\n");
        return new_arr;

    }
    else{

        printf("\n\nПроизошла подозрительно удивительная ошибка при применении MAP\n\n");

        return NULL;
    }

}

dynamic_arr_t* do_where_console(dynamic_arr_t *arr){

    int flag, a;
    error_code error;
    dynamic_arr_t *new_arr = NULL;

    if (arr == NULL){

        printf("\n\nПрименить WHERE невозможно, массив еще не создан\n\n");

        return NULL;
    }

    if (arr->type == get_double_info()){

        printf("\n\nВыберите функцию(фильтр), который хотите применить к массиву\n\n0 - is_less_than_ten\n1 - perfect_man_height\n2 - is_more_than_ten\n\nВведите номер действия: ");

        int check_scanf = scanf("%d", &flag);
        while ((a = getchar()) != '\n');
        
        while ((check_scanf != 1) || ((flag != 0) && (flag != 1) && (flag != 2))){

            printf("\n\nНЕКОРРЕКТНЫЙ ВВОД\n\n=============================\n");
            printf("\n\nВыберите функцию(фильтр), который хотите применить к массиву\n\n0 - is_less_than_ten\n1 - perfect_man_height\n2 - is_more_than_ten\n\nВведите номер действия: ");

            check_scanf = scanf("%d", &flag);
            while ((a = getchar()) != '\n');

        }

        switch (flag){

            case 0:
                new_arr = where(is_less_than_ten, arr, &error);
                break;
        
            case 1:
                new_arr = where(perfect_man_height, arr, &error);
                break;

            case 2:
                new_arr = where(is_more_than_ten, arr, &error);
                break;
            
            default:
                break;
        }
    }
    else if (arr->type == get_func_info()){

        printf("\n\nВыберите функцию, которую хотите применить к массиву\n\n0 - is_square\n1 - is_square_square\n\nВведите номер действия: ");

        int check_scanf = scanf("%d", &flag);
        while ((a = getchar()) != '\n');
        
        while ((check_scanf != 1) || ((flag != 0) && (flag != 1))){

            printf("\n\nНЕКОРРЕКТНЫЙ ВВОД\n\n=============================\n");
            printf("\n\nВыберите функцию, которую хотите применить к массиву\n\n0 - is_square\n1 - is_square_square\n\nВведите номер действия: ");

            check_scanf = scanf("%d", &flag);
            while ((a = getchar()) != '\n');

        }

        switch (flag){

            case 0:
                new_arr = where(is_square, arr, &error);
                break;
        
            case 1:
                new_arr = where(is_square_square, arr, &error);
                break;

            default:
                break;
        }        
    }
    else{

        printf("\n\nМассив неизвестного типа, WHERE не была применена\n\n");
        return NULL;

    }

    if (error == OK){
            
        printf("\n\nWHERE успешно применена\n\n");
        if (arr->type == get_double_info()){

            printf("\n\nТекущий массив: [ ");

            for (size_t i = 0; i < new_arr->size; ++i){

                if (i != new_arr->size - 1){

                    printf("%.9f; ", *(double*)get_elem(new_arr, i, &error));

                }
                else{

                    printf("%.9f ]", *(double*)get_elem(new_arr, i, &error));

                }

            }

            printf(" ]\n\n");

        }
        
        return new_arr;

    }
    else{

        printf("\n\nПроизошла подозрительно удивительная ошибка при применении WHERE\n\n");

        return NULL;
    }

}

dynamic_arr_t *do_concatenate_console(){

    int flag, a;
    error_code error;
    dynamic_arr_t *arr1, *arr2, *res_arr;

    printf("\n\nКакого типа массивы хотите конкатенировать?\n\n0 - double\n1 - function\n\nВведите номер действия: ");
        
    int check_scanf = scanf("%d", &flag);
    while ((a = getchar()) != '\n');
    
    while ((check_scanf != 1) || ((flag != 0) && (flag != 1))){

        printf("\n\nНЕКОРРЕКТНЫЙ ВВОД\n\n=============================\n");
        printf("\n\nКакого типа массивы хотите конкатенировать?\n\n0 - double\n1 - function\n\nВведите номер действия: ");

        check_scanf = scanf("%d", &flag);
        while ((a = getchar()) != '\n');

    }

    if (flag == 0){

        arr1 = create_double_array_console();

        printf("\n\nПервый массив создан, заполните второй: \n\n");

        arr2 = create_double_array_console();
        res_arr = concatenate(arr1, arr2, &error);

    }
    else{

        arr1 = create_func_array_console();
        printf("\n\nПервый массив создан, заполните второй: \n\n");
        arr2 = create_func_array_console();
        res_arr = concatenate(arr1, arr2, &error);        

    }

    if (error == OK){

        printf("\n\nCONCATENATE успешно применена\n\n");

        if (flag == 0){

            printf("\n\nТекущий массив: [ ");

            for (size_t i = 0; i < res_arr->size; ++i){

                if (i != res_arr->size - 1){

                    printf("%.9f; ", *(double*)get_elem(res_arr, i, &error));

                }
                else{

                    printf("%.9f", *(double*)get_elem(res_arr, i, &error));

                }

            }

            printf(" ]\n\n");

        }

        return res_arr;

    }
    else{

        printf("\n\nПроизошла подозрительно удивительная ошибка при применении CONCATENATE\n\n");

        return NULL;

    }
    
}

dynamic_arr_t* do_interface(){

    dynamic_arr_t *arr = NULL;

    int type;
    int flag = choose_action();

    while (flag != 4){

        switch (flag){

            case 0:
                type = choose_array_type();

                if (type == 0){

                    arr = create_func_array_console();

                }
                else{

                    arr = create_double_array_console();

                }

                break;
            
            case 1:
                arr = do_map_console(arr);
                break;

            case 2:
                arr = do_where_console(arr);
                break;

            case 3:
                arr = do_concatenate_console();
                break;
        }

        flag = choose_action();

    }
    
    return arr;

}
///доделать выбор ф-ций ++++++++
//доделать визуализацию функций
//gcc main.c console_interface.c dynamic_array.c dynamic_arr_operations.c field_info.c checker_printf.c test.c -o a.exe 