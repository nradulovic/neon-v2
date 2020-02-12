/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */

#include <stddef.h>
#include <stdint.h>

#include "../testsuite/ntestsuite.h"
#include "core/nbitarray.h"
#include "core/nport.h"
#include "test_nbitarray.h"

NTESTSUITE_TEST(test_none_array_instance)
{
    struct nbitarray(20) my_array;

    NPLATFORM_UNUSED_ARG(my_array);
}

NTESTSUITE_TEST(test_none_init)
{
    struct nbitarray(20) my_array;

    NBITARRAY_INIT(&my_array);
}

NTESTSUITE_TEST(test_none_is_empty)
{
    struct nbitarray(20) my_array;

    NBITARRAY_INIT(&my_array);

    ntestsuite_expect_bool(true);
    ntestsuite_actual_bool(NBITARRAY_IS_EMPTY(&my_array));
}

NTESTSUITE_TEST(test_none_is_not_empty)
{
    struct nbitarray(20) my_array;

    NBITARRAY_INIT(&my_array);
    NBITARRAY_SET(&my_array, 1);

    ntestsuite_expect_bool(false);
    ntestsuite_actual_bool(NBITARRAY_IS_EMPTY(&my_array));
}

NTESTSUITE_TEST(test_none_set_1_and_clear_1)
{
    struct nbitarray(20) my_array;

    NBITARRAY_INIT(&my_array);
    NBITARRAY_SET(&my_array, 1);
    NBITARRAY_CLEAR(&my_array, 1);

    ntestsuite_expect_bool(true);
    ntestsuite_actual_bool(NBITARRAY_IS_EMPTY(&my_array));
}

NTESTSUITE_TEST(test_none_set_1_and_clear_2)
{
    struct nbitarray(20) my_array;

    NBITARRAY_INIT(&my_array);
    NBITARRAY_SET(&my_array, 1);
    NBITARRAY_CLEAR(&my_array, 2);

    ntestsuite_expect_bool(false);
    ntestsuite_actual_bool(NBITARRAY_IS_EMPTY(&my_array));
}

void test_exec_nbitarray(void)
{
    ntestsuite_set_fixture(none, NULL, NULL);
    ntestsuite_run(test_none_array_instance);
    ntestsuite_run(test_none_init);
    ntestsuite_run(test_none_is_empty);
    ntestsuite_run(test_none_is_not_empty);
    ntestsuite_run(test_none_set_1_and_clear_1);
    ntestsuite_run(test_none_set_1_and_clear_2);
}
