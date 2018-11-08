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

#define TEST_DISABLE_DEBUG

#include <string.h>
#include "testsuite/ntestsuite.h"
#include "debug/ndebug.h"
#include "main.h"

#define narch_cpu_stop()        g_cpu_state_output = false

static bool g_cpu_state_output;

NTESTSUITE_TEST(test_empty_obligation)
{
    uint32_t n = 5;

    NTESTSUITE_EXPECT_UINT(5);
    NOBLIGATION(n = 1);
    NTESTSUITE_ACTUAL_UINT(n);
}

NTESTSUITE_TEST(test_empty_assert)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NASSERT(true);
    NTESTSUITE_ACTUAL_BOOL(g_cpu_state_output);
}

NTESTSUITE_TEST(test_empty_require)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NREQUIRE(true);
    NTESTSUITE_ACTUAL_BOOL(g_cpu_state_output);
}

NTESTSUITE_TEST(test_empty_ensure)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NENSURE(true);
    NTESTSUITE_ACTUAL_BOOL(g_cpu_state_output);
}

NTESTSUITE_TEST(test_empty_internal)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NASSERT_INTERNAL(true);
    NTESTSUITE_ACTUAL_BOOL(g_cpu_state_output);
}

NTESTSUITE_TEST(test_empty_f_assert)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NASSERT(false);
    NTESTSUITE_ACTUAL_BOOL(g_cpu_state_output);
}

NTESTSUITE_TEST(test_empty_f_require)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NREQUIRE(false);
    NTESTSUITE_ACTUAL_BOOL(g_cpu_state_output);
}

NTESTSUITE_TEST(test_empty_f_ensure)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NENSURE(false);
    NTESTSUITE_ACTUAL_BOOL(g_cpu_state_output);
}

NTESTSUITE_TEST(test_empty_f_internal)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NASSERT_INTERNAL(false);
    NTESTSUITE_ACTUAL_BOOL(g_cpu_state_output);
}

static void setup_empty(void)
{
    g_cpu_state_output = true;
}

void test_exec(void)
{
    NTESTSUITE_FIXTURE(empty, setup_empty, NULL);
    NTESTSUITE_RUN(empty, test_empty_obligation);
    NTESTSUITE_RUN(empty, test_empty_assert);
    NTESTSUITE_RUN(empty, test_empty_require);
    NTESTSUITE_RUN(empty, test_empty_ensure);
    NTESTSUITE_RUN(empty, test_empty_internal);
    NTESTSUITE_RUN(empty, test_empty_f_assert);
    NTESTSUITE_RUN(empty, test_empty_f_require);
    NTESTSUITE_RUN(empty, test_empty_f_ensure);
    NTESTSUITE_RUN(empty, test_empty_f_internal);
    NTESTSUITE_PRINT_RESULTS(empty);   
}


