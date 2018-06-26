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

#include <stddef.h>

#include "testsuite/ntestsuite.h"
#include "list/nlist_sll.h"
#include "test_nlist_sll.h"

struct node_list
{
    struct nlist_sll list;
    char letter;
};

static struct node_list g_node_a =
{
    .letter = 'a'
};

static struct node_list g_node_b =
{
    .letter = 'b'
};

static struct node_list g_node_c =
{
    .letter = 'c'
};

static struct node_list g_node_d =
{
    .letter = 'd'
};

static struct node_list g_node_0 =
{
    .letter = '0'
};

static struct nlist_sll g_sentinel;

static void test_none_init(void)
{
    struct nlist_sll list;

    NTESTSUITE_EXPECT_PTR(&list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_init(&list));
    NTESTSUITE_EVALUATE();
}

static void test_none_init_is_null_true(void)
{
    struct nlist_sll list = {0};

    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(nlist_sll_is_null(&list));
    NTESTSUITE_EVALUATE();
}

static void test_none_init_is_null_false(void)
{
    struct nlist_sll list = {0};

    NTESTSUITE_EXPECT_BOOL(false);
    nlist_sll_init(&list);
    NTESTSUITE_ACTUAL_BOOL(nlist_sll_is_null(&list));
    NTESTSUITE_EVALUATE();
}

static void test_none_is_null_false(void)
{
    struct nlist_sll list;

    NTESTSUITE_EXPECT_BOOL(false);
    nlist_sll_init(&list);
    NTESTSUITE_ACTUAL_BOOL(nlist_sll_is_null(&list));
    NTESTSUITE_EVALUATE();
}

static void test_empty_is_empty(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(nlist_sll_is_empty(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_empty_next(void)
{
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_empty_prev(void)
{
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_empty_first(void)
{
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_first(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_empty_last(void)
{
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_last(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_empty_add_after(void)
{
    nlist_sll_add_after(&g_sentinel, &g_node_a.list);

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_a.list));
    NTESTSUITE_EVALUATE();
}

static void test_empty_add_before(void)
{
    nlist_sll_add_before(&g_sentinel, &g_node_a.list);

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_a.list));
    NTESTSUITE_EVALUATE();
}

static void test_empty_add_head(void)
{
    nlist_sll_add_head(&g_sentinel, &g_node_a.list);
   
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_a.list));
    NTESTSUITE_EVALUATE();
}

static void test_empty_add_tail(void)
{
    nlist_sll_add_tail(&g_sentinel, &g_node_a.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_a.list));
    NTESTSUITE_EVALUATE();
}

static void test_empty_remove(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    nlist_sll_remove(&g_sentinel);
    NTESTSUITE_ACTUAL_BOOL(nlist_sll_is_empty(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_single_is_empty(void)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(nlist_sll_is_empty(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_single_next(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_single_prev(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_single_first(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_first(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_single_last(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_last(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_single_add_after(void)
{
    nlist_sll_add_after(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_b.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_b.list));
    NTESTSUITE_EVALUATE();
}

static void test_single_add_before(void)
{
    nlist_sll_add_before(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_b.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_b.list));
    NTESTSUITE_EVALUATE();
}

static void test_single_add_head(void)
{
    nlist_sll_add_head(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_b.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_b.list));
    NTESTSUITE_EVALUATE();
}

static void test_single_add_tail(void)
{
    nlist_sll_add_tail(&g_sentinel, &g_node_b.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_b.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_b.list));
    NTESTSUITE_EVALUATE();
}

static void test_single_remove(void)
{
    nlist_sll_remove(&g_node_a.list);
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(nlist_sll_is_empty(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_abcd_is_empty(void)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(nlist_sll_is_empty(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_abcd_next(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_abcd_prev(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_abcd_first(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_first(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_abcd_last(void)
{
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_last(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void test_abcd_add_after(void)
{
    nlist_sll_add_after(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_d.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_c.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_d.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_0.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_0.list));
    NTESTSUITE_EVALUATE();
}

static void test_abcd_add_before(void)
{
    nlist_sll_add_before(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_0.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_0.list));
    NTESTSUITE_EVALUATE();
}

static void test_abcd_add_head(void)
{
    nlist_sll_add_head(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_b.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_a.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_0.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_0.list));
    NTESTSUITE_EVALUATE();
}

static void test_abcd_add_tail(void)
{
    nlist_sll_add_tail(&g_sentinel, &g_node_0.list);
    
    NTESTSUITE_EXPECT_PTR(&g_node_a.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_sentinel));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_0.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_d.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_c.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_d.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_sentinel);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_next(&g_node_0.list));
    NTESTSUITE_EVALUATE();
    
    NTESTSUITE_EXPECT_PTR(&g_node_d.list);
    NTESTSUITE_ACTUAL_PTR(nlist_sll_prev(&g_node_0.list));
    NTESTSUITE_EVALUATE();
}

static void test_abcd_remove(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    nlist_sll_remove(&g_node_a.list);
    nlist_sll_remove(&g_node_b.list);
    nlist_sll_remove(&g_node_c.list);
    nlist_sll_remove(&g_node_d.list);
    NTESTSUITE_ACTUAL_BOOL(nlist_sll_is_empty(&g_sentinel));
    NTESTSUITE_EVALUATE();
}

static void setup_empty(void)
{
    nlist_sll_init(&g_sentinel);
    nlist_sll_init(&g_node_a.list);
    nlist_sll_init(&g_node_b.list);
    nlist_sll_init(&g_node_c.list);
    nlist_sll_init(&g_node_d.list);
    nlist_sll_init(&g_node_0.list);
}

static void setup_single(void)
{
    nlist_sll_init(&g_sentinel);
    nlist_sll_init(&g_node_a.list);
    nlist_sll_init(&g_node_b.list);
    nlist_sll_init(&g_node_c.list);
    nlist_sll_init(&g_node_d.list);
    nlist_sll_init(&g_node_0.list);
    nlist_sll_add_tail(&g_sentinel, &g_node_a.list);
}

static void setup_abcd(void)
{
    nlist_sll_init(&g_sentinel);
    nlist_sll_init(&g_node_a.list);
    nlist_sll_init(&g_node_b.list);
    nlist_sll_init(&g_node_c.list);
    nlist_sll_init(&g_node_d.list);
    nlist_sll_init(&g_node_0.list);
    nlist_sll_add_tail(&g_sentinel, &g_node_a.list);
    nlist_sll_add_tail(&g_sentinel, &g_node_b.list);
    nlist_sll_add_tail(&g_sentinel, &g_node_c.list);
    nlist_sll_add_tail(&g_sentinel, &g_node_d.list);
}

void test_nlist_sll(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);
    NTESTSUITE_FIXTURE(empty, setup_empty, NULL);
    NTESTSUITE_FIXTURE(single, setup_single, NULL);
    NTESTSUITE_FIXTURE(abcd, setup_abcd, NULL);

    NTESTSUITE_RUN(none, test_none_init);
    NTESTSUITE_RUN(none, test_none_init_is_null_true);
    NTESTSUITE_RUN(none, test_none_init_is_null_false);
    NTESTSUITE_RUN(none, test_none_is_null_false);
    NTESTSUITE_PRINT_RESULTS(none);   

    NTESTSUITE_RUN(empty, test_empty_is_empty);
    NTESTSUITE_RUN(empty, test_empty_next);
    NTESTSUITE_RUN(empty, test_empty_prev);
    NTESTSUITE_RUN(empty, test_empty_first);
    NTESTSUITE_RUN(empty, test_empty_last);
    NTESTSUITE_RUN(empty, test_empty_add_after);
    NTESTSUITE_RUN(empty, test_empty_add_before);
    NTESTSUITE_RUN(empty, test_empty_add_head);
    NTESTSUITE_RUN(empty, test_empty_add_tail);
    NTESTSUITE_RUN(empty, test_empty_remove);
    NTESTSUITE_PRINT_RESULTS(empty);   

    NTESTSUITE_RUN(single, test_single_is_empty);
    NTESTSUITE_RUN(single, test_single_next);
    NTESTSUITE_RUN(single, test_single_prev);
    NTESTSUITE_RUN(single, test_single_first);
    NTESTSUITE_RUN(single, test_single_last);
    NTESTSUITE_RUN(single, test_single_add_after);
    NTESTSUITE_RUN(single, test_single_add_before);
    NTESTSUITE_RUN(single, test_single_add_head);
    NTESTSUITE_RUN(single, test_single_add_tail);
    NTESTSUITE_RUN(single, test_single_remove);
    NTESTSUITE_PRINT_RESULTS(single);   
    
    NTESTSUITE_RUN(abcd, test_abcd_is_empty);
    NTESTSUITE_RUN(abcd, test_abcd_next);
    NTESTSUITE_RUN(abcd, test_abcd_prev);
    NTESTSUITE_RUN(abcd, test_abcd_first);
    NTESTSUITE_RUN(abcd, test_abcd_last);
    NTESTSUITE_RUN(abcd, test_abcd_add_after);
    NTESTSUITE_RUN(abcd, test_abcd_add_before);
    NTESTSUITE_RUN(abcd, test_abcd_add_head);
    NTESTSUITE_RUN(abcd, test_abcd_add_tail);
    NTESTSUITE_RUN(abcd, test_abcd_remove);
    NTESTSUITE_PRINT_RESULTS(abcd);   
}


