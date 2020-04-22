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

#include "ntestsuite.h"
#include "nqueue_lqueue.h"
#include "test_nqueue_lqueue.h"

#define QUEUE_SIZE 4

static nlqueue(uint8_t, QUEUE_SIZE) g_test_queue;

NTESTSUITE_TEST(test_none_init)
{
    nlqueue(uint8_t, 16) my_queue;

    /* NOTE:
     * Compile time test only. Ensure that the expected is equal to actual
     * value.
     */
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(true);
    NLQUEUE_INIT(&my_queue);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_empty)
{
    NTESTSUITE_EXPECT_UINT(QUEUE_SIZE);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_EMPTY(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_size)
{
    NTESTSUITE_EXPECT_UINT(QUEUE_SIZE);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_SIZE(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_is_full)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(NLQUEUE_IS_FULL(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_is_empty)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(NLQUEUE_IS_EMPTY(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_fifo_head)
{
    NTESTSUITE_EXPECT_UINT(234);
    NLQUEUE_PUT_FIFO(&g_test_queue, 234);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_HEAD(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_fifo_tail)
{
    NTESTSUITE_EXPECT_UINT(234);
    NLQUEUE_PUT_FIFO(&g_test_queue, 234);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_TAIL(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_lifo_head)
{
    NTESTSUITE_EXPECT_UINT(234);
    NLQUEUE_PUT_LIFO(&g_test_queue, 234);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_HEAD(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_lifo_tail)
{
    NTESTSUITE_EXPECT_UINT(234);
    NLQUEUE_PUT_LIFO(&g_test_queue, 234);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_TAIL(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_nonempty_empty)
{
    NTESTSUITE_EXPECT_UINT(QUEUE_SIZE - 2u);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_EMPTY(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_nonempty_size)
{
    NTESTSUITE_EXPECT_UINT(QUEUE_SIZE);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_SIZE(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_nonempty_is_full)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(NLQUEUE_IS_FULL(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_nonempty_is_empty)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(NLQUEUE_IS_EMPTY(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_nonempty_fifo_head)
{
    NTESTSUITE_EXPECT_UINT(1);
    NLQUEUE_PUT_FIFO(&g_test_queue, 233);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_HEAD(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_nonempty_fifo_tail)
{
    NTESTSUITE_EXPECT_UINT(233);
    NLQUEUE_PUT_FIFO(&g_test_queue, 233);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_TAIL(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_nonempty_lifo_head)
{
    NTESTSUITE_EXPECT_UINT(234);
    NLQUEUE_PUT_LIFO(&g_test_queue, 234);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_HEAD(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_nonempty_lifo_tail)
{
    NTESTSUITE_EXPECT_UINT(2);
    NLQUEUE_PUT_LIFO(&g_test_queue, 234);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_TAIL(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_full_empty)
{
    NTESTSUITE_EXPECT_UINT(0);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_EMPTY(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_full_size)
{
    NTESTSUITE_EXPECT_UINT(QUEUE_SIZE);
    NTESTSUITE_ACTUAL_UINT(NLQUEUE_SIZE(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_full_is_full)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(NLQUEUE_IS_FULL(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_full_is_empty)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(NLQUEUE_IS_EMPTY(&g_test_queue));
    NTESTSUITE_EVALUATE();
}

static void setup_empty(void)
{
    NLQUEUE_INIT(&g_test_queue);
}

static void setup_nonempty(void)
{
    NLQUEUE_INIT(&g_test_queue);
    NLQUEUE_PUT_FIFO(&g_test_queue, 1);
    NLQUEUE_PUT_FIFO(&g_test_queue, 2);
}

static void setup_full(void)
{
    NLQUEUE_INIT(&g_test_queue);
    NLQUEUE_PUT_FIFO(&g_test_queue, 1);
    NLQUEUE_PUT_FIFO(&g_test_queue, 2);
    NLQUEUE_PUT_FIFO(&g_test_queue, 3);
    NLQUEUE_PUT_FIFO(&g_test_queue, 4);
}

void test_nqueue_lqueue(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);
    NTESTSUITE_FIXTURE(empty, setup_empty, NULL);
    NTESTSUITE_FIXTURE(nonempty, setup_nonempty, NULL);
    NTESTSUITE_FIXTURE(full, setup_full, NULL);

    NTESTSUITE_RUN(none, test_none_init);
    NTESTSUITE_PRINT_RESULTS(none);

    NTESTSUITE_RUN(empty, test_empty_empty);
    NTESTSUITE_RUN(empty, test_empty_size);
    NTESTSUITE_RUN(empty, test_empty_is_full);
    NTESTSUITE_RUN(empty, test_empty_is_empty);
    NTESTSUITE_RUN(empty, test_empty_fifo_head);
    NTESTSUITE_RUN(empty, test_empty_fifo_tail);
    NTESTSUITE_RUN(empty, test_empty_lifo_head);
    NTESTSUITE_RUN(empty, test_empty_lifo_tail);
    NTESTSUITE_PRINT_RESULTS(empty);

    NTESTSUITE_RUN(nonempty, test_nonempty_empty);
    NTESTSUITE_RUN(nonempty, test_nonempty_size);
    NTESTSUITE_RUN(nonempty, test_nonempty_is_full);
    NTESTSUITE_RUN(nonempty, test_nonempty_is_empty);
    NTESTSUITE_RUN(nonempty, test_nonempty_fifo_head);
    NTESTSUITE_RUN(nonempty, test_nonempty_fifo_tail);
    NTESTSUITE_RUN(nonempty, test_nonempty_lifo_head);
    NTESTSUITE_RUN(nonempty, test_nonempty_lifo_tail);
    NTESTSUITE_PRINT_RESULTS(nonempty);

    NTESTSUITE_RUN(full, test_full_empty);
    NTESTSUITE_RUN(full, test_full_size);
    NTESTSUITE_RUN(full, test_full_is_full);
    NTESTSUITE_RUN(full, test_full_is_empty);
    NTESTSUITE_PRINT_RESULTS(full);
}


