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

#define NK_DEBUG__IS_ENABLED 1

#include "test_nk_debug_enabled.h"

#include <stdint.h>

#include "nk_debug.h"
#include "ntestsuite.h"

#if (NK_DEBUG__IS_ENABLED != 1)
#error "Failed to enable debug for this translation module."
#endif

/*
 * Override assert macro in C standard assert.h and set g_assert_state to
 * expression evaluation result. If this macro is not overridden then the
 * execution would stop at test code.
 */
#undef assert
#define assert(expression)          g_assert_state = (!!(expression))

static int g_assert_state;

static void test_empty_obligation(void)
{
    uint32_t n = 0;

    NTESTSUITE_EXPECT_UINT(1);
    NK_DEBUG__OBLIGATION(n = 1);
    NTESTSUITE_ACTUAL_UINT(n);
}

static void test_empty_require(void)
{
    NTESTSUITE_EXPECT_INT(1);
    NK_DEBUG__REQUIRE(true);
    NTESTSUITE_ACTUAL_INT(g_assert_state);
}

static void test_empty_ensure(void)
{
    NTESTSUITE_EXPECT_INT(1);
    NK_DEBUG__ENSURE(true);
    NTESTSUITE_ACTUAL_INT(g_assert_state);
}

static void test_empty_internal(void)
{
    NTESTSUITE_EXPECT_INT(1);
    NK_DEBUG__ASSERT(true);
    NTESTSUITE_ACTUAL_INT(g_assert_state);
}

static void test_empty_f_require(void)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NK_DEBUG__REQUIRE(false);
    NTESTSUITE_ACTUAL_INT(g_assert_state);
}

static void test_empty_f_ensure(void)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NK_DEBUG__ENSURE(false);
    NTESTSUITE_ACTUAL_INT(g_assert_state);
}

static void test_empty_f_internal(void)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NK_DEBUG__ASSERT(false);
    NTESTSUITE_ACTUAL_INT(g_assert_state);
}

static void setup_empty(void)
{
    g_assert_state = -1;
}

void test_nk_debug_enabled(void)
{
	static const struct nk_testsuite_test tests_empty[] =
	{
		NK_TESTSUITE_TEST(test_empty_obligation),
		NK_TESTSUITE_TEST(test_empty_require),
		NK_TESTSUITE_TEST(test_empty_ensure),
		NK_TESTSUITE_TEST(test_empty_internal),
		NK_TESTSUITE_TEST(test_empty_f_require),
		NK_TESTSUITE_TEST(test_empty_f_ensure),
		NK_TESTSUITE_TEST(test_empty_f_internal),
		NK_TESTSUITE_TEST_TERMINATE()
	};

	nk_testsuite_set_fixture(
			setup_empty, NULL, NK_TESTSUITE_FIXTURE_NAME(empty));
	nk_testsuite_run_tests(tests_empty);
}


