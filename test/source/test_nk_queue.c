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

#include "test_nk_queue.h"
#include "nk_queue.h"
#include "ntestsuite.h"

#define QUEUE_SIZE 						4u
#define TEST_PREDEFINED_ID_0 			1u
#define TEST_PREDEFINED_ID_1 			2u
#define TEST_PREDEFINED_ID_2 			3u
#define TEST_PREDEFINED_ID_3 			4u
#define TEST_ITEM_ID 					234u

static struct nk_queue * g_test_queue;

static void test_none_init(void)
{
    /* NOTE:
     * Compile time test only. Ensure that the expected is equal to actual
     * value.
     */
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(true);
}

static void test_empty_empty(void)
{
	size_t empty = 0u;

    NTESTSUITE_EXPECT_UINT(QUEUE_SIZE);
    empty = nk_queue__empty(g_test_queue);
    NTESTSUITE_ACTUAL_UINT((uint32_t)empty);
}

static void test_empty_size(void)
{
	size_t size = 0u;

    NTESTSUITE_EXPECT_UINT(QUEUE_SIZE);
    size = nk_queue__size(g_test_queue);
    NTESTSUITE_ACTUAL_UINT((uint32_t)size);
}

static void test_empty_is_full(void)
{
	bool is_full = true;

    NTESTSUITE_EXPECT_BOOL(false);
    is_full = nk_queue__is_full(g_test_queue);
    NTESTSUITE_ACTUAL_BOOL(is_full);
}

static void test_empty_is_empty(void)
{
	bool is_empty = false;

    NTESTSUITE_EXPECT_BOOL(true);
    is_empty = nk_queue__is_empty(g_test_queue);
    NTESTSUITE_ACTUAL_BOOL(is_empty);
}

static void test_empty_fifo_head(void)
{
	uint8_t * item;

    item = nk_queue__put_fifo(g_test_queue);
    *item = TEST_ITEM_ID;
    NTESTSUITE_EXPECT_UINT(TEST_ITEM_ID);
    item = nk_queue__peek_head(g_test_queue);
    NTESTSUITE_ACTUAL_UINT(*item);
}

static void test_empty_fifo_tail(void)
{
	uint8_t * item;

    item = nk_queue__put_fifo(g_test_queue);
    *item = TEST_ITEM_ID;
    NTESTSUITE_EXPECT_UINT(TEST_ITEM_ID);
	item = nk_queue__peek_tail(g_test_queue);
	NTESTSUITE_ACTUAL_UINT(*item);
}

static void test_empty_lifo_head(void)
{
	uint8_t * item;

	item = nk_queue__put_lifo(g_test_queue);
    *item = TEST_ITEM_ID;
    NTESTSUITE_EXPECT_UINT(TEST_ITEM_ID);
    item = nk_queue__peek_head(g_test_queue);
    NTESTSUITE_ACTUAL_UINT(*item);
}

static void test_empty_lifo_tail(void)
{
	uint8_t * item;

	item = nk_queue__put_lifo(g_test_queue);
	*item = TEST_ITEM_ID;
    NTESTSUITE_EXPECT_UINT(TEST_ITEM_ID);
	item = nk_queue__peek_tail(g_test_queue);
	NTESTSUITE_ACTUAL_UINT(*item);
}

static void test_nonempty_empty(void)
{
	size_t empty = 0u;

    NTESTSUITE_EXPECT_UINT(QUEUE_SIZE - 2u);
    empty = nk_queue__empty(g_test_queue);
    NTESTSUITE_ACTUAL_UINT((uint32_t)empty);
}

static void test_nonempty_size(void)
{
	size_t size = 0u;

	NTESTSUITE_EXPECT_UINT(QUEUE_SIZE);
	size = nk_queue__size(g_test_queue);
	NTESTSUITE_ACTUAL_UINT((uint32_t)size);
}

static void test_nonempty_is_full(void)
{
	bool is_full = true;

	NTESTSUITE_EXPECT_BOOL(false);
	is_full = nk_queue__is_full(g_test_queue);
	NTESTSUITE_ACTUAL_BOOL(is_full);
}

static void test_nonempty_is_empty(void)
{
	bool is_empty = true;

	NTESTSUITE_EXPECT_BOOL(false);
	is_empty = nk_queue__is_empty(g_test_queue);
	NTESTSUITE_ACTUAL_BOOL(is_empty);
}

static void test_nonempty_fifo_head(void)
{
	uint8_t * item;

	item = nk_queue__put_fifo(g_test_queue);
	*item = TEST_ITEM_ID;
    NTESTSUITE_EXPECT_UINT(TEST_ITEM_ID);
    item = nk_queue__peek_head(g_test_queue);
    NTESTSUITE_ACTUAL_UINT(*item);
}

static void test_nonempty_fifo_tail(void)
{
	uint8_t * item;

	item = nk_queue__put_fifo(g_test_queue);
	*item = TEST_ITEM_ID;
    NTESTSUITE_EXPECT_UINT(TEST_PREDEFINED_ID_0);
    item = nk_queue__peek_tail(g_test_queue);
    NTESTSUITE_ACTUAL_UINT(*item);
}

static void test_nonempty_lifo_head(void)
{
	uint8_t * item;

	item = nk_queue__put_lifo(g_test_queue);
	*item = TEST_ITEM_ID;
    NTESTSUITE_EXPECT_UINT(TEST_PREDEFINED_ID_1);
    item = nk_queue__peek_head(g_test_queue);
    NTESTSUITE_ACTUAL_UINT(*item);
}

static void test_nonempty_lifo_tail(void)
{
	uint8_t * item;

	item = nk_queue__put_lifo(g_test_queue);
	* item = TEST_ITEM_ID;
    NTESTSUITE_EXPECT_UINT(TEST_ITEM_ID);
    item = nk_queue__peek_tail(g_test_queue);
    NTESTSUITE_ACTUAL_UINT(*item);
}

static void test_full_empty(void)
{
    size_t empty = QUEUE_SIZE;

	NTESTSUITE_EXPECT_UINT(0u);
	empty = nk_queue__empty(g_test_queue);
	NTESTSUITE_ACTUAL_UINT((uint32_t)empty);
}

static void test_full_size(void)
{
    size_t size = 0u;

	NTESTSUITE_EXPECT_UINT(QUEUE_SIZE);
	size = nk_queue__size(g_test_queue);
	NTESTSUITE_ACTUAL_UINT((uint32_t)size);
}

static void test_full_is_full(void)
{
	bool is_full = false;

	NTESTSUITE_EXPECT_BOOL(true);
	is_full = nk_queue__is_full(g_test_queue);
	NTESTSUITE_ACTUAL_BOOL(is_full);
}

static void test_full_is_empty(void)
{
	bool is_empty = true;

	NTESTSUITE_EXPECT_BOOL(false);
	is_empty = nk_queue__is_empty(g_test_queue);
	NTESTSUITE_ACTUAL_BOOL(is_empty);
}

static void setup_empty(void)
{
	g_test_queue = nk_queue__create(sizeof(uint8_t), QUEUE_SIZE);
}

static void teardown_empty(void)
{
	nk_queue__delete(g_test_queue);
}

static void setup_nonempty(void)
{
	g_test_queue = nk_queue__create(sizeof(uint8_t), QUEUE_SIZE);
	*(uint8_t *)nk_queue__put_fifo(g_test_queue) = TEST_PREDEFINED_ID_0;
	*(uint8_t *)nk_queue__put_fifo(g_test_queue) = TEST_PREDEFINED_ID_1;
}

static void teardown_nonempty(void)
{
	nk_queue__delete(g_test_queue);
}

static void setup_full(void)
{
	g_test_queue = nk_queue__create(sizeof(uint8_t), QUEUE_SIZE);
	*(uint8_t *)nk_queue__put_fifo(g_test_queue) = TEST_PREDEFINED_ID_0;
	*(uint8_t *)nk_queue__put_fifo(g_test_queue) = TEST_PREDEFINED_ID_1;
	*(uint8_t *)nk_queue__put_fifo(g_test_queue) = TEST_PREDEFINED_ID_2;
	*(uint8_t *)nk_queue__put_fifo(g_test_queue) = TEST_PREDEFINED_ID_3;
}

static void teardown_full(void)
{
	nk_queue__delete(g_test_queue);
}

static void test_nk_queue_none(void)
{
	static const struct nk_testsuite_test none_tests[] =
	{
		NK_TESTSUITE_TEST(test_none_init),
		NK_TESTSUITE_TEST_TERMINATE()
	};
	nk_testsuite_set_fixture(NULL, NULL, NK_TESTSUITE_FIXTURE_NAME(none));
	nk_testsuite_run_tests(none_tests);
}

static void test_nk_queue_empty(void)
{
	static const struct nk_testsuite_test empty_tests[] =
	{
		NK_TESTSUITE_TEST(test_empty_empty),
		NK_TESTSUITE_TEST(test_empty_size),
		NK_TESTSUITE_TEST(test_empty_is_full),
		NK_TESTSUITE_TEST(test_empty_is_empty),
		NK_TESTSUITE_TEST(test_empty_fifo_head),
		NK_TESTSUITE_TEST(test_empty_fifo_tail),
		NK_TESTSUITE_TEST(test_empty_lifo_head),
		NK_TESTSUITE_TEST(test_empty_lifo_tail),
		NK_TESTSUITE_TEST_TERMINATE()
	};
	nk_testsuite_set_fixture(
			setup_empty, teardown_empty, NK_TESTSUITE_FIXTURE_NAME(empty));
	nk_testsuite_run_tests(empty_tests);
}

static void test_nk_queue_nonempty(void)
{
	static const struct nk_testsuite_test non_empty_tests[] =
	{
		NK_TESTSUITE_TEST(test_nonempty_empty),
		NK_TESTSUITE_TEST(test_nonempty_size),
		NK_TESTSUITE_TEST(test_nonempty_is_full),
		NK_TESTSUITE_TEST(test_nonempty_is_empty),
		NK_TESTSUITE_TEST(test_nonempty_fifo_head),
		NK_TESTSUITE_TEST(test_nonempty_fifo_tail),
		NK_TESTSUITE_TEST(test_nonempty_lifo_head),
		NK_TESTSUITE_TEST(test_nonempty_lifo_tail),
		NK_TESTSUITE_TEST_TERMINATE()
	};
	nk_testsuite_set_fixture(
			setup_nonempty,
			teardown_nonempty,
			NK_TESTSUITE_FIXTURE_NAME(nonempty));
	nk_testsuite_run_tests(non_empty_tests);
}

static void test_nk_queue_full(void)
{
	static const struct nk_testsuite_test full_tests[] =
	{
		NK_TESTSUITE_TEST(test_full_empty),
		NK_TESTSUITE_TEST(test_full_size),
		NK_TESTSUITE_TEST(test_full_is_full),
		NK_TESTSUITE_TEST(test_full_is_empty),
		NK_TESTSUITE_TEST_TERMINATE()
	};
	nk_testsuite_set_fixture(
			setup_full, teardown_full, NK_TESTSUITE_FIXTURE_NAME(full));
	nk_testsuite_run_tests(full_tests);
}

void test_nk_queue(void)
{
	test_nk_queue_none();
	test_nk_queue_empty();
	test_nk_queue_nonempty();
	test_nk_queue_full();
}


