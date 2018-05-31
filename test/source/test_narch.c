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
#include "port/nport_arch.h"
#include "test_narch.h"

#define EXPECT(a_num)           g_expected = (a_num)

#define EVALUATE()                                                          \
    do {                                                                    \
        NTESTSUITE_ASSERT_EQUAL_UINT((g_expected), (g_output)); \
    } while (0)

static void test_exp2_0(void);
static void test_exp2_1(void);
static void test_exp2_7(void);
static void test_exp2_31(void);
static void test_log2_1(void);
static void test_log2_3(void);
static void test_log2_UINT8_MAX(void);
static void test_log2_UINT16_MAX(void);
static void test_log2_UINT32_MAX(void);

static uint32_t g_output;
static uint32_t g_expected;


static void test_exp2_0(void)
{
    EXPECT(0x01);
    g_output = narch_exp2(0);
    EVALUATE();
}

static void test_exp2_1(void)
{
    EXPECT(0x02);
    g_output = narch_exp2(1);
    EVALUATE();
}

static void test_exp2_7(void)
{
    EXPECT(0x80);
    g_output = narch_exp2(7);
    EVALUATE();
}

static void test_exp2_31(void)
{
    EXPECT(0x80000000);
    g_output = narch_exp2(31);
    EVALUATE();
}

static void test_log2_1(void)
{
    EXPECT(0);
    g_output = narch_log2(0x01);
    EVALUATE();
}

static void test_log2_3(void)
{
    EXPECT(1);
    g_output = narch_log2(0x03);
    EVALUATE();
}

static void test_log2_UINT8_MAX(void)
{
    EXPECT(7);
    g_output = narch_log2(0xff);
    EVALUATE();
}

static void test_log2_UINT16_MAX(void)
{
    EXPECT(15);
    g_output = narch_log2(0xffff);
    EVALUATE();
}

static void test_log2_UINT32_MAX(void)
{
    EXPECT(31);
    g_output = narch_log2(0xffffffff);
    EVALUATE();
}

static void setup_empty(void)
{
    g_output = 0u;
    g_expected = 0u;
}

static void teardown_empty(void)
{
}

void test_narch(void)
{
    NTESTSUITE_FIXTURE(empty, setup_empty, teardown_empty);
    NTESTSUITE_RUN(empty, test_exp2_0);
    NTESTSUITE_RUN(empty, test_exp2_1);
    NTESTSUITE_RUN(empty, test_exp2_7);
    NTESTSUITE_RUN(empty, test_exp2_31);
    NTESTSUITE_RUN(empty, test_log2_1);
    NTESTSUITE_RUN(empty, test_log2_3);
    NTESTSUITE_RUN(empty, test_log2_UINT8_MAX);
    NTESTSUITE_RUN(empty, test_log2_UINT16_MAX);
    NTESTSUITE_RUN(empty, test_log2_UINT32_MAX);
    NTESTSUITE_PRINT_RESULTS();   
}


