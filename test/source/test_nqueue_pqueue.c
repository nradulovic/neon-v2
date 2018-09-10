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
#include <test_nqueue_pqueue.h>

#include "testsuite/ntestsuite.h"
#include "queue/nqueue_pqueue.h"

static struct npqueue g_node0;
static struct npqueue g_node1;
static struct npqueue g_node2;
static struct npqueue g_node3;

NTESTSUITE_TEST(test_none_node_init)
{
    struct npqueue my_queue_node;

    NTESTSUITE_EXPECT_PTR(&my_queue_node);
    NTESTSUITE_ACTUAL_PTR(npqueue_init(&my_queue_node, 0));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_node_priority)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_UINT(1);
    npqueue_init(&node, 1);
    NTESTSUITE_ACTUAL_UINT(npqueue_priority(&node));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_node_mod_priority)
{
    struct npqueue node;
    uint_fast8_t old_prio;

    npqueue_init(&node, 1);
    old_prio = npqueue_mod_priority(&node, 3);
    NTESTSUITE_EXPECT_UINT(1);
    NTESTSUITE_ACTUAL_UINT(old_prio);
    NTESTSUITE_EVALUATE();
    NTESTSUITE_EXPECT_UINT(3);
    NTESTSUITE_ACTUAL_UINT(npqueue_priority(&node));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_node_term)
{
    struct npqueue my_queue_node;

    NTESTSUITE_EXPECT_UINT(0);
    npqueue_init(&my_queue_node, 1);
    npqueue_term(&my_queue_node);
    NTESTSUITE_ACTUAL_UINT(npqueue_priority(&my_queue_node));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_is_last)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_last(&g_node0));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_empty_insert)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(true);
    npqueue_init(&node, 1);
    npqueue_insert_sorted(&g_node0, &node);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_single_is_last)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_last(&g_node0));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_single_first)
{
    NTESTSUITE_EXPECT_UINT(0);
    NTESTSUITE_ACTUAL_UINT(npqueue_priority(&g_node0));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_single_remove)
{
    NTESTSUITE_EXPECT_BOOL(true);
    npqueue_remove(&g_node0);
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_last(&g_node0));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_single_insert)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_BOOL(false);
    npqueue_init(&node, 1);
    npqueue_insert_sorted(&g_node0, &node);
    npqueue_remove(&node);
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_last(&g_node0));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_multi_is_empty)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_last(&g_node0));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_multi_first)
{
    NTESTSUITE_EXPECT_UINT(0);
    NTESTSUITE_ACTUAL_UINT(npqueue_priority(&g_node0));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_multi_remove)
{
    NTESTSUITE_EXPECT_BOOL(true);
    npqueue_remove(&g_node1);
    npqueue_remove(&g_node2);
    npqueue_remove(&g_node3);
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_last(&g_node0));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_multi_insert)
{
    struct npqueue node;

    NTESTSUITE_EXPECT_BOOL(false);
    npqueue_init(&node, 1);
    npqueue_insert_sorted(&g_node0, &node);
    npqueue_remove(&g_node1);
    npqueue_remove(&g_node2);
    npqueue_remove(&g_node3);
    NTESTSUITE_ACTUAL_BOOL(npqueue_is_last(&g_node0));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_multi_sort_first)
{
    NTESTSUITE_EXPECT_PTR(&g_node3);
    NTESTSUITE_ACTUAL_PTR(&g_node3);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_multi_sort_duplicate)
{
    struct npqueue node3_1;

    NTESTSUITE_EXPECT_PTR(&g_node3);
    npqueue_init(&node3_1, 3);
    npqueue_insert_sorted(&g_node0, &node3_1);
    NTESTSUITE_ACTUAL_PTR(&g_node3);
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_multi_sort_middle_duplicate)
{
    struct npqueue node2_1;

    NTESTSUITE_EXPECT_PTR(&g_node2);
    npqueue_init(&node2_1, 2);
    npqueue_insert_sorted(&g_node0, &node2_1);
    npqueue_remove(&g_node0);
    NTESTSUITE_ACTUAL_PTR(&g_node2);
    NTESTSUITE_EVALUATE();
}

static void setup_empty(void)
{
    npqueue_init(&g_node0, 0);
}

static void setup_single(void)
{
    npqueue_init(&g_node0, 0);
    npqueue_init(&g_node1, 1);
    npqueue_insert_sorted(&g_node0, &g_node1);
}

static void setup_multi(void)
{
    npqueue_init(&g_node0, 0);
    npqueue_init(&g_node1, 1);
    npqueue_init(&g_node2, 2);
    npqueue_init(&g_node3, 3);
    npqueue_insert_sorted(&g_node0, &g_node1);
    npqueue_insert_sorted(&g_node1, &g_node2);
    npqueue_insert_sorted(&g_node2, &g_node3);
}

void test_nqueue_pqueue(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);
    NTESTSUITE_FIXTURE(empty, setup_empty, NULL);
    NTESTSUITE_FIXTURE(single, setup_single, NULL);
    NTESTSUITE_FIXTURE(multi, setup_multi, NULL);

    NTESTSUITE_RUN(none, test_none_node_init);
    NTESTSUITE_RUN(none, test_none_node_priority);
    NTESTSUITE_RUN(none, test_none_node_mod_priority);
    NTESTSUITE_RUN(none, test_none_node_term);
    NTESTSUITE_PRINT_RESULTS(none);

    NTESTSUITE_RUN(empty, test_empty_is_last);
    NTESTSUITE_RUN(empty, test_empty_insert);
    NTESTSUITE_PRINT_RESULTS(empty);   

    NTESTSUITE_RUN(single, test_single_is_last);
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


