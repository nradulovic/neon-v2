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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "testsuite/ntestsuite.h"
#include "thread/nthread_fiber.h"
#include "test_nfiber.h"

#define EXPECT(a_num)           g_expected = (a_num)

#define EVALUATE()                                                          \
    do {                                                                    \
        NTESTSUITE_ASSERT_EQUAL_UINT((g_expected), (g_output)); \
    } while (0)

static uint32_t g_output;
static uint32_t g_expected;
static uint32_t g_should_stop;

static NFIBER(fiber_empty(struct nfiber *));

static NFIBER(fiber_empty(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    NFIBER_END(fb);
}

static NFIBER(fiber_exit(struct nfiber *));

static NFIBER(fiber_exit(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    g_output = 1u;
    NFIBER_EXIT(fb);
    g_output = 0u;
    NFIBER_END(fb);
}

static NFIBER(fiber_until(struct nfiber *));

static NFIBER(fiber_until(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    for (;;) {
        g_output++;
        NFIBER_WAIT_UNTIL(fb, g_output < 3);
    }
    NFIBER_END(fb);
}

static NFIBER(fiber_while(struct nfiber *));

static NFIBER(fiber_while(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    for (;;) {
        NFIBER_WAIT_WHILE(fb, g_output > 2);
        g_output++;
    }
    NFIBER_END(fb);
}

static NFIBER(fiber_yielded_0(struct nfiber *));

static NFIBER(fiber_yielded_0(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    for (;;) {
        g_output++;
        NFIBER_YIELD(fb);
    }
    NFIBER_END(fb);
}

static NFIBER(fiber_yielded_1(struct nfiber *));

static NFIBER(fiber_yielded_1(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    for (;;) {
        NFIBER_YIELD(fb);
    }
    NFIBER_END(fb);
}

static NFIBER(fiber_yielded_2(struct nfiber *));

static NFIBER(fiber_yielded_2(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    for (;;) {
        if (g_output == g_expected) {
            g_should_stop = 1;
        }
        NFIBER_YIELD(fb);
    }
    NFIBER_END(fb);
}

static NFIBER(fiber_waited_0(struct nfiber *));

static NFIBER(fiber_waited_0(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    g_output++;
    NFIBER_END(fb);
}

static NFIBER(fiber_wait_0(struct nfiber *));

static NFIBER(fiber_wait_0(struct nfiber * fb))
{
    NFIBER_BEGIN(fb);
    static struct nfiber waited_0;
        
    nfiber_init(&waited_0);
    NFIBER_WAIT(fb, fiber_waited_0(&waited_0));
    nfiber_init(&waited_0);
    NFIBER_WAIT(fb, fiber_waited_0(&waited_0));
    nfiber_init(&waited_0);
    NFIBER_WAIT(fb, fiber_waited_0(&waited_0));
    NFIBER_END(fb);
}

static void test_empty(void)
{
    struct nfiber empty;
    nfiber_init(&empty);
    NTESTSUITE_ASSERT_EQUAL_UINT(NFIBER_TERMINATED,
        nfiber_dispatch(fiber_empty(&empty)));
}

static void test_exit(void)
{
    struct nfiber exit;
    EXPECT(1u);

    nfiber_init(&exit);
    NTESTSUITE_ASSERT_EQUAL_UINT(NFIBER_TERMINATED,
        nfiber_dispatch(fiber_exit(&exit)));
    EVALUATE();
}

static void test_until(void)
{
    struct nfiber until;
    EXPECT(3u);
    nfiber_init(&until);
    while (nfiber_dispatch(fiber_until(&until)) != NFIBER_WAITING);
    EVALUATE();
}

static void test_while(void)
{
    struct nfiber while_ctx;
    EXPECT(3u);
    nfiber_init(&while_ctx);
    while (nfiber_dispatch(fiber_while(&while_ctx)) != NFIBER_WAITING);
    EVALUATE();
}

static void test_wait_0(void)
{
    struct nfiber wait;
    EXPECT(3u);
    nfiber_init(&wait);
    while (nfiber_dispatch(fiber_wait_0(&wait)) != NFIBER_TERMINATED);
    EVALUATE();
}

static void test_yield(void)
{
    static struct nfiber yielded_0;
    static struct nfiber yielded_1;
    static struct nfiber yielded_2;
    EXPECT(3u);
    g_should_stop = 0u;
        
    while (!g_should_stop) {
        nfiber_dispatch(fiber_yielded_0(&yielded_0));
        nfiber_dispatch(fiber_yielded_1(&yielded_1));
        nfiber_dispatch(fiber_yielded_2(&yielded_2));
    }
    EVALUATE();
}

static void setup_empty(void)
{
    g_output = 0u;
    g_expected = 0u;
}

static void teardown_empty(void)
{
}

void test_nfiber(void)
{
    NTESTSUITE_FIXTURE(empty, setup_empty, teardown_empty);
    NTESTSUITE_RUN(empty, test_empty);
    NTESTSUITE_RUN(empty, test_exit);
    NTESTSUITE_RUN(empty, test_until);
    NTESTSUITE_RUN(empty, test_while);
    NTESTSUITE_RUN(empty, test_wait_0);
    NTESTSUITE_RUN(empty, test_yield);
    NTESTSUITE_PRINT_RESULTS(empty);   
}


