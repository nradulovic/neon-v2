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

#include <stdint.h>
#include <stdbool.h>

#include "test_ntask_fiber.h"
#include "ntask_fiber.h"
#include "ntestsuite.h"

static uint8_t g_output;
static bool g_should_stop;

static NFIBER(fiber_empty(struct nfiber *));

static NFIBER(fiber_empty(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    NFIBER_END();
}

static NFIBER(fiber_exit(struct nfiber *));

static NFIBER(fiber_exit(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    g_output = 1u;
    nfiber_exit();
    g_output = 0u;
    NFIBER_END();
}

static NFIBER(fiber_until(struct nfiber *));

static NFIBER(fiber_until(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    for (;;) {
        g_output++;
        nfiber_wait_until(g_output < 3);
    }
    NFIBER_END();
}

static NFIBER(fiber_while(struct nfiber *));

static NFIBER(fiber_while(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    for (;;) {
        nfiber_wait_while(g_output > 2);
        g_output++;
    }
    NFIBER_END();
}

static NFIBER(fiber_yielded_0(struct nfiber *));

static NFIBER(fiber_yielded_0(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    for (;;) {
        g_output++;
        nfiber_yield();
    }
    NFIBER_END();
}

static NFIBER(fiber_yielded_1(struct nfiber *));

static NFIBER(fiber_yielded_1(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    for (;;) {
        nfiber_yield();
    }
    NFIBER_END();
}

static NFIBER(fiber_yielded_2(struct nfiber *));

static NFIBER(fiber_yielded_2(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    for (;;) {
        if (g_output == 3u) {
            g_should_stop = true;
        }
        nfiber_yield();
    }
    NFIBER_END();
}

static NFIBER(fiber_waited_0(struct nfiber *));

static NFIBER(fiber_waited_0(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    g_output++;
    NFIBER_END();
}

static NFIBER(fiber_wait_0(struct nfiber *));

static NFIBER(fiber_wait_0(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    static struct nfiber waited_0;
        
    nfiber_init(&waited_0);
    nfiber_call(fiber_waited_0(&waited_0));
    nfiber_init(&waited_0);
    nfiber_call(fiber_waited_0(&waited_0));
    nfiber_init(&waited_0);
    nfiber_call(fiber_waited_0(&waited_0));
    NFIBER_END();
}

static void test_none_empty(void)
{
    struct nfiber empty;

    NTESTSUITE_EXPECT_UINT(NFIBER_TERMINATED);
    nfiber_init(&empty);
    NTESTSUITE_ACTUAL_UINT(nfiber_dispatch(fiber_empty(&empty)));
}

static void test_none_exit(void)
{
    struct nfiber exit;

    NTESTSUITE_EXPECT_UINT(1u);
    nfiber_init(&exit);
    nfiber_dispatch(fiber_exit(&exit));
    NTESTSUITE_ACTUAL_UINT(g_output);
}

static void test_none_until(void)
{
    struct nfiber until;

    NTESTSUITE_EXPECT_UINT(3u);
    nfiber_init(&until);
    while (nfiber_dispatch(fiber_until(&until)) != NFIBER_WAITING);
    NTESTSUITE_ACTUAL_UINT(g_output);
}

static void test_none_while(void)
{
    struct nfiber while_ctx;

    NTESTSUITE_EXPECT_UINT(3u);
    nfiber_init(&while_ctx);
    while (nfiber_dispatch(fiber_while(&while_ctx)) != NFIBER_WAITING);
    NTESTSUITE_ACTUAL_UINT(g_output);
}

static void test_none_wait(void)
{
    struct nfiber wait;

    NTESTSUITE_EXPECT_UINT(3u);
    nfiber_init(&wait);
    while (nfiber_dispatch(fiber_wait_0(&wait)) != NFIBER_TERMINATED);
    NTESTSUITE_ACTUAL_UINT(g_output);
}

static void test_none_yield(void)
{
    struct nfiber yielded_0;
    struct nfiber yielded_1;
    struct nfiber yielded_2;

    NTESTSUITE_EXPECT_UINT(3u);
    nfiber_init(&yielded_0);
    nfiber_init(&yielded_1);
    nfiber_init(&yielded_2);
    g_should_stop = false;
        
    while (!g_should_stop) {
        nfiber_dispatch(fiber_yielded_0(&yielded_0));
        nfiber_dispatch(fiber_yielded_1(&yielded_1));
        nfiber_dispatch(fiber_yielded_2(&yielded_2));
    }
    NTESTSUITE_ACTUAL_UINT(g_output);
}

static void setup_none(void)
{
    g_output = 0u;
}

void test_ntask_fiber(void)
{
	static const struct nk_testsuite_test none_tests[] =
	{
		NK_TESTSUITE_TEST(test_none_empty),
		NK_TESTSUITE_TEST(test_none_exit),
	    NK_TESTSUITE_TEST(test_none_until),
	    NK_TESTSUITE_TEST(test_none_while),
	    NK_TESTSUITE_TEST(test_none_wait),
	    NK_TESTSUITE_TEST(test_none_yield),
	    NK_TESTSUITE_TEST(test_none_yield),
		NK_TESTSUITE_TEST_TERMINATE()
	};
    nk_testsuite_set_fixture(setup_none, NULL, NK_TESTSUITE_FIXTURE_NAME(none));
    nk_testsuite_run_tests(none_tests);
}

