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
    struct nk_list list;
};

static struct node_list g_node_a;

static struct node_list g_node_b;

static struct node_list g_node_c;

static struct node_list g_node_d;

static struct node_list g_node_0;

static struct nk_list g_sentinel;

NTESTSUITE_TEST(test_empty_is_empty)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(NLIST_DLL_IS_EMPTY(&g_sentinel));
}

NTESTSUITE_TEST(test_empty_next)
{
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
}

NTESTSUITE_TEST(test_empty_prev)
{
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
}

NTESTSUITE_TEST(test_empty_add_after)
{
    nk_list_add_after(&g_sentinel, &g_node_a.list);

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_a.list));
}

NTESTSUITE_TEST(test_empty_add_before)
{
    nk_list_add_before(&g_sentinel, &g_node_a.list);

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));

    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_a.list));
}

NTESTSUITE_TEST(test_empty_add_head)
{
    nk_list_add_head(&g_sentinel, &g_node_a.list);
   
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_a.list));
}

NTESTSUITE_TEST(test_empty_add_tail)
{
    nk_list_add_tail(&g_sentinel, &g_node_a.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));

    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_a.list));
}

NTESTSUITE_TEST(test_empty_remove)
{
    NTESTSUITE_EXPECT_BOOL(true);
    nk_list_remove(&g_sentinel);
    NTESTSUITE_ACTUAL_BOOL(NLIST_DLL_IS_EMPTY(&g_sentinel));
}

NTESTSUITE_TEST(test_single_is_empty)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(NLIST_DLL_IS_EMPTY(&g_sentinel));
}

NTESTSUITE_TEST(test_single_next)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
}

NTESTSUITE_TEST(test_single_prev)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
}

NTESTSUITE_TEST(test_single_add_after)
{
    nk_list_add_after(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_b.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_b.list));
}

NTESTSUITE_TEST(test_single_add_before)
{
    nk_list_add_before(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_b.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_b.list));
}

NTESTSUITE_TEST(test_single_add_head)
{
    nk_list_add_head(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_b.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_b.list));
}

NTESTSUITE_TEST(test_single_add_tail)
{
    nk_list_add_tail(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_b.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_b.list));
}

NTESTSUITE_TEST(test_single_remove)
{
    nk_list_remove(&g_node_a.list);
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(NLIST_DLL_IS_EMPTY(&g_sentinel));
}

NTESTSUITE_TEST(test_abcd_is_empty)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(NLIST_DLL_IS_EMPTY(&g_sentinel));
}

NTESTSUITE_TEST(test_abcd_next)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
}

NTESTSUITE_TEST(test_abcd_prev)
{
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
}

NTESTSUITE_TEST(test_abcd_add_after)
{
    nk_list_add_after(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_d.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_c.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_d.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_0.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_0.list));
}

NTESTSUITE_TEST(test_abcd_add_before)
{
    nk_list_add_before(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_0.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_0.list));
}

NTESTSUITE_TEST(test_abcd_add_head)
{
    nk_list_add_head(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_a.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_0.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_0.list));
}

NTESTSUITE_TEST(test_abcd_add_tail)
{
    nk_list_add_tail(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_sentinel));
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_d.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_c.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_d.list));
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nk_list_next(&g_node_0.list));
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nk_list_prev(&g_node_0.list));
}

NTESTSUITE_TEST(test_abcd_remove)
{
    NTESTSUITE_EXPECT_BOOL(true);
    nk_list_remove(&g_node_a.list);
    nk_list_remove(&g_node_b.list);
    nk_list_remove(&g_node_c.list);
    nk_list_remove(&g_node_d.list);
    NTESTSUITE_ACTUAL_BOOL(NLIST_DLL_IS_EMPTY(&g_sentinel));
}

static void setup_empty(void)
{
	nk_list_init(&g_sentinel, NULL);
	nk_list_init(&g_node_a.list, &g_node_a);
	nk_list_init(&g_node_b.list, &g_node_b);
	nk_list_init(&g_node_c.list, &g_node_c);
	nk_list_init(&g_node_d.list, &g_node_d);
	nk_list_init(&g_node_0.list, &g_node_0);
}

static void setup_single(void)
{
	nk_list_init(&g_sentinel, NULL);
	nk_list_init(&g_node_a.list, &g_node_a);
	nk_list_init(&g_node_b.list, &g_node_b);
	nk_list_init(&g_node_c.list, &g_node_c);
	nk_list_init(&g_node_d.list, &g_node_d);
	nk_list_init(&g_node_0.list, &g_node_0);
    nk_list_add_tail(&g_sentinel, &g_node_a.list);
}

static void setup_abcd(void)
{
    nk_list_init(&g_sentinel, NULL);
    nk_list_init(&g_node_a.list, &g_node_a);
    nk_list_init(&g_node_b.list, &g_node_b);
    nk_list_init(&g_node_c.list, &g_node_c);
    nk_list_init(&g_node_d.list, &g_node_d);
    nk_list_init(&g_node_0.list, &g_node_0);
    nk_list_add_tail(&g_sentinel, &g_node_a.list);
    nk_list_add_tail(&g_sentinel, &g_node_b.list);
    nk_list_add_tail(&g_sentinel, &g_node_c.list);
    nk_list_add_tail(&g_sentinel, &g_node_d.list);
}

void test_nk_list(void)
{
    NTESTSUITE_FIXTURE(empty, setup_empty, NULL);
    NTESTSUITE_FIXTURE(single, setup_single, NULL);
    NTESTSUITE_FIXTURE(abcd, setup_abcd, NULL);

    NTESTSUITE_RUN(empty, test_empty_is_empty);
    NTESTSUITE_RUN(empty, test_empty_next);
    NTESTSUITE_RUN(empty, test_empty_prev);
    NTESTSUITE_RUN(empty, test_empty_add_after);
    NTESTSUITE_RUN(empty, test_empty_add_before);
    NTESTSUITE_RUN(empty, test_empty_add_head);
    NTESTSUITE_RUN(empty, test_empty_add_tail);
    NTESTSUITE_RUN(empty, test_empty_remove);
    NTESTSUITE_PRINT_RESULTS(empty);   

    NTESTSUITE_RUN(single, test_single_is_empty);
    NTESTSUITE_RUN(single, test_single_next);
    NTESTSUITE_RUN(single, test_single_prev);
    NTESTSUITE_RUN(single, test_single_add_after);
    NTESTSUITE_RUN(single, test_single_add_before);
    NTESTSUITE_RUN(single, test_single_add_head);
    NTESTSUITE_RUN(single, test_single_add_tail);
    NTESTSUITE_RUN(single, test_single_remove);
    NTESTSUITE_PRINT_RESULTS(single);   
    
    NTESTSUITE_RUN(abcd, test_abcd_is_empty);
    NTESTSUITE_RUN(abcd, test_abcd_next);
    NTESTSUITE_RUN(abcd, test_abcd_prev);
    NTESTSUITE_RUN(abcd, test_abcd_add_after);
    NTESTSUITE_RUN(abcd, test_abcd_add_before);
    NTESTSUITE_RUN(abcd, test_abcd_add_head);
    NTESTSUITE_RUN(abcd, test_abcd_add_tail);
    NTESTSUITE_RUN(abcd, test_abcd_remove);
    NTESTSUITE_PRINT_RESULTS(abcd);   
}


