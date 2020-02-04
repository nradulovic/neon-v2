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


#ifndef NEON_ARCH_VARIANT_X86_H_
#define NEON_ARCH_VARIANT_X86_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   x86_variant_arch_cpu Architecture CPU (x86) operations
 *  @brief      Architecture CPU (x86) operations.
 *  @{
 */

/** @brief		Used internally by X86 clients.
 */
#define X86_ARCH						1

#define NARCH_ID 						"x86"
#define NARCH_DATA_WIDTH 				32 /* sizeof(uint32_t) * 8 */

#define NARCH_ALIGN						4
#define NARCH_HAS_ATOMICS				0
#define NARCH_HAS_EXCLUSIVE_LS			0

typedef uint32_t uint32_t;

/** @brief      Used internally by x86 clients.
 */
void x86_arch_init(void);

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_ARCH_VARIANT_X86_H_ */
