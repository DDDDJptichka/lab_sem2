#pragma once

#include <stdbool.h>

typedef void (*func_t)(void *arg);

typedef bool (*predicate_t)(void *arg);

typedef struct Function{
    
    func_t *f;
    const char *func_name;

}function_t;
