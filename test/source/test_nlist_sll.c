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

#include "testsuite/ntestsuite.h"
#include "list/nlist_sll.h"
#include "test_nlist_sll.h"

#define EXPECT(a_string)        g_expected = (a_string)

#define EVALUATE()                                                          \
    do {                                                                    \
        node_dump(&g_sentinel, g_output, sizeof(g_output));                 \
        NTESTSUITE_ASSERT_EQUAL_UINT(strlen(g_expected), strlen(g_output)); \
        NTESTSUITE_ASSERT_EQUAL_STRING(g_expected, g_output);               \
    } while (0)

struct node_list
{
    struct nlist_sll list;
    char letter;
};

static void test_initialized(void);
static void test_init_initialized(void);
static void test_init_uninitialized(void);
static void test_is_empty(void);
static void test_add(void);
static void test_remove(void);
static void test_next(void);
static void test_prev(void);
static void test_first(void);
static void test_last(void);
static void test_m_add_head(void);
static void test_m_add_tail(void);
static void test_m_add_middle(void);
static void test_m_remove_middle(void);

static struct node_list * from_list(struct nlist_sll * list);
static struct node_list * node_create(char letter);
static void node_dump(struct nlist_sll * sentinel, char * sequence,
        uint32_t n);
static void node_delete_all(struct nlist_sll * sentinel);

static struct nlist_sll g_sentinel;
static char g_output[100];
static const char * g_expected;

static struct node_list * from_list(struct nlist_sll * list)
{
    return NLIST_ENTRY(list, struct node_list, list);
}

static struct node_list * node_create(char letter)
{
    struct node_list * node;

    node = malloc(sizeof(*node));

    if (!node) {
        return (node);
    }
    nlist_sll_init(&node->list);
    node->letter = letter;

    return (node);
}

static void node_dump(struct nlist_sll * sentinel, char * sequence, uint32_t n)
{
    struct nlist_sll * current;
    uint32_t i;

    for (i = 0u, NLIST_SLL_EACH(current, sentinel)) {
        sequence[i++] = from_list(current)->letter;

        if (i >= n) {
            break;
        }
    }
    sequence[i] = '\0';
}

static void node_delete_all(struct nlist_sll * sentinel)
{
    struct nlist_sll * current;
    struct nlist_sll * iterator;

    for (NLIST_SLL_EACH_SAFE(current, iterator, sentinel)) {
        struct node_list * current_node = from_list(current);
        nlist_sll_remove(current);
        free(current_node);
    }
}

static void test_initialized(void)
{
    struct nlist_sll list = {0};

    NTESTSUITE_ASSERT_EQUAL_BOOL(true, nlist_sll_is_null(&list));
}

static void test_init_initialized(void)
{
    struct nlist_sll list = {0};

    nlist_sll_init(&list);
    NTESTSUITE_ASSERT_EQUAL_BOOL(false, nlist_sll_is_null(&list));
}

static void test_init_uninitialized(void)
{
    struct nlist_sll list;

    nlist_sll_init(&list);
    NTESTSUITE_ASSERT_EQUAL_BOOL(false, nlist_sll_is_null(&list));
}

static void test_is_empty(void)
{
    NTESTSUITE_ASSERT_EQUAL_BOOL(true, nlist_sll_is_empty(&g_sentinel));
}

static void test_add(void)
{
    struct nlist_sll list;

    nlist_sll_init(&list);
    NTESTSUITE_ASSERT_EQUAL_PTR(&list, nlist_sll_add_head(&g_sentinel, &list));
}

static void test_remove(void)
{
    struct nlist_sll list;

    nlist_sll_init(&list);
    nlist_sll_add_head(&g_sentinel, &list);
    nlist_sll_remove(&list);
    NTESTSUITE_ASSERT_EQUAL_BOOL(true, nlist_sll_is_empty(&list));
    NTESTSUITE_ASSERT_EQUAL_BOOL(true, nlist_sll_is_empty(&g_sentinel));
}

static void test_next(void)
{
    struct nlist_sll list;

    nlist_sll_init(&list);
    nlist_sll_add_head(&g_sentinel, &list);
    NTESTSUITE_ASSERT_EQUAL_PTR(&list, nlist_sll_next(&g_sentinel));
}

static void test_prev(void)
{
    struct nlist_sll list;

    nlist_sll_init(&list);
    nlist_sll_add_head(&g_sentinel, &list);
    NTESTSUITE_ASSERT_EQUAL_PTR(&list, nlist_sll_prev(&g_sentinel));
}

static void test_first(void)
{
    struct nlist_sll list;

    nlist_sll_init(&list);
    nlist_sll_add_head(&g_sentinel, &list);
    NTESTSUITE_ASSERT_EQUAL_PTR(&list, nlist_sll_first(&g_sentinel));
}

static void test_last(void)
{
    struct nlist_sll list;

    nlist_sll_init(&list);
    nlist_sll_add_head(&g_sentinel, &list);
    NTESTSUITE_ASSERT_EQUAL_PTR(&list, nlist_sll_last(&g_sentinel));
}

static void test_m_add_head(void)
{
    struct node_list * node;

    EXPECT("dcba");
    
    node = node_create('a');
    nlist_sll_add_head(&g_sentinel, &node->list);
    node = node_create('b');
    nlist_sll_add_head(&g_sentinel, &node->list);
    node = node_create('c');
    nlist_sll_add_head(&g_sentinel, &node->list);
    node = node_create('d');
    nlist_sll_add_head(&g_sentinel, &node->list);

    EVALUATE();
}

static void test_m_add_tail(void)
{
    struct node_list * node;
    
    EXPECT("abcd");

    node = node_create('a');
    nlist_sll_add_tail(&g_sentinel, &node->list);
    node = node_create('b');
    nlist_sll_add_tail(&g_sentinel, &node->list);
    node = node_create('c');
    nlist_sll_add_tail(&g_sentinel, &node->list);
    node = node_create('d');
    nlist_sll_add_tail(&g_sentinel, &node->list);
    
    EVALUATE();
}

static void test_is_not_empty(void)
{
    NTESTSUITE_ASSERT_EQUAL_BOOL(false, nlist_sll_is_empty(&g_sentinel));
}

static void test_m_add_middle(void)
{
    struct node_list * node;
    struct nlist_sll * current;
    
    EXPECT("ab0cd");

    node = node_create('0');
    
    for (NLIST_SLL_EACH(current, &g_sentinel)) {

        if (from_list(current)->letter == 'b') {
            nlist_sll_add_tail(current, &node->list);
        }
    }

    EVALUATE();
}

static void test_m_remove_middle(void)
{
    struct nlist_sll * current;
    struct nlist_sll * iterator;
    
    EXPECT("abd");
    
    for (NLIST_SLL_EACH_SAFE(current, iterator, &g_sentinel)) {

        if (from_list(current)->letter == 'c') {
            nlist_sll_remove(current);
        }
    }

    EVALUATE();
}

static void setup_empty(void)
{
    nlist_sll_init(&g_sentinel);
    memset(g_output, 0xaa, sizeof(g_output));
    g_expected = "";
}

static void teardown_empty(void)
{
}

static void setup_abcd(void)
{
    struct node_list * node;

    setup_empty();

    node = node_create('a');
    nlist_sll_add_tail(&g_sentinel, &node->list);
    node = node_create('b');
    nlist_sll_add_tail(&g_sentinel, &node->list);
    node = node_create('c');
    nlist_sll_add_tail(&g_sentinel, &node->list);
    node = node_create('d');
    nlist_sll_add_tail(&g_sentinel, &node->list);
}

static void teardown_abcd(void)
{
    node_delete_all(&g_sentinel);
}

void test_nlist_sll(void)
{
    NTESTSUITE_FIXTURE(empty, setup_empty, teardown_empty);
    NTESTSUITE_RUN(empty, test_initialized);
    NTESTSUITE_RUN(empty, test_init_initialized);
    NTESTSUITE_RUN(empty, test_init_uninitialized);
    NTESTSUITE_RUN(empty, test_is_empty);
    NTESTSUITE_RUN(empty, test_add);
    NTESTSUITE_RUN(empty, test_remove);
    NTESTSUITE_RUN(empty, test_next);
    NTESTSUITE_RUN(empty, test_prev);
    NTESTSUITE_RUN(empty, test_first);
    NTESTSUITE_RUN(empty, test_last);
    NTESTSUITE_RUN(empty, test_m_add_head);
    NTESTSUITE_RUN(empty, test_m_add_tail);
    NTESTSUITE_PRINT_RESULTS(empty);   
    NTESTSUITE_FIXTURE(abcd, setup_abcd, teardown_abcd);
    NTESTSUITE_RUN(abcd, test_is_not_empty);
    NTESTSUITE_RUN(abcd, test_m_add_middle);
    NTESTSUITE_RUN(abcd, test_m_remove_middle);
    NTESTSUITE_PRINT_RESULTS(abcd);   
}


