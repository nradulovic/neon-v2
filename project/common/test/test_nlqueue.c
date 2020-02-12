/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "test_nlqueue.h"

#include "../testsuite/ntestsuite.h"
#include "core/nlqueue.h"

#define QUEUE_SIZE 4

static struct test_queue nlqueue(uint8_t, QUEUE_SIZE) g_test_queue;

NTESTSUITE_TEST(test_none_init)
{
    struct my_queue nlqueue(uint8_t, 16) my_queue;

    /* NOTE:
     * Compile time test only. Ensure that the expected is equal to actual
     * value.
     */
    ntestsuite_expect_bool(true);
    ntestsuite_actual_bool(true);
    NLQUEUE_INIT(&my_queue);
}

NTESTSUITE_TEST(test_empty_empty)
{
    ntestsuite_expect_uint(QUEUE_SIZE);
    ntestsuite_actual_uint(NLQUEUE_EMPTY(&g_test_queue));
}

NTESTSUITE_TEST(test_empty_size)
{
    ntestsuite_expect_uint(QUEUE_SIZE);
    ntestsuite_actual_uint(NLQUEUE_SIZE(&g_test_queue));
}

NTESTSUITE_TEST(test_empty_is_full)
{
    ntestsuite_expect_bool(false);
    ntestsuite_actual_bool(NLQUEUE_IS_FULL(&g_test_queue));
}

NTESTSUITE_TEST(test_empty_is_empty)
{
    ntestsuite_expect_bool(true);
    ntestsuite_actual_bool(NLQUEUE_IS_EMPTY(&g_test_queue));
}

NTESTSUITE_TEST(test_empty_fifo_head)
{
    ntestsuite_expect_uint(234);
    NLQUEUE_PUT_FIFO(&g_test_queue, 234);
    ntestsuite_actual_uint(NLQUEUE_HEAD(&g_test_queue));
}

NTESTSUITE_TEST(test_empty_fifo_tail)
{
    ntestsuite_expect_uint(234);
    NLQUEUE_PUT_FIFO(&g_test_queue, 234);
    ntestsuite_actual_uint(NLQUEUE_TAIL(&g_test_queue));
}

NTESTSUITE_TEST(test_empty_lifo_head)
{
    ntestsuite_expect_uint(234);
    NLQUEUE_PUT_LIFO(&g_test_queue, 234);
    ntestsuite_actual_uint(NLQUEUE_HEAD(&g_test_queue));
}

NTESTSUITE_TEST(test_empty_lifo_tail)
{
    ntestsuite_expect_uint(234);
    NLQUEUE_PUT_LIFO(&g_test_queue, 234);
    ntestsuite_actual_uint(NLQUEUE_TAIL(&g_test_queue));
}

NTESTSUITE_TEST(test_nonempty_empty)
{
    ntestsuite_expect_uint(QUEUE_SIZE - 2u);
    ntestsuite_actual_uint(NLQUEUE_EMPTY(&g_test_queue));
}

NTESTSUITE_TEST(test_nonempty_size)
{
    ntestsuite_expect_uint(QUEUE_SIZE);
    ntestsuite_actual_uint(NLQUEUE_SIZE(&g_test_queue));
}

NTESTSUITE_TEST(test_nonempty_is_full)
{
    ntestsuite_expect_bool(false);
    ntestsuite_actual_bool(NLQUEUE_IS_FULL(&g_test_queue));
}

NTESTSUITE_TEST(test_nonempty_is_empty)
{
    ntestsuite_expect_bool(false);
    ntestsuite_actual_bool(NLQUEUE_IS_EMPTY(&g_test_queue));
}

NTESTSUITE_TEST(test_nonempty_fifo_head)
{
    ntestsuite_expect_uint(1);
    NLQUEUE_PUT_FIFO(&g_test_queue, 233);
    ntestsuite_actual_uint(NLQUEUE_HEAD(&g_test_queue));
}

NTESTSUITE_TEST(test_nonempty_fifo_tail)
{
    ntestsuite_expect_uint(233);
    NLQUEUE_PUT_FIFO(&g_test_queue, 233);
    ntestsuite_actual_uint(NLQUEUE_TAIL(&g_test_queue));
}

NTESTSUITE_TEST(test_nonempty_lifo_head)
{
    ntestsuite_expect_uint(234);
    NLQUEUE_PUT_LIFO(&g_test_queue, 234);
    ntestsuite_actual_uint(NLQUEUE_HEAD(&g_test_queue));
}

NTESTSUITE_TEST(test_nonempty_lifo_tail)
{
    ntestsuite_expect_uint(2);
    NLQUEUE_PUT_LIFO(&g_test_queue, 235);
    ntestsuite_actual_uint(NLQUEUE_TAIL(&g_test_queue));
}

NTESTSUITE_TEST(test_full_empty)
{
    ntestsuite_expect_uint(0);
    ntestsuite_actual_uint(NLQUEUE_EMPTY(&g_test_queue));
}

NTESTSUITE_TEST(test_full_size)
{
    ntestsuite_expect_uint(QUEUE_SIZE);
    ntestsuite_actual_uint(NLQUEUE_SIZE(&g_test_queue));
}

NTESTSUITE_TEST(test_full_is_full)
{
    ntestsuite_expect_bool(true);
    ntestsuite_actual_bool(NLQUEUE_IS_FULL(&g_test_queue));
}

NTESTSUITE_TEST(test_full_is_empty)
{
    ntestsuite_expect_bool(false);
    ntestsuite_actual_bool(NLQUEUE_IS_EMPTY(&g_test_queue));
}

static void setup_empty(void)
{
    memset(&g_test_queue, 0, sizeof(g_test_queue));
    NLQUEUE_INIT(&g_test_queue);
}

static void setup_nonempty(void)
{
    memset(&g_test_queue, 0, sizeof(g_test_queue));
    NLQUEUE_INIT(&g_test_queue);
    NLQUEUE_PUT_FIFO(&g_test_queue, 1);
    NLQUEUE_PUT_FIFO(&g_test_queue, 2);
}

static void setup_full(void)
{
    memset(&g_test_queue, 0, sizeof(g_test_queue));
    NLQUEUE_INIT(&g_test_queue);
    NLQUEUE_PUT_FIFO(&g_test_queue, 1);
    NLQUEUE_PUT_FIFO(&g_test_queue, 2);
    NLQUEUE_PUT_FIFO(&g_test_queue, 3);
    NLQUEUE_PUT_FIFO(&g_test_queue, 4);
}

void test_exec_nlqueue(void)
{
    ntestsuite_set_fixture(none, NULL, NULL);
    ntestsuite_run(test_none_init);

    ntestsuite_set_fixture(empty, setup_empty, NULL);
    ntestsuite_run(test_empty_empty);
    ntestsuite_run(test_empty_size);
    ntestsuite_run(test_empty_is_full);
    ntestsuite_run(test_empty_is_empty);
    ntestsuite_run(test_empty_fifo_head);
    ntestsuite_run(test_empty_fifo_tail);
    ntestsuite_run(test_empty_lifo_head);
    ntestsuite_run(test_empty_lifo_tail);

    ntestsuite_set_fixture(nonempty, setup_nonempty, NULL);
    ntestsuite_run(test_nonempty_empty);
    ntestsuite_run(test_nonempty_size);
    ntestsuite_run(test_nonempty_is_full);
    ntestsuite_run(test_nonempty_is_empty);
    ntestsuite_run(test_nonempty_fifo_head);
    ntestsuite_run(test_nonempty_fifo_tail);
    ntestsuite_run(test_nonempty_lifo_head);
    ntestsuite_run(test_nonempty_lifo_tail);

    ntestsuite_set_fixture(full, setup_full, NULL);
    ntestsuite_run(test_full_empty);
    ntestsuite_run(test_full_size);
    ntestsuite_run(test_full_is_full);
    ntestsuite_run(test_full_is_empty);
}
