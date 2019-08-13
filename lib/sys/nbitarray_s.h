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
/** @defgroup   bits_bitarray_s Simple bit array (NARCH_DATA_WIDTH bits)
 *  @brief      Functions for manipulating NARCH_DATA_WIDTH-bit array.
 *  @{
 */

#ifndef NEON_BITARRAY_S_H_
#define NEON_BITARRAY_S_H_

#include "sys/nport.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Defines what is the maximum number of bits in bitarray_s.
 */
#define NBITARRAY_S_MAX_SIZE            NARCH_DATA_WIDTH

/** @brief      Bitarray s type
 */
typedef narch_uint nbitarray_s;

/** @brief      Set a bit in the array.
 */
#define nbitarray_s_set(a_array, a_bit)                                     \
        do {                                                                \
            *(a_array) |= narch_exp2(a_bit);                                \
        } while (0)

/** @brief      Clear a bit in the array.
 */
#define nbitarray_s_clear(a_array, a_bit)                                   \
        do {                                                                \
            *(a_array) &= ~narch_exp2(a_bit);                               \
        } while (0)

/** @brief      Get the first set bit in the array.
 */
#define nbitarray_s_msbs(a_array)       narch_log2(*(a_array))

/** @brief      Returns true if no bit is set in whole array.
 */
#define nbitarray_s_is_empty(a_array)   (*(a_array) == 0)

/** @brief      Evaluates if a specified bit is set in the array.
 */
#define nbitarray_s_is_set(a_array, a_bit)                                  \
        (*(a_array) & narch_exp2(a_bit))

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_BITARRAY_S_H_ */
