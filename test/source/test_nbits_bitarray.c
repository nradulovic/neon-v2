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

#include "test_nbits_bitarray.h"
#include "nbits_bitarray.h"
#include "ntestsuite.h"

static struct nbitarray g_instance;

static void test_none_init(void)
{
    struct nbitarray a_instance;

    /* NOTE:
     * Compile time test only. Ensure that the expected is equal to actual
     * value.
     */
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(true);
    nbitarray_init(&a_instance);
}

static void test_empty_set_0(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    nbitarray_set(&g_instance, 0u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
}

static void test_empty_set_get_1(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    nbitarray_set(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
}

static void test_empty_set_get_31(void)
{
    NTESTSUITE_EXPECT_UINT(31);
    nbitarray_set(&g_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
}

static void test_empty_set_m_0(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 0u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
}

static void test_empty_set_m_1(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
}

static void test_empty_set_m_31(void)
{
    NTESTSUITE_EXPECT_UINT(31);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 1u);
    nbitarray_set(&g_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
}

static void test_empty_set_clr_get_1(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 1u);
    nbitarray_clear(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
}

static void test_empty_set_clr_get_31(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 1u);
    nbitarray_set(&g_instance, 31u);
    nbitarray_clear(&g_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
}

static void test_empty_set_clr_get_31_m(void)
{
    NTESTSUITE_EXPECT_UINT(31);
    nbitarray_set(&g_instance, 0u);
    nbitarray_set(&g_instance, 1u);
    nbitarray_set(&g_instance, 31u);
    nbitarray_clear(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(nbitarray_msbs(&g_instance));
}

static void setup_empty(void)
{
    nbitarray_init(&g_instance);
}

static void test_nbits_bitarray_none()
{
	static const struct nk_testsuite_test none_tests[] =
	{
		NK_TESTSUITE_TEST(test_none_init),
		NK_TESTSUITE_TEST_TERMINATE()
	};

	nk_testsuite_set_fixture(NULL, NULL, NK_TESTSUITE_FIXTURE_NAME(none));
	nk_testsuite_run_tests(none_tests);
}

static void test_nbits_bitarray_empty(void)
{
	static const struct nk_testsuite_test empty_tests[] =
	{
		NK_TESTSUITE_TEST(test_empty_set_0),
		NK_TESTSUITE_TEST(test_empty_set_get_1),
		NK_TESTSUITE_TEST(test_empty_set_get_31),
		NK_TESTSUITE_TEST(test_empty_set_m_0),
		NK_TESTSUITE_TEST(test_empty_set_m_1),
		NK_TESTSUITE_TEST(test_empty_set_m_31),
		NK_TESTSUITE_TEST(test_empty_set_clr_get_1),
		NK_TESTSUITE_TEST(test_empty_set_clr_get_31),
		NK_TESTSUITE_TEST(test_empty_set_clr_get_31_m),
		NK_TESTSUITE_TEST_TERMINATE()
	};

	nk_testsuite_set_fixture(
			setup_empty, NULL, NK_TESTSUITE_FIXTURE_NAME(empty));
	nk_testsuite_run_tests(empty_tests);
}

void test_nbits_bitarray(void)
{
	test_nbits_bitarray_none();
	test_nbits_bitarray_empty();
}

