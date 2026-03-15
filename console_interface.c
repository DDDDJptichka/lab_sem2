#include <stdlib.h>
#include <stdio.h>
#include "checker.h"
#include "dynamic_array.h"
#include "dynamic_arr_operations.h"
#include "field_info.h"
#include "func.h"
#include "math.h"

bool is_more_than_ten(void *num){

    double *h = num;

    return ((*h - 10.0) > 0);

}

int choose_action(){

    int flag;

    flag = 0;

    printf("=============================\n"
            "0 - Создать массив(DOUBLE)\n1 - Применить map\n2 - Применить where\n3 - Применить concatenate\n4 - Выход\n\n"
            "-----------------------------\n"
            "Введите номер действия: ");

    int check_scanf = scanf("%d", &flag);

    while ((check_scanf != 1) || ((flag != 0) && (flag != 1) && (flag != 2) && (flag != 3) && (flag != 4))){
        
        printf("\n\nНЕКОРРЕКТНЫЙ ВВВОД\n\n=============================\n"
                "0 - Создать массив(DOUBLE)\n1 - Применить map\n2 - Применить where\n3 - Применить concatenate\n4 - Выход\n\n"
                "-----------------------------\n"
                "Введите номер действия: ");

        check_scanf = scanf("%d", &flag);
        int a;
        while ((a = getchar()) != '\n');

    }
    
    return flag;
}

dynamic_arr_t* create_array_CONSOLE(){

    double element;
    int flag;
    error_code error;
    dynamic_arr_t *arr = create_arr(1, get_double_info(), &error);

    printf("\n\nХотите добавить элемент?\n\n0 - да\n1 - нет\n\n");

    int check_scanf = scanf("%d", &flag);

    while (flag != 1){
        
        while (check_scanf != 1){

            printf("\n\nНЕКОРРЕКТНЫЙ ВВВОД\n\n=============================\n");
            printf("\n\nХотите добавить элемент?\n\n0 - да\n1 - нет\n\n");

            check_scanf = scanf("%d", &flag);
            int a;
            while ((a = getchar()) != '\n');

        }

        if (flag == 0){

            printf("\n\nВведите элемент:   ");
            check_scanf = scanf("%lf", &element);

            while (check_scanf != 1){

                printf("\n\nНЕКОРРЕКТНЫЙ ВВВОД\n\n=============================\n");
                printf("\n\nВведите элемент:   ");

                check_scanf = scanf("%lf", &element);
                int a;
                while ((a = getchar()) != '\n');

            }       

            add_to_arr(arr, &element, &error);

            if (error == OK){
            
                printf("\n\nЭлемент успешно добавлен\n\n");

            }
            else{

                printf("\n\nПроизошла подозрительно удивительная ошибка\n\n");

                return NULL;
            }
        }

        printf("\n\nХотите добавить элемент?\n\n0 - да\n1 - нет\n\n");

        check_scanf = scanf("%d", &flag);
        int a;
        while ((a = getchar()) != '\n');
    }

    return arr;
}

dynamic_arr_t* check_where(dynamic_arr_t *arr, predicate_t pred){

    error_code error;
    
    pred = is_more_than_ten;
    
    dynamic_arr_t *new_arr = where(pred, arr, &error);

    printf("\n\nЭлемент массива, большие, чем 10:  ");

    for (size_t i = 0; i < new_arr->size; ++i){

        double x = *(double*)get_elem(new_arr, i, &error);
        if (error == OK){
        
            printf("%lf ", x);

        }
    }

    if (error == OK){

        return new_arr;

    }
    else{

        return NULL;

    }


    ///доделать выбор ф-ций
}