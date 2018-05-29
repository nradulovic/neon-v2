/*
 * Neon
 * Copyright (C)  2018  REAL-TIME CONSULTING
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Variant architecture for x86 header
 *
 *  @addtogroup  port
 *  @{
 */
/** @defgroup    port_x86_variant_arch Variant architecture for x86
 *  @brief       Variant architecture for x86.
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_X86_VARIANT_ARCH_H_
#define NEON_X86_VARIANT_ARCH_H_

#include <stdint.h>
#include "port/nport_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   x86_variant_arch_cpu Architecture CPU (x86) operations
 *  @brief      Architecture CPU (x86) operations.
 *  @{
 */

NPLATFORM_INLINE
uint32_t narch_exp2(uint_fast8_t x)
{
    return (0x1u << x);
}

NPLATFORM_INLINE
uint_fast8_t narch_log2(uint32_t x)
{
    return (31u - __builtin_clz(x));
}

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_X86_VARIANT_ARCH_H_ */
