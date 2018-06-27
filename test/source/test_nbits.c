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

static void test_none_array_size(void);
static void test_none_bit_size(void);
static void test_none_divide_round(void);
static void test_none_divide_roundup(void);
static void test_none_align(void);
static void test_none_alignup(void);
static void test_none_log2_0(void);
static void test_none_log2_x(void);
static void test_none_log2_UINT32_MAX(void);
static void test_none_is_powerof2_0(void);
static void test_none_is_powerof2_1(void);
static void test_none_is_powerof2_4(void);
static void test_none_xbn(void);
static void test_none_msb(void);
static void test_none_lsb(void);
static void test_none_ftou32_u32tof(void);

static void test_none_array_size(void)
{
    const char small_array[1];
    const char big_array[10];

    NTESTSUITE_EXPECT_UINT(1);
    NTESTSUITE_ACTUAL_UINT(NBITS_ARRAY_SIZE(small_array));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(10);
    NTESTSUITE_ACTUAL_UINT(NBITS_ARRAY_SIZE(big_array));
    NTESTSUITE_EVALUATE();
}

static void test_none_bit_size(void)
{
    uint8_t small_var;
    uint32_t big_var;
    
    NTESTSUITE_EXPECT_UINT(8);
    NTESTSUITE_ACTUAL_UINT(NBITS_BIT_SIZE(small_var));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(32);
    NTESTSUITE_ACTUAL_UINT(NBITS_BIT_SIZE(big_var));
    NTESTSUITE_EVALUATE();
}

static void test_none_divide_round(void)
{
    NTESTSUITE_EXPECT_UINT(15);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUND(15, 1));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(5);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUND(27, 5));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(6);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUND(28, 5));
    NTESTSUITE_EVALUATE();
}

static void test_none_divide_roundup(void)
{
    NTESTSUITE_EXPECT_UINT(15);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUNDUP(15, 1));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(6);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUNDUP(27, 5));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(6);
    NTESTSUITE_ACTUAL_UINT(NBITS_DIVIDE_ROUNDUP(28, 5));
    NTESTSUITE_EVALUATE();
}

static void test_none_align(void)
{
    NTESTSUITE_EXPECT_UINT(148);
    NTESTSUITE_ACTUAL_UINT(NBITS_ALIGN(149, 4));
    NTESTSUITE_EVALUATE();
}

static void test_none_alignup(void)
{
    NTESTSUITE_EXPECT_UINT(152);
    NTESTSUITE_ACTUAL_UINT(NBITS_ALIGN_UP(149, 4));
    NTESTSUITE_EVALUATE();
}

static void test_none_log2_0(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(0));
    NTESTSUITE_EVALUATE();
}

static void test_none_log2_x(void)
{
    NTESTSUITE_EXPECT_UINT(0);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(1));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(1);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(2));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(2);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(4));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(3);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(8));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(4);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(16));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(5);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(32));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(6);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(64));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(7);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(128));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(7);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(255));
    NTESTSUITE_EVALUATE();
}

static void test_none_log2_UINT32_MAX(void)
{
    NTESTSUITE_EXPECT_UINT(7);
    NTESTSUITE_ACTUAL_UINT(NBITS_LOG2_8(UINT32_MAX));
    NTESTSUITE_EVALUATE();
}

static void test_none_is_powerof2_0(void)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(NBITS_IS_POWEROF2(0));
    NTESTSUITE_EVALUATE();
}

static void test_none_is_powerof2_1(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(NBITS_IS_POWEROF2(1));
    NTESTSUITE_EVALUATE();
}

static void test_none_is_powerof2_4(void)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(NBITS_IS_POWEROF2(4));
    NTESTSUITE_EVALUATE();
}

static void test_none_xbn(void)
{
    uint32_t i = 0xdeadbeef;

    NTESTSUITE_EXPECT_UINT(0xde);
    NTESTSUITE_ACTUAL_UINT(nbits_xb4(i));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(0xad);
    NTESTSUITE_ACTUAL_UINT(nbits_xb3(i));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(0xbe);
    NTESTSUITE_ACTUAL_UINT(nbits_xb2(i));
    NTESTSUITE_EVALUATE();

    NTESTSUITE_EXPECT_UINT(0xef);
    NTESTSUITE_ACTUAL_UINT(nbits_xb1(i));
    NTESTSUITE_EVALUATE();
}

static void test_none_msb(void) 
{
    uint32_t i = 0xdeadbeef;

    NTESTSUITE_EXPECT_UINT(0xde);
    NTESTSUITE_ACTUAL_UINT(nbits_msb_32(i));
    NTESTSUITE_EVALUATE();
}

static void test_none_lsb(void) 
{
    uint32_t i = 0xdeadbeef;

    NTESTSUITE_EXPECT_UINT(0xef);
    NTESTSUITE_ACTUAL_UINT(nbits_lsb_32(i));
    NTESTSUITE_EVALUATE();
}

static void test_none_ftou32_u32tof(void)
{
    uint32_t itestval = 0xdeadbeef;
    uint32_t igiven = itestval;
    uint32_t iexpect = itestval;
    uint32_t ioutput;
    float intermediatte;

    intermediatte = nbits_u32tof(igiven);
    ioutput = nbits_ftou32(intermediatte);

    NTESTSUITE_EXPECT_UINT(iexpect);
    NTESTSUITE_ACTUAL_UINT(ioutput);
    NTESTSUITE_EVALUATE();
}

void test_nbits(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);
    NTESTSUITE_RUN(none, test_none_array_size);
    NTESTSUITE_RUN(none, test_none_bit_size);
    NTESTSUITE_RUN(none, test_none_divide_round);
    NTESTSUITE_RUN(none, test_none_divide_roundup);
    NTESTSUITE_RUN(none, test_none_align);
    NTESTSUITE_RUN(none, test_none_alignup);
    NTESTSUITE_RUN(none, test_none_log2_0);
    NTESTSUITE_RUN(none, test_none_log2_x);
    NTESTSUITE_RUN(none, test_none_log2_UINT32_MAX);
    NTESTSUITE_RUN(none, test_none_is_powerof2_0);
    NTESTSUITE_RUN(none, test_none_is_powerof2_1);
    NTESTSUITE_RUN(none, test_none_is_powerof2_4);
    NTESTSUITE_RUN(none, test_none_xbn);
    NTESTSUITE_RUN(none, test_none_msb);
    NTESTSUITE_RUN(none, test_none_lsb);
    NTESTSUITE_RUN(none, test_none_ftou32_u32tof);
    NTESTSUITE_PRINT_RESULTS(none);   
}


