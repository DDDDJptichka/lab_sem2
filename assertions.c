#include "stdlib.h"
#include "stdio.h"
#include "assertions.h"

static size_t local_success_count = 0;
static size_t local_fail_count = 0;

void assert_success(int number){

    ++local_success_count;
    printf("TEST ON LINE %d  ----------- OK\n", number);

}

void assert_fail(int number){

    ++local_fail_count;
    printf("TEST ON LINE %d  ----------- FAILED\n", number);

}

int success_result(){

    int success_flag = local_success_count;
    local_success_count = 0;

    return success_flag;

}

int fail_result(){

    int fail_flag = local_fail_count;
    local_fail_count = 0;

    return fail_flag;

}