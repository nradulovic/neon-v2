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

#include "test_nqueue_pqueue.h"
#include "nqueue_pqueue.h"
#include "ntestsuite.h"

static struct npqueue_sentinel g_queue;
static struct npqueue g_node1;
static struct npqueue g_node2;
static struct npqueue g_node3;

static void test_none_node_init_ptr)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_PTR(&node);
    NTESTSUITE_ACTUAL_PTR(npqueue_init(&node, 1));
}

static void test_none_node_init_prio)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_UINT(1);
    npqueue_init(&node, 1);
    NTESTSUITE_ACTUAL_UINT(npqueue_priority(&node));
}

static void test_none_node_init_next)
{
    struct npqueue node;
    
    NTESTSUITE_EXPECT_PTR(&node);
    npqueue_init(&node, 1);
    NTESTSUITE_ACTUAL_PTR(npqueue_next(&node));
}

static void test_none_node_term_prio)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_UINT(0);
    npqueue_init(&node, 1);
    npqueue_term(&node);
    NTESTSUITE_ACTUAL_UINT(npqueue_priority(&node));
}

static void test_none_node_term_next)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_PTR(&node);
    npqueue_init(&node, 1);
    npqueue_term(&node);
    NTESTSUITE_ACTUAL_PTR(npqueue_next(&node));
}

static void test_empty_sentinel_init)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(npqueue_sentinel_is_empty(&g_queue));
}

static void test_empty_sentinel_term)
{
    NTESTSUITE_EXPECT_BOOL(true);
    npqueue_sentinel_term(&g_queue);
    NTESTSUITE_ACTUAL_BOOL(npqueue_sentinel_is_empty(&g_queue));
}

static void test_empty_insert_fifo_is_empty)
{
    struct npqueue node;
    
    NTESTSUITE_EXPECT_BOOL(false);
    npqueue_init(&node, 1);
    npqueue_insert_fifo(&g_queue, &node);
    NTESTSUITE_ACTUAL_BOOL(npqueue_sentinel_is_empty(&g_queue));
}

static void test_empty_insert_fifo_head)
{
    struct npqueue node;
    
    NTESTSUITE_EXPECT_PTR(&node);
    npqueue_init(&node, 1);
    npqueue_insert_fifo(&g_queue, &node);
    NTESTSUITE_ACTUAL_PTR(npqueue_sentinel_head(&g_queue));
}

static void test_empty_insert_sort_is_empty)
{
    struct npqueue node;
    
    NTESTSUITE_EXPECT_BOOL(false);
    npqueue_init(&node, 1);
    npqueue_insert_sort(&g_queue, &node);
    NTESTSUITE_ACTUAL_BOOL(npqueue_sentinel_is_empty(&g_queue));
}

static void test_empty_insert_sort_head)
{
    struct npqueue node;
    
    NTESTSUITE_EXPECT_PTR(&node);
    npqueue_init(&node, 1);
    npqueue_insert_sort(&g_queue, &node);
    NTESTSUITE_ACTUAL_PTR(npqueue_sentinel_head(&g_queue));
}

static void test_single_is_last)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(npqueue_sentinel_is_empty(&g_queue));
}

static void test_single_first)
{
    NTESTSUITE_EXPECT_PTR(&g_node1);
    NTESTSUITE_ACTUAL_PTR(npqueue_sentinel_head(&g_queue));
}

static void test_single_remove)
{
    NTESTSUITE_EXPECT_BOOL(true);
    npqueue_remove(&g_node1);
    NTESTSUITE_ACTUAL_BOOL(npqueue_sentinel_is_empty(&g_queue));
}

static void test_single_insert_fifo_head)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_PTR(&g_node1);
    npqueue_init(&node, 2);
    npqueue_insert_fifo(&g_queue, &node);
    NTESTSUITE_ACTUAL_PTR(npqueue_sentinel_head(&g_queue));
}

static void test_single_insert_sort_head)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_PTR(&node);
    npqueue_init(&node, 2);
    npqueue_insert_sort(&g_queue, &node);
    NTESTSUITE_ACTUAL_PTR(npqueue_sentinel_head(&g_queue));
}

static void test_multi_is_empty)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(npqueue_sentinel_is_empty(&g_queue));
}

static void test_multi_first)
{
    NTESTSUITE_EXPECT_PTR(&g_node3);
    NTESTSUITE_ACTUAL_PTR(npqueue_sentinel_head(&g_queue));
}

static void test_multi_remove)
{
    NTESTSUITE_EXPECT_BOOL(true);
    npqueue_remove(&g_node1);
    npqueue_remove(&g_node2);
    npqueue_remove(&g_node3);
    NTESTSUITE_ACTUAL_BOOL(npqueue_sentinel_is_empty(&g_queue));
}

static void test_multi_insert_fifo_head)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_PTR(&g_node3);
    npqueue_init(&node, 4);
    npqueue_insert_fifo(&g_queue, &node);
    NTESTSUITE_ACTUAL_PTR(npqueue_sentinel_head(&g_queue));
}

static void test_multi_insert_sort_head)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_PTR(&node);
    npqueue_init(&node, 4);
    npqueue_insert_sort(&g_queue, &node);
    NTESTSUITE_ACTUAL_PTR(npqueue_sentinel_head(&g_queue));
}

static void test_multi_sort_first)
{
    NTESTSUITE_EXPECT_PTR(&g_node3);
    NTESTSUITE_ACTUAL_PTR(&g_node3);
}

static void test_multi_sort_duplicate)
{
    struct npqueue node3_1;

    NTESTSUITE_EXPECT_PTR(&g_node3);
    npqueue_init(&node3_1, 3);
    npqueue_insert_sort(&g_queue, &node3_1);
    NTESTSUITE_ACTUAL_PTR(&g_node3);
}

static void test_multi_sort_middle_duplicate)
{
    struct npqueue node2_1;

    NTESTSUITE_EXPECT_PTR(&g_node3);
    npqueue_init(&node2_1, 2);
    npqueue_insert_sort(&g_queue, &node2_1);
    npqueue_remove(&g_node2);
    NTESTSUITE_ACTUAL_PTR(npqueue_sentinel_head(&g_queue));
}

static void setup_empty(void)
{
    npqueue_sentinel_init(&g_queue);
}

static void setup_single(void)
{
    npqueue_sentinel_init(&g_queue);
    npqueue_init(&g_node1, 1);
    npqueue_insert_fifo(&g_queue, &g_node1);
}

static void setup_multi(void)
{
    npqueue_sentinel_init(&g_queue);
    npqueue_init(&g_node1, 1);
    npqueue_init(&g_node2, 2);
    npqueue_init(&g_node3, 3);
    npqueue_insert_fifo(&g_queue, &g_node3);
    npqueue_insert_fifo(&g_queue, &g_node2);
    npqueue_insert_fifo(&g_queue, &g_node1);
}

void test_nqueue_pqueue(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);
    NTESTSUITE_FIXTURE(empty, setup_empty, NULL);
    NTESTSUITE_FIXTURE(single, setup_single, NULL);
    NTESTSUITE_FIXTURE(multi, setup_multi, NULL);

    NTESTSUITE_RUN(none, test_none_node_init_ptr);
    NTESTSUITE_RUN(none, test_none_node_init_prio);
    NTESTSUITE_RUN(none, test_none_node_init_next);
    NTESTSUITE_RUN(none, test_none_node_term_prio);
    NTESTSUITE_RUN(none, test_none_node_term_next);
    NTESTSUITE_PRINT_RESULTS(none);

    NTESTSUITE_RUN(empty, test_empty_sentinel_init);
    NTESTSUITE_RUN(empty, test_empty_sentinel_term);
    NTESTSUITE_RUN(empty, test_empty_insert_fifo_is_empty);
    NTESTSUITE_RUN(empty, test_empty_insert_fifo_head);
    NTESTSUITE_RUN(empty, test_empty_insert_sort_is_empty);
    NTESTSUITE_RUN(empty, test_empty_insert_sort_head);
    NTESTSUITE_PRINT_RESULTS(empty);
    
    NTESTSUITE_RUN(single, test_single_is_last);
    NTESTSUITE_RUN(single, test_single_first);
    NTESTSUITE_RUN(single, test_single_remove);
    NTESTSUITE_RUN(single, test_single_insert_fifo_head);
    NTESTSUITE_RUN(single, test_single_insert_sort_head);
    NTESTSUITE_PRINT_RESULTS(single);

    NTESTSUITE_RUN(multi, test_multi_is_empty);
    NTESTSUITE_RUN(multi, test_multi_first);
    NTESTSUITE_RUN(multi, test_multi_remove);
    NTESTSUITE_RUN(multi, test_multi_insert_fifo_head);
    NTESTSUITE_RUN(multi, test_multi_insert_sort_head);
    NTESTSUITE_RUN(multi, test_multi_sort_first);
    NTESTSUITE_RUN(multi, test_multi_sort_duplicate);
    NTESTSUITE_RUN(multi, test_multi_sort_middle_duplicate);
    NTESTSUITE_PRINT_RESULTS(multi);
}


