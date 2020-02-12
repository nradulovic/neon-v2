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

/** @brief      Template for static bitarray structure.
 */
#define nbitarray(a_size)                                                   \
        {                                                                   \
            uint32_t array[1 +                                              \
                NBITS_DIVIDE_ROUNDUP((a_size), NARCH_DATA_WIDTH)];  \
        }

/** @brief      Initialize bitarray.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_INIT(BA)                                                  \
        np_bitarray_init((BA)->array, sizeof((BA)->array))

/** @brief      Set a bit in bitarray.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_SET(BA, a_bit)                                            \
        np_bitarray_set(&(BA)->array[0], (a_bit))

/** @brief      Clear a bit in bitarray.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_CLEAR(BA, a_bit)                                          \
        np_bitarray_clear(&(BA)->array[0], (a_bit))

/** @brief      Return most significant bit set.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_MSBS(BA)              np_bitarray_msbs(&(BA)->array[0])

/** @brief      Returns true if no bit is set in whole array.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_IS_EMPTY(BA)          ((BA)->array[0] == 0u)

/** @brief      Return if a bit is set.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_IS_SET(BA, a_bit)                                         \
        np_bitarray_is_set(&(BA)->array[0], (a_bit))

/** @brief      Initialize the array.
 *  @notapi
 */
void np_bitarray_init(uint32_t * array, uint8_t size_bytes);

/** @brief      Set a bit in the array.
 *  @notapi
 */
void np_bitarray_set(uint32_t * array, uint_fast8_t bit);

/** @brief      Clear a bit in the array.
 *  @notapi
 */
void np_bitarray_clear(uint32_t * array, uint_fast8_t bit);

/** @brief      Get the first set bit in the array .
 *  @notapi
 */
uint_fast8_t np_bitarray_msbs(const uint32_t * array);

/** @brief      Evaluates if a specified bit is set in the array.
 *  @notapi
 */
bool np_bitarray_is_set(const uint32_t * array, uint_fast8_t bit);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_BITARRAY_H_ */
