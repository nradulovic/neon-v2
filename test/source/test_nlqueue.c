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
#include <stdlib.h>
#include <string.h>

#include "testsuite/ntestsuite.h"
#include "queue/nqueue_lqueue.h"
#include "test_nlqueue.h"

#define EXPECT(a_num)           g_expected = (a_num)

#define EVALUATE()                                                          \
    do {                                                                    \
        NTESTSUITE_ASSERT_EQUAL_UINT((g_expected), (g_output)); \
    } while (0)

#define QUEUE_SIZE              16

static void test_init(void);

static uint32_t g_output;
static uint32_t g_expected;
static nlqueue(uint32_t, QUEUE_SIZE) g_test_queue;

static void test_init(void)
{
    EXPECT(0);
    static nlqueue(uint32_t, 16) my_queue;

    NLQUEUE_INIT(&my_queue);
    EVALUATE();
}

static void test_get_empty(void)
{
    EXPECT(QUEUE_SIZE);
    g_output = NLQUEUE_EMPTY(&g_test_queue);
    EVALUATE();
}

static void test_get_size(void)
{
    EXPECT(QUEUE_SIZE);
    g_output = NLQUEUE_SIZE(&g_test_queue);
    EVALUATE();
}

static void test_empty_is_full(void)
{
    EXPECT(false);
    g_output = NLQUEUE_IS_FULL(&g_test_queue);
    EVALUATE();
}

static void test_empty_is_empty(void)
{
    EXPECT(true);
    g_output = NLQUEUE_IS_EMPTY(&g_test_queue);
    EVALUATE();
}

static void setup_empty(void)
{
    g_output = 0u;
    g_expected = 0u;
    NLQUEUE_INIT(&g_test_queue);
}

static void teardown_empty(void)
{
}

void test_nlqueue(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);
    NTESTSUITE_FIXTURE(empty, setup_empty, teardown_empty);
    NTESTSUITE_RUN(none, test_init);
    NTESTSUITE_PRINT_RESULTS(none);   
    NTESTSUITE_RUN(empty, test_get_empty);
    NTESTSUITE_RUN(empty, test_get_size);
    NTESTSUITE_RUN(empty, test_empty_is_full);
    NTESTSUITE_RUN(empty, test_empty_is_empty);
    NTESTSUITE_PRINT_RESULTS(empty);   
}


