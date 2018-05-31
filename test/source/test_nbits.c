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

#include "testsuite/ntestsuite.h"
#include "bits/nbits.h"
#include "test_nbits.h"

static void test_array_size(void);
static void test_bit_size(void);
static void test_divide_round_1_15(void);
static void test_divide_round_5_27(void);
static void test_divide_round_5_28(void);
static void test_divide_roundup_1_15(void);
static void test_divide_roundup_5_27(void);
static void test_divide_roundup_5_28(void);
static void test_align_4_149(void);
static void test_alignup_4_149(void);
static void test_log2_0(void);
static void test_log2_x(void);
static void test_log2_256(void);
static void test_is_powerof2_0(void);
static void test_is_powerof2_1(void);
static void test_is_powerof2_4(void);
static void test_xbn(void);
static void test_msb(void);
static void test_lsb(void);
static void test_ftou32_u32tof(void);

static void test_array_size(void)
{
    const char array[10];

    NTESTSUITE_ASSERT_EQUAL_UINT(10, NBITS_ARRAY_SIZE(array));
}

static void test_bit_size(void)
{
    uint32_t i;
    NTESTSUITE_ASSERT_EQUAL_UINT(32u, NBITS_BIT_SIZE(i));
}

static void test_divide_round_1_15(void)
{
    NTESTSUITE_ASSERT_EQUAL_UINT(15, NBITS_DIVIDE_ROUND(15, 1));
}

static void test_divide_round_5_27(void)
{
    NTESTSUITE_ASSERT_EQUAL_UINT(5, NBITS_DIVIDE_ROUND(27, 5));
}

static void test_divide_round_5_28(void)
{
    NTESTSUITE_ASSERT_EQUAL_UINT(6, NBITS_DIVIDE_ROUND(28, 5));
}

static void test_divide_roundup_1_15(void)
{
    NTESTSUITE_ASSERT_EQUAL_UINT(15, NBITS_DIVIDE_ROUNDUP(15, 1));
}

static void test_divide_roundup_5_27(void)
{
    NTESTSUITE_ASSERT_EQUAL_UINT(6, NBITS_DIVIDE_ROUNDUP(27, 5));
}

static void test_divide_roundup_5_28(void)
{
    NTESTSUITE_ASSERT_EQUAL_UINT(6, NBITS_DIVIDE_ROUNDUP(28, 5));
}

static void test_align_4_149(void)
{
    NTESTSUITE_ASSERT_EQUAL_UINT(148, NBITS_ALIGN(149, 4));
}

static void test_alignup_4_149(void)
{
    NTESTSUITE_ASSERT_EQUAL_UINT(152, NBITS_ALIGN_UP(149, 4));
}

static void test_log2_0(void)
{
    NTESTSUITE_ASSERT_EQUAL_UINT(0, NBITS_LOG2_8(0));
}

static void test_log2_x(void)
{
    NTESTSUITE_ASSERT_EQUAL_UINT(0, NBITS_LOG2_8(1));
    NTESTSUITE_ASSERT_EQUAL_UINT(1, NBITS_LOG2_8(2));
    NTESTSUITE_ASSERT_EQUAL_UINT(2, NBITS_LOG2_8(4));
    NTESTSUITE_ASSERT_EQUAL_UINT(3, NBITS_LOG2_8(8));
    NTESTSUITE_ASSERT_EQUAL_UINT(4, NBITS_LOG2_8(16));
    NTESTSUITE_ASSERT_EQUAL_UINT(5, NBITS_LOG2_8(32));
    NTESTSUITE_ASSERT_EQUAL_UINT(6, NBITS_LOG2_8(64));
    NTESTSUITE_ASSERT_EQUAL_UINT(7, NBITS_LOG2_8(128));
    NTESTSUITE_ASSERT_EQUAL_UINT(7, NBITS_LOG2_8(255));
}

static void test_log2_256(void)
{
    NTESTSUITE_ASSERT_EQUAL_UINT(7, NBITS_LOG2_8(UINT32_MAX));
}

static void test_is_powerof2_0(void)
{
    NTESTSUITE_ASSERT_EQUAL_BOOL(false, NBITS_IS_POWEROF2(0));
}

static void test_is_powerof2_1(void)
{
    NTESTSUITE_ASSERT_EQUAL_BOOL(true, NBITS_IS_POWEROF2(1));
}

static void test_is_powerof2_4(void)
{
    NTESTSUITE_ASSERT_EQUAL_BOOL(true, NBITS_IS_POWEROF2(4));
}

static void test_xbn(void)
{
    uint32_t i = 0xdeadbeef;

    NTESTSUITE_ASSERT_EQUAL_UINT(0xde, nbits_xb4(i));
    NTESTSUITE_ASSERT_EQUAL_UINT(0xad, nbits_xb3(i));
    NTESTSUITE_ASSERT_EQUAL_UINT(0xbe, nbits_xb2(i));
    NTESTSUITE_ASSERT_EQUAL_UINT(0xef, nbits_xb1(i));
}

static void test_msb(void) 
{
    uint32_t i = 0xdeadbeef;

    NTESTSUITE_ASSERT_EQUAL_UINT(0xde, nbits_msb_32(i));
}

static void test_lsb(void) 
{
    uint32_t i = 0xdeadbeef;

    NTESTSUITE_ASSERT_EQUAL_UINT(0xef, nbits_lsb_32(i));
}

static void test_ftou32_u32tof(void)
{
    uint32_t itestval = 0xdeadbeef;
    uint32_t igiven = itestval;
    uint32_t iexpect = itestval;
    uint32_t ioutput;
    float intermediatte;

    intermediatte = nbits_u32tof(igiven);
    ioutput = nbits_ftou32(intermediatte);

    NTESTSUITE_ASSERT_EQUAL_UINT(iexpect, ioutput);
}

void test_nbits(void)
{
    NTESTSUITE_FIXTURE(empty, NULL, NULL);
    NTESTSUITE_RUN(empty, test_array_size);
    NTESTSUITE_RUN(empty, test_bit_size);
    NTESTSUITE_RUN(empty, test_divide_round_1_15);
    NTESTSUITE_RUN(empty, test_divide_round_5_27);
    NTESTSUITE_RUN(empty, test_divide_round_5_28);
    NTESTSUITE_RUN(empty, test_divide_roundup_1_15);
    NTESTSUITE_RUN(empty, test_divide_roundup_5_27);
    NTESTSUITE_RUN(empty, test_divide_roundup_5_28);
    NTESTSUITE_RUN(empty, test_align_4_149);
    NTESTSUITE_RUN(empty, test_alignup_4_149);
    NTESTSUITE_RUN(empty, test_log2_0);
    NTESTSUITE_RUN(empty, test_log2_x);
    NTESTSUITE_RUN(empty, test_log2_256);
    NTESTSUITE_RUN(empty, test_is_powerof2_0);
    NTESTSUITE_RUN(empty, test_is_powerof2_1);
    NTESTSUITE_RUN(empty, test_is_powerof2_4);
    NTESTSUITE_RUN(empty, test_xbn);
    NTESTSUITE_RUN(empty, test_msb);
    NTESTSUITE_RUN(empty, test_lsb);
    NTESTSUITE_RUN(empty, test_ftou32_u32tof);
    NTESTSUITE_PRINT_RESULTS();   
}


