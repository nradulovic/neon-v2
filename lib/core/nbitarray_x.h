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

#include "sys/nport.h"

#ifdef __cplusplus
extern "C" {
#endif

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
