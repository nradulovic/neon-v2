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

#include "testsuite/ntestsuite.h"
#include "fiber/nfiber.h"
#include "main.h"

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

NTESTSUITE_TEST(test_none_empty)
{
    struct nfiber empty;

    NTESTSUITE_EXPECT_UINT(NFIBER_TERMINATED);
    nfiber_init(&empty);
    NTESTSUITE_ACTUAL_UINT(nfiber_dispatch(fiber_empty(&empty)));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_exit)
{
    struct nfiber exit;

    NTESTSUITE_EXPECT_UINT(1u);
    nfiber_init(&exit);
    nfiber_dispatch(fiber_exit(&exit));
    NTESTSUITE_ACTUAL_UINT(g_output);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_until)
{
    struct nfiber until;

    NTESTSUITE_EXPECT_UINT(3u);
    nfiber_init(&until);
    while (nfiber_dispatch(fiber_until(&until)) != NFIBER_BLOCKED);
    NTESTSUITE_ACTUAL_UINT(g_output);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_while)
{
    struct nfiber while_ctx;

    NTESTSUITE_EXPECT_UINT(3u);
    nfiber_init(&while_ctx);
    while (nfiber_dispatch(fiber_while(&while_ctx)) != NFIBER_BLOCKED);
    NTESTSUITE_ACTUAL_UINT(g_output);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_wait)
{
    struct nfiber wait;

    NTESTSUITE_EXPECT_UINT(3u);
    nfiber_init(&wait);
    while (nfiber_dispatch(fiber_wait_0(&wait)) != NFIBER_TERMINATED);
    NTESTSUITE_ACTUAL_UINT(g_output);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_yield)
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
    NTESTSUITE_EVALUATE();
}

static void setup_none(void)
{
    g_output = 0u;
}

void test_exec(void)
{
    NTESTSUITE_FIXTURE(none, setup_none, NULL);
    NTESTSUITE_RUN(none, test_none_empty);
    NTESTSUITE_RUN(none, test_none_exit);
    NTESTSUITE_RUN(none, test_none_until);
    NTESTSUITE_RUN(none, test_none_while);
    NTESTSUITE_RUN(none, test_none_wait);
    NTESTSUITE_RUN(none, test_none_yield);
    NTESTSUITE_RUN(none, test_none_yield);
    NTESTSUITE_PRINT_RESULTS(none);   
}


