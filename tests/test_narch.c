/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */

#include <stddef.h>
#include <stdint.h>

#include "test_narch.h"
#include "../testsuite/ntestsuite.h"
#include "sys/nport.h"

NTESTSUITE_TEST(test_none_NPLATFORM_ID)
{
    ntestsuite_not_expect_ptr(NULL);
    ntestsuite_actual_ptr(NPLATFORM_ID);
}

#if !defined(NPLATFORM_INLINE)
#error "NPLATFORM_INLINE is not defined!"
#endif

#if !defined(NPLATFORM_INLINE_ALWAYS)
#error "NPLATFORM_INLINE_ALWAYS is not defined!"
#endif

#if !defined(NPLATFORM_CONTAINER_OF)
#error "NPLATFORM_CONTAINER_OF is not defined!"
#endif

NTESTSUITE_TEST(test_none_NPLATFORM_FUNC)
{
    ntestsuite_not_expect_ptr(NULL);
    ntestsuite_actual_ptr((void *)NPLATFORM_FUNC);
}

NTESTSUITE_TEST(test_none_NPLATFORM_FILE)
{
    ntestsuite_not_expect_ptr(NULL);
    ntestsuite_actual_ptr(NPLATFORM_FILE);
}

NTESTSUITE_TEST(test_none_NPLATFORM_LINE)
{
    ntestsuite_not_expect_uint(0);
    ntestsuite_actual_uint(NPLATFORM_LINE);
}

#if !defined(NPLATFORM_NAKED)
#error "NPLATFORM_NAKED is not defined!"
#endif

#if !defined(NPLATFORM_UNUSED)
#error "NPLATFORM_UNUSED is not defined!"
#endif

#if !defined(NPLATFORM_UNUSED_ARG)
#error "NPLATFORM_UNUSED_ARG is not defined!"
#endif

#if !defined(NPLATFORM_NORETURN)
#error "NPLATFORM_NORETURN is not defined!"
#endif

#if !defined(NPLATFORM_PACKED)
#error "NPLATFORM_PACKED is not defined!"
#endif

#if !defined(NPLATFORM_ALIGN)
#error "NPLATFORM_ALIGN is not defined!"
#endif

NTESTSUITE_TEST(test_none_NPLATFORM_DATE)
{
    ntestsuite_not_expect_ptr(NULL);
    ntestsuite_actual_ptr(NPLATFORM_DATE);
}

NTESTSUITE_TEST(test_none_NPLATFORM_TIME)
{
    ntestsuite_not_expect_ptr(NULL);
    ntestsuite_actual_ptr(NPLATFORM_TIME);
}

NTESTSUITE_TEST(test_none_NARCH_ID)
{
    ntestsuite_not_expect_ptr(NULL);
    ntestsuite_actual_ptr(NARCH_ID);
}

NTESTSUITE_TEST(test_none_NARCH_DATA_WIDTH)
{
    ntestsuite_not_expect_uint(0);
    ntestsuite_actual_uint(NARCH_DATA_WIDTH);
}

#if !defined(NARCH_HAS_ATOMICS)
#error "NARCH_HAS_ATOMICS is not defined!"
#endif

NTESTSUITE_TEST(test_none_NARCH_ALIGN)
{
    ntestsuite_not_expect_uint(0);
    ntestsuite_actual_uint(NARCH_ALIGN);
}

NTESTSUITE_TEST(test_none_atomic_set_bit)
{
#if (NARCH_HAS_ATOMICS == 1)
    uint32_t var;
    
    var = 0u;
    ntestsuite_expect_uint((uint32_t)0x1u << 1u);
    narch_atomic_set_bit(&var, 1u);
    ntestsuite_actual_uint(var);
    
    var = 0u;
    ntestsuite_expect_uint((uint32_t)0x1u << 2u);
    narch_atomic_set_bit(&var, 2u);
    ntestsuite_actual_uint(var);
    
    var = 0u;
    ntestsuite_expect_uint((uint32_t)0x1u << 8u);
    narch_atomic_set_bit(&var, 8u);
    ntestsuite_actual_uint(var);
    
    var = 0u;
    ntestsuite_expect_uint((uint32_t)0x1u << 16u);
    narch_atomic_set_bit(&var, 16u);
    ntestsuite_actual_uint(var);
    
    var = 0u;
    ntestsuite_expect_uint((uint32_t)0x1u << 24u);
    narch_atomic_set_bit(&var, 16u);
    ntestsuite_actual_uint(var);
    
    var = 0u;
    ntestsuite_expect_uint((uint32_t)0x1u << 31u);
    narch_atomic_set_bit(&var, 31u);
    ntestsuite_actual_uint(var);
#endif
}

NTESTSUITE_TEST(test_none_exp2)
{
    ntestsuite_expect_uint(0x01u);
    ntestsuite_actual_uint(narch_exp2(0));
    
    ntestsuite_expect_uint(0x02u);
    ntestsuite_actual_uint(narch_exp2(1));
    
    ntestsuite_expect_uint(0x80u);
    ntestsuite_actual_uint(narch_exp2(7));
    
#if (NARCH_DATA_WIDTH >= 16)
    ntestsuite_expect_uint(0x8000);
    ntestsuite_actual_uint(narch_exp2(15));
#endif
    
#if (NARCH_DATA_WIDTH >= 32)
    ntestsuite_expect_uint(0x80000000);
    ntestsuite_actual_uint(narch_exp2(31));
#endif
}

NTESTSUITE_TEST(test_none_log2)
{
    ntestsuite_expect_uint(0);
    ntestsuite_actual_uint(narch_log2(0x01));
    
    ntestsuite_expect_uint(1);
    ntestsuite_actual_uint(narch_log2(0x03));
    
    ntestsuite_expect_uint(7);
    ntestsuite_actual_uint(narch_log2(0xff));
    
#if (NARCH_DATA_WIDTH >= 16)
    ntestsuite_expect_uint(15);
    ntestsuite_actual_uint(narch_log2(0xffff));
#endif
    
#if (NARCH_DATA_WIDTH >= 32)
    ntestsuite_expect_uint(31);
    ntestsuite_actual_uint(narch_log2(0xffffffff));
#endif
}

#if !defined(NOS_CRITICAL_LOCK)
#error "NOS_CRITICAL_LOCK is not defined!"
#endif

#if !defined(NOS_CRITICAL_UNLOCK)
#error "NOS_CRITICAL_UNLOCK is not defined!"
#endif

void test_exec_narch(void)
{
    ntestsuite_set_fixture(none, NULL, NULL);
    ntestsuite_run(test_none_NPLATFORM_ID);
    ntestsuite_run(test_none_NPLATFORM_FUNC);
    ntestsuite_run(test_none_NPLATFORM_FILE);
    ntestsuite_run(test_none_NPLATFORM_LINE);
    ntestsuite_run(test_none_NPLATFORM_DATE);
    ntestsuite_run(test_none_NPLATFORM_TIME);
    ntestsuite_run(test_none_NARCH_ID);
    ntestsuite_run(test_none_NARCH_DATA_WIDTH);
    ntestsuite_run(test_none_NARCH_ALIGN);
    ntestsuite_run(test_none_atomic_set_bit);
    ntestsuite_run(test_none_exp2);
    ntestsuite_run(test_none_log2);
}
