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
/** @defgroup    nk_bits Common bitwise operations
 *  @brief       Common bitwise operations.
 *
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NK_BITS_H_
#define NK_BITS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   bits_array Sizeof macros
 *  @brief      Sizeof macros.
 *  @{
 */

/** @brief      Determines the first dimension of an array.
 *  @param      array
 *              An array : type unspecified
 *  @mseffect
 */
#define NK_BITS__ARRAY_SIZE(array) 											\
		(sizeof(array) / sizeof(array[0]))

/** @brief      Returns the sizeof @c type in bits.
 *  @mseffect
 */
#define NK_BITS__BIT_SIZE(type)    		(sizeof(type) * 8u)

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
#define NK_BITS__DIVIDE_ROUND(numerator, denominator)                     	\
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
#define NK_BITS__DIVIDE_ROUNDUP(numerator, denominator)                    	\
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
#define NK_BITS__ALIGN(num, align) 		((num) & ~((align) - 1u))

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
#define NK_BITS__ALIGN_UP(num, align)                                      	\
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
#define NK_BITS__LOG2_8(x)                                                  \
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

#define NK_BITS__IS_POWEROF2(num)    										\
    (((num) != 0u) && (((num) & ((num) - 1)) == 0u))

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NK_BITS_H_ */

