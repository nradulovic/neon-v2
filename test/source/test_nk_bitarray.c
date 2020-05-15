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
#include <string.h>

#include "test_nk_bitarray.h"
#include "nk_bitarray.h"
#include "ntestsuite.h"

static struct my_bitarray NK_BITARRAY__DEFINITE(32) g_instance;

#define MY_BIG_BITARRAY_SIZE 			256u

static struct my_big_bitarray NK_BITARRAY__DEFINITE(MY_BIG_BITARRAY_SIZE) g_big_instance;

static void test_none_init(void)
{
    struct my_other_bitarray NK_BITARRAY__DEFINITE(45) a_instance;

    /* NOTE:
     * Compile time test only. Ensure that the expected is equal to actual
     * value.
     */
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(true);
    NK_BITARRAY__DEFINITE_INIT(&a_instance);
}

static void test_empty_set_0(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 0u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_instance));
}

static void test_empty_set_get_1(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_instance));
}

static void test_empty_set_get_31(void)
{
    NTESTSUITE_EXPECT_UINT(31);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_instance));
}

static void test_empty_set_m_0(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 0u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_instance));
}

static void test_empty_set_m_1(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_instance));
}

static void test_empty_set_m_31(void)
{
    NTESTSUITE_EXPECT_UINT(31);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_instance));
}

static void test_empty_set_clr_get_1(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 1u);
    NK_BITARRAY__DEFINITE_CLEAR(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_instance));
}

static void test_empty_set_clr_get_31(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 31u);
    NK_BITARRAY__DEFINITE_CLEAR(&g_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_instance));
}

static void test_empty_set_clr_get_31_m(void)
{
    NTESTSUITE_EXPECT_UINT(31);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_instance, 31u);
    NK_BITARRAY__DEFINITE_CLEAR(&g_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_instance));
}

static void test_big_empty_set_0(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_get_1(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_get_31(void)
{
    NTESTSUITE_EXPECT_UINT(31);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_get_32(void)
{
    NTESTSUITE_EXPECT_UINT(32);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 32u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_get_MAX(void)
{
    NTESTSUITE_EXPECT_UINT(MY_BIG_BITARRAY_SIZE - 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, MY_BIG_BITARRAY_SIZE - 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_m_0(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_m_1(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_m_31(void)
{
    NTESTSUITE_EXPECT_UINT(31);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_m_32(void)
{
    NTESTSUITE_EXPECT_UINT(32);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 32u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_m_MAX(void)
{
    NTESTSUITE_EXPECT_UINT(MY_BIG_BITARRAY_SIZE - 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, MY_BIG_BITARRAY_SIZE - 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_clr_get_1(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NK_BITARRAY__DEFINITE_CLEAR(&g_big_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_clr_get_31(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 31u);
    NK_BITARRAY__DEFINITE_CLEAR(&g_big_instance, 31u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_clr_get_32(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 32u);
    NK_BITARRAY__DEFINITE_CLEAR(&g_big_instance, 32u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_clr_get_MAX(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, MY_BIG_BITARRAY_SIZE - 1u);
    NK_BITARRAY__DEFINITE_CLEAR(&g_big_instance, MY_BIG_BITARRAY_SIZE - 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_clr_get_31_m(void)
{
    NTESTSUITE_EXPECT_UINT(31);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 31u);
    NK_BITARRAY__DEFINITE_CLEAR(&g_big_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_clr_get_32_m(void)
{
    NTESTSUITE_EXPECT_UINT(32);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 32u);
	NK_BITARRAY__DEFINITE_CLEAR(&g_big_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void test_big_empty_set_clr_get_MAX_m(void)
{
    NTESTSUITE_EXPECT_UINT(MY_BIG_BITARRAY_SIZE - 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 0u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, 1u);
    NK_BITARRAY__DEFINITE_SET(&g_big_instance, MY_BIG_BITARRAY_SIZE - 1u);
	NK_BITARRAY__DEFINITE_CLEAR(&g_big_instance, 1u);
    NTESTSUITE_ACTUAL_UINT(NK_BITARRAY__DEFINITE_MSBS(&g_big_instance));
}

static void setup_empty(void)
{
	memset(&g_instance, 0, sizeof(g_instance));
	NK_BITARRAY__DEFINITE_INIT(&g_instance);
}

static void setup_big_empty(void)
{
	memset(&g_big_instance, 0, sizeof(g_big_instance));
	NK_BITARRAY__DEFINITE_INIT(&g_big_instance);
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

static void test_nbits_bitarray_big_empty(void)
{
	static const struct nk_testsuite_test big_empty_tests[] =
	{
		NK_TESTSUITE_TEST(test_big_empty_set_0),
		NK_TESTSUITE_TEST(test_big_empty_set_get_1),
		NK_TESTSUITE_TEST(test_big_empty_set_get_31),
		NK_TESTSUITE_TEST(test_big_empty_set_get_32),
		NK_TESTSUITE_TEST(test_big_empty_set_get_MAX),
		NK_TESTSUITE_TEST(test_big_empty_set_m_0),
		NK_TESTSUITE_TEST(test_big_empty_set_m_1),
		NK_TESTSUITE_TEST(test_big_empty_set_m_31),
		NK_TESTSUITE_TEST(test_big_empty_set_m_32),
		NK_TESTSUITE_TEST(test_big_empty_set_m_MAX),
		NK_TESTSUITE_TEST(test_big_empty_set_clr_get_1),
		NK_TESTSUITE_TEST(test_big_empty_set_clr_get_31),
		NK_TESTSUITE_TEST(test_big_empty_set_clr_get_32),
		NK_TESTSUITE_TEST(test_big_empty_set_clr_get_MAX),
		NK_TESTSUITE_TEST(test_big_empty_set_clr_get_31_m),
		NK_TESTSUITE_TEST(test_big_empty_set_clr_get_32_m),
		NK_TESTSUITE_TEST(test_big_empty_set_clr_get_MAX_m),
		NK_TESTSUITE_TEST_TERMINATE()
	};

	nk_testsuite_set_fixture(
			setup_big_empty, NULL, NK_TESTSUITE_FIXTURE_NAME(big_empty));
	nk_testsuite_run_tests(big_empty_tests);
}

void test_nk_bitarray(void)
{
	test_nbits_bitarray_none();
	test_nbits_bitarray_empty();
	test_nbits_bitarray_big_empty();
}


