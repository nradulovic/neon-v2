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

#include "pic32_isr.h"
#include "pic32_common.h"

struct pic32_isr_desc
{
    uint_fast8_t ifs_iec_reg;
    uint_fast8_t ifs_iec_bit;
    uint_fast8_t ipc_reg;
    uint_fast8_t ipc_bit;
};

#if defined(__32MX534F064H) || \
    defined(__32MX564F064H) || \
    defined(__32MX564F128H) || \
    defined(__32MX575F256H) || \
    defined(__32MX575F512H)

static const struct pic32_isr_desc g_pic32_interrupt_map[] =
{
    [PIC32_ISR_U5E] =
    {
        .ifs_iec_reg = 2,
        .ifs_iec_bit = 9,
        .ipc_reg = 12,
        .ipc_bit = 24
    },
    [PIC32_ISR_U5RX] =
    {
        .ifs_iec_reg = 2,
        .ifs_iec_bit = 10,
        .ipc_reg = 12,
        .ipc_bit = 24
    },
    [PIC32_ISR_U5TX] = 
    {
        .ifs_iec_reg = 2,
        .ifs_iec_bit = 11,
        .ipc_reg = 12,
        .ipc_bit = 24
    },
};
#endif


#define calc_iec_reg(base, isr_id)                                          \
        (&((pic32_periph_access(&IEC0))[(base)[(isr_id)].ifs_iec_reg]))

#define calc_iec_bit(base, isr_id)                                          \
        ((base)[(isr_id)].ifs_iec_bit)
    
#define calc_ifs_reg(base, isr_id)                                          \
        (&((pic32_periph_access(&IFS0))[(base)[(isr_id)].ifs_iec_reg]))

#define calc_ifs_bit(base, isr_id)                                          \
        calc_iec_bit(base, isr_id)

#define calc_ipc_reg(base, isr_id)                                          \
        (&((pic32_periph_access(&IPC0))[(base)[(isr_id)].ipc_reg]))

#define calc_ipc_bit(base, isr_id)                                          \
        ((base)[(isr_id)].ipc_bit)

void pic32_isr_resolve_iec(
        enum pic32_isr_id isr_id, 
        volatile uint32_t ** reg, 
        uint_fast8_t * bit)
{
    *reg = &calc_iec_reg(g_pic32_interrupt_map, isr_id)->reg;
    *bit = calc_iec_bit(g_pic32_interrupt_map, isr_id);
}

void pic32_isr_resolve_ifs(
        enum pic32_isr_id isr_id, 
        volatile uint32_t ** reg, 
        uint_fast8_t * bit)
{
    *reg = &calc_ifs_reg(g_pic32_interrupt_map, isr_id)->reg;
    *bit = calc_ifs_bit(g_pic32_interrupt_map, isr_id);
}

void pic32_isr_resolve_ipc(
        enum pic32_isr_id isr_id, 
        volatile uint32_t ** reg, 
        uint_fast8_t * bit)
{
    *reg = &calc_ipc_reg(g_pic32_interrupt_map, isr_id)->reg;
    *bit = calc_ipc_bit(g_pic32_interrupt_map, isr_id);
}

void pic32_isr_enable(enum pic32_isr_id isr_id)
{
    volatile uint32_t * iec_set = &calc_iec_reg(g_pic32_interrupt_map, isr_id)->set;
    uint_fast8_t bit = calc_iec_bit(g_pic32_interrupt_map, isr_id);

    *iec_set = 0x1ul << bit;
}

void pic32_isr_disable(enum pic32_isr_id isr_id)
{
    volatile uint32_t * iec_clr = &calc_iec_reg(g_pic32_interrupt_map, isr_id)->clr;
    uint_fast8_t bit = calc_iec_bit(g_pic32_interrupt_map, isr_id);

    *iec_clr = 0x1ul << bit;
}

bool pic32_isr_is_enabled(enum pic32_isr_id isr_id)
{
    volatile uint32_t * iec = &calc_iec_reg(g_pic32_interrupt_map, isr_id)->reg;
    uint_fast8_t bit = calc_iec_bit(g_pic32_interrupt_map, isr_id);

    return !!(*iec & (0x1ul << bit));
}

void pic32_isr_set_flag(enum pic32_isr_id isr_id)
{
    volatile uint32_t * ifs_set = &calc_ifs_reg(g_pic32_interrupt_map, isr_id)->set;
    uint_fast8_t bit = calc_ifs_bit(g_pic32_interrupt_map, isr_id);

    *ifs_set = 0x1ul << bit;
}

void pic32_isr_clear_flag(enum pic32_isr_id isr_id)
{
    volatile uint32_t * ifs_clr = &calc_ifs_reg(g_pic32_interrupt_map, isr_id)->clr;
    uint_fast8_t bit = calc_ifs_bit(g_pic32_interrupt_map, isr_id);

    *ifs_clr = 0x1ul << bit;
}

bool pic32_isr_is_flagged(enum pic32_isr_id isr_id)
{
    volatile uint32_t * ifs = &calc_ifs_reg(g_pic32_interrupt_map, isr_id)->reg;
    uint_fast8_t bit = calc_ifs_bit(g_pic32_interrupt_map, isr_id);

    return !!(*ifs & (0x1ul << bit));
}

void pic32_isr_set_prio(enum pic32_isr_id isr_id, uint_fast8_t prio)
{
    volatile uint32_t * ipc_clr = 
            &calc_ipc_reg(g_pic32_interrupt_map, isr_id)->clr;
    volatile uint32_t * ipc_set = 
            &calc_ipc_reg(g_pic32_interrupt_map, isr_id)->set;
    uint_fast8_t bit = calc_ipc_bit(g_pic32_interrupt_map, isr_id);

    *ipc_clr = 0x1ful << bit;
    *ipc_set = (uint32_t)prio << bit;
}

uint_fast8_t pic32_isr_get_prio(enum pic32_isr_id isr_id)
{
    volatile uint32_t * ipc = &calc_ipc_reg(g_pic32_interrupt_map, isr_id)->reg;
    uint_fast8_t bit = calc_ipc_bit(g_pic32_interrupt_map, isr_id);

    return (uint_fast8_t)((*ipc >> bit) & 0x1ful);
}

