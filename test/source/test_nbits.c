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

#include "test_nbits.h"

#include <stdint.h>
#include <stddef.h>

#include "nbits.h"
#include "ntestsuite.h"

static void test_none_array_size(void)
{
    char small_array[1];
    char big_array[10];

    NTESTSUITE_EXPECT_UINT(1);
    NTESTSUITE_ACTUAL_UINT(NBITS_ARRAY_SIZE(small_array));

    NTESTSUITE_EXPECT_UINT(10);
    NTESTSUITE_ACTUAL_UINT(NBITS_ARRAY_SIZE(big_array));
}

static void test_none_bit_size(void)
{
    uint8_t small_var;
    uint32_t big_var;
    
    NTESTSUITE_EXPECT_UINT(8);
    NTESTSUITE_ACTUAL_UINT(NBITS_BIT_SIZE(small_var));

    NTESTSUITE_EXPECT_UINT(32);
    NTESTSUITE_ACTUAL_UINT(NBITS_BIT_SIZE(big_var));
}

static void test_none_divide_round(void)
{
    NTESTSUITE_EXPECT_UINT(15);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUND(15, 1));

    NTESTSUITE_EXPECT_UINT(5);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUND(27, 5));

    NTESTSUITE_EXPECT_UINT(6);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUND(28, 5));
}

static void test_none_divide_roundup(void)
{
    NTESTSUITE_EXPECT_UINT(15);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUNDUP(15, 1));

    NTESTSUITE_EXPECT_UINT(6);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUNDUP(27, 5));

    NTESTSUITE_EXPECT_UINT(6);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUNDUP(28, 5));
}

static void test_none_align(void)
{
    NTESTSUITE_EXPECT_UINT(148);
    NTESTSUITE_ACTUAL_UINT(NBITS_ALIGN(149, 4));
}

static void test_none_alignup(void)
{
    NTESTSUITE_EXPECT_UINT(152);
    NTESTSUITE_ACTUAL_UINT(NBITS_ALIGN_UP(149, 4));
}

static void test_none_log2_0(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(0));
}

static void test_none_log2_x(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(1));

    NTESTSUITE_EXPECT_UINT(1);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(2));

    NTESTSUITE_EXPECT_UINT(2);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(4));

    NTESTSUITE_EXPECT_UINT(3);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(8));

    NTESTSUITE_EXPECT_UINT(4);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(16));

    NTESTSUITE_EXPECT_UINT(5);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(32));

    NTESTSUITE_EXPECT_UINT(6);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(64));
}

static void test_none_log2_UINT32_MAX(void)
{
    NTESTSUITE_EXPECT_UINT(7);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(UINT32_MAX));
}

static void test_none_is_powerof2_0(void)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(NBITS_IS_POWEROF2(0));
}

static void test_none_is_powerof2_1(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(NBITS_IS_POWEROF2(1));
}

static void test_none_is_powerof2_4(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(NBITS_IS_POWEROF2(4));
}

void test_nbits(void)
{
	static const struct nk_testsuite_test none_tests[] =
	{
		NK_TESTSUITE_TEST(test_none_array_size),
		NK_TESTSUITE_TEST(test_none_bit_size),
		NK_TESTSUITE_TEST(test_none_divide_round),
		NK_TESTSUITE_TEST(test_none_divide_roundup),
		NK_TESTSUITE_TEST(test_none_align),
		NK_TESTSUITE_TEST(test_none_alignup),
		NK_TESTSUITE_TEST(test_none_log2_0),
		NK_TESTSUITE_TEST(test_none_log2_x),
		NK_TESTSUITE_TEST(test_none_log2_UINT32_MAX),
		NK_TESTSUITE_TEST(test_none_is_powerof2_0),
		NK_TESTSUITE_TEST(test_none_is_powerof2_1),
		NK_TESTSUITE_TEST(test_none_is_powerof2_4),
		NK_TESTSUITE_TEST_TERMINATE()
	};
    nk_testsuite_set_fixture(NULL, NULL, NK_TESTSUITE_FIXTURE_NAME(none));
    nk_testsuite_run_tests(none_tests);
}


