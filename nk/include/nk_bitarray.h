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


#ifndef NK_BITARRAY_H_
#define NK_BITARRAY_H_

#include <stdint.h>
#include <stdbool.h>

#include "nk_bits.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Initialize the bitarray.
 *  @param      a_ba
 *              Pointer to bitarray structure @ref nbitarray.
 *  @api
 */

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

/** @brief      Get the position of Most Significat Bit Set.
 *  @param      a_ba
 *              Pointer to bitarray structure.
 *  @returns    The position of the MSB set bit: 0 - 255.
 *  @api
 */

struct nk_bitarray__indefinite
{
	uint32_t column;
	uint32_t * rows;
};

void nk_bitarray__indefinite_init(
		struct nk_bitarray__indefinite * ba, uint32_t * rows);

void nk_bitarray__indefinite_set(
		struct nk_bitarray__indefinite * ba, uint_fast8_t a_bit);

void nk_bitarray__indefinite_clear(
		struct nk_bitarray__indefinite * ba, uint_fast8_t a_bit);

uint_fast8_t nk_bitarray__indefinite_msbs(
		const struct nk_bitarray__indefinite * ba);

bool nk_bitarray__indefinite_is_set(
		const struct nk_bitarray__indefinite * ba, uint_fast8_t a_bit);

#define NK_BITARRAY__DEFINITE(bit_size) 									\
		{ 																	\
			struct nk_bitarray__indefinite indefinite; 						\
			uint32_t row[													\
					NK_BITS__DIVIDE_ROUNDUP(								\
							bit_size, NK_BITS__BIT_SIZE(uint32_t))]; 		\
		}

#define NK_BITARRAY__TO_INDEFINITE(ba)	&((ba)->indefinite)

#define NK_BITARRAY__DEFINITE_INIT(ba) 										\
		nk_bitarray__indefinite_init(										\
				NK_BITARRAY__TO_INDEFINITE(ba), &(ba)->row[0])

#define NK_BITARRAY__DEFINITE_SET(ba, a_bit) 								\
		nk_bitarray__indefinite_set(NK_BITARRAY__TO_INDEFINITE(ba), (a_bit))

#define NK_BITARRAY__DEFINITE_CLEAR(ba, a_bit) 								\
		nk_bitarray__indefinite_clear(NK_BITARRAY__TO_INDEFINITE(ba), (a_bit))

#define NK_BITARRAY__DEFINITE_MSBS(ba) 										\
		nk_bitarray__indefinite_msbs(NK_BITARRAY__TO_INDEFINITE(ba))

#define NK_BITARRAT__DEFINITE_IS_SET(ba)									\
		nk_bitarray__indefinite_is_set(NK_BITARRAY__TO_INDEFINITE(ba))

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NK_BITARRAY_H_ */
