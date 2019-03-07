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
 *  @brief       Neon header
 *
 *  @defgroup    lib_task Task
 *  @brief       Task
 *  @{
 */

#ifndef NEON_H_
#define NEON_H_

#include <stdbool.h>
#include <stdint.h>

#include "platform_variant/platform.h"
#include "arch_variant/arch.h"
#include "mcu_variant/mcu.h"
#include "board_variant/board.h"
#include "os_variant/os.h"

/*===========================================================================*/
/** @defgroup   nconfig Configuration module
 *  @brief      Configuration module
 *  @{ *//*==================================================================*/

#if defined(NCONFIG_PROJECT_CONFIG)
#include "neon_config.h"
#endif

#ifndef NCONFIG_ENABLE_LOGGER
#define NCONFIG_ENABLE_LOGGER 0
#endif

#ifndef NCONFIG_ENABLE_DEBUG
#define NCONFIG_ENABLE_DEBUG 0
#endif

#ifndef NCONFIG_TASK_INSTANCES
#define NCONFIG_TASK_INSTANCES 8
#endif

#ifndef NCONFIG_EXITABLE_SCHEDULER
#define NCONFIG_EXITABLE_SCHEDULER 0
#endif

#ifndef NCONFIG_TESTSUITE_STOP_ON_ERROR
#define NCONFIG_TESTSUITE_STOP_ON_ERROR 1
#endif

#define NCONFIG_ID															\
	  ((uint32_t)NCONFIG_ENABLE_LOGGER << 31) 								\
	| ((uint32_t)NCONFIG_ENABLE_DEBUG << 30) 								\
	| ((uint32_t)NCONFIG_TESTSUITE_STOP_ON_ERROR << 29)						\
	| ((uint32_t)NCONFIG_TASK_INSTANCES << 0)

#define nconfig_validate()													\
	do {																	\
		extern const uint32_t nconfig_compiled_id;							\
		NASSERT(nconfig_compiled_id == NCONFIG_ID);							\
	} while (0)

/** @} *//*==================================================================*/
/** @defgroup   nport_platform Port platform module
 *  @brief      Port platform module
 *  @{ *//*==================================================================*/

/** @} */
/** @defgroup   platformid Platform identification information
 *  @brief      Port compiler identification macros.
 *  @{
 */
#ifdef __DOXYGEN__
#define NPLATFORM_ID            "unknown"
#endif

/** @brief      Each port defines a macro named NPLATFORM_xxx.
 *
 *  For example, the GCC based compilers will define 'NPLATFORM_GCC'. ARM
 *  based compilers will define NPLATFORM_ARM.
 */
#ifdef __DOXYGEN__
#define NPLATFORM_xxx
#endif

extern const char * nplatform_id;
extern const char * nplatform_build;

/** @defgroup   platform_compiler Platform compiler macros
 *  @brief      Port compiler helper macros.
 *  @{ */

/** @brief      Compiler directive to inline a function.
 *  @note       This macro is usually defined in port.
 */
#ifdef __DOXYGEN__
#define NPLATFORM_INLINE        static inline
#endif

#ifdef __DOXYGEN__
#define NPLATFORM_INLINE_ALWAYS NPLATFORM_INLINE
#endif

/**@brief       Cast a member of a structure out to the containing structure
 * @param       ptr
 *              the pointer to the member.
 * @param       type
 *              the type of the container struct this is embedded in.
 * @param       member
 *              the name of the member within the struct.
 */
#ifdef __DOXYGEN__
#define NPLATFORM_CONTAINER_OF(ptr, type, member)                      \
    ((type *)((char *)ptr - offsetof(type, member)))
#endif

/**@brief       Provides function name for assert macros
 */
#ifdef __DOXYGEN__
#define NPLATFORM_FUNC             "unknown"
#endif

/**@brief       Provides the free file's name which is being compiled
 */
#ifdef __DOXYGEN__
#define NPLATFORM_FILE             "unknown"
#endif

/**@brief       Provides the free source line
 */
#ifdef __DOXYGEN__
#define NPLATFORM_LINE             0
#endif

/**@brief       Omit function prologue/epilogue sequences
 * @note        Using this macro when the compiler feature is not supported
 *              will generate compilation error.
 */
#ifdef __DOXYGEN__
#define NPLATFORM_NAKED(x)              __provoke_error__ x
#endif

#ifdef __DOXYGEN__
#define NPLATFORM_UNUSED(y)             __provoke_error__ y
#endif

/**@brief       Declare a function that will never return
 */
#ifdef __DOXYGEN__
#define NPLATFORM_NORETURN(x)           x
#endif

#ifdef __DOXYGEN__
#define NPLATFORM_PACKED(x)             __provoke_error__ x
#endif

/**@brief       This attribute specifies a minimum alignment (in bytes) for
 *              variables of the specified type.
 */
#ifdef __DOXYGEN__
#define NPLATFORM_ALIGN(align, x)       __provoke_error__ x
#endif

/**@brief       Prevent the compiler from merging or refetching accesses.
 * @details     The compiler is also forbidden from reordering successive
 *              instances of NPLATFORM_ACCESS_ONCE(), but only when the
 *              compiler is aware of some particular ordering.  One way to make
 *              the compiler aware of ordering is to put the two invocations of
 *              NPLATFORM_ACCESS_ONCE() in different C statements.
 */
#ifdef __DOXYGEN__
#define NPLATFORM_ACCESS_ONCE(x)        (*(volatile typeof(x) *)&(x))
#endif

/** @brief      Returns current date.
 */
#ifdef __DOXYGEN__
#define NPLATFORM_DATE                  __DATE__
#endif

/** @brief      Returns current time.
 */
#ifdef __DOXYGEN__
#define NPLATFORM_TIME                  __TIME__
#endif

/** @} */
/** @} *//*==================================================================*/
/** @defgroup   nport_arch Port architecture module
 *  @brief      Port architecture module
 *  @{ *//*==================================================================*/

/** @defgroup   archid Architecture identification information
 *  @brief      Port identification macros.
 *  @{ */

/** @brief		Name of the architecture (as string)
 */
#ifdef __DOXYGEN__
#define NARCH_ID                "unknown"
#endif

/** @brief      Each port defines a macro named NARCH_xxx.
 *
 *  For example, the ARM based architectures will define 'NARCH_ARM'. In
 *  addition to this macro it will probably define macros like 'NARCH_ARM_V7M'
 *  which identifies a subset of architecture information.
 */
#ifdef __DOXYGEN__
#define NARCH_xxx
#endif

/** @brief      Number of bits of the used architecture
 *  @api
 */
#ifdef __DOXYGEN__
#define NARCH_DATA_WIDTH              8
#endif

/** @} */
/** @defgroup   arch_cpu Architecture CPU operations
 *  @brief      Architecture CPU operations.
 *  @{ */

/** @brief      Stop the CPU execution.
 *
 *  On embedded targets this function will actually stop the CPU execution.
 *  Usually you want to stop the execution in case of some serious error. When
 *  a High Level OS is used, this function will terminate the current process.
 */
void narch_cpu_stop(void);

/** @brief      Set a bit in unsigned 32-bit integer variable
 *  @param      u32
 *              Pointer to unsigned 32-bit integer.
 *  @param      bit
 *              Argument specifying which bit to set.
 *  @note       Do not use bit >= 32 since it will result in undefined
 *              behaviour.
 *  @api
 */
void narch_set_bit(uint32_t * u32, uint_fast8_t bit);

/** @brief      Clear a bit in unsigned integer 32-bit variable
 *  @param      u32
 *              Pointer to unsigned 32-bit integer.
 *  @param      bit
 *              Argument specifying which bit to clear.
 *  @note       Do not use bit >= 32 since it will result in undefined
 *              behaviour.
 *  @api
 */
void narch_clear_bit(uint32_t * u32, uint_fast8_t bit);

/** @brief      Calculate exponent of 2.
 */
narch_uint narch_exp2(uint_fast8_t x);

/** @brief      Calculate logarithm of base 2.
 *  @example    log2(2) = 1, log2(10) = 4
 */
uint_fast8_t narch_log2(narch_uint x);

/** @} */

/** @} *//*==================================================================*/
/** @defgroup   nport_mcu Port MCU module
 *  @brief      Port MCU module
 *  @{ *//*==================================================================*/

/** @} *//*==================================================================*/
/** @defgroup   nport_mcu Port Board module
 *  @brief      Port Board module
 *  @{ *//*==================================================================*/

/** @} *//*==================================================================*/
/** @defgroup   nport_os Port OS module
 *  @brief      Port OSmodule
 *  @{ *//*==================================================================*/

/** @} *//*==================================================================*/
/** @defgroup   ndebug Debug module
 *  @brief      Debug module
 *  @{ *//*==================================================================*/

/** @defgroup   debug_moduleconfig Debug module configuration
 *  @brief      These features are enabled/disabled using the option
 *              @ref NCONFIG_ENABLE_NDEBUG.
 *  @{
 */
#if defined(NCONFIG_ENABLE_DEBUG) && (NCONFIG_ENABLE_DEBUG == 1)
#define NDEBUG_IS_ENABLED 1
#else
/** @brief      Macro that returns current ndebug configuration
 */
#define NDEBUG_IS_ENABLED 0
#endif

/** @} */
/** @defgroup   debug_errorcheck Error checking
 *  @brief      Error checking
 *  @{ */

/** @brief      Generic assert macro.
 *  @param      msg
 *              Message : a standard error message, see
 *              @ref standard_error_messages.
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @api
 */
#if (NDEBUG_IS_ENABLED == 1)
#define NASSERT(expr)                                                        \
    if (!(expr)) {                                                           \
    	NASSERT_ALWAYS(# expr);												 \
    }
#else
#define NASSERT(expr)                   (void)0
#endif

/** @brief      Generic assert macro with action.
 *  @param      msg
 *              Message : a standard error message, see
 *              @ref standard_error_messages.
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @param		action
 *  			Expression : C expression : expression which will be executed
 *  			when asser fails.
 *  @api
 */
#define NASSERT_ACTION(expr, action)                                        \
    if (!(expr)) {                                                          \
    	NASSERT_ALWAYS_ACTION(# expr, action);								\
    }

/** @brief      Assert macro that will always execute (no conditional) with
 *              action.
 *  @param      msg
 *              Message : a standard error message, see
 *              @ref Standard error messages.
 *  @param      text
 *              Text : string : a text which will be printed when this assert
 *              macro is executed.
 *  @api
 */
#if (NDEBUG_IS_ENABLED == 1)
#define NASSERT_ALWAYS_ACTION(text, action)                                 \
    do {																	\
    	nlogger_err("Failed assert %s at %s:%u in %s\n", text, 				\
    		NPLATFORM_FUNC, NPLATFORM_LINE, NPLATFORM_FILE);				\
    	action;																\
    } while (0)
#else
#define NASSERT_ALWAYS_ACTION(text, action)    								\
	action
#endif

/** @brief      Assert macro that will always execute (no conditional).
 *  @param      msg
 *              Message : a standard error message, see
 *              @ref Standard error messages.
 *  @param      text
 *              Text : string : a text which will be printed when this assert
 *              macro is executed.
 *  @api
 */
#if (NDEBUG_IS_ENABLED == 1)
#define NASSERT_ALWAYS(text)                                                 \
    do {																	\
    	nlogger_err("Failed assert %s at %s:%u in %s\n", text, 				\
    		NPLATFORM_FUNC, NPLATFORM_LINE, NPLATFORM_FILE);				\
    	narch_cpu_stop();													\
    } while (0)
#else
#define NASSERT_ALWAYS(text)             (void)0
#endif

/** @} */
/** @defgroup   debug_api_valid API contract validation
 *  @brief      These macros are enabled/disabled using the option
 *              @ref NCONFIG_ENABLE_NDEBUG.
 *  @{ */

/** @brief      Execute code to fulfill the contract
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @api
 */
#if (NDEBUG_IS_ENABLED == 1)
#define NOBLIGATION(expr)               expr
#else
#define NOBLIGATION(expr)               (void)0
#endif

/** @brief      Make sure the caller has fulfilled all contract preconditions
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @api
 */
#define NREQUIRE(expr)                  NASSERT(expr)

/** @brief      Make sure the caller has fulfilled all contract preconditions
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @api
 */
#define NREQUIRE_ACTION(expr, action)   NASSERT_ACTION(expr, action)

/** @brief      Make sure the callee has fulfilled all contract postconditions
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @api
 */
#define NENSURE(expr)                   NASSERT(expr)

/** @brief      Make sure the callee has fulfilled all contract postconditions
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @api
 */
#define NENSURE_ACTION(expr, action)    NASSERT_ACTION(expr, action)

/**@} */
/** @defgroup    debug_internal Internal checking
 *  @brief      These macros are enabled/disabled using the option
 *              @ref NCONFIG_ENABLE_NDEBUG.
 *  @{ */

/** @brief      Assert macro used for internal execution checking
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @api
 */
#define NASSERT_INTERNAL(expr)            NASSERT(expr)

/** @} */
/** @defgroup   Object debug signatures
 *  @brief      During debugging the objects will use the signatures.
 *  @{ */

#define NSIGNATURE_HEAP                     ((unsigned int)0xdeadbee0u)
#define NSIGNATURE_POOL                     ((unsigned int)0xdeadbee1u)
#define NSIGNATURE_STATIC                   ((unsigned int)0xdeadbee2u)
#define NSIGNATURE_STDHEAP                  ((unsigned int)0xdeadbee3u)
#define NSIGNATURE_TIMER                    ((unsigned int)0xdeadcee0u)
#define NSIGNATURE_THREAD                   ((unsigned int)0xdeaddee0u)
#define NSIGNATURE_EPA                      ((unsigned int)0xdeadfeeau)
#define NSIGNATURE_EQUEUE                   ((unsigned int)0xdeadfeebu)
#define NSIGNATURE_ETIMER                   ((unsigned int)0xdeadfeecu)
#define NSIGNATURE_EVENT                    ((unsigned int)0xdeadfeedu)
#define NSIGNATURE_SM                       ((unsigned int)0xdeadfeeeu)
#define NSIGNATURE_DEFER                    ((unsigned int)0xdeadfeefu)

#if (NDEBUG_IS_ENABLED == 1)
#define NSIGNATURE_DECLARE                     unsigned int _signature;
#define NSIGNATURE_INITIALIZER(signature)   ._signature = signature,
#else
#define NSIGNATURE_DECLARE
#define NSIGNATURE_INITIALIZER(signature)
#endif

#define NSIGNATURE_OF(object)    			((object) ? (object)->_signature : 0)
#define NSIGNATURE_IS(object, signature)    (object)->_signature = (signature)

/** @defgroup   Object debug signatures
 *  @brief      During debugging the objects will use the signatures.
 *  @{ */

#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
/* These can't be used after statements in c89. */
#ifdef __COUNTER__
  /* microsoft */
  #define STATIC_ASSERT(e,m) \
    enum { ASSERT_CONCAT(static_assert_, __COUNTER__) = 1/(!!(e)) }
#else
  /* This can't be used twice on the same line so ensure if using in headers
   * that the headers are not included twice (by wrapping in #ifndef...#endif)
   * Note it doesn't cause an issue when used on same line of separate modules
   * compiled with gcc -combine -fwhole-program.  */
  #define STATIC_ASSERT(e,m) \
    enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(e)) }
#endif

/** @} */

/** @} *//*==================================================================*/
/** @defgroup   nbits Bit operations module
 *  @brief      Bit operations module
 *  @{ *//*==================================================================*/

/** @defgroup   bits_array Sizeof macros
 *  @brief      Sizeof macros.
 *  @{ */

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
/** @defgroup   bits_division Integer division
 *  @brief      Integer division.
 *  @{ */

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
/** @defgroup   bits_align Data alignment
 *  @brief      Data alignment.
 *  @{ */

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
/** @defgroup   bits_log Logarithm calculation
 *  @brief      Logarithm calculation.
 *  @{ */

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
/** @defgroup   bits_power2 Power of 2 macros
 *  @brief      Power of 2 macros.
 *  @{ */

/** @brief      Right mask lookup table
 */
extern const uint32_t nbits_right_mask[33];


/** @brief      Determining if an integer is a power of 2
 *  @note       For more details please refer to the following URL:
 *              https://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
 */
#define NBITS_IS_POWEROF2(num)    										    \
    (((num) != 0u) && (((num) & ((num) - 1)) == 0u))

/** @brief      Create a bit mask of width @a v bits.
 *  @note       If the value of argument @a v is greater than 32 then the
 *              behaviour undefined.
 */
#define nbits_to_mask(v)        nbits_right_mask[v]

/** @} */
/** @defgroup   bits_byteextract Byte extract
 *  @brief      Byte extract.
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

/**@brief       Sign extend signed 24 bit integer to signed 32 bits integer
 * @param       val - signed 24 bit integer
 * @return
 */
#define n_ext_i24(value)                ncore_ext_i24(value)

/** @} */
/** @defgroup   bits_conv Data convert
 *  @brief      Data convert.
 *  @{ */

uint32_t nbits_ftou32(float val);

float nbits_u32tof(uint32_t val);

/** @} */
/** @defgroup   bits_bitarray_s Simple bit array (NARCH_DATA_WIDTH bits)
 *  @brief      Functions for manipulating NARCH_DATA_WIDTH-bit array.
 *  @{ */

#define NBITARRAY_S_MAX_SIZE        NARCH_DATA_WIDTH

typedef narch_uint nbitarray_s;

#define nbitarray_s_set(a_array, a_bit)                                     \
    *(a_array) |= (0x1u << (a_bit))

#define nbitarray_s_clear(a_array, a_bit)                                   \
    *(a_array) &= ~(0x1u << (a_bit))

#define nbitarray_s_msbs(a_array)                                           \
    narch_log2(*(a_array))

#define nbitarray_s_is_empty(a_array)                                       \
    (*(a_array) == 0)

/** @} */
/** @defgroup   bits_bitarray_x Extended bit array
 *  @brief      Functions for manipulating bit arrays with bit length more than
 *              NARCH_DATA_WIDTH bits.
 *  @{ */

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
/** @} *//*==================================================================*/
/** @defgroup   nerror Error module
 *  @brief      Error module
 *  @{ *//*==================================================================*/

/** @defgroup   debug_errorcheck Error checking
 *  @brief      These features are enabled/disabled using the option
 *              @ref NCONFIG_ENABLE_NDEBUG.
 *  @{ */

/** @brief      Generic assert macro.
 *  @param      msg
 *              Message : a standard error message, see
 *              @ref standard_error_messages.
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 */
enum nerror_id
{
    EOBJ_INVALID, /**< Invalid object error */
    EOBJ_INITIALIZED,
    EARG_OUTOFRANGE, /**< Argument is out of range */
};

/** @} */
/** @} *//*==================================================================*/
/** @defgroup   nqueue_lqueue Lightweight queue module
 *  @brief      Lightweight queue module
 *  @{ *//*==================================================================*/

/** @brief    	Lightweight base structure.
 *  @notapi
 */
struct np_lqueue_base
{
	uint_fast8_t head;
	uint_fast8_t tail;
	uint_fast8_t empty;
	uint_fast8_t mask;
};

/** @brief    	Lightweight queue custom structure.
 *
 *  Contains the Base structure and buffer of type @a T with @a elements
 *  number of elements in that buffer. The buffer contains only pointers
 *  to items, not the actual items. This macro should be used to define a
 *  custom @a nlqueue structure.
 *
 *  @param    	T
 *    			Type of items in this queue.
 *  @param    	elements
 *    			Number of elements in queue buffer.
 *
 *  @note    	The macro can accept the parameter @a elements which is
 *              greater than 2 and equal to a number which is power of 2.
 *  @api
 */
#define nlqueue(T, elements)     										    \
    { 																		\
    	struct np_lqueue_base base; 										\
    	T np_qb_buffer[	((elements < 2) || !NBITS_IS_POWEROF2(elements)) ?  \
    		-1 : elements]; 												\
    }

/** @brief      Initialize a queue structure
 *  @api
 */
#define NLQUEUE_INIT(Q)     												\
    np_lqueue_base_init(&(Q)->base, 									    \
    		sizeof((Q)->np_qb_buffer) / sizeof((Q)->np_qb_buffer[0]))

/** @brief      Put an item to queue in FIFO mode.
 *  @note       Before calling this function ensure that queue is not full, see
 *     			@ref nqueue_is_full.
 */
#define NLQUEUE_PUT_FIFO(Q, item)     										\
    (Q)->np_qb_buffer[np_lqueue_base_put_fifo(&(Q)->base)] = (item)

/** @brief      Put an item to queue in LIFO mode.
 *  @note       Before calling this function ensure that queue is not full, see
 *     			@ref nqueue_is_full.
 */
#define NLQUEUE_PUT_LIFO(Q, item)     										\
    (Q)->np_qb_buffer[np_lqueue_base_put_lifo(&(Q)->base)] = (item)

/** @brief      Get an item from the queue buffer.
 *  @note       Before calling this function ensure that queue has an item. See
 *              @ref nqueue_is_empty.
 */
#define NLQUEUE_GET(Q)    													\
    (Q)->np_qb_buffer[np_lqueue_base_get(&(Q)->base)]

/** @brief      Peek to queue head; the item is not removed from queue.
 *
 *  Get the pointer to head item in the queue. The item is not removed from
 *  queue buffer.
 */
#define NLQUEUE_HEAD(Q)    													\
    (Q)->np_qb_buffer[np_lqueue_base_head(&(Q)->base)]

#define NLQUEUE_TAIL(Q)    													\
    (Q)->np_qb_buffer[np_lqueue_base_tail(&(Q)->base)]

/** @brief      Returns the buffer size in number of elements.
 */
#define NLQUEUE_SIZE(Q)    				(Q)->base.mask + 1u

/** @brief      Returns the current number of free elements in queue buffer.
 */
#define NLQUEUE_EMPTY(Q)    			(Q)->base.empty

/** @brief      Return true if queue is full else false.
 */
#define NLQUEUE_IS_FULL(Q)    			(!NLQUEUE_EMPTY(Q))

/** @brief      Return true if queue is empty else false.
 */
#define NLQUEUE_IS_EMPTY(Q)    												\
    (NLQUEUE_EMPTY(Q) == NLQUEUE_SIZE(Q))

/** @brief      Return the pointer to queue base structure
 */
#define NLQUEUE_BASE(Q)                 &(Q)->base

void np_lqueue_base_init(struct np_lqueue_base * qb, uint8_t elements);

uint32_t np_lqueue_base_put_fifo(struct np_lqueue_base * qb);

uint32_t np_lqueue_base_put_lifo(struct np_lqueue_base * qb);

uint32_t np_lqueue_base_get(struct np_lqueue_base * qb);

uint32_t np_lqueue_base_head(const struct np_lqueue_base * qb);

uint32_t np_lqueue_base_tail(const struct np_lqueue_base * qb);

/** @} *//*==================================================================*/
/** @defgroup   nlogger Extended logger module
 *  @brief      Extended logger module
 *  @{ *//*==================================================================*/

/** @defgroup   loggerprinters Logger printers
 *  @brief      Logger printers.
 *  @{
 */

#if defined(NCONFIG_ENABLE_LOGGER) && (NCONFIG_ENABLE_LOGGER == 1)
#define NLOGGER_IS_ENABLED 1
#else
/** @brief      Macro that returns current nlogger configuration
 */
#define NLOGGER_IS_ENABLED 0
#endif

#define NLOGGER_INITIALIZER(a_name) {.name = a_name}

/** @brief      Log a debug message.
 */
#define nlogger_x_debug(instance, msg, ...)                                 \
        nlogger_x_print(instance, NLOGGER_LEVEL_DEBUG, msg, __VA_ARGS__)

/** @brief      Log an informational message.
 */
#define nlogger_x_info(instance, msg, ...)                                  \
        nlogger_x_print(instance, NLOGGER_LEVEL_INFO, msg, __VA_ARGS__)

/** @brief      Log a warning message.
 */
#define nlogger_x_warn(instance, msg, ...)                                  \
        nlogger_x_print(instance, NLOGGER_LEVEL_WARN, msg, __VA_ARGS__)

/** @brief      Log an error message.
 */
#define nlogger_x_err(instance, msg, ...)                                   \
        nlogger_x_print(instance, NLOGGER_LEVEL_ERR, msg, __VA_ARGS__)

#if (NLOGGER_IS_ENABLED == 1)
#define nlogger_x_print(instance, level, msg, ...)                          \
    do {                                                                    \
        struct nlogger_instance * _instance = (instance);                   \
        p_nlogger_x_print(!_instance ? &p_nlogger_global : _instance, level,\
                msg, __VA_ARGS__);                                          \
    } while (0)
#else
#define nlogger_x_print(instance, level, msg, ...)
#endif

#if (NLOGGER_IS_ENABLED == 1)
#define nlogger_x_set_level(instance, level)                                \
    do {                                                                    \
        struct nlogger_instance * _instance = (instance);                   \
        p_nlogger_x_set_level(!_instance ? &p_nlogger_global : _instance,   \
                (level));                                                   \
    } while (0)
#else
#define nlogger_x_set_level(instance, level)
#endif

struct nlogger_instance
{
    const char * name;
    uint8_t level;
};

extern struct nlogger_instance p_nlogger_global;

void p_nlogger_x_print(struct nlogger_instance * instance,
        uint8_t level, const char * msg, ...);
void p_nlogger_x_set_level(struct nlogger_instance * instance, uint8_t level);

/** @} */
/** @} *//*==================================================================*/
/** @defgroup   nlogger Basic logger module
 *  @brief      Basic logger module
 *  @{ *//*==================================================================*/

/** @defgroup   loggerlevels Logger levels
 *  @brief      Logger levels.
 *  @{ */

/** @brief      Logger levels
 *  @details    Default log level is @ref NLOGGER_LVL_DEBUG.
 */
enum nlogger_levels
{
    NLOGGER_LEVEL_DEBUG = 4,
    NLOGGER_LEVEL_INFO = 3,
    NLOGGER_LEVEL_WARN = 2,
    NLOGGER_LEVEL_ERR = 1
};

/** @} */
/** @defgroup   loggerprinters Logger printers
 *  @brief      Logger printers.
 *  @{ */

/** @brief      Log a debug message.
 */
#define nlogger_debug(msg, ...)                                             \
        nlogger_x_debug(NULL, msg, __VA_ARGS__)

/** @brief      Log a informational message.
 */
#define nlogger_info(msg, ...)                                              \
        nlogger_x_info(NULL, msg, __VA_ARGS__)

/** @brief      Log a warning message.
 */
#define nlogger_warn(msg, ...)                                              \
        nlogger_x_warn(NULL, msg, __VA_ARGS__)

/** @brief      Log a error message.
 */
#define nlogger_err(msg, ...)                                               \
        nlogger_x_err(NULL, msg, __VA_ARGS__)

/** @} */
/** @} *//*==================================================================*/
/** @defgroup   ntask Task module
 *  @brief      Task module
 *  @{ *//*==================================================================*/

/** @brief  	The highest task priority value.
 *
 *  The task with this priority has the highest urgency to be selected and
 *  dispatched by scheduler.
 */
#define NTASK_PRIO_MAX          255

/** @brief		The lowest task priority value
 */
#define NTASK_PRIO_MIN          0

/** @brief		The current thread.
 */
#define ncurrent                ntask_current()

/** @brief		The current thread error.
 */
#define nerror                  ncurrent->tls.error

/** @brief		Task function pointer
 */
typedef void (ntask_fn)(void * arg);

enum ntask_state
{
    NTASK_UNINITIALIZED         = 0,
    NTASK_DORMANT               = 251,
    NTASK_READY                 = 252,
    NTASK_CANCELLED             = 253,
    NTASK_BLOCKED               = 254
};


typedef uint_fast8_t ntask_id;

/** @brief		Initialise a task instance
 *  @param      fn
 *  			Pointer to task function. See @ref ntask_fn.
 *  @param		arg
 *  			Task function argument.
 *  @param		prio
 *  			Priority of the task. Minimum priority is @ref NTASK_PRIO_MIN
 *  			and maximum priority @ref NTASK_PRIO_MAX.
 *
 *  @pre		Pointer @a fn != NULL.
 *  @pre		Priority @a prio range ``(NTASK_PRIO_MIN, NCONFIG_TASK_INSTANCES]``
 *
 *  Initialise the task with given attributes. 
 * 
 *  Before executing a task it needs to be initialised. The task structure is 
 *  allocated from internal task pool which size is defined by
 *  @ref NCONFIG_TASK_INSTANCES configuration macro. When a task is initialised 
 *  it is transitioned to state @ref NTASK_DORMANT. After initialisation the
 *  task can be started by @ref ntask_start function. 
 * 
 *  @note       This function can be called only during initialisation phase,
 *              before scheduler 
 *              Once a task is initialised it can't be de-initialised, it can
 *              be put only in dormant state by using @ref ntask_terminate
 *              function.
 */
void ntask_init(ntask_fn * fn, void * arg, uint_fast8_t prio);

/** @brief		Terminate the task instance.
 *  @param		task
 *  			Task structure.
 */
void ntask_terminate(ntask_id task);

/** @brief 		Start a task
 *  @param		task
 *  			Task structure.
 *
 *  When a task is started its state is changed to @ref NTASK_READY.
 */
void ntask_start(ntask_id task);

void ntask_stop(ntask_id task);

void ntask_schedule(void);

enum nerror_id ntask_current_error(void);

enum ntask_state ntask_state(ntask_id task);

void ntask_ready(ntask_id task_id);

void ntask_block(ntask_id task_id);

/** @} *//*==================================================================*/
/** @defgroup   nevent Event module
 *  @brief      Event module
 *  @{ *//*==================================================================*/

enum nevent_sys_id
{
    NEVENT_SUPER = 0u,
    NEVENT_ENTRY = 1u,
    NEVENT_EXIT = 2u,
    NEVENT_RESERVED_MAX = 15u
};

typedef uint_fast16_t nevent_id;

/** @} *//*==================================================================*/
/** @defgroup   nevent Event module
 *  @brief      Event module
 *  @{ *//*==================================================================*/

typedef uint_fast8_t nepa_id;

enum nepa_activity
{
    NEPA_HANDLED
};

typedef enum neap_activity (nepa_state)(void * ws, nevent_id event_id);

#define nepa_workspace(q_size) \
    { \
        struct evt_q nlqueue(nevent_id, (q_size)) evt_q; \
    }

#define NEPA_INIT(epa, init_state, prio) \
    NLQUEUE_INIT(&(epa)->evt_q); \
    np_epa_init(NLQUEUE_BASE(&(epa)->evt_q), (prio))

void np_epa_init(void * ws, nepa_state * init_state, uint_fast8_t prio);

/** @} */
#endif /* NEON_H_ */
