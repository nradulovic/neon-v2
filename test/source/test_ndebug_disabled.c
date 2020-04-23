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
#include "../../kernel/include/ntestsuite.h"
#include "../../kernel/include/ndebug.h"
#include "../../../nk/test/include/test_ndebug_disabled.h"

#if (NDEBUG_IS_ENABLED == 1)
#error "Failed to disable debug for this translation module."
#endif

#undef assert
#define assert(expression)          g_assert_state = (!!(expression))

static int g_assert_state;

NTESTSUITE_TEST(test_empty_obligation)
{
    uint32_t n = 5;

    NTESTSUITE_EXPECT_UINT(5);
    NOBLIGATION(n = 1);
    NTESTSUITE_ACTUAL_UINT(n);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_require)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NREQUIRE(true);
    NTESTSUITE_ACTUAL_BOOL(g_assert_state);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_ensure)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NENSURE(true);
    NTESTSUITE_ACTUAL_BOOL(g_assert_state);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_internal)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NASSERT_INTERNAL(true);
    NTESTSUITE_ACTUAL_BOOL(g_assert_state);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_f_require)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NREQUIRE(false);
    NTESTSUITE_ACTUAL_BOOL(g_assert_state);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_f_ensure)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NENSURE(false);
    NTESTSUITE_ACTUAL_BOOL(g_assert_state);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_f_internal)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NASSERT_INTERNAL(false);
    NTESTSUITE_ACTUAL_BOOL(g_assert_state);
    NTESTSUITE_EVALUATE();
}

static void setup_empty(void)
{
    g_assert_state = -1;
}

void test_ndebug_disabled(void)
{
    NTESTSUITE_FIXTURE(empty, setup_empty, NULL);
    NTESTSUITE_RUN(empty, test_empty_obligation);
    NTESTSUITE_RUN(empty, test_empty_require);
    NTESTSUITE_RUN(empty, test_empty_ensure);
    NTESTSUITE_RUN(empty, test_empty_internal);
    NTESTSUITE_RUN(empty, test_empty_f_require);
    NTESTSUITE_RUN(empty, test_empty_f_ensure);
    NTESTSUITE_RUN(empty, test_empty_f_internal);
    NTESTSUITE_PRINT_RESULTS(empty);   
}


