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
#include "test_ndebug_disabled.h"

#if (NDEBUG_IS_ENABLED == 1)
#error "Failed to disable debug for this translation module."
#endif

#define EXPECT(a_cpu_state)                                                 \
    do {                                                                    \
        g_expected_cpu_state = (a_cpu_state);                               \
    } while (0)

#define EVALUATE()                                                          \
    do {                                                                    \
        NTESTSUITE_ASSERT_EQUAL_BOOL(g_expected_cpu_state,                  \
                g_cpu_state_output);                                        \
    } while (0)

#define narch_cpu_stop()        g_cpu_state_output = false

static void test_obligation(void);
static void test_assert(void);
static void test_require(void);
static void test_ensure(void);
static void test_internal(void);

static bool g_cpu_state_output;
static bool g_expected_cpu_state;

static void test_obligation(void)
{
    uint32_t n = 0;

    NOBLIGATION(n = 1);
    NTESTSUITE_ASSERT_EQUAL_INT(0, n);
}

static void test_assert(void)
{
    EXPECT(true);
    NASSERT(true);
    EVALUATE();
}

static void test_require(void)
{
    EXPECT(true);
    NREQUIRE(true);
    EVALUATE();
}

static void test_ensure(void)
{
    EXPECT(true);
    NENSURE(true);
    EVALUATE();
}

static void test_internal(void)
{
    EXPECT(true);
    NASSERT_INTERNAL(true);
    EVALUATE();
}

static void test_f_assert(void)
{
    EXPECT(true);
    NASSERT(false);
    EVALUATE();
}

static void test_f_require(void)
{
    EXPECT(true);
    NREQUIRE(false);
    EVALUATE();
}

static void test_f_ensure(void)
{
    EXPECT(true);
    NENSURE(false);
    EVALUATE();
}

static void test_f_internal(void)
{
    EXPECT(true);
    NASSERT_INTERNAL(false);
    EVALUATE();
}

static void setup_empty(void)
{
    g_cpu_state_output = true;
}

static void teardown_empty(void)
{
}

void test_ndebug_disabled(void)
{
    NTESTSUITE_FIXTURE(empty, setup_empty, teardown_empty);
    NTESTSUITE_RUN(empty, test_obligation);
    NTESTSUITE_RUN(empty, test_assert);
    NTESTSUITE_RUN(empty, test_require);
    NTESTSUITE_RUN(empty, test_ensure);
    NTESTSUITE_RUN(empty, test_internal);
    NTESTSUITE_RUN(empty, test_f_assert);
    NTESTSUITE_RUN(empty, test_f_require);
    NTESTSUITE_RUN(empty, test_f_ensure);
    NTESTSUITE_RUN(empty, test_f_internal);
    NTESTSUITE_PRINT_RESULTS();   
}


