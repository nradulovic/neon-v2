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

#include "test_nk_arch.h"

#include <stddef.h>

#include "nk_arch.h"
#include "ntestsuite.h"

static void test_none_exp2_0(void)
{
    NTESTSUITE_EXPECT_UINT(0x01u);
    NTESTSUITE_ACTUAL_UINT(nk_arch_exp2(0));
}

static void test_none_exp2_1(void)
{
    NTESTSUITE_EXPECT_UINT(0x02u);
    NTESTSUITE_ACTUAL_UINT(nk_arch_exp2(1));
}

static void test_none_exp2_7(void)
{
    NTESTSUITE_EXPECT_UINT(0x80u);
    NTESTSUITE_ACTUAL_UINT(nk_arch_exp2(7));
}

static void test_none_exp2_31(void)
{
    NTESTSUITE_EXPECT_UINT(0x80000000);
    NTESTSUITE_ACTUAL_UINT(nk_arch_exp2(31));
}

static void test_none_log2_1(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    NTESTSUITE_ACTUAL_UINT(nk_arch_log2(0x01));
}

static void test_none_log2_3(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    NTESTSUITE_ACTUAL_UINT(nk_arch_log2(0x03));
}

static void test_none_log2_UINT8_MAX(void)
{
    NTESTSUITE_EXPECT_UINT(7);
    NTESTSUITE_ACTUAL_UINT(nk_arch_log2(0xff));
}

static void test_none_log2_UINT16_MAX(void)
{
    NTESTSUITE_EXPECT_UINT(15);
    NTESTSUITE_ACTUAL_UINT(nk_arch_log2(0xffff));
}

static void test_none_log2_UINT32_MAX(void)
{
    NTESTSUITE_EXPECT_UINT(31);
    NTESTSUITE_ACTUAL_UINT(nk_arch_log2(0xffffffff));
}

void test_nk_arch(void)
{
    static const struct nk_testsuite_test tests[] = {
    		NK_TESTSUITE_TEST(test_none_exp2_0),
			NK_TESTSUITE_TEST(test_none_exp2_1),
			NK_TESTSUITE_TEST(test_none_exp2_7),
			NK_TESTSUITE_TEST(test_none_exp2_31),
			NK_TESTSUITE_TEST(&test_none_log2_1),
			NK_TESTSUITE_TEST(&test_none_log2_3),
			NK_TESTSUITE_TEST(&test_none_log2_UINT8_MAX),
			NK_TESTSUITE_TEST(&test_none_log2_UINT16_MAX),
			NK_TESTSUITE_TEST(&test_none_log2_UINT32_MAX),
			NK_TESTSUITE_TEST_TERMINATE()
    };

    nk_testsuite_set_fixture(NULL, NULL, NK_TESTSUITE_FIXTURE_NAME(none));
    nk_testsuite_run_tests(tests);
}


