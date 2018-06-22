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
static struct npqueue_node g_node;

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
    struct npqueue_node * node;

    node = npqueue_first(&g_queue);
    EXPECT(true);
    npqueue_remove(node);
    g_actual = npqueue_is_empty(&g_queue);
    EVALUATE();
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
    npqueue_node_init(&g_node, 1);
    npqueue_insert(&g_queue, &g_node);
}

void test_nqueue_pqueue(void)
{
	NTESTSUITE_FIXTURE(none, setup_null, NULL);
    NTESTSUITE_FIXTURE(empty, setup_empty, NULL);
    NTESTSUITE_FIXTURE(single, setup_single, NULL);

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
    NTESTSUITE_PRINT_RESULTS(single);   
}


