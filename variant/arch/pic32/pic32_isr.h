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

#include "pic32_common.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#define PIC32_ISR_PRIO(prio, subprio)                                       \
        ((((prio) & 0x7u) << 2u) | ((subprio) & 0x3u))

enum pic32_isr_id
{
    PIC32_ISR_U1E_RX_TX,
    PIC32_ISR_U2E_RX_TX,
    PIC32_ISR_U3E_RX_TX,
    PIC32_ISR_U4E_RX_TX,
    PIC32_ISR_U5E_RX_TX,
};

void pic32_isr_resolve_iec(
        enum pic32_isr_id vector_id, 
        struct pic32_periph_reg ** iec,
        uint_fast8_t * bit);

void pic32_isr_resolve_ifs(
        enum pic32_isr_id vector_id, 
        struct pic32_periph_reg ** ifs, 
        uint_fast8_t * bit);

#define pic32_isr_resolved_enable(en_reg, en_bit, en_offset)                \
        do {                                                                \
            (en_reg)->set = (0x1ul << (en_offset)) << (en_bit);             \
        } while (0)

#define pic32_isr_resolved_disable(en_reg, en_bit, en_offset)               \
        do {                                                                \
            (en_reg)->clr = (0x1ul << (en_offset)) << (en_bit);              \
        } while (0)

#define pic32_isr_resolved_is_enabled(en_reg, en_bit, en_offset)            \
        ((en_reg)->reg & ((0x1ul << (en_offset)) << (en_bit)))

#define pic32_isr_resolved_set_flag(flag_reg, flag_bit, flag_offset)        \
        do {                                                                \
            (flag_reg)->set = (0x1ul << (flag_offset)) << (flag_bit);       \
        } while (0)

#define pic32_isr_resolved_clear_flag(flag_reg, flag_bit, flag_offset)      \
        do {                                                                \
            (flag_reg)->clr = (0x1ul << (flag_offset)) << (flag_bit);        \
        } while (0)

#define pic32_isr_resolved_is_flagged(flag_reg, flag_bit, flag_offset)      \
        ((flag_reg)->reg & ((0x1ul << (flag_offset)) << (flag_bit)))

void pic32_isr_enable(enum pic32_isr_id vector_id, uint_fast8_t offset);

void pic32_isr_disable(enum pic32_isr_id vector_id, uint_fast8_t offset);

bool pic32_isr_is_enabled(enum pic32_isr_id vector_id, uint_fast8_t offset);

void pic32_isr_set_flag(enum pic32_isr_id vector_id, uint_fast8_t offset);

void  pic32_isr_clear_flag(enum pic32_isr_id vector_id, uint_fast8_t offset);

bool pic32_isr_is_flagged(enum pic32_isr_id vector_id, uint_fast8_t offset);

void pic32_isr_set_prio(enum pic32_isr_id vector_id, uint_fast8_t prio);

uint_fast8_t pic32_isr_get_prio(enum pic32_isr_id vector_id);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_PIC32_ISR_H_ */
