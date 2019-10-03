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

#define pic32_isr_iec_reg(irq_no)                                           \
        (&((pic32_periph_access(&IEC0))[(irq_no) >> 5]))

#define pic32_isr_iec_mask(irq_no)                                          \
        (0x1u << ((irq_no) & 0x1fu))
    
#define pic32_isr_ifs_reg(irq_no)                                           \
        (&((pic32_periph_access(&IFS0))[(irq_no) >> 5]))

#define pic32_isr_ifs_mask(irq_no)                                          \
        pic32_isr_iec_mask(irq_no)

static inline
void pic32_isr_irq_enable(uint_fast8_t irq_no)
{
    struct pic32_periph_reg * iec = pic32_isr_iec_reg(irq_no);
    uint32_t mask = pic32_isr_iec_mask(irq_no);
    
    iec->set = mask;
}

static inline
void pic32_isr_irq_disable(uint_fast8_t irq_no)
{
    struct pic32_periph_reg * iec = pic32_isr_iec_reg(irq_no);
    uint32_t mask = pic32_isr_iec_mask(irq_no);
    
    iec->clr = mask;
}

static inline
bool pic32_isr_irq_is_enabled(uint_fast8_t irq_no)
{
    struct pic32_periph_reg * iec = pic32_isr_iec_reg(irq_no);
    uint32_t mask = pic32_isr_iec_mask(irq_no);
    
    return !!(iec->reg & mask);
}

static inline
void pic32_isr_irq_set(uint_fast8_t irq_no)
{
    struct pic32_periph_reg * ifs = pic32_isr_ifs_reg(irq_no);
    uint32_t mask = pic32_isr_ifs_mask(irq_no);
    
    ifs->set = mask;
}

static inline
void pic32_isr_irq_clear(uint_fast8_t irq_no)
{
    struct pic32_periph_reg * ifs = pic32_isr_ifs_reg(irq_no);
    uint32_t mask = pic32_isr_ifs_mask(irq_no);
    
    ifs->clr = mask;
}

static inline
bool pic32_isr_irq_is_set(uint_fast8_t irq_no)
{
    struct pic32_periph_reg * ifs = pic32_isr_ifs_reg(irq_no);
    uint32_t mask = pic32_isr_ifs_mask(irq_no);
    
    return !!(ifs->reg & mask);
}

void pic32_isr_vector_set_prio(uint_fast8_t vector_no, uint_fast8_t prio);

uint_fast8_t pic32_isr_vector_get_prio(uint_fast8_t vector_no);

void pic32_isr_init(void);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_PIC32_ISR_H_ */
