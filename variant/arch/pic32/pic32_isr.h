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

#ifndef NEON_PIC32_ISR_H_
#define NEON_PIC32_ISR_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum pic32_isr_id
{
    PIC32_ISR_U5E,
    PIC32_ISR_U5RX,
    PIC32_ISR_U5TX     
};
    
void pic32_isr_resolve_iec(
        enum pic32_isr_id isr_id, 
        volatile uint32_t ** reg, 
        uint_fast8_t * bit);

void pic32_isr_resolve_ifs(
        enum pic32_isr_id isr_id, 
        volatile uint32_t ** reg, 
        uint_fast8_t * bit);

void pic32_isr_resolve_ipc(
        enum pic32_isr_id isr_id, 
        volatile uint32_t ** reg, 
        uint_fast8_t * bit);

void pic32_isr_enable(enum pic32_isr_id isr_id);

void pic32_isr_disable(enum pic32_isr_id isr_id);

bool pic32_isr_is_enabled(enum pic32_isr_id isr_id);

void pic32_isr_set_flag(enum pic32_isr_id isr_id);

void  pic32_isr_clear_flag(enum pic32_isr_id isr_id);

bool pic32_isr_is_flagged(enum pic32_isr_id isr_id);

void pic32_isr_set_prio(enum pic32_isr_id isr_id, uint_fast8_t prio);

uint_fast8_t pic32_isr_get_prio(enum pic32_isr_id isr_id);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_PIC32_ISR_H_ */
