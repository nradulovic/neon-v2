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
 *  @brief       Scheduler Bitmap header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_bitmap Scheduler bitmap
 *  @brief       Scheduler bitmap.
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_SCHED_BITARRAY_H_
#define NEON_SCHED_BITARRAY_H_

#include <stdint.h>
#include <string.h>
#include "port/nport_platform.h"
#include "port/nport_arch.h"
#include "bits/nbits.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Defines the maximum number of bits in @ref nbitarray.
 */
#define NBITARRAY_BITS     256u

struct nbitarray
{
    uint32_t        column[NBITARRAY_BITS / NBITS_BIT_SIZE(uint32_t)];
    uint_fast8_t    row_indicator;
};

/** @brief      Initialize the bitmap.
 *  @param      bitmap
 *              Pointer to bitmap structure.
 *  @api
 */
NPLATFORM_INLINE
void nbitarray_init(struct nbitarray * bitmap)
{
    memset(bitmap, 0, sizeof(*bitmap));   
}

/** @brief      Set a bit.
 *  @param      bitmap
 *              Pointer to bitmap structure.
 *  @param      bit
 *              Bit number in the bitmap. The bit value must be in range:
 *              0 - (@ref NBITARRAY_BITS - 1u).
 *  @api
 */
NPLATFORM_INLINE
void nbitarray_set(struct nbitarray * bitmap, uint_fast8_t bit)
{
    uint_fast8_t row;
    uint_fast8_t column;

    column = bit & ((uint_fast8_t)~0u >> (NBITS_BIT_SIZE(bit) - 
            NBITS_LOG2_8(NBITS_BIT_SIZE(bitmap->column[0]))));
    row = bit >> NBITS_LOG2_8(NBITS_BIT_SIZE(bitmap->column[0]));
    bitmap->column[row] |= 0x1u << column;
    bitmap->row_indicator |= 0x1u << row;
}

/** @brief      Clear a bit.
 *  @param      bitmap
 *              Pointer to bitmap structure.
 *  @param      bit
 *              Bit number in the bitmap. The bit value must be in range:
 *              0 - (@ref NBITARRAY_BITS - 1u).
 *  @api
 */
NPLATFORM_INLINE
void nbitarray_clear(struct nbitarray * bitmap, uint_fast8_t bit)
{
    uint_fast8_t row;
    uint_fast8_t column;

    column = bit & ((uint_fast8_t)~0u >> (NBITS_BIT_SIZE(bit) - 
            NBITS_LOG2_8(NBITS_BIT_SIZE(bitmap->column[0]))));
    row = bit >> NBITS_LOG2_8(NBITS_BIT_SIZE(bitmap->column[0]));
    bitmap->column[row] &= ~(0x1u << column);

    if (bitmap->column[row] == 0u) {
        bitmap->row_indicator &= ~(0x1u << row);
    }
}

/** @brief      Get the position of Most Significat Bit Set.
 *  @param      bitmap
 *              Pointer to bitmap structure.
 *  @returns    The position of the MSB set bit: 0 - 255.
 *  @api
 */
NPLATFORM_INLINE
uint_fast8_t nbitarray_msbs(const struct nbitarray * bitmap)
{
    uint_fast8_t                row;
    uint_fast8_t                column;

    row = narch_log2(bitmap->row_indicator);
    column = narch_log2(bitmap->column[row]);

    return ((row << NBITS_LOG2_8(NBITS_BIT_SIZE(bitmap->column[0]))) | column);
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_SCHED_BITARRAY_H_ */
