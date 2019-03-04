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
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Architecture header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_arch Architecture
 *  @brief       Architecture
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_MODULE_ARCH_H_
#define NEON_MODULE_ARCH_H_

#include <stdint.h>

#include "arch_variant/arch.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   archid Architecture identification information
 *  @brief      Port identification macros.
 *  @{
 */
#ifndef NARCH_ID
#define NARCH_ID                "unknown"
#endif

/** @brief      Each port defines a macro named NARCH_xxx.
 *  
 *  For example, the ARM based architectures will define 'NARCH_ARM'. In 
 *  addition to this macro it will probably define macros like 'NARCH_ARM_V7M'
 *  which identifies a subset of architecture information.
 */
#define NARCH_xxx

/** @brief      Number of bits of the used architecture
 *  @api
 */
#ifdef __DOXYGEN__
#define NARCH_DATA_WIDTH              8
#endif
    
/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   arch_cpu Architecture CPU operations
 *  @brief      Architecture CPU operations.
 *  @{
 */

/** @brief      Stop the CPU execution.
 *  
 *  On embedded targets this function will actually stop the CPU execution.
 *  Usually you want to stop the execution in case of some serious error. When
 *  a High Level OS is used, this function will terminate the current process.
 */
void narch_cpu_stop(void);

/** @brief      Set a bit in unsigned 32-bit integer variable
 *  @param      u32
 *              Pointer to unsigned 32-bit integer.
 *  @param      bit
 *              Argument specifying which bit to set.
 *  @note       Do not use bit >= 32 since it will result in undefined
 *              behaviour.
 *  @api
 */
void narch_set_bit(uint32_t * u32, uint_fast8_t bit);

/** @brief      Clear a bit in unsigned integer 32-bit variable
 *  @param      u32
 *              Pointer to unsigned 32-bit integer.
 *  @param      bit
 *              Argument specifying which bit to clear.
 *  @note       Do not use bit >= 32 since it will result in undefined
 *              behaviour.
 *  @api
 */
void narch_clear_bit(uint32_t * u32, uint_fast8_t bit);

/** @brief      Calculate exponent of 2.
 */
narch_uint narch_exp2(uint_fast8_t x);

/** @brief      Calculate logarithm of base 2.
 *  @example    log2(2) = 1, log2(10) = 4
 */
uint_fast8_t narch_log2(narch_uint x);

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_ARCH_H_ */
