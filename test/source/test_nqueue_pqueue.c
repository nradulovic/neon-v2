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
#include <stdbool.h>
#include <test_nqueue_pqueue.h>

#include "testsuite/ntestsuite.h"
#include "queue/nqueue_pqueue.h"

static struct npqueue g_queue;
static struct npqueue_node g_node1;
static struct npqueue_node g_node2;
static struct npqueue_node g_node3;

static void test_none_init_queue(void)
{
    struct npqueue my_queue;

    /* NOTE:
     * Compile time test only. Ensure that the expected is equal to actual
     * value.
     */
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(true);
    npqueue_init(&my_queue);
    NTESTSUITE_EVALUATE();
}

static void test_none_node_init(void)
{
    struct npqueue_node my_queue_node;

    NTESTSUITE_EXPECT_PTR(&my_queue_node);
    NTESTSUITE_ACTUAL_PTR(npqueue_node_init(&my_queue_node, 0));
    NTESTSUITE_EVALUATE();
}

static void test_none_node_priority(void)
{
    struct npqueue_node node;

    NTESTSUITE_EXPECT_UINT(1);
    npqueue_node_init(&node, 1);
    NTESTSUITE_ACTUAL_UINT(npqueue_node_priority(&node));
    NTESTSUITE_EVALUATE();
}

static void test_none_node_mod_priority(void)
{
    struct npqueue_node node;
    uint_fast8_t old_prio;

    npqueue_node_init(&node, 1);
    old_prio = npqueue_node_mod_priority(&node, 3);
    NTESTSUITE_EXPECT_UINT(1);
    NTESTSUITE_ACTUAL_UINT(old_prio);
    NTESTSUITE_EVALUATE();
    NTESTSUITE_EXPECT_UINT(3);
    NTESTSUITE_ACTUAL_UINT(npqueue_node_priority(&node));
    NTESTSUITE_EVALUATE();
}

static void test_none_node_term(void)
{
    struct npqueue_node my_queue_node;

    NTESTSUITE_EXPECT_UINT(0);
    npqueue_node_init(&my_queue_node, 1);
    npqueue_node_term(&my_queue_node);
    NTESTSUITE_ACTUAL_UINT(npqueue_node_priority(&my_queue_node));
    NTESTSUITE_EVALUATE();
}

static void test_empty_is_empty(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_empty(&g_queue));
    NTESTSUITE_EVALUATE();
}

static void test_empty_insert(void)
{
    struct npqueue_node node;

    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(true);
    npqueue_node_init(&node, 1);
    npqueue_insert(&g_queue, &node);
    NTESTSUITE_EVALUATE();
}

static void test_single_is_empty(void)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_empty(&g_queue));
    NTESTSUITE_EVALUATE();
}

static void test_single_first(void)
{
    NTESTSUITE_EXPECT_UINT(1);
    NTESTSUITE_ACTUAL_UINT(npqueue_node_priority(npqueue_first(&g_queue)));
    NTESTSUITE_EVALUATE();
}

static void test_single_remove(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    npqueue_remove(npqueue_first(&g_queue));
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_empty(&g_queue));
    NTESTSUITE_EVALUATE();
}

static void test_single_insert(void)
{
    struct npqueue_node node;

    NTESTSUITE_EXPECT_BOOL(false);
    npqueue_node_init(&node, 1);
    npqueue_insert(&g_queue, &node);
    npqueue_remove(npqueue_first(&g_queue));
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_empty(&g_queue));
    NTESTSUITE_EVALUATE();
}

static void test_multi_is_empty(void)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_empty(&g_queue));
    NTESTSUITE_EVALUATE();
}

static void test_multi_first(void)
{
    NTESTSUITE_EXPECT_UINT(3);
    NTESTSUITE_ACTUAL_UINT(npqueue_node_priority(npqueue_first(&g_queue)));
    NTESTSUITE_EVALUATE();
}

static void test_multi_remove(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    npqueue_remove(npqueue_first(&g_queue));
    npqueue_remove(npqueue_first(&g_queue));
    npqueue_remove(npqueue_first(&g_queue));
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_empty(&g_queue));
    NTESTSUITE_EVALUATE();
}

static void test_multi_insert(void)
{
    struct npqueue_node node;

    NTESTSUITE_EXPECT_BOOL(false);
    npqueue_node_init(&node, 1);
    npqueue_insert(&g_queue, &node);
    npqueue_remove(npqueue_first(&g_queue));
    npqueue_remove(npqueue_first(&g_queue));
    npqueue_remove(npqueue_first(&g_queue));
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_empty(&g_queue));
    NTESTSUITE_EVALUATE();
}

static void test_multi_sort_first(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node3);
    NTESTSUITE_ACTUAL_PTR(npqueue_first(&g_queue));
    NTESTSUITE_EVALUATE();
}

static void test_multi_sort_duplicate(void)
{
    struct npqueue_node node3_1;

    NTESTSUITE_EXPECT_PTR(&g_node3);
    npqueue_node_init(&node3_1, 3);
    npqueue_insert(&g_queue, &node3_1);
    NTESTSUITE_ACTUAL_PTR(npqueue_first(&g_queue));
    NTESTSUITE_EVALUATE();
}

static void test_multi_sort_middle_duplicate(void)
{
    struct npqueue_node node2_1;

    NTESTSUITE_EXPECT_PTR(&g_node2);
    npqueue_node_init(&node2_1, 2);
    npqueue_insert(&g_queue, &node2_1);
    npqueue_remove(npqueue_first(&g_queue));
    NTESTSUITE_ACTUAL_PTR(npqueue_first(&g_queue));
    NTESTSUITE_EVALUATE();
}

static void setup_empty(void)
{
    npqueue_init(&g_queue);
}

static void setup_single(void)
{
    npqueue_init(&g_queue);
    npqueue_node_init(&g_node1, 1);
    npqueue_insert(&g_queue, &g_node1);
}

static void setup_multi(void)
{
    npqueue_init(&g_queue);
    npqueue_node_init(&g_node1, 1);
    npqueue_node_init(&g_node2, 2);
    npqueue_node_init(&g_node3, 3);
    npqueue_insert(&g_queue, &g_node1);
    npqueue_insert(&g_queue, &g_node2);
    npqueue_insert(&g_queue, &g_node3);
}

void test_nqueue_pqueue(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);
    NTESTSUITE_FIXTURE(empty, setup_empty, NULL);
    NTESTSUITE_FIXTURE(single, setup_single, NULL);
    NTESTSUITE_FIXTURE(multi, setup_multi, NULL);

    NTESTSUITE_RUN(none, test_none_init_queue);
    NTESTSUITE_RUN(none, test_none_node_init);
    NTESTSUITE_RUN(none, test_none_node_priority);
    NTESTSUITE_RUN(none, test_none_node_mod_priority);
    NTESTSUITE_RUN(none, test_none_node_term);
    NTESTSUITE_PRINT_RESULTS(none);

    NTESTSUITE_RUN(empty, test_empty_is_empty);
    NTESTSUITE_RUN(empty, test_empty_insert);
    NTESTSUITE_PRINT_RESULTS(empty);   

    NTESTSUITE_RUN(single, test_single_is_empty);
    NTESTSUITE_RUN(single, test_single_first);
    NTESTSUITE_RUN(single, test_single_remove);
    NTESTSUITE_RUN(single, test_single_insert);
    NTESTSUITE_PRINT_RESULTS(single);

    NTESTSUITE_RUN(multi, test_multi_is_empty);
    NTESTSUITE_RUN(multi, test_multi_first);
    NTESTSUITE_RUN(multi, test_multi_remove);
    NTESTSUITE_RUN(multi, test_multi_insert);
    NTESTSUITE_RUN(multi, test_multi_sort_first);
    NTESTSUITE_RUN(multi, test_multi_sort_duplicate);
    NTESTSUITE_RUN(multi, test_multi_sort_middle_duplicate);
    NTESTSUITE_PRINT_RESULTS(multi);
}


