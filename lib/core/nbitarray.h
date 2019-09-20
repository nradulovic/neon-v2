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

/** @brief      Specifies the maximum number of bits in @a nbitarray array.
 *
 *  This macro defines maximum bit array size. Its value depends on used
 *  architecture. Use this macro before creating a new bit array to check if
 *  desired bit size is supported.
 *
 *  The maximum bit size is dependent on @ref NARCH_DATA_WIDTH. The maximum bit
 *  size is equal to @ref NARCH_DATA_WIDTH squared. For example, for 8-bit
 *  architecture the maximum bit size is 8*8=64 bits.
 *
 *  This constraint exists purely for efficiency reasons. By having this
 *  constraint an efficient implementation can be made while the constraint is
 *  not of such high impact.
 */
#define NBITARRAY_X_MAX_SIZE            (NARCH_DATA_WIDTH * NARCH_DATA_WIDTH)

/** @brief      Calculate the array size from desired size of bits.
 *  @notapi
 */
#define NP_BITARRAY_ARRAY_SIZE(a_size)                                      \
        NBITS_DIVIDE_ROUNDUP((a_size), NARCH_DATA_WIDTH)

/** @brief      Template for bitarray using pointer to array.
 */
#define nbitarray_pointer()                                                 \
        {                                                                   \
            struct np_bitarray super;                                       \
            narch_uint * array;                                             \
        }

/** @brief      Template for bitarray bits storage.
 */
#define nbitarray_storage(size)                                             \
        {                                                                   \
            narch_uint array[NP_BITARRAY_ARRAY_SIZE(size)];                 \
        }

/** @brief      Template for static bitarray structure.
 */
#define nbitarray(size)                                                     \
        {                                                                   \
            struct np_bitarray super;                                       \
            narch_uint array[NP_BITARRAY_ARRAY_SIZE(size)];                 \
        }

/** @brief      Bitarray super structure.
 */
struct np_bitarray
{
    narch_uint group;
};

/** @brief      Initialize a pointer bitarray.
 *  @param      BA
 *              Pointer to allocated bitarray.
 *  @param      a_storage
 *              Pointer to allocated storage.
 *  @mseffect
 */
#define NBITARRAY_INIT_POINTER(BA, a_storage)                               \
        do {                                                                \
            (BA)->array = &(a_storage)->array[0];                           \
            np_bitarray_init(                                               \
                    &(BA)->super,                                           \
                    (BA)->array,                                            \
                    sizeof((a_storage)->array));                            \
        } while (0)

/** @brief      Initialize bitarray.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_INIT(BA)                                                  \
        np_bitarray_init(&(BA)->super, (BA)->array, sizeof((BA)->array))

/** @brief      Set a bit in bitarray.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_SET(BA, a_bit)                                            \
        np_bitarray_set(&(BA)->super, (BA)->array, (a_bit)

/** @brief      Clear a bit in bitarray.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_CLEAR(BA, a_bit)                                          \
        np_bitarray_clear(&(BA)->super, (BA)->array, (a_bit)

/** @brief      Return most significant bit set.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_MSBS(BA)                                                  \
        np_bitarray_msbs(&(BA)->super, (BA)->array)

/** @brief      Returns true if no bit is set in whole array.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_IS_EMPTY(BA)          ((BA)->super.group == 0u)

/** @brief      Return if a bit is set.
 *  @param      BA
 *              Pointer to bitarray.
 *  @mseffect
 */
#define NBITARRAY_IS_SET(BA, a_bit)                                         \
        np_bitarray_is_set(&(BA)->super, (BA)->array, (a_bit)

/** @brief      Initialize the array.
 *  @notapi
 */
void np_bitarray_init(
        struct np_bitarray * super,
        narch_uint * array,
        uint8_t size_bits);

/** @brief      Set a bit in the array.
 *  @notapi
 */
void np_bitarray_set(
        struct np_bitarray * super,
        narch_uint * array,
        uint_fast8_t bit);

/** @brief      Clear a bit in the array.
 *  @notapi
 */
void np_bitarray_clear(
        struct np_bitarray * super,
        narch_uint * array,
        uint_fast8_t bit);

/** @brief      Get the first set bit in the array .
 *  @notapi
 */
uint_fast8_t np_bitarray_msbs(
        const struct np_bitarray * super,
        const narch_uint * array);

/** @brief      Evaluates if a specified bit is set in the array.
 *  @notapi
 */
bool np_bitarray_is_set(
        const struct np_bitarray * super,
        const narch_uint * array,
        uint_fast8_t bit);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_BITARRAY_H_ */
