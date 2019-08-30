/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */

#include <stddef.h>
#include <stdint.h>
#include <test_nlist_dll.h>

#include "../testsuite/ntestsuite.h"
#include "sys/nlist_dll.h"

struct node_list
{
    struct nlist_dll list;
};

static struct node_list g_node_a;

static struct node_list g_node_b;

static struct node_list g_node_c;

static struct node_list g_node_d;

static struct node_list g_node_0;

static struct nlist_dll g_sentinel;

NTESTSUITE_TEST(test_none_init)
{
    struct nlist_dll list;

    ntestsuite_expect_ptr(&list);
    ntestsuite_actual_ptr(nlist_dll_init(&list));
}

NTESTSUITE_TEST(test_none_init_is_null_true)
{
    struct nlist_dll list = {0};

    ntestsuite_expect_bool(true);
    ntestsuite_actual_bool(nlist_dll_is_null(&list));
}

NTESTSUITE_TEST(test_none_init_is_null_false)
{
    struct nlist_dll list = {0};

    ntestsuite_expect_bool(false);
    nlist_dll_init(&list);
    ntestsuite_actual_bool(nlist_dll_is_null(&list));
}

NTESTSUITE_TEST(test_none_is_null_false)
{
    struct nlist_dll list;

    ntestsuite_expect_bool(false);
    nlist_dll_init(&list);
    ntestsuite_actual_bool(nlist_dll_is_null(&list));
}

NTESTSUITE_TEST(test_empty_is_empty)
{
    ntestsuite_expect_bool(true);
    ntestsuite_actual_bool(nlist_dll_is_empty(&g_sentinel));
}

NTESTSUITE_TEST(test_empty_next)
{
    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));
}

NTESTSUITE_TEST(test_empty_prev)
{
    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));
}

NTESTSUITE_TEST(test_empty_first)
{
    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_first(&g_sentinel));
}

NTESTSUITE_TEST(test_empty_last)
{
    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_last(&g_sentinel));
}

NTESTSUITE_TEST(test_empty_add_after)
{
    nlist_dll_add_after(&g_sentinel, &g_node_a.list);

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_a.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_a.list));
}

NTESTSUITE_TEST(test_empty_add_before)
{
    nlist_dll_add_before(&g_sentinel, &g_node_a.list);

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_a.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_a.list));
}

NTESTSUITE_TEST(test_empty_add_head)
{
    nlist_dll_add_head(&g_sentinel, &g_node_a.list);

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_a.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_a.list));
}

NTESTSUITE_TEST(test_empty_add_tail)
{
    nlist_dll_add_tail(&g_sentinel, &g_node_a.list);

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_a.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_a.list));
}

NTESTSUITE_TEST(test_empty_remove)
{
    ntestsuite_expect_bool(true);
    nlist_dll_remove(&g_sentinel);
    ntestsuite_actual_bool(nlist_dll_is_empty(&g_sentinel));
}

NTESTSUITE_TEST(test_single_is_empty)
{
    ntestsuite_expect_bool(false);
    ntestsuite_actual_bool(nlist_dll_is_empty(&g_sentinel));
}

NTESTSUITE_TEST(test_single_next)
{
    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));
}

NTESTSUITE_TEST(test_single_prev)
{
    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));
}

NTESTSUITE_TEST(test_single_first)
{
    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_first(&g_sentinel));
}

NTESTSUITE_TEST(test_single_last)
{
    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_last(&g_sentinel));
}

NTESTSUITE_TEST(test_single_add_after)
{
    nlist_dll_add_after(&g_sentinel, &g_node_b.list);

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_b.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_b.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_a.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_a.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_b.list));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_b.list));
}

NTESTSUITE_TEST(test_single_add_before)
{
    nlist_dll_add_before(&g_sentinel, &g_node_b.list);

    ntestsuite_expect_ptr(&g_node_b.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_a.list));

    ntestsuite_expect_ptr(&g_node_b.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_a.list));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_b.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_b.list));
}

NTESTSUITE_TEST(test_single_add_head)
{
    nlist_dll_add_head(&g_sentinel, &g_node_b.list);

    ntestsuite_expect_ptr(&g_node_b.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_a.list));

    ntestsuite_expect_ptr(&g_node_b.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_a.list));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_b.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_b.list));
}

NTESTSUITE_TEST(test_single_add_tail)
{
    nlist_dll_add_tail(&g_sentinel, &g_node_b.list);

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_b.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_b.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_a.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_a.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_b.list));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_b.list));
}

NTESTSUITE_TEST(test_single_remove)
{
    nlist_dll_remove(&g_node_a.list);
    ntestsuite_expect_bool(true);
    ntestsuite_actual_bool(nlist_dll_is_empty(&g_sentinel));
}

NTESTSUITE_TEST(test_abcd_is_empty)
{
    ntestsuite_expect_bool(false);
    ntestsuite_actual_bool(nlist_dll_is_empty(&g_sentinel));
}

NTESTSUITE_TEST(test_abcd_next)
{
    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));
}

NTESTSUITE_TEST(test_abcd_prev)
{
    ntestsuite_expect_ptr(&g_node_d.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));
}

NTESTSUITE_TEST(test_abcd_first)
{
    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_first(&g_sentinel));
}

NTESTSUITE_TEST(test_abcd_last)
{
    ntestsuite_expect_ptr(&g_node_d.list);
    ntestsuite_actual_ptr(nlist_dll_last(&g_sentinel));
}

NTESTSUITE_TEST(test_abcd_add_after)
{
    nlist_dll_add_after(&g_sentinel, &g_node_0.list);

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_0.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_0.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_d.list));

    ntestsuite_expect_ptr(&g_node_c.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_d.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_0.list));

    ntestsuite_expect_ptr(&g_node_d.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_0.list));
}

NTESTSUITE_TEST(test_abcd_add_before)
{
    nlist_dll_add_before(&g_sentinel, &g_node_0.list);

    ntestsuite_expect_ptr(&g_node_0.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_d.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_b.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_a.list));

    ntestsuite_expect_ptr(&g_node_0.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_a.list));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_0.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_0.list));
}

NTESTSUITE_TEST(test_abcd_add_head)
{
    nlist_dll_add_head(&g_sentinel, &g_node_0.list);

    ntestsuite_expect_ptr(&g_node_0.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_d.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_b.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_a.list));

    ntestsuite_expect_ptr(&g_node_0.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_a.list));

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_0.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_0.list));
}

NTESTSUITE_TEST(test_abcd_add_tail)
{
    nlist_dll_add_tail(&g_sentinel, &g_node_0.list);

    ntestsuite_expect_ptr(&g_node_a.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_0.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_sentinel));

    ntestsuite_expect_ptr(&g_node_0.list);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_d.list));

    ntestsuite_expect_ptr(&g_node_c.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_d.list));

    ntestsuite_expect_ptr(&g_sentinel);
    ntestsuite_actual_ptr(nlist_dll_next(&g_node_0.list));

    ntestsuite_expect_ptr(&g_node_d.list);
    ntestsuite_actual_ptr(nlist_dll_prev(&g_node_0.list));
}

NTESTSUITE_TEST(test_abcd_remove)
{
    ntestsuite_expect_bool(true);
    nlist_dll_remove(&g_node_a.list);
    nlist_dll_remove(&g_node_b.list);
    nlist_dll_remove(&g_node_c.list);
    nlist_dll_remove(&g_node_d.list);
    ntestsuite_actual_bool(nlist_dll_is_empty(&g_sentinel));
}

static void setup_empty(void)
{
    nlist_dll_init(&g_sentinel);
    nlist_dll_init(&g_node_a.list);
    nlist_dll_init(&g_node_b.list);
    nlist_dll_init(&g_node_c.list);
    nlist_dll_init(&g_node_d.list);
    nlist_dll_init(&g_node_0.list);
}

static void setup_single(void)
{
    nlist_dll_init(&g_sentinel);
    nlist_dll_init(&g_node_a.list);
    nlist_dll_init(&g_node_b.list);
    nlist_dll_init(&g_node_c.list);
    nlist_dll_init(&g_node_d.list);
    nlist_dll_init(&g_node_0.list);
    nlist_dll_add_tail(&g_sentinel, &g_node_a.list);
}

static void setup_abcd(void)
{
    nlist_dll_init(&g_sentinel);
    nlist_dll_init(&g_node_a.list);
    nlist_dll_init(&g_node_b.list);
    nlist_dll_init(&g_node_c.list);
    nlist_dll_init(&g_node_d.list);
    nlist_dll_init(&g_node_0.list);
    nlist_dll_add_tail(&g_sentinel, &g_node_a.list);
    nlist_dll_add_tail(&g_sentinel, &g_node_b.list);
    nlist_dll_add_tail(&g_sentinel, &g_node_c.list);
    nlist_dll_add_tail(&g_sentinel, &g_node_d.list);
}

void test_exec_nlist_dll(void)
{
    ntestsuite_set_fixture(none, NULL, NULL);
    ntestsuite_run(test_none_init);
    ntestsuite_run(test_none_init_is_null_true);
    ntestsuite_run(test_none_init_is_null_false);
    ntestsuite_run(test_none_is_null_false);

    ntestsuite_set_fixture(empty, setup_empty, NULL);
    ntestsuite_run(test_empty_is_empty);
    ntestsuite_run(test_empty_next);
    ntestsuite_run(test_empty_prev);
    ntestsuite_run(test_empty_first);
    ntestsuite_run(test_empty_last);
    ntestsuite_run(test_empty_add_after);
    ntestsuite_run(test_empty_add_before);
    ntestsuite_run(test_empty_add_head);
    ntestsuite_run(test_empty_add_tail);
    ntestsuite_run(test_empty_remove);

    ntestsuite_set_fixture(single, setup_single, NULL);
    ntestsuite_run(test_single_is_empty);
    ntestsuite_run(test_single_next);
    ntestsuite_run(test_single_prev);
    ntestsuite_run(test_single_first);
    ntestsuite_run(test_single_last);
    ntestsuite_run(test_single_add_after);
    ntestsuite_run(test_single_add_before);
    ntestsuite_run(test_single_add_head);
    ntestsuite_run(test_single_add_tail);
    ntestsuite_run(test_single_remove);

    ntestsuite_set_fixture(abcd, setup_abcd, NULL);
    ntestsuite_run(test_abcd_is_empty);
    ntestsuite_run(test_abcd_next);
    ntestsuite_run(test_abcd_prev);
    ntestsuite_run(test_abcd_first);
    ntestsuite_run(test_abcd_last);
    ntestsuite_run(test_abcd_add_after);
    ntestsuite_run(test_abcd_add_before);
    ntestsuite_run(test_abcd_add_head);
    ntestsuite_run(test_abcd_add_tail);
    ntestsuite_run(test_abcd_remove);
}


