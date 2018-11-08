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
#include "port/nport_arch.h"
#include "main.h"

NTESTSUITE_TEST(test_none_exp2_0)
{
    NTESTSUITE_EXPECT_UINT(0x01u);
    NTESTSUITE_ACTUAL_UINT(narch_exp2(0));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_exp2_1)
{
    NTESTSUITE_EXPECT_UINT(0x02u);
    NTESTSUITE_ACTUAL_UINT(narch_exp2(1));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_exp2_7)
{
    NTESTSUITE_EXPECT_UINT(0x80u);
    NTESTSUITE_ACTUAL_UINT(narch_exp2(7));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_exp2_31)
{
    NTESTSUITE_EXPECT_UINT(0x80000000);
    NTESTSUITE_ACTUAL_UINT(narch_exp2(31));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_log2_1)
{
    NTESTSUITE_EXPECT_UINT(0);
    NTESTSUITE_ACTUAL_UINT(narch_log2(0x01));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_log2_3)
{
    NTESTSUITE_EXPECT_UINT(1);
    NTESTSUITE_ACTUAL_UINT(narch_log2(0x03));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_log2_UINT8_MAX)
{
    NTESTSUITE_EXPECT_UINT(7);
    NTESTSUITE_ACTUAL_UINT(narch_log2(0xff));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_log2_UINT16_MAX)
{
    NTESTSUITE_EXPECT_UINT(15);
    NTESTSUITE_ACTUAL_UINT(narch_log2(0xffff));
    NTESTSUITE_EVALUATE();
}

NTESTSUITE_TEST(test_none_log2_UINT32_MAX)
{
    NTESTSUITE_EXPECT_UINT(31);
    NTESTSUITE_ACTUAL_UINT(narch_log2(0xffffffff));
    NTESTSUITE_EVALUATE();
}

void test_exec(void)
{
    NTESTSUITE_FIXTURE(none, NULL, NULL);
    NTESTSUITE_RUN(none, test_none_exp2_0);
    NTESTSUITE_RUN(none, test_none_exp2_1);
    NTESTSUITE_RUN(none, test_none_exp2_7);
    NTESTSUITE_RUN(none, test_none_exp2_31);
    NTESTSUITE_RUN(none, test_none_log2_1);
    NTESTSUITE_RUN(none, test_none_log2_3);
    NTESTSUITE_RUN(none, test_none_log2_UINT8_MAX);
    NTESTSUITE_RUN(none, test_none_log2_UINT16_MAX);
    NTESTSUITE_RUN(none, test_none_log2_UINT32_MAX);
    NTESTSUITE_PRINT_RESULTS(none);
}


