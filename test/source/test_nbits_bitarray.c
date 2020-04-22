/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include "ntestsuite.h"
#include "nbits_bitarray.h"

static struct nbitarray g_instance;

NTESTSUITE_TEST(test_none_init)
{
    struct nbitarray a_instance;

    /* NOTE:
     * Compile time test only. Ensure that the expected is equal to actual
     * value.
     */
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(true);
    nbitarray_init(&a_instance);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_set_0)
{
    NTESTSUITE_EXPECT_UINT(0);
    nbitarray_set(&g_instance, 0u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_set_get_1)
{
    NTESTSUITE_EXPECT_UINT(1);
    nbitarray_set(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_set_get_31)
{
    NTESTSUITE_EXPECT_UINT(31);
    nbitarray_set(&g_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_set_m_0)
{
    NTESTSUITE_EXPECT_UINT(0);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 0u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_set_m_1)
{
    NTESTSUITE_EXPECT_UINT(1);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_set_m_31)
{
    NTESTSUITE_EXPECT_UINT(31);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 1u);
    nbitarray_set(&g_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_set_clr_get_1)
{
    NTESTSUITE_EXPECT_UINT(0);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 1u);
    nbitarray_clear(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_set_clr_get_31)
{
    NTESTSUITE_EXPECT_UINT(1);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 1u);
    nbitarray_set(&g_instance, 31u);
    nbitarray_clear(&g_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_set_clr_get_31_m)
{
    NTESTSUITE_EXPECT_UINT(31);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 1u);
    nbitarray_set(&g_instance, 31u);
    nbitarray_clear(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
    NTESTSUITE_EVALUATE();
}

static void setup_empty(void)
{
    nbitarray_init(&g_instance);
}

void test_nbits_bitarray(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);
    NTESTSUITE_FIXTURE(empty, setup_empty, NULL);

    NTESTSUITE_RUN(none, test_none_init);
    NTESTSUITE_PRINT_RESULTS(none);   

    NTESTSUITE_RUN(empty, test_empty_set_0);
    NTESTSUITE_RUN(empty, test_empty_set_get_1);
    NTESTSUITE_RUN(empty, test_empty_set_get_31);
    NTESTSUITE_RUN(empty, test_empty_set_m_0);
    NTESTSUITE_RUN(empty, test_empty_set_m_1);
    NTESTSUITE_RUN(empty, test_empty_set_m_31);
    NTESTSUITE_RUN(empty, test_empty_set_clr_get_1);
    NTESTSUITE_RUN(empty, test_empty_set_clr_get_31);
    NTESTSUITE_RUN(empty, test_empty_set_clr_get_31_m);
    NTESTSUITE_PRINT_RESULTS(empty);   
}


