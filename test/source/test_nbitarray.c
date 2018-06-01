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
#include "sched/nsched_bitarray.h"
#include "test_nbitarray.h"

#define SETUP_SET(a_num)        nbitarray_set(&g_instance, (a_num))
#define EXPECT(a_num)           g_expected = (a_num)

#define EVALUATE()                                                          \
    NTESTSUITE_ASSERT_EQUAL_UINT((g_expected), nbitarray_msbs(&g_instance))


static void test_init(void);
static void test_set_get_0(void);
static void test_set_get_1(void);
static void test_set_get_127(void);
static void test_set_get_255(void);
static void test_set_clr_get_1(void);
static void test_set_clr_get_255(void);
static void test_set_m_0(void);
static void test_set_m_1(void);
static void test_set_m_255(void);
static void test_set_clr_get_255_m(void);

static uint32_t g_output;
static uint32_t g_expected;
static struct nbitarray g_instance;

static void test_init(void)
{
    struct nbitarray a_instance;

    nbitarray_init(&a_instance);
}

static void test_set_get_0(void)
{
    SETUP_SET(0);
    EXPECT(0);
    EVALUATE();
}

static void test_set_get_1(void)
{
    SETUP_SET(1);
    EXPECT(1);
    EVALUATE();
}

static void test_set_get_127(void)
{
    SETUP_SET(127);
    EXPECT(127);
    EVALUATE();
}

static void test_set_get_255(void)
{
    SETUP_SET(255);
    EXPECT(255);
    EVALUATE();
}

static void test_set_m_0(void)
{
    SETUP_SET(0);
    EXPECT(0);
    nbitarray_set(&g_instance, 0);
    EVALUATE();
}

static void test_set_m_1(void)
{
    SETUP_SET(0);
    SETUP_SET(1);
    EXPECT(1);
    nbitarray_set(&g_instance, 1);
    EVALUATE();
}

static void test_set_m_255(void)
{
    SETUP_SET(0);
    SETUP_SET(1);
    SETUP_SET(255);
    EXPECT(255);
    nbitarray_set(&g_instance, 255);
    EVALUATE();
}

static void test_set_clr_get_1(void)
{
    SETUP_SET(0);
    SETUP_SET(1);
    EXPECT(0);
    nbitarray_clear(&g_instance, 1);
    EVALUATE();
}

static void test_set_clr_get_255(void)
{
    SETUP_SET(0);
    SETUP_SET(1);
    SETUP_SET(255);
    EXPECT(1);
    nbitarray_clear(&g_instance, 255);
    EVALUATE();
}

static void test_set_clr_get_255_m(void)
{
    SETUP_SET(0);
    SETUP_SET(1);
    SETUP_SET(255);
    EXPECT(255);
    nbitarray_clear(&g_instance, 1);
    EVALUATE();
}

static void setup_empty(void)
{
    nbitarray_init(&g_instance);
    g_output = UINT32_MAX;
    g_expected = 0u;
}

static void teardown_empty(void)
{
}

void test_nbitarray(void)
{
    NTESTSUITE_FIXTURE(empty, setup_empty, teardown_empty);
    NTESTSUITE_RUN(empty, test_init);
    NTESTSUITE_RUN(empty, test_set_get_0);
    NTESTSUITE_RUN(empty, test_set_get_1);
    NTESTSUITE_RUN(empty, test_set_get_127);
    NTESTSUITE_RUN(empty, test_set_get_255);
    NTESTSUITE_RUN(empty, test_set_m_0);
    NTESTSUITE_RUN(empty, test_set_m_1);
    NTESTSUITE_RUN(empty, test_set_m_255);
    NTESTSUITE_RUN(empty, test_set_clr_get_1);
    NTESTSUITE_RUN(empty, test_set_clr_get_255);
    NTESTSUITE_RUN(empty, test_set_clr_get_255_m);
    NTESTSUITE_PRINT_RESULTS(empty);   
}


