/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */

#include <stddef.h>
#include <stdint.h>

#include "../testsuite/ntestsuite.h"
#include "core/nport.h"
#include "test_nport.h"

NTESTSUITE_TEST(test_none_nsys_build_date)
{
    ntestsuite_not_expect_ptr(NULL);
    ntestsuite_actual_ptr(nsys_build_date);
}


NTESTSUITE_TEST(test_none_nsys_build_time)
{
    ntestsuite_not_expect_ptr(NULL);
    ntestsuite_actual_ptr(nsys_build_time);
}

NTESTSUITE_TEST(test_none_nsys_platform_id)
{
    ntestsuite_not_expect_ptr(NULL);
    ntestsuite_actual_ptr(nsys_platform_id);
}

NTESTSUITE_TEST(test_none_nsys_platform_version)
{
    ntestsuite_not_expect_ptr(NULL);
    ntestsuite_actual_ptr(nsys_platform_version);
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

NTESTSUITE_TEST(test_none_narch_id)
{
    ntestsuite_not_expect_ptr(NULL);
    ntestsuite_actual_ptr(narch_id);
}

NTESTSUITE_TEST(test_none_narch_has_atomics)
{
    ntestsuite_not_expect_uint(2);
    ntestsuite_actual_uint(narch_has_atomics);
}

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

NTESTSUITE_TEST(test_none_atomic_clear_bit)
{
#if (NARCH_HAS_ATOMICS == 1)
    uint32_t var;

    var = (uint32_t)0x1u << 1;
    ntestsuite_expect_uint(0u);
    narch_atomic_clear_bit(&var, 1u);
    ntestsuite_actual_uint(var);

    var = (uint32_t)0x1u << 2u;
    ntestsuite_expect_uint(0u);
    narch_atomic_clear_bit(&var, 2u);
    ntestsuite_actual_uint(var);

    var = (uint32_t)0x1u << 8u;
    ntestsuite_expect_uint(0u);
    narch_atomic_clear_bit(&var, 8u);
    ntestsuite_actual_uint(var);

    var = (uint32_t)0x1u << 16u;
    ntestsuite_expect_uint(0u);
    narch_atomic_clear_bit(&var, 16u);
    ntestsuite_actual_uint(var);

    var = (uint32_t)0x1u << 24u;
    ntestsuite_expect_uint(0u);
    narch_atomic_clear_bit(&var, 16u);
    ntestsuite_actual_uint(var);

    var = (uint32_t)0x1u << 31u;
    ntestsuite_expect_uint(0u);
    narch_atomic_clear_bit(&var, 31u);
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
    
    ntestsuite_expect_uint(0x8000);
    ntestsuite_actual_uint(narch_exp2(15));
    
    ntestsuite_expect_uint(0x80000000);
    ntestsuite_actual_uint(narch_exp2(31));
}

NTESTSUITE_TEST(test_none_log2)
{
    ntestsuite_expect_uint(0);
    ntestsuite_actual_uint(narch_log2(0x01));
    
    ntestsuite_expect_uint(1);
    ntestsuite_actual_uint(narch_log2(0x03));
    
    ntestsuite_expect_uint(7);
    ntestsuite_actual_uint(narch_log2(0xff));
    
    ntestsuite_expect_uint(15);
    ntestsuite_actual_uint(narch_log2(0xffff));
    
    ntestsuite_expect_uint(31);
    ntestsuite_actual_uint(narch_log2(0xffffffff));
}

NTESTSUITE_TEST(test_none_critical_lock)
{
    /* TODO: This needs a bit elaborate test which will test the critical lock.
     */
    struct nos_critical lock;

    nos_critical_lock(&lock);
    nos_critical_unlock(&lock);
}

void test_exec_nport(void)
{
    ntestsuite_set_fixture(none, NULL, NULL);
    ntestsuite_run(test_none_nsys_build_date);
    ntestsuite_run(test_none_nsys_build_time);
    ntestsuite_run(test_none_nsys_platform_id);
    ntestsuite_run(test_none_nsys_platform_version);
	ntestsuite_run(test_none_NPLATFORM_FUNC);
	ntestsuite_run(test_none_NPLATFORM_FILE);
	ntestsuite_run(test_none_NPLATFORM_LINE);
	ntestsuite_run(test_none_NPLATFORM_DATE);
	ntestsuite_run(test_none_NPLATFORM_TIME);
    ntestsuite_run(test_none_narch_id);
    ntestsuite_run(test_none_narch_has_atomics);
    ntestsuite_run(test_none_NARCH_ALIGN);
    ntestsuite_run(test_none_atomic_set_bit);
    ntestsuite_run(test_none_atomic_clear_bit);
    ntestsuite_run(test_none_exp2);
    ntestsuite_run(test_none_log2);
    ntestsuite_run(test_none_critical_lock);
}
