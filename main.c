#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include "test.h"
#include "checker.h"
#include "dynamic_arr_operations.h"
#include "dynamic_array.h"
#include "func.h"
#include "console_interface.h"

int main(){
    
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    dynamic_arr_t *arr = do_interface();

    return 0;
}

//gcc test.c console_interface.c dynamic_array.c dynamic_arr_operations.c field_info.c checker_printf.c assertions.c -o test.exe