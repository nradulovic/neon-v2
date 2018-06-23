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
#include <test_nqueue_pqueue.h>

#include "testsuite/ntestsuite.h"
#include "queue/nqueue_pqueue.h"

#define EXPECT(a_number)        g_expected = (a_number)

#define EVALUATE()                                                          \
    do {                                                                    \
    	NTESTSUITE_ASSERT_EQUAL_INT(g_expected, g_actual);					\
    } while (0)

static uint32_t g_actual;
static uint32_t g_expected;
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
	EXPECT(g_actual);
	npqueue_init(&my_queue);
	EVALUATE();
}

static void test_none_init_queue_node(void)
{
	struct npqueue_node my_queue_node;

	/* NOTE:
	 * Compile time test only. Ensure that the expected is equal to actual
	 * value.
	 */
	EXPECT(g_actual);
	npqueue_node_init(&my_queue_node, 0);
	EVALUATE();
}

static void test_none_node_priority(void)
{
    struct npqueue_node node;

    EXPECT(1);
    npqueue_node_init(&node, 1);
    g_actual = npqueue_node_priority(&node);
    EVALUATE();
}

static void test_empty_is_empty(void)
{
	EXPECT(true);
	g_actual = npqueue_is_empty(&g_queue);
	EVALUATE();
}

static void test_empty_insert(void)
{
    struct npqueue_node node;

    EXPECT(g_actual);
    npqueue_node_init(&node, 1);
    npqueue_insert(&g_queue, &node);
    EVALUATE();
}

static void test_single_is_empty(void)
{
    EXPECT(false);
    g_actual = npqueue_is_empty(&g_queue);
    EVALUATE();
}

static void test_single_first(void)
{
    EXPECT(1);
    g_actual = npqueue_node_priority(npqueue_first(&g_queue));
    EVALUATE();
}

static void test_single_remove(void)
{
    EXPECT(true);
    npqueue_remove(npqueue_first(&g_queue));
    g_actual = npqueue_is_empty(&g_queue);
    EVALUATE();
}

static void test_single_insert(void)
{
	struct npqueue_node node;

	npqueue_node_init(&node, 1);
	EXPECT(false);
	npqueue_insert(&g_queue, &node);
	npqueue_remove(npqueue_first(&g_queue));
	g_actual = npqueue_is_empty(&g_queue);
	EVALUATE();
}

static void test_multi_is_empty(void)
{
	EXPECT(false);
	g_actual = npqueue_is_empty(&g_queue);
	EVALUATE();
}

static void test_multi_first(void)
{
	EXPECT(3);
	g_actual = npqueue_node_priority(npqueue_first(&g_queue));
	EVALUATE();
}

static void test_multi_remove(void)
{
	EXPECT(true);
	npqueue_remove(npqueue_first(&g_queue));
	npqueue_remove(npqueue_first(&g_queue));
	npqueue_remove(npqueue_first(&g_queue));
	g_actual = npqueue_is_empty(&g_queue);
	EVALUATE();
}

static void test_multi_insert(void)
{
	struct npqueue_node node;

	npqueue_node_init(&node, 1);
	EXPECT(false);
	npqueue_insert(&g_queue, &node);
	npqueue_remove(npqueue_first(&g_queue));
	npqueue_remove(npqueue_first(&g_queue));
	npqueue_remove(npqueue_first(&g_queue));
	g_actual = npqueue_is_empty(&g_queue);
	EVALUATE();
}

static void test_multi_sort_first(void)
{
	NTESTSUITE_ASSERT_EQUAL_PTR(&g_node3, npqueue_first(&g_queue));
}

static void test_multi_sort_duplicate(void)
{
	struct npqueue_node node3_1;

	npqueue_node_init(&node3_1, 3);
	npqueue_insert(&g_queue, &node3_1);
	NTESTSUITE_ASSERT_EQUAL_PTR(&g_node3, npqueue_first(&g_queue));
}

static void test_multi_sort_middle_duplicate(void)
{
	struct npqueue_node node2_1;

	npqueue_node_init(&node2_1, 2);
	npqueue_insert(&g_queue, &node2_1);
	npqueue_remove(npqueue_first(&g_queue));
	NTESTSUITE_ASSERT_EQUAL_PTR(&g_node2, npqueue_first(&g_queue));
}

static void setup_null(void)
{
	g_actual = 0u;
	g_expected = 1u;
}

static void setup_empty(void)
{
	g_actual = 0u;
	g_expected = 1u;
	npqueue_init(&g_queue);
}

static void setup_single(void)
{

	g_actual = 0u;
	g_expected = 1u;
	npqueue_init(&g_queue);
    npqueue_node_init(&g_node1, 1);
    npqueue_insert(&g_queue, &g_node1);
}

static void setup_multi(void)
{
	g_actual = 0u;
	g_expected = 1u;
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
	NTESTSUITE_FIXTURE(none, setup_null, NULL);
    NTESTSUITE_FIXTURE(empty, setup_empty, NULL);
    NTESTSUITE_FIXTURE(single, setup_single, NULL);
    NTESTSUITE_FIXTURE(multi, setup_multi, NULL);

    NTESTSUITE_RUN(none, test_none_init_queue);
    NTESTSUITE_RUN(none, test_none_init_queue_node);
    NTESTSUITE_RUN(none, test_none_node_priority);
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


