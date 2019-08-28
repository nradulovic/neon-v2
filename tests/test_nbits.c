/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */

#include <stddef.h>
#include <stdint.h>
#include <test_nbits.h>

#include "../testsuite/ntestsuite.h"
#include "sys/nbits.h"

NTESTSUITE_TEST(test_none_array_size)
{
    char small_array[1];
    char big_array[10];

    ntestsuite_expect_uint(1);
    ntestsuite_actual_uint(NBITS_ARRAY_SIZE(small_array));

    ntestsuite_expect_uint(10);
    ntestsuite_actual_uint(NBITS_ARRAY_SIZE(big_array));
}

NTESTSUITE_TEST(test_none_bit_size)
{
    uint8_t small_var;
    uint32_t big_var;

    ntestsuite_expect_uint(8);
    ntestsuite_actual_uint(NBITS_BIT_SIZE(small_var));

    ntestsuite_expect_uint(32);
    ntestsuite_actual_uint(NBITS_BIT_SIZE(big_var));
}

NTESTSUITE_TEST(test_none_divide_round)
{
    ntestsuite_expect_uint(15);
    ntestsuite_actual_uint(NBITS_DIVIDE_ROUND(15, 1));

    ntestsuite_expect_uint(5);
    ntestsuite_actual_uint(NBITS_DIVIDE_ROUND(27, 5));

    ntestsuite_expect_uint(6);
    ntestsuite_actual_uint(NBITS_DIVIDE_ROUND(28, 5));
}

NTESTSUITE_TEST(test_none_divide_roundup)
{
    ntestsuite_expect_uint(15);
    ntestsuite_actual_uint(NBITS_DIVIDE_ROUNDUP(15, 1));

    ntestsuite_expect_uint(6);
    ntestsuite_actual_uint(NBITS_DIVIDE_ROUNDUP(27, 5));

    ntestsuite_expect_uint(6);
    ntestsuite_actual_uint(NBITS_DIVIDE_ROUNDUP(28, 5));
}

NTESTSUITE_TEST(test_none_align)
{
    ntestsuite_expect_uint(148);
    ntestsuite_actual_uint(NBITS_ALIGN(149, 4));
}

NTESTSUITE_TEST(test_none_alignup)
{
    ntestsuite_expect_uint(152);
    ntestsuite_actual_uint(NBITS_ALIGN_UP(149, 4));
}

NTESTSUITE_TEST(test_none_log2_0)
{
    ntestsuite_expect_uint(0);
    ntestsuite_actual_uint(NBITS_LOG2_8(0));
}

NTESTSUITE_TEST(test_none_log2_x)
{
    ntestsuite_expect_uint(0);
    ntestsuite_actual_uint(NBITS_LOG2_8(1));

    ntestsuite_expect_uint(1);
    ntestsuite_actual_uint(NBITS_LOG2_8(2));

    ntestsuite_expect_uint(2);
    ntestsuite_actual_uint(NBITS_LOG2_8(4));

    ntestsuite_expect_uint(3);
    ntestsuite_actual_uint(NBITS_LOG2_8(8));

    ntestsuite_expect_uint(4);
    ntestsuite_actual_uint(NBITS_LOG2_8(16));

    ntestsuite_expect_uint(5);
    ntestsuite_actual_uint(NBITS_LOG2_8(32));

    ntestsuite_expect_uint(6);
    ntestsuite_actual_uint(NBITS_LOG2_8(64));

    ntestsuite_expect_uint(7);
    ntestsuite_actual_uint(NBITS_LOG2_8(128));

    ntestsuite_expect_uint(7);
    ntestsuite_actual_uint(NBITS_LOG2_8(255));
}

NTESTSUITE_TEST(test_none_log2_UINT32_MAX)
{
#if (NARCH_DATA_WIDTH >= 32)
    ntestsuite_expect_uint(7);
    ntestsuite_actual_uint(NBITS_LOG2_8(UINT32_MAX));
#endif
}

NTESTSUITE_TEST(test_none_is_powerof2_0)
{
    NTESTSUITE_EXPECT_BOOL(false);
    NTESTSUITE_ACTUAL_BOOL(NBITS_IS_POWEROF2(0));
}

NTESTSUITE_TEST(test_none_is_powerof2_1)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(NBITS_IS_POWEROF2(1));
}

NTESTSUITE_TEST(test_none_is_powerof2_4)
{
    NTESTSUITE_EXPECT_BOOL(true);
    NTESTSUITE_ACTUAL_BOOL(NBITS_IS_POWEROF2(4));
}

NTESTSUITE_TEST(test_none_to_mask_0)
{
    ntestsuite_expect_uint(0);
    ntestsuite_actual_uint(nbits_to_right_mask(0));
}

NTESTSUITE_TEST(test_none_to_mask_8)
{
    ntestsuite_expect_uint(0xffu);
    ntestsuite_actual_uint(nbits_to_right_mask(8));
}

NTESTSUITE_TEST(test_none_to_mask_32)
{
    ntestsuite_expect_uint(0xffffffffu);
    ntestsuite_actual_uint(nbits_to_right_mask(32));
}

NTESTSUITE_TEST(test_none_xbn)
{
    uint32_t i = 0xdeadbeef;

    ntestsuite_expect_uint(0xde);
    ntestsuite_actual_uint(nbits_xb4(i));

    ntestsuite_expect_uint(0xad);
    ntestsuite_actual_uint(nbits_xb3(i));

    ntestsuite_expect_uint(0xbe);
    ntestsuite_actual_uint(nbits_xb2(i));

    ntestsuite_expect_uint(0xef);
    ntestsuite_actual_uint(nbits_xb1(i));
}

NTESTSUITE_TEST(test_none_msb)
{
    uint32_t i = 0xdeadbeef;

    ntestsuite_expect_uint(0xde);
    ntestsuite_actual_uint(nbits_msb_32(i));
}

NTESTSUITE_TEST(test_none_lsb)
{
    uint32_t i = 0xdeadbeef;

    ntestsuite_expect_uint(0xef);
    ntestsuite_actual_uint(nbits_lsb_32(i));
}

NTESTSUITE_TEST(test_none_ftou32_u32tof)
{
    uint32_t itestval = 0xdeadbeef;
    uint32_t igiven = itestval;
    uint32_t iexpect = itestval;
    uint32_t ioutput;
    float intermediatte;

    intermediatte = nbits_u32tof(igiven);
    ioutput = nbits_ftou32(intermediatte);

    ntestsuite_expect_uint(iexpect);
    ntestsuite_actual_uint(ioutput);
}

void test_exec_nbits(void)
{
    ntestsuite_set_fixture(none, NULL, NULL);
    ntestsuite_run(test_none_array_size);
    ntestsuite_run(test_none_bit_size);
    ntestsuite_run(test_none_divide_round);
    ntestsuite_run(test_none_divide_roundup);
    ntestsuite_run(test_none_align);
    ntestsuite_run(test_none_alignup);
    ntestsuite_run(test_none_log2_0);
    ntestsuite_run(test_none_log2_x);
    ntestsuite_run(test_none_log2_UINT32_MAX);
    ntestsuite_run(test_none_is_powerof2_0);
    ntestsuite_run(test_none_is_powerof2_1);
    ntestsuite_run(test_none_is_powerof2_4);
    ntestsuite_run(test_none_to_mask_0);
    ntestsuite_run(test_none_to_mask_8);
    ntestsuite_run(test_none_to_mask_32);
    ntestsuite_run(test_none_xbn);
    ntestsuite_run(test_none_msb);
    ntestsuite_run(test_none_lsb);
    ntestsuite_run(test_none_ftou32_u32tof);
}
