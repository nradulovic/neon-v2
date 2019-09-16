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
/** @defgroup   nbits Bit operations
 *  @brief      Bit operations
 *  @{
 */

#ifndef NEON_BITS_H_
#define NEON_BITS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup   bits_array Sizeof macros
 *  @brief      Sizeof macros.
 *  @{ */

/** @brief      Determines the first dimension of an array.
 * 
 *  The size of the array is calculated by the compiler at compile time.
 *
 *  @param      a_array
 *              An array : type unspecified
 * 
 *  @mseffect
 *              Argument \a a_array is used multiple times in macro expansion.
 *  @hideinitializer
 */
#define NBITS_ARRAY_SIZE(a_array)       (sizeof(a_array) / sizeof(a_array[0]))

/** @brief      Determine the size (in bytes) of specified @a field in
 *              structure of type @a type.
 * 
 *  The size of the field is calculated by the compiler at compile time.
 *
 *  @param      a_type
 *              Type of the structure which contains the field : structure type
 *  @param      a_field
 *              Name of the field.
 *  @hideinitializer
 */
#define NBITS_FIELD_SIZE(a_type, a_field)                                   \
        (sizeof(((a_type *)0)->a_field))

/** @brief      Returns the sizeof @c type in bits.
 * 
 *  @param      a_type
 *              A type of a structure or variable.
 *  @hideinitializer
 */
#define NBITS_BIT_SIZE(a_type)          (sizeof(a_type) * 8u)

/** @} */
/** @defgroup   bits_division Integer division
 *  @brief      Integer division.
 *  @{ */

/** @brief      Round a division.
 * 
 *  @param      numerator
 *  @param      denominator
 *  @note       It is desirable that denominator is a constant expression,
 *              otherwise the compiler will generate two division operations.
 *  @mseffect
 *              Argument \a denominator is instantiated multiple times during
 *              macro expansion.
 * 
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
 * 
 *  @hideinitializer
 */
#define NBITS_DIVIDE_ROUND(numerator, denominator)                          \
    (((numerator) + ((denominator) / 2u)) / (denominator))

/** @brief      Round up a division
 * 
 *  @param      numerator
 *  @param      denominator
 *  @note       It is desirable that denominator is a constant expression,
 *              otherwise the compiler will generate one subtraction and one
 *              division operation.
 *  @mseffect
 *              Argument \a denominator is instantiated multiple times during
 *              macro expansion.
 * 
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
 * 
 *  @hideinitializer
 */
#define NBITS_DIVIDE_ROUNDUP(numerator, denominator)                        \
    (((numerator) + (denominator) - 1u) / (denominator))

/** @} */
/** @defgroup   bits_align Data alignment
 *  @brief      Data alignment.
 *  @{ */

/** @brief      Do the alignment of @a num value as specified by @a align.
 * 
 *  @param      num
 *              A value which needs to be aligned.
 *  @param      align
 *              Align value.
 *  @par        Example 1:
 *
 *              num  : 10010101 = 149
 *              align: 00000100 = 4
 *              Result is 148.
 * 
 *  @hideinitializer
 */
#define NBITS_ALIGN(num, align)         ((num) & ~((align) - 1u))

/** @brief      Do the alignment of @a num value as specified by @a align.
 * 
 *  In contrast to @ref NBITS_ALIGN, this macro will always pick a next bigger
 *  value for alignment.
 *
 *  @param      num
 *              A value which needs to be aligned.
 *  @param      align
 *              Align value.
 * 
 *  @mseffect
 *              Argument \a align is instantiated multiple times during  macro 
 *              expansion.
 * 
 *  @par        Example 1:
 *
 *              num  : 10010101 = 149
 *              align: 00000100 = 4
 *              Result is 152.
 * 
 *  @hideinitializer
 */
#define NBITS_ALIGN_UP(num, align)                                          \
    (((num) + (align) - 1u) & ~((align) - 1u))

/** @} */
/** @defgroup   bits_log Logarithm calculation
 *  @brief      Logarithm calculation.
 *  @{ */

/** @brief      Calculate log2 for value @c x during the compilation.
 * 
 *  This macro is best used when @c x is a constant. If the argument is a
 *  variable there are faster approaches.
 *
 *  @note       The @c x argument has to be in 0 - 255 range.
 * 
 *  @mseffect
 *              Argument \a x is instantiated multiple times during  macro 
 *              expansion.
 * 
 *  @hideinitializer
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
/** @defgroup   bits_power2 Power of 2 calculation
 *  @brief      Power of 2 calculation.
 *  @{ */

/** @brief      Right aligned bit mask lookup table.
 * 
 *  @note       If the value of argument @a v is greater than 32 then the
 *              behaviour is undefined.
 *  @notapi
 */
extern const uint32_t g_np_bits_right_mask[33];

/** @brief      Left aligned bit mask lookup table.
 * 
 *  @note       If the value of argument @a v is greater than 32 then the
 *              behaviour is undefined.
 *  @notapi
 */
extern const uint32_t g_np_bits_left_mask[33];

/** @brief      Determining if an integer is a power of 2.
 * 
 *  @note       For more details please refer to the following URL:
 *              https://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
 *  @notapi
 */
#define NBITS_IS_POWEROF2(num)                                              \
    (((num) != 0u) && (((num) & ((num) - 1)) == 0u))

/** @brief      Create a bit mask of width @a v bits.
 */
#define nbits_to_right_mask(v)          g_np_bits_right_mask[v]

/** @brief      Create a bit mask of width @a v bits.
 */
#define nbits_to_left_mask(v)           g_np_bits_left_mask[v]

/** @} */
/** @addtogroup bits_byteextract
 *  @{ */

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

/** @brief      Sign extend signed 24 bit integer to signed 32 bits integer.
 * 
 *  @param      value
 *              Signed 24 bit integer.
 */
#define nbits_ext_i24(value)            ncpu_ext_i24(value)

/** @} */
/** @defgroup   bits_conv Data convert
 *  @brief      Data convert.
 *  @{ */

uint32_t nbits_ftou32(float val);

float nbits_u32tof(uint32_t val);

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_BITS_H_ */
