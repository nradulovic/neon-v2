/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
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
 *  @brief       Common bitwise operations.
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_bits Common bitwise operations
 *  @brief       Common bitwise operations.
 *
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_MODULE_BITS_H_
#define NEON_MODULE_BITS_H_

#include <stdbool.h>
#include <stdint.h>

#include "../port/nport_platform.h"
#include "port/nport_arch.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   bits_array Sizeof macros
 *  @brief      Sizeof macros.
 *  @{
 */

/** @brief      Determines the first dimension of an array.
 *
 *  The size of the array is calculated by the compiler at compile time.
 * 
 *  @param      array
 *              An array : type unspecified
 *  @mseffect
 */
#define NBITS_ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

/** @brief      Determine the size (in bytes) of specified @r field in 
 *              structure of type @r type.
 *
 *  The size of the field is calculated by the compiler at compile time.
 * 
 *  @param      type
 *              Type of the structure which contains the field : structure type
 *  @param      field
 *              Name of the field.
 */
#define NBITS_FIELD_SIZE(type, field) (sizeof(((type *)0)->field))

/** @brief      Returns the sizeof @c type in bits.
 */
#define NBITS_BIT_SIZE(type)    (sizeof(type) * 8u)    

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   bits_division Integer division
 *  @brief      Integer division.
 *  @{
 */

/** @brief      Round a division
 *  @param      numerator
 *  @param      denominator
 *  @note       It is desirable that denominator is a constant expression,
 *              otherwise the compiler will generate two division operations.
 *  @mseffect
 *  @par        Example 1:
 *
 *              numerator   = 28
 *              denominator = 5
 *
 *              Integer division: 28 / 5 = 5
 *              Float division  : 28 / 5 = 5.6
 *              Rounded division: 28 / 5 = 6
 *
 *  @par        Example 2:
 *
 *              numerator   = 27
 *              denominator = 5
 *
 *              Integer division: 27 / 5 = 5
 *              Float division  : 27 / 5 = 5.4
 *              Rounded division: 27 / 5 = 5
 */
#define NBITS_DIVIDE_ROUND(numerator, denominator)                          \
    (((numerator) + ((denominator) / 2u)) / (denominator))

/** @brief      Round up a division
 *  @param      numerator
 *  @param      denominator
 *  @note       It is desirable that denominator is a constant expression,
 *              otherwise the compiler will generate one subtraction and one
 *              division operation.
 *  @mseffect
 *  @par        Example 1:
 *
 *              numerator   = 28
 *              denominator = 5
 *
 *              Integer division   : 28 / 5 = 5
 *              Float division     : 28 / 5 = 5.6
 *              Rounded up division: 28 / 5 = 6
 *
 *  @par        Example 2:
 *
 *              numerator   = 27
 *              denominator = 5
 *
 *              Integer division   : 27 / 5 = 5
 *              Float division     : 27 / 5 = 5.4
 *              Rounded up division: 27 / 5 = 6
 */
#define NBITS_DIVIDE_ROUNDUP(numerator, denominator)                        \
    (((numerator) + (denominator) - 1u) / (denominator))

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   bits_align Data alignment
 *  @brief      Data alignment.
 *  @{
 */

/** @brief      Do the alignment of @a num value as specified by @a align.
 *  @param      num
 *              A value which needs to be aligned.
 *  @param      align
 *              Align value.
 *  @mseffect
 *  @par        Example 1:
 *
 *              num  : 10010101 = 149
 *              align: 00000100 = 4
 *              Result is 148.
 */
#define NBITS_ALIGN(num, align) ((num) & ~((align) - 1u))

/** @brief      Do the alignment of @a num value as specified by @a align.
 *
 *  In contrast to @ref NBITS_ALIGN, this macro will always pick a next bigger
 *  value for alignment.
 *
 *  @param      num
 *              A value which needs to be aligned.
 *  @param      align
 *              Align value.
 *  @par        Example 1:
 *
 *              num  : 10010101 = 149
 *              align: 00000100 = 4
 *              Result is 152.
 */
#define NBITS_ALIGN_UP(num, align)                                          \
    (((num) + (align) - 1u) & ~((align) - 1u))

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   bits_log Logarithm calculation
 *  @brief      Logarithm calculation.
 *  @{
 */

/** @brief      Calculate log2 for value @c x during the compilation.
 * 
 *  This macro is best used when @c x is a constant. If the argument is a
 *  variable there are faster approaches.
 *
 *  @note       The @c x argument has to be in 0 - 255 range.
 *  @mseffect
 */
#define NBITS_LOG2_8(x)                                                     \
    ((x) <   2u ? 0u :                                                      \
     ((x) <   4u ? 1u :                                                     \
      ((x) <   8u ? 2u :                                                    \
       ((x) <  16u ? 3u :                                                   \
        ((x) <  32u ? 4u :                                                  \
         ((x) <  64u ? 5u :                                                 \
          ((x) < 128u ? 6u : 7u)))))))

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   bits_power2 Power of 2 macros
 *  @brief      Power of 2 macros.
 *  @{
 */

#define NBITS_IS_POWEROF2(num)    										    \
    (((num) != 0u) && (((num) & ((num) - 1)) == 0u))

/** @brief      Determining if an integer is a power of 2
 *  @note       For more details please refer to the following URL:
 *              https://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
 */
NPLATFORM_INLINE
uint32_t nbits_is_powerof2(uint32_t v)
{
    return v && !(v & (v - 1));
}

/** @brief      Create a bit mask of width @a v bits.
 *  @note       If the value of argument @a v is greater than 32 then the
 *              behaviour undefined.
 */
NPLATFORM_INLINE
uint32_t nbits_to_mask(uint32_t v)
{
    static const uint32_t mask[33] =
    {
        [ 0] = 0x00000000u,
        [ 1] = 0x00000001u,
        [ 2] = 0x00000003u,
        [ 3] = 0x00000007u,
        [ 4] = 0x0000000fu,
        [ 5] = 0x0000001fu,
        [ 6] = 0x0000003fu,
        [ 7] = 0x0000007fu,
        [ 8] = 0x000000ffu,
        [ 9] = 0x000001ffu,
        [10] = 0x000003ffu,
        [11] = 0x000007ffu,
        [12] = 0x00000fffu,
        [13] = 0x00001fffu,
        [14] = 0x00003fffu,
        [15] = 0x00007fffu,
        [16] = 0x0000ffffu,
        [17] = 0x0001ffffu,
        [18] = 0x0003ffffu,
        [19] = 0x0007ffffu,
        [20] = 0x000fffffu,
        [21] = 0x001fffffu,
        [22] = 0x003fffffu,
        [23] = 0x007fffffu,
        [24] = 0x00ffffffu,
        [25] = 0x01ffffffu,
        [26] = 0x03ffffffu,
        [27] = 0x07ffffffu,
        [28] = 0x0fffffffu,
        [29] = 0x1fffffffu,
        [30] = 0x3fffffffu,
        [31] = 0x7fffffffu,
        [32] = 0xffffffffu
    };
    return mask[v];
}

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   bits_byteextract Byte extract
 *  @brief      Byte extract.
 *  @{
 */

/** @brief      Extract the MSB byte from 4-byte word.
 */
#define nbits_msb_32(x)                 nbits_xb4(x)

/** @brief      Extract the LSB byte from 4-byte word.
 */
#define nbits_lsb_32(x)                 nbits_xb1(x)

#define nbits_xb4(value)                ((uint32_t)(value) >> 24u)

#define nbits_xb3(value)                (((uint32_t)(value) >> 16u) & 0xffu)

#define nbits_xb2(value)                (((uint32_t)(value) >> 8u) & 0xffu)

#define nbits_xb1(value)                ((uint32_t)(value) & 0xffu)

/**@brief       Sign extend signed 24 bit integer to signed 32 bits integer
 * @param       val - signed 24 bit integer
 * @return
 */
#define n_ext_i24(value)                ncore_ext_i24(value)

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   bits_conv Data convert
 *  @brief      Data convert.
 *  @{
 */

uint32_t nbits_ftou32(float val);

float nbits_u32tof(uint32_t val);

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   bits_bitarray_s Simple bit array (NARCH_DATA_WIDTH bits)
 *  @brief      Functions for manipulating NARCH_DATA_WIDTH-bit array.
 *  @{
 */

#define NBITARRAY_S_MAX_SIZE        NARCH_DATA_WIDTH
 
typedef narch_uint nbitarray_s;

#define nbitarray_s_set(a_array, a_bit)                                     \
    narch_set_bit((a_array), (a_bit))
    
#define nbitarray_s_clear(a_array, a_bit)                                   \
    narch_clear_bit((a_array), (a_bit))
    
#define nbitarray_s_msbs(a_array)                                           \
    narch_log2(*(a_array))

#define nbitarray_s_is_empty(a_array)                                       \
    (*(a_array) == 0)

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   bits_bitarray_x Extended bit array
 *  @brief      Functions for manipulating bit arrays with bit length more than
 *              NARCH_DATA_WIDTH bits.
 *  @{
 */

typedef narch_uint nbitarray_x;

#define NBITARRAY_X_DEF(bits)												\
	NBITS_DIVIDE_ROUNDUP((bits), NARCH_DATA_WIDTH) + 1

/** @brief      Specifies the maximum number of bits in @a nbitarray_x array.
 */
#define NBITARRAY_X_MAX_SIZE                                                \
    (NARCH_DATA_WIDTH * NARCH_DATA_WIDTH)

void nbitarray_x_set(nbitarray_x * array, uint_fast8_t bit);
void nbitarray_x_clear(nbitarray_x * array, uint_fast8_t bit);
uint_fast8_t nbitarray_x_msbs(const nbitarray_x * array);

#define nbitarray_x_is_empty(a_array)										\
	((a_array)[0] == 0u)

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_BITS_H_ */

