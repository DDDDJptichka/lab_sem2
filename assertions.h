#pragma once

#include <math.h>

#define ASSERT(expr) \
    do { \
        if (expr) \
            assert_success(__LINE__); \
        else { \
            assert_fail(__LINE__); \
            return; \
        } \
    } while (0)

#define ASSERT_EQ(expr, expected) \
    do { \
        if ((expr) == (expected)) \
            assert_success(__LINE__); \
        else { \
            assert_fail(__LINE__); \
            return; \
        } \
    } while (0)

#define ASSERT_DOUBLE_EQ(a, b) \
    do { \
        if (fabs((a) - (b)) < (1e-9)) \
            assert_success(__LINE__); \
        else { \
            assert_fail(__LINE__); \
            return; \
        } \
    } while (0)

#define ASSERT_NULL(arr) \
    do { \
        if ((arr) == NULL) \
            assert_success(__LINE__); \
        else { \
            assert_fail(__LINE__); \
            return; \
        } \
    } while (0)

#define ASSERT_NOT_NULL(arr) \
    do { \
        if ((arr) != NULL) \
            assert_success(__LINE__); \
        else { \
            assert_fail(__LINE__); \
            return; \
        } \
    } while (0)

    
void assert_success(int number);

void assert_fail(int number);

int success_result();

int fail_result();