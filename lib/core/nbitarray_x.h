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
/** @defgroup   bits_bitarray_x Extended bit array
 *  @brief      Functions for manipulating bit arrays with bit length more than
 *              NARCH_DATA_WIDTH bits.
 *  @{
 */

#ifndef NEON_BITARRAY_X_H_
#define NEON_BITARRAY_X_H_

#include <stdint.h>
#include <stdbool.h>

#include "core/nport.h"
#include "core/nbits.h"

#ifdef __cplusplus
extern "C" {
#endif

#define nbitarray_dynamic(T) \
		{ \
			struct nbitarray super; \
			narch_uint * array; \
		}

#define nbitarray_dynamic_storage(T, size)                                    \
    {                                                                       \
        T narch_uint array[NBITS_DIVIDE_ROUNDUP((size), NARCH_DATA_WIDTH)];                                                    \
    }

#define nbitarray(T, size) \
		{ \
			struct nbitarray super; \
			narch_uint array[NBITS_DIVIDE_ROUNDUP((size), NARCH_DATA_WIDTH)]; \
		}

struct nbitarray
{
	narch_uint group;
};

/** @brief      Initialize a dynamic queue structure
 *  @param      Q
 *              Pointer to dynamically allocated lightweight queue.
 *  @param      a_size_bytes
 *              The size of storage in bytes.
 *  @param      a_storage
 *              Pointer to allocated storage.
 *  @mseffect
 */
#define NBITARRAY_INIT_DYNAMIC(A, a_size, a_storage)                   \
        do {                                                                \
            (A)->super.group = 0u; \
            (A)->array = (a_storage);                               \
            memset((A)->array, 0, NBITS_DIVIDE_ROUNDUP((a_size), 8u)); \
        } while (0)

/** @brief      Bitarray x type
 */
typedef narch_uint nbitarray_x;

/** @brief      Define an array of size bits.
 */
#define NBITARRAY_X_DEF(bits)                                               \
        NBITS_DIVIDE_ROUNDUP((bits), NARCH_DATA_WIDTH) + 1

/** @brief      Specifies the maximum number of bits in @a nbitarray_x array.
 */
#define NBITARRAY_X_MAX_SIZE            (NARCH_DATA_WIDTH * NARCH_DATA_WIDTH)

/** @brief      Set a bit in the array.
 */
void nbitarray_x_set(nbitarray_x * array, uint_fast8_t bit);

/** @brief      Clear a bit in the array.
 */
void nbitarray_x_clear(nbitarray_x * array, uint_fast8_t bit);

/** @brief      Get the first set bit in the array .
 */
uint_fast8_t nbitarray_x_msbs(const nbitarray_x * array);

/** @brief      Returns true if no bit is set in whole array.
 */
#define nbitarray_x_is_empty(a_array)   ((a_array)[0] == 0u)

/** @brief      Evaluates if a specified bit is set in the array.
 */
bool nbitarray_x_is_set(const nbitarray_x * array, uint_fast8_t bit);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_BITARRAY_X_H_ */
