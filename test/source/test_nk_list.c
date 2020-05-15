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

#include "test_nk_list.h"

#include <stddef.h>

#include "nk_list.h"
#include "ntestsuite.h"

struct node_list
{
    struct nk_list__node list;
};

static struct node_list g_node_a;

static struct node_list g_node_b;

static struct node_list g_node_c;

static struct node_list g_node_d;

static struct node_list g_node_0;

static struct nk_list__node g_sentinel;

static void test_none_object(void)
{
	struct node_list a_node;

	nk_list__init(&a_node.list, &a_node);

	NTESTSUITE_EXPECT_PTR(&a_node);
	NTESTSUITE_ACTUAL_PTR(nk_list__object(&a_node.list));
}

static void test_empty_is_empty(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(nk_list__is_empty(&g_sentinel));
}

static void test_empty_next(void)
{
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
}

static void test_empty_prev(void)
{
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
}

static void test_empty_add_after(void)
{
    nk_list__add_after(&g_sentinel, &g_node_a.list);

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_a.list));
}

static void test_empty_add_before(void)
{
    nk_list__add_before(&g_sentinel, &g_node_a.list);

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));

    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_a.list));
}

static void test_empty_add_head(void)
{
    nk_list__add_head(&g_sentinel, &g_node_a.list);
   
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_a.list));
}

static void test_empty_add_tail(void)
{
    nk_list__add_tail(&g_sentinel, &g_node_a.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));

    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_a.list));
}

static void test_empty_remove(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    nk_list__remove(&g_sentinel);
    NTESTSUITE_ACTUAL_BOOL(nk_list__is_empty(&g_sentinel));
}

static void test_single_is_empty(void)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(nk_list__is_empty(&g_sentinel));
}

static void test_single_next(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
}

static void test_single_prev(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
}

static void test_single_add_after(void)
{
    nk_list__add_after(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_b.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_b.list));
}

static void test_single_add_before(void)
{
    nk_list__add_before(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_b.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_b.list));
}

static void test_single_add_head(void)
{
    nk_list__add_head(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_b.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_b.list));
}

static void test_single_add_tail(void)
{
    nk_list__add_tail(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_b.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_b.list));
}

static void test_single_remove(void)
{
    nk_list__remove(&g_node_a.list);
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(nk_list__is_empty(&g_sentinel));
}

static void test_abcd_is_empty(void)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(nk_list__is_empty(&g_sentinel));
}

static void test_abcd_next(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
}

static void test_abcd_prev(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
}

static void test_abcd_add_after(void)
{
    nk_list__add_after(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_d.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_c.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_d.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_0.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_0.list));
}

static void test_abcd_add_before(void)
{
    nk_list__add_before(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_0.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_0.list));
}

static void test_abcd_add_head(void)
{
    nk_list__add_head(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_0.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_0.list));
}

static void test_abcd_add_tail(void)
{
    nk_list__add_tail(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_d.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_c.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_d.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list__next(&g_node_0.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nk_list__prev(&g_node_0.list));
}

static void test_abcd_remove(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    nk_list__remove(&g_node_a.list);
    nk_list__remove(&g_node_b.list);
    nk_list__remove(&g_node_c.list);
    nk_list__remove(&g_node_d.list);
    NTESTSUITE_ACTUAL_BOOL(nk_list__is_empty(&g_sentinel));
}

static void setup_empty(void)
{
	nk_list__init(&g_sentinel, NULL);
	nk_list__init(&g_node_a.list, &g_node_a);
	nk_list__init(&g_node_b.list, &g_node_b);
	nk_list__init(&g_node_c.list, &g_node_c);
	nk_list__init(&g_node_d.list, &g_node_d);
	nk_list__init(&g_node_0.list, &g_node_0);
}

static void setup_single(void)
{
	nk_list__init(&g_sentinel, NULL);
	nk_list__init(&g_node_a.list, &g_node_a);
	nk_list__init(&g_node_b.list, &g_node_b);
	nk_list__init(&g_node_c.list, &g_node_c);
	nk_list__init(&g_node_d.list, &g_node_d);
	nk_list__init(&g_node_0.list, &g_node_0);
    nk_list__add_tail(&g_sentinel, &g_node_a.list);
}

static void setup_abcd(void)
{
    nk_list__init(&g_sentinel, NULL);
    nk_list__init(&g_node_a.list, &g_node_a);
    nk_list__init(&g_node_b.list, &g_node_b);
    nk_list__init(&g_node_c.list, &g_node_c);
    nk_list__init(&g_node_d.list, &g_node_d);
    nk_list__init(&g_node_0.list, &g_node_0);
    nk_list__add_tail(&g_sentinel, &g_node_a.list);
    nk_list__add_tail(&g_sentinel, &g_node_b.list);
    nk_list__add_tail(&g_sentinel, &g_node_c.list);
    nk_list__add_tail(&g_sentinel, &g_node_d.list);
}

static void test_nk_list_none(void)
{
	static const struct nk_testsuite_test tests_none[] =
	{
		NK_TESTSUITE_TEST(test_none_object),
		NK_TESTSUITE_TEST_TERMINATE()
	};
	nk_testsuite_set_fixture(NULL, NULL, NK_TESTSUITE_FIXTURE_NAME(none));
	nk_testsuite_run_tests(tests_none);
}

static void test_nk_list_empty(void)
{
	static const struct nk_testsuite_test tests_empty[] =
	{
		NK_TESTSUITE_TEST(test_empty_is_empty),
		NK_TESTSUITE_TEST(test_empty_next),
		NK_TESTSUITE_TEST(test_empty_prev),
		NK_TESTSUITE_TEST(test_empty_add_after),
		NK_TESTSUITE_TEST(test_empty_add_before),
		NK_TESTSUITE_TEST(test_empty_add_head),
		NK_TESTSUITE_TEST(test_empty_add_tail),
		NK_TESTSUITE_TEST(test_empty_remove),
		NK_TESTSUITE_TEST_TERMINATE()
	};
	nk_testsuite_set_fixture(
			setup_empty, NULL, NK_TESTSUITE_FIXTURE_NAME(empty));
	nk_testsuite_run_tests(tests_empty);
}

static void test_nk_list_single(void)
{
	static const struct nk_testsuite_test tests_single[] =
	{
		NK_TESTSUITE_TEST(test_single_is_empty),
		NK_TESTSUITE_TEST(test_single_next),
		NK_TESTSUITE_TEST(test_single_prev),
		NK_TESTSUITE_TEST(test_single_add_after),
		NK_TESTSUITE_TEST(test_single_add_before),
		NK_TESTSUITE_TEST(test_single_add_head),
		NK_TESTSUITE_TEST(test_single_add_tail),
		NK_TESTSUITE_TEST(test_single_remove),
		NK_TESTSUITE_TEST_TERMINATE()
	};
	nk_testsuite_set_fixture(
			setup_single, NULL, NK_TESTSUITE_FIXTURE_NAME(single));
	nk_testsuite_run_tests(tests_single);
}

static void test_nk_list_abcd(void)
{
	static const struct nk_testsuite_test tests_abcd[] =
	{
		NK_TESTSUITE_TEST(test_abcd_is_empty),
		NK_TESTSUITE_TEST(test_abcd_next),
		NK_TESTSUITE_TEST(test_abcd_prev),
		NK_TESTSUITE_TEST(test_abcd_add_after),
		NK_TESTSUITE_TEST(test_abcd_add_before),
		NK_TESTSUITE_TEST(test_abcd_add_head),
		NK_TESTSUITE_TEST(test_abcd_add_tail),
		NK_TESTSUITE_TEST(test_abcd_remove),
		NK_TESTSUITE_TEST_TERMINATE()
	};
	nk_testsuite_set_fixture(
			setup_abcd, NULL, NK_TESTSUITE_FIXTURE_NAME(abcd));
	nk_testsuite_run_tests(tests_abcd);
}

void test_nk_list(void)
{
	test_nk_list_none();
	test_nk_list_empty();
	test_nk_list_single();
	test_nk_list_abcd();
}


