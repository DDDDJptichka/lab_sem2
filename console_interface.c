#include <stdlib.h>
#include "checker.h"
#include "dynamic_array.h"
#include "dynamic_arr_operations.h"
#include "field_info.h"
#include "func.h"

int dialoge(){

    int flag;

    flag = 0;

    //dynamic_arr_t *arr = create_arr();

    printf("=======================================================================================\n"
        "\t\t\tХотите записать элемент в массив?\n"
        "\t\t\t\t0 - нет       1 - да \n\n");

    int check_scanf = scanf("%d", &flag);
    getchar();

    while ((check_scanf != 1) || ((flag != 1) && (flag != 0))){
        
        printf("Некорректный ввод!\n\n=======================================================================================\n"
            "\t\t\tХотите записать элемент в массив?\n" 
            "\t\t\t\t0 - нет       1 - да \n\n");
            
        check_scanf = scanf("%d", &flag);
        getchar();        

    }

    
    return OK;
}