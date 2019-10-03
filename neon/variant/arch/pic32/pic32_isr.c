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
#include "pic32_isr.h"
#include "pic32_common.h"

#include "neon.h"

#define pic32_isr_ipc_reg(vector_no)                                        \
        (&((pic32_periph_access(&IPC0))[(vector_no) >> 2u]))

#define pic32_isr_ipc_position(vector_no)                                   \
        ((vector_no & 0x3u) * 8u)


void pic32_isr_vector_set_prio(uint_fast8_t vector_no, uint_fast8_t prio)
{
    struct pic32_periph_reg * ipc = pic32_isr_ipc_reg(vector_no);
    uint32_t position = pic32_isr_ipc_position(vector_no);

    nlogger_info("PIC32 ISR: set vector %u prio to %u:%u", 
            vector_no, 
            prio >> 2, 
            prio & 0x3);

    /* read-modify-write */
    ipc->clr = (uint32_t)0x7u << position;
    ipc->set = (uint32_t)prio  << position;
}

uint_fast8_t pic32_isr_get_prio(uint_fast8_t vector_no)
{
    struct pic32_periph_reg * ipc = pic32_isr_ipc_reg(vector_no);
    uint32_t position = pic32_isr_ipc_position(vector_no);

    return (ipc->reg >> position) & 0x7u;
}

void pic32_isr_init(void)
{
    NARCH_DISABLE_INTERRUPTS();
    INTCONSET = _INTCON_MVEC_MASK;

    // set the CP0 cause IV bit high: Use the special interrupt vector (0x200)
    _CP0_BIS_CAUSE(_CP0_CAUSE_IV_MASK);

    // clear the CP0 status BEV bit: Controls the location of exception vectors.
    _CP0_BIC_STATUS(_CP0_STATUS_BEV_MASK);
    NARCH_ENABLE_INTERRUPTS();
    nlogger_info("PIC32 ISR: STATUS 0x%x CAUSE 0x%x",
            _CP0_GET_STATUS(),
            _CP0_GET_CAUSE());
    nlogger_info("PIC32 ISR: Neon priority ceiling %u", 
            NCONFIG_ARCH_ISR_LOCK_CODE);
}