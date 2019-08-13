/*
 * Neon
 * Copyright (C)  2018  REAL-TIME CONSULTING
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
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Variant architecture for PIC32 header
 *
 *  @addtogroup  port
 *  @{ */

/** @defgroup    port_pic18_variant_arch Variant architecture for PIC32
 *  @brief       Variant architecture for PIC32.
 *  @{ */

#ifndef NEON_ARCH_VARIANT_PIC32_H_
#define NEON_ARCH_VARIANT_PIC32_H_

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "platform_variant/platform.h"

#if defined(NCONFIG_ARCH_CONFIG)
#include "neon_arch_config.h"
#endif

#if !defined(NCONFIG_USE_EXCLUSIVE_ACCESS)
#define NCONFIG_USE_EXCLUSIVE_ACCESS    1
#endif

#if !defined(NCONFIG_ARCH_ISR_LOCK_CODE)
#define NCONFIG_ARCH_ISR_LOCK_CODE      7
#endif

#if !defined(NCONFIG_ARCH_TIMER_SOURCE)
#define NCONFIG_ARCH_TIMER_SOURCE       1
#endif

#if !defined(NCONFIG_ARCH_TIMER_FREQ_HZ)
#define NCONFIG_ARCH_TIMER_FREQ_HZ      1000
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define NARCH_ID                        "pic32"
#define NARCH_DATA_WIDTH                32 /* sizeof(narch_uint) * 8 */
#define NARCH_ALIGN                     4
#define PIC32_ARCH                      1
    
/*
 * Architecture has equally efficient 8bit load-store instructions, no benefit
 * in using uint_fast8_t
 */
#define NARCH_HAS_U8_LS                 1
/*
 * Atomic CAS depends on NCONFIG option.
 */    
#if (NCONFIG_USE_EXCLUSIVE_ACCESS == 1)
#define NARCH_HAS_ATOMICS                   1
#else
#define NARCH_HAS_ATOMICS                   0
#endif
    
/*
 * Atomic set/clear depends on CAS on PIC32
 */
#if (NARCH_HAS_ATOMICS == 1)
#define NARCH_HAS_ATOMIC_SET_CLEAR_BIT  1
#else
#define NARCH_HAS_ATOMIC_SET_CLEAR_BIT  0
#endif
    
#define NARCH_IS_ISR_ACTIVE()           (_CP0_GET_CAUSE() & _CP0_CAUSE_RIPL_MASK)

#define NARCH_DISABLE_INTERRUPTS()      __builtin_disable_interrupts()
#define NARCH_ENABLE_INTERRUPTS()       __builtin_enable_interrupts()


/* TODO: Use static assert to compare NARCH_DATA_WIDTH and sizeof(narch_uint) */

NPLATFORM_INLINE
narch_uint narch_exp2(uint_fast8_t x)
{
    return ((narch_uint)0x1u << x);
}

NPLATFORM_INLINE
uint_fast8_t narch_log2(narch_uint x)
{
    return (uint_fast8_t)((NARCH_DATA_WIDTH - 1u) - __builtin_clz(x));
}

NPLATFORM_INLINE
NPLATFORM_NORETURN(void narch_cpu_stop(void))
{
    NARCH_DISABLE_INTERRUPTS();
    for (;;);
}

#if (NARCH_HAS_ATOMICS == 1)
#define narch_compare_and_swap(p, oldval, newval)                           \
        __sync_bool_compare_and_swap((p), (oldval), (newval))

NPLATFORM_INLINE
void narch_atomic_increment(uint32_t * u32)
{
    __sync_fetch_and_add(u32, 1);
}

NPLATFORM_INLINE
void narch_atomic_decrement(uint32_t * u32)
{
    __sync_fetch_and_sub(u32, 1);
}

NPLATFORM_INLINE
void narch_atomic_set_bit(uint32_t * u32, uint_fast8_t bit)
{
    __sync_fetch_and_or(u32, narch_exp2(bit));
}

NPLATFORM_INLINE
void narch_atomic_clear_bit(uint32_t * u32, uint_fast8_t bit)
{
    __sync_fetch_and_and(u32, ~narch_exp2(bit));
}

#endif /* (NARCH_HAS_CAS == 1) */


typedef uint32_t narch_isr_state;

#define NARCH_ISR_LOCK(local_state)     np_arch_isr_lock(local_state)
    
#define NARCH_ISR_UNLOCK(local_state)   np_arch_isr_unlock(local_state)


static inline
void np_arch_isr_lock(narch_uint * local_state)
{
    unsigned int                ipl_status;

    ipl_status  = _CP0_GET_STATUS();
    *local_state = ipl_status;
    ipl_status &= ~_CP0_STATUS_IPL_MASK;
    ipl_status |= NCONFIG_ARCH_ISR_LOCK_CODE << _CP0_STATUS_IPL_POSITION;
    _CP0_SET_STATUS(ipl_status);
}

static inline
void np_arch_isr_unlock(const narch_uint * local_state)
{
    unsigned int                ipl_status;

    ipl_status  = _CP0_GET_STATUS();
    ipl_status &= ~_CP0_STATUS_IPL_MASK;
    ipl_status |= *local_state & _CP0_STATUS_IPL_MASK;
    _CP0_SET_STATUS(ipl_status);
}

void pic18_init(void);
void narch_term(void);

#if (NCONFIG_ARCH_TIMER_SOURCE == 1)
void narch_timer_enable(void);
void narch_timer_disable(void);
#else
#define narch_timer_enable()                    (void)0
#define narch_timer_disable()                   (void)0
#endif

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_ARCH_VARIANT_PIC32_H_ */
