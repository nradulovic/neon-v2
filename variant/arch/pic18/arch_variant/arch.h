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
 *  @brief       Variant architecture for PIC18 header
 *
 *  @addtogroup  port
 *  @{ */

/** @defgroup    port_pic18_variant_arch Variant architecture for PIC18
 *  @brief       Variant architecture for PIC18.
 *  @{ */

#ifndef NEON_ARCH_VARIANT_PIC18_H_
#define NEON_ARCH_VARIANT_PIC18_H_

#include <stdint.h>
#include <xc.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Used internally by PIC18 clients.
 */
#define PIC18_ARCH                      1

#define NARCH_ID                        "pic18"
#define NARCH_DATA_WIDTH                8u /* sizeof(narch_uint) * 8 */

#define NARCH_ALIGN                     1
#define NARCH_HAS_EXCLUSIVE_LS          0
    
#define NARCH_ISR_LOCK(local_state)                                         \
    do {                                                                    \
        (local_state)->state = INTCONbits.GIE;                              \
        while (INTCONbits.GIE == 1) {                                       \
            INTCONbits.GIE == 0;                                            \
        }                                                                   \
    } while (0)
    
#define NARCH_ISR_UNLOCK(local_state)                                       \
    INTCONbits.GIE = (local_state)->state
    
struct narch_isr_state
{
    uint8_t state;
};

/** @brief      Used internally by PIC18 clients.
 */
void pic18_init(void);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
#endif /* NEON_ARCH_VARIANT_PIC18_H_ */
