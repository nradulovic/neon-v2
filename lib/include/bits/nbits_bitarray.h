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
#include "port/nport_platform.h"
#include "port/nport_arch.h"
#include "bits/nbits.h"

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
 *  @param      ba
 *              Pointer to bitarray structure.
 *  @api
 */
NPLATFORM_INLINE
void nbitarray_init(struct nbitarray * ba)
{
    ba->bits = 0u;
}

/** @brief      Set a bit.
 *  @param      bitarray
 *              Pointer to bitarray structure.
 *  @param      bit
 *              Bit number in the bitarray. The bit value must be in range:
 *              0 - (@ref NBITARRAY_BITS - 1u).
 *  @api
 */
NPLATFORM_INLINE
void nbitarray_set(struct nbitarray * ba, uint_fast8_t bit)
{
    ba->bits |= 0x1u << bit;
}

/** @brief      Clear a bit.
 *  @param      bitarray
 *              Pointer to bitarray structure.
 *  @param      bit
 *              Bit number in the bitarray. The bit value must be in range:
 *              0 - (@ref NBITARRAY_BITS - 1u).
 *  @api
 */
NPLATFORM_INLINE
void nbitarray_clear(struct nbitarray * ba, uint_fast8_t bit)
{
    ba->bits &= ~(0x1u << bit);
}

/** @brief      Get the position of Most Significat Bit Set.
 *  @param      ba
 *              Pointer to bitarray structure.
 *  @returns    The position of the MSB set bit: 0 - 255.
 *  @api
 */
NPLATFORM_INLINE
uint_fast8_t nbitarray_msbs(const struct nbitarray * ba)
{
    return (narch_log2(ba->bits));
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_BITS_BITARRAY_H_ */
