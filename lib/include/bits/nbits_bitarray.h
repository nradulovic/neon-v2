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
 *  @brief       Bits bit array header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_bitmap Bitarray
 *  @brief       Bitarray.
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_BITS_BITARRAY_H_
#define NEON_BITS_BITARRAY_H_

#include <stdint.h>
#include "port/nport_arch.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Maximum number of bits in bitarray.
 *  @api
 */
#define NBITARRAY_BITS 32

struct nbitarray
{
    uint32_t bits;
};

/** @brief      Initialize the bitarray.
 *  @param      a_ba
 *              Pointer to bitarray structure @ref nbitarray.
 *  @api
 */
#define nbitarray_init(a_ba)    (a_ba)->bits = 0u

/** @brief      Set a bit.
 *  @param      a_ba
 *              Pointer to bitarray structure @ref nbitarray.
 *  @param      a_bit
 *              Bit number in the bitarray. The bit value must be in range:
 *              0 - (@ref NBITARRAY_BITS - 1u). Type uint_fast8_t.
 *  @note       Using a value bigger than @ref NBITARRAY_BITS - 1u for argument
 *              a_bit will cause undefined behaviour.
 *  @api
 */
#define nbitarray_set(a_ba, a_bit)                                          \
    narch_set_bit(&(a_ba)->bits, (a_bit))

/** @brief      Clear a bit.
 *  @param      a_ba
 *              Pointer to bitarray structure @ref nbitarray.
 *  @param      a_bit
 *              Bit number in the bitarray. The bit value must be in range:
 *              0 - (@ref NBITARRAY_BITS - 1u). Type uint_fast8_t.
 *  @note       Using a value bigger than @ref NBITARRAY_BITS - 1u for argument
 *              a_bit will cause undefined behaviour.
 *  @api
 */
#define nbitarray_clear(a_ba, a_bit)                                        \
    narch_clear_bit(&(a_ba)->bits, (a_bit))

/** @brief      Get the position of Most Significat Bit Set.
 *  @param      a_ba
 *              Pointer to bitarray structure.
 *  @returns    The position of the MSB set bit: 0 - 255.
 *  @api
 */
#define nbitarray_msbs(a_ba)    narch_log2((a_ba)->bits)

#define nbitarray_is_empty(a_ba)                                            \
    ((a_ba)->bits == 0u)

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_BITS_BITARRAY_H_ */
