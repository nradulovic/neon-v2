/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @addtogroup neon
 *  @{
 */
/** @defgroup   bits_bitarray Bit array
 *  @brief      Functions for manipulating bit arrays with various bit length.
 *  @{
 */

#ifndef NEON_BITARRAY_H_
#define NEON_BITARRAY_H_

#include <stdint.h>
#include <stdbool.h>

#include "core/nport.h"
#include "core/nbits.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t nbitarray;

struct nbitarray
{
	uint32_t * array;
};

#define NBITARRAY_SIZE(a_bits)											\
			(1u + NBITS_DIVIDE_ROUNDUP((a_size), NARCH_DATA_WIDTH))

#define nbitarray_elements(a_bits)	\
		uint32_t elements[NBITARRAY_SIZE(a_bits)]

#define nbitarray_static(a_bits) 											\
		{ 																	\
			struct nbitarray base;											\
			nbitarray_elements(a_bits); 									\
		}

#define nbitarray(a_size) \
		{					\
			uint32_t elements[(1u + NBITS_DIVIDE_ROUNDUP((a_size), NARCH_DATA_WIDTH))]; \
		}

/** @brief      Initialize the array.
 */
void nbitarray_init(nbitarray * array, uint8_t size_bytes);

/** @brief      Set a bit in the array.
 *  @notapi
 */
void nbitarray_set(uint32_t * array, uint_fast8_t bit);

/** @brief      Clear a bit in the array.
 *  @notapi
 */
void nbitarray_clear(uint32_t * array, uint_fast8_t bit);

/** @brief      Get the first set bit in the array .
 *  @notapi
 */
uint_fast8_t nbitarray_msbs(const uint32_t * array);

/** @brief      Evaluates if a specified bit is set in the array.
 *  @notapi
 */
bool nbitarray_is_set(const uint32_t * array, uint_fast8_t bit);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_BITARRAY_H_ */
