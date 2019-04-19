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

#include <xc.h>

#include "arch_variant/arch.h"

#include "pic18_osc.h"
#include "pic18_isr.h"
#include "neon.h"

#if (NCONFIG_ARCH_TIMER_SOURCE == 1)
static void timer_init(void)
{
    nlogger_info("PIC32 Core timer: %uHz", NCONFIG_ARCH_TIMER_FREQ_HZ);
    
    /* Disable timer */
    _CP0_BIS_CAUSE(_CP0_CAUSE_DC_MASK);

    /* Disable ISR */
    IEC0CLR = _IEC0_CTIE_MASK;

    /* Set ISR priority */
    pic32_isr_vector_set_prio(
            _CORE_TIMER_VECTOR, 
            NCONFIG_ARCH_ISR_LOCK_CODE << 2);
}
#endif

void narch_init(void)
{
    nlogger_info("PIC18 ARCH: Processor %x Version %x",
            *(const uint16_t *)0x3ffffe,
            *(const uint16_t *)0x3ffffc);
    /* Setup interrupt chip */
    pic18_isr_init();
    
#if (NCONFIG_ARCH_TIMER_SOURCE == 1)
    timer_init();
#endif
}

#if (NCONFIG_ARCH_TIMER_SOURCE == 1)
void narch_timer_enable(void)
{
    uint32_t cause;
    uint32_t compare;

    /* Set and enable timer */
    cause  = _CP0_GET_CAUSE();
    _CP0_SET_CAUSE(cause | _CP0_CAUSE_DC_MASK);
    _CP0_SET_COUNT(0u);
    compare = NCONFIG_ARCH_TIMER_FREQ_HZ / pic32_osc_get_sysclk_hz();
    _CP0_SET_COMPARE(compare);
    _CP0_SET_CAUSE(cause & ~_CP0_CAUSE_DC_MASK);

    /* Enable ISR */
    IFS0CLR = _IFS0_CTIF_MASK;
    IEC0SET = _IEC0_CTIE_MASK;
}

void narch_timer_disable(void)
{
    uint32_t cause;

    /* Disable ISR */
    IEC0CLR = _IEC0_CTIE_MASK;

    /* Disable timer */
    cause  = _CP0_GET_CAUSE();
    cause |= _CP0_CAUSE_DC_MASK;
    _CP0_SET_CAUSE(cause);
}

extern void nsys_timer_isr(void);

void PIC32_SOFT_ISR_DECL(_CORE_TIMER_VECTOR, PIC32_NEON_ISR_IPL_MAX) arch_timer_isr(void)
{
    uint32_t cause;
    uint32_t compare;

    /* Disable timer */
    cause  = _CP0_GET_CAUSE();
    _CP0_SET_CAUSE(cause | _CP0_CAUSE_DC_MASK);

    /* Reload value */
    compare = _CP0_GET_COMPARE();
    _CP0_SET_COUNT(0u);
    _CP0_SET_COMPARE(compare);

    /* Enable timer */
    _CP0_SET_CAUSE(cause);

    nsys_timer_isr();
}
#endif /* (NCONFIG_ARCH_TIMER_SOURCE == 1) */

void narch_cpu_stop(void)
{
    for (;;);
}

narch_uint narch_exp2(uint_fast8_t x)
{
    static const narch_uint exp2[8] =
    {
        0x01,
        0x02,
        0x04,
        0x08,
        0x10,
        0x20,
        0x40,
        0x80
    };
    return exp2[x];
}

uint_fast8_t narch_log2(narch_uint x)
{
    static const uint_fast8_t log2_table[256] =
    {
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
        0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
        LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
        LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
#undef LT
    };
    
    return log2_table[x];
}
