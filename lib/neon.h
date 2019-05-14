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
 *  @defgroup    neon Neon library
 *  @brief       Neon library interface
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

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/
/** @defgroup   nconfig Configuration module
 *  @brief      Configuration module
 *  @{ *//*==================================================================*/

/*
 * Use "neon_config.h" file to customize various modules  of the Neon
 * library. Each project should have its own configuration file.
 */
#if defined(NCONFIG_PROJECT_CONFIG)
#include "neon_config.h"
#endif

/** @brief      Configure if logger module is enabled.
 *
 *  This macro defines if Neon should be compiled with logger support. If this
 *  module is not enabled all API calls will be replaced by
 *  preprocessor to empty macros thus not consumimg RAM or const memory.
 *
 *  When this macro is set to '1' the module is enabled, when the macro is set
 *  to '0' the module is disabled. Using any other value is undefined
 *  behaviour.
 */
#if !defined(NCONFIG_ENABLE_LOGGER) || defined(__DOXYGEN__)
#define NCONFIG_ENABLE_LOGGER           1
#endif

/** @brief      Configure if debug module is enabled.
 *
 *  This macro defines if Neon should be compiled with debug support. If this
 *  module is not enabled all API calls will be replaced by
 *  preprocessor to empty macros thus not consumimg RAM or const memory.
 *  Debug component also uses logger component. If logger is not enabled
 *  then debug module will only stop the execution of the application in case
 *  of failed assertion.
 *
 *  When this macro is set to '1' the module is enabled, when the macro is set
 *  to '0' the module is disabled. Using any other value is undefined
 *  behaviour.
 */
#if !defined(NCONFIG_ENABLE_DEBUG) || defined(__DOXYGEN__)
#define NCONFIG_ENABLE_DEBUG            0
#endif

#if !defined(NCONFIG_LOGGER_BUFFER_SIZE) || defined(__DOXYGEN__)
#define NCONFIG_LOGGER_BUFFER_SIZE      1024
#endif
    
#if !defined(NCONFIG_LOGGER_LEVEL) || defined(__DOXYGEN__)
#define NCONFIG_LOGGER_LEVEL            3
#endif

#if !defined(NCONFIG_EPA_INSTANCES) || defined(__DOXYGEN__)
#define NCONFIG_EPA_INSTANCES           8
#endif
    
#if !defined(NCONFIG_EPA_USE_HSM) || defined(__DOXYGEN__)
#define NCONFIG_EPA_USE_HSM             0
#endif
    
#if !defined(NCONFIG_EPA_HSM_LEVELS) || defined(__DOXYGEN__)
#define NCONFIG_EPA_HSM_LEVELS          8
#endif

#if !defined(NCONFIG_SYS_EXITABLE_SCHEDULER) || defined(__DOXYGEN__)
#define NCONFIG_SYS_EXITABLE_SCHEDULER  0
#endif
    
#if !defined(NCONFIG_EVENT_USE_DYNAMIC) || defined(__DOXYGEN__)
#define NCONFIG_EVENT_USE_DYNAMIC       0
#endif
    
#define NCONFIG_ID                                                          \
      (((uint32_t)NCONFIG_ENABLE_LOGGER << 31)                              \
    | ((uint32_t)NCONFIG_ENABLE_DEBUG << 30)                                \
    | ((uint32_t)NCONFIG_EVENT_USE_DYNAMIC << 8)                            \
    | ((uint32_t)NCONFIG_EPA_USE_HSM << 1)                                  \
    | ((uint32_t)NCONFIG_EPA_INSTANCES << 0))

#define nconfig_validate()                                                  \
    do {                                                                    \
        extern NPLATFORM_UNUSED(const uint32_t nconfig_compiled_id);        \
        NASSERT(nconfig_compiled_id == NCONFIG_ID);                         \
    } while (0)

/** @} *//*==================================================================*/
/** @defgroup   nport_platform Port platform module
 *  @brief      Port platform module
 *  @{ *//*==================================================================*/

/** @defgroup   platformid Platform identification information
 *  @brief      Port compiler identification macros.
 *  @{ */
#if defined(__DOXYGEN__)
#define NPLATFORM_ID            "unknown"
#endif

/** @brief      Each port defines a macro named NPLATFORM_xxx.
 *
 *  For example, the GCC based compilers will define 'NPLATFORM_GCC'. ARM
 *  based compilers will define NPLATFORM_ARM.
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_xxx
#endif

/** @defgroup   platform_compiler Platform compiler macros
 *  @brief      Port compiler helper macros.
 *  @{ */

/** @brief      Compiler directive to inline a function.
 *  @note       This macro is usually defined in port.
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_INLINE        static inline
#endif

#if defined(__DOXYGEN__)
#define NPLATFORM_INLINE_ALWAYS NPLATFORM_INLINE
#endif

/** @brief      Cast a member of a structure out to the containing structure
 * @param       ptr
 *              the pointer to the member.
 * @param       type
 *              the type of the container struct this is embedded in.
 * @param       member
 *              the name of the member within the struct.
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_CONTAINER_OF(ptr, type, member)                      \
    ((type *)((char *)ptr - offsetof(type, member)))
#endif

/** @brief      Provides function name for assert macros
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_FUNC             "unknown"
#endif

/** @brief      Provides the free file's name which is being compiled
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_FILE             "unknown"
#endif

/** @brief      Provides the free source line
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_LINE             0
#endif

/** @brief      Omit function prologue/epilogue sequences
 *  @note       Using this macro when the compiler feature is not supported
 *              will generate compilation error.
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_NAKED(x)              __provoke_error__ x
#endif

#if defined(__DOXYGEN__)
#define NPLATFORM_UNUSED(y)             __provoke_error__ y
#endif

/** @brief      Declare a function that will never return
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_NORETURN(x)           x
#endif

#if defined(__DOXYGEN__)
#define NPLATFORM_PACKED(x)             __provoke_error__ x
#endif

/** @brief      This attribute specifies a minimum alignment (in bytes) for
 *              variables of the specified type.
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_ALIGN(align, x)       __provoke_error__ x
#endif

/** @brief      Prevent the compiler from merging or refetching accesses.
 * 
 *  The compiler is also forbidden from reordering successive instances of 
 *  NPLATFORM_ACCESS_ONCE(), but only when the compiler is aware of some 
 *  particular ordering.  One way to make the compiler aware of ordering is to
 *  put the two invocations of NPLATFORM_ACCESS_ONCE() in different C 
 *  statements.
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_ACCESS_ONCE(x)        (*(volatile typeof(x) *)&(x))
#endif

/** @brief      Returns current date.
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_DATE                  __DATE__
#endif

/** @brief      Returns current time.
 */
#if defined(__DOXYGEN__)
#define NPLATFORM_TIME                  __TIME__
#endif

#if (NPLATFORM_BROKEN_INLINE == 1)
#if defined(NEON_C_SOURCE)
#define NEON_INLINE_DECL(x)             x
#define NEON_INLINE_DEF(x)              x
#else
#define NEON_INLINE_DECL(x)             x;
#define NEON_INLINE_DEF(x)
#endif
#else
#define NEON_INLINE_DECL(x)             NPLATFORM_INLINE x
#define NEON_INLINE_DEF(x)              x
#endif

/** @} */
/** @} *//*==================================================================*/
/** @defgroup   nport_arch Port architecture module
 *  @brief      Port architecture module
 *  @{ *//*==================================================================*/

/** @defgroup   archid Architecture identification information
 *  @brief      Port identification macros.
 *  @{ */

/** @brief      Name of the architecture (as string)
 */
#if defined(__DOXYGEN__)
#define NARCH_ID                "unknown"
#endif

/** @brief      This macro is defined to 1 if current architecture has exclusive
 *              load/store access.
 */
#if defined(__DOXYGEN__)
#define NARCH_HAS_ATOMICS
#endif
    
/** @brief      Each port defines a macro named NARCH_xxx.
 *
 *  For example, the ARM based architectures will define 'NARCH_ARM'. In
 *  addition to this macro it will probably define macros like 'NARCH_ARM_V7M'
 *  which identifies a subset of architecture information.
 */
#if defined(__DOXYGEN__)
#define NARCH_xxx
#endif

/** @brief      Number of bits of the used architecture
 *  @api
 */
#if defined(__DOXYGEN__)
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
#if defined(__DOXYGEN__)
#define narch_cpu_stop()
#endif

/** @brief      Set a bit in unsigned 32-bit integer variable
 *  @param      u32
 *              Pointer to unsigned 32-bit integer.
 *  @param      bit
 *              Argument specifying which bit to set.
 *  @note       Do not use bit >= 32 since it will result in undefined
 *              behaviour.
 */
void narch_atomic_set_bit(uint32_t * u32, uint_fast8_t bit);

/** @brief      Clear a bit in unsigned integer 32-bit variable
 *  @param      u32
 *              Pointer to unsigned 32-bit integer.
 *  @param      bit
 *              Argument specifying which bit to clear.
 *  @note       Do not use bit >= 32 since it will result in undefined
 *              behaviour.
 */
void narch_atomic_clear_bit(uint32_t * u32, uint_fast8_t bit);

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

/** @brief      Initialize board
 */
void nboard_init(void);

/** @} *//*==================================================================*/
/** @defgroup   nport_os Port OS module
 *  @brief      Port OS module
 *  @{ *//*==================================================================*/

#if defined(__DOXYGEN__)
#define NOS_MUTEX_DECL(mutex_name)
#endif

#if defined(__DOXYGEN__)
#define NOS_MUTEX_INIT(mutex)
#endif

#if defined(__DOXYGEN__)
#define NOS_MUTEX_LOCK(mutex)
#endif

#if defined(__DOXYGEN__)
#define NOS_MUTEX_UNLOCK(mutex)
#endif

/** @} *//*==================================================================*/
/** @defgroup   nport_critical Port critical module
 *  @brief      Port critical module
 *  @{ *//*==================================================================*/

#if defined(__DOXYGEN__)
#define NCRITICAL_DECL(name)
#endif

#if defined(__DOXYGEN__)
#define NCRITICAL_STATE_DECL(name)
#endif

#if defined(__DOXYGEN__)
#define NCRITICAL_INIT(instance)
#endif

#if defined(__DOXYGEN__)
#define NCRITICAL_LOCK(local_state, instance)
#endif

#if defined(__DOXYGEN__)
#define NCRITICAL_UNLOCK(local_state, instance)
#endif

/** @} *//*==================================================================*/
/** @defgroup   ndebug Debug module
 *  @brief      Debug module
 *  @{ *//*==================================================================*/

/** @defgroup   debug_moduleconfig Debug module configuration
 *  @brief      These features are enabled/disabled using the option
 *              @ref NCONFIG_ENABLE_NDEBUG.
 *  @{
 */
#if (NCONFIG_ENABLE_DEBUG == 1)
#define NDEBUG_IS_ENABLED               1
static const char g_debug_filename[] = NPLATFORM_FILE;
#else
/** @brief      Macro that returns current ndebug configuration
 */
#define NDEBUG_IS_ENABLED               0
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
 */
#if (NDEBUG_IS_ENABLED == 1)
#define NASSERT(expr)                                                        \
    if (!(expr)) {                                                           \
        NASSERT_ALWAYS(# expr);                                              \
    }
#else
#define NASSERT(expr)                   (void)0
#endif

/** @brief      Assert macro that will always execute (no conditional).
 *  @param      msg
 *              Message : a standard error message, see
 *              @ref Standard error messages.
 *  @param      text
 *              Text : string : a text which will be printed when this assert
 *              macro is executed.
 */
#if (NDEBUG_IS_ENABLED == 1)
#define NASSERT_ALWAYS(text)                                                \
        nassert(text, NPLATFORM_FILE, NPLATFORM_FUNC, NPLATFORM_LINE)
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
 */
#if (NDEBUG_IS_ENABLED == 1)
#define NOBLIGATION(expr)               expr
#else
#define NOBLIGATION(expr)               (void)0
#endif

/** @brief      Make sure the caller has fulfilled all contract preconditions
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 */
#define NREQUIRE(expr)                  NASSERT(expr)

/** @brief      Make sure the callee has fulfilled all contract postconditions
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 */
#define NENSURE(expr)                   NASSERT(expr)

/**@} */
/** @defgroup    debug_internal Internal checking
 *  @brief      These macros are enabled/disabled using the option
 *              @ref NCONFIG_ENABLE_NDEBUG.
 *  @{ */

/** @brief      Assert macro used for internal execution checking
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 */
#define NASSERT_INTERNAL(expr)          NASSERT(expr)

/** @} */
/** @defgroup   Object debug signatures
 *  @brief      During debugging the objects will use the signatures.
 *  @{ */

#define NSIGNATURE_HEAP                 ((unsigned int)0xdeadbee0u)
#define NSIGNATURE_POOL                 ((unsigned int)0xdeadbee1u)
#define NSIGNATURE_STATIC               ((unsigned int)0xdeadbee2u)
#define NSIGNATURE_STDHEAP              ((unsigned int)0xdeadbee3u)
#define NSIGNATURE_TIMER                ((unsigned int)0xdeadcee0u)
#define NSIGNATURE_EPA                  ((unsigned int)0xdeaddee0u)
#define NSIGNATURE_EQUEUE               ((unsigned int)0xdeadfeebu)
#define NSIGNATURE_ETIMER               ((unsigned int)0xdeadfeecu)
#define NSIGNATURE_EVENT                ((unsigned int)0xdeadfeedu)
#define NSIGNATURE_SM                   ((unsigned int)0xdeadfeeeu)
#define NSIGNATURE_DEFER                ((unsigned int)0xdeadfeefu)

#if (NDEBUG_IS_ENABLED == 1) || defined(__DOXYGEN__)
#define NSIGNATURE_DECLARE              unsigned int _signature;

#define NSIGNATURE_INITIALIZER(signature)                                   \
        ._signature = signature,

#else
#define NSIGNATURE_DECLARE
#define NSIGNATURE_INITIALIZER(signature)
#endif

#define NSIGNATURE_OF(object)                                               \
        ((object) ? (object)->_signature : 0)

#define NSIGNATURE_IS(object, signature)                                    \
        (object)->_signature = (signature)

/** @defgroup   Static assert
 *  @brief      Static assert (compile time check)
 *  @{ */

#define ASSERT_CONCAT_(a, b)            a##b
#define ASSERT_CONCAT(a, b)             ASSERT_CONCAT_(a, b)

/* This can't be used twice on the same line so ensure if using in headers
 * that the headers are not included twice (by wrapping in #ifndef...#endif)
 * Note it doesn't cause an issue when used on same line of separate modules
 * compiled with gcc -combine -fwhole-program.  */
#define STATIC_ASSERT(e, m)                                                 \
        enum m { ASSERT_CONCAT(m, ASSERT_CONCAT(_assert_line_, __LINE__)) = 1/(!!(e)) }

NPLATFORM_NORETURN(void nassert(
        const char * text, 
        const char * file, 
        const char * func, 
        uint32_t line));

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

/** @brief      Right aligned bit mask lookup table
 *  @notapi
 */
extern const uint32_t g_np_bits_right_mask[33];

/** @brief      Left aligned bit mask lookup table
 *  @notapi
 */
extern const uint32_t g_np_bits_left_mask[33];

/** @brief      Determining if an integer is a power of 2
 *  @note       For more details please refer to the following URL:
 *              https://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
 */
#define NBITS_IS_POWEROF2(num)                                              \
    (((num) != 0u) && (((num) & ((num) - 1)) == 0u))

/** @brief      Create a bit mask of width @a v bits.
 *  @note       If the value of argument @a v is greater than 32 then the
 *              behaviour undefined.
 */
#define nbits_to_right_mask(v)          g_np_bits_right_mask[v]

/** @brief      Create a bit mask of width @a v bits.
 *  @note       If the value of argument @a v is greater than 32 then the
 *              behaviour undefined.
 */
#define nbits_to_left_mask(v)           g_np_bits_left_mask[v]

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

/** @brief      Sign extend signed 24 bit integer to signed 32 bits integer
 * @param       val - signed 24 bit integer
 * @return
 */
#define n_ext_i24(value)                ncpu_ext_i24(value)

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

/** @brief      Defines what is the maximum number of bits in bitaarray_s
 *  @hideinitializer
 */
#define NBITARRAY_S_MAX_SIZE            NARCH_DATA_WIDTH

/** @brief      Bitarray s type
 */
typedef narch_uint nbitarray_s;

/** @brief      Set a bit in the array.
 *  @hideinitializer
 */
#define nbitarray_s_set(a_array, a_bit)                                     \
        do {                                                                \
            *(a_array) |= narch_exp2(a_bit);                                \
        } while (0)

/** @brief      Clear a bit in the array.
 *  @hideinitializer
 */
#define nbitarray_s_clear(a_array, a_bit)                                   \
        do {                                                                \
            *(a_array) &= ~narch_exp2(a_bit);                               \
        } while (0)

/** @brief      Get the first set bit in the array .
 */
#define nbitarray_s_msbs(a_array)       narch_log2(*(a_array))

/** @brief      Returns true if no bit is set in whole array.
 *  @hideinitializer
 */
#define nbitarray_s_is_empty(a_array)   (*(a_array) == 0)

/** @brief      Evaluates if a specified bit is set in the array.
 */
#define nbitarray_s_is_set(a_array, a_bit)                                  \
        (*(a_array) & narch_exp2(a_bit))

#if (NARCH_HAS_ATOMIC_SET_CLEAR_BIT == 1) || defined(__DOXYGEN__)

/** @brief      When this macro is set 1 then atomic access calls are available.
 *  @hideinitializer
 */
#define NEON_HAS_BITARRAY_S_ATOMICS     1

/** @brief      Atomically set a bit in the array.
 */
#define nbitarray_s_set_atomic(a_array, a_bit)                              \
        narch_atomic_set_bit((a_array), (a_bit))

/** @brief      Atomically clear a bit in the array.
 */
#define nbitarray_s_clear_atomic(a_array, a_bit)                            \
        narch_atomic_clear_bit((a_array), (a_bit))

#endif /* (NARCH_HAS_ATOMIC_SET_CLEAR_BIT == 1) */

/** @} */
/** @defgroup   bits_bitarray_x Extended bit array
 *  @brief      Functions for manipulating bit arrays with bit length more than
 *              NARCH_DATA_WIDTH bits.
 *  @{ */

/** @brief      Bitarray x type
 */
typedef narch_uint nbitarray_x;

/** @brief      Define an array of size bits.
 *  @hideinitializer
 */
#define NBITARRAY_X_DEF(bits)                                               \
        NBITS_DIVIDE_ROUNDUP((bits), NARCH_DATA_WIDTH) + 1

/** @brief      Specifies the maximum number of bits in @a nbitarray_x array.
 *  @hideinitializer
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
 *  @hideinitializer
 */
#define nbitarray_x_is_empty(a_array)   ((a_array)[0] == 0u)

/** @brief      Evaluates if a specified bit is set in the array.
 */
bool nbitarray_x_is_set(const nbitarray_x * array, uint_fast8_t bit);

#if (NARCH_HAS_ATOMICS == 1) || defined(__DOXYGEN__)

/** @brief      When this macro is set 1 then atomic access calls are available.
 *  @hideinitializer
 */
#define NEON_HAS_BITARRAY_X_ATOMICS     1

/** @brief      Atomically set a bit in the array.
 */
void nbitarray_x_set_atomic(nbitarray_x * array, uint_fast8_t bit);

/** @brief      Atomically clear a bit in the array.
 */
void nbitarray_x_clear_atomic(nbitarray_x * array, uint_fast8_t bit);
#else
#define NEON_HAS_BITARRAY_X_ATOMICS     0
#endif /* (NARCH_HAS_EXCLUSIVE_LS == 1) */ 

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
    EOK,
    EOBJ_INVALID,                           /**< Invalid object error.        */
    EOBJ_INITIALIZED,
    EARG_OUTOFRANGE,                        /**< Argument is out of range.    */
};

typedef enum nerror_id nerror;

/** @} */
/** @} *//*==================================================================*/
/** @defgroup   nlist_sll Singly linked list module
 *  @brief      Singly linked list module
 *  @{ *//*==================================================================*/

/** @brief      Macro to get the pointer to structure which contains any struct
 *              of a list.
 *  @param[in]  ptr
 *              Pointer to structure/data that is containing a list structure.
 *  @param[in]  type
 *              Type of variable which contains a list structure.
 *  @param[in]  member
 *              Name of member in variable structure.
 *  @return     Pointer to container structure.
 *
 *  @code
 *  struct my_struct
 *  {
 *      char my_name[8];
 *      struct nlist_sll some_list;
 *      int some_stuff;
 *  };
 *
 *  struct nlist_sll * current_element;
 *  struct my_struct * current;
 *
 *  current = NLIST_SLL_ENTRY(current_element, struct my_struct, some_list);
 *  @endcode
 */
#define nlist_sll_entry(ptr, type, member)                                  \
        NPLATFORM_CONTAINER_OF(ptr, type, member)

#define nlist_sll_is_null(list)         ((list)->next == NULL)

/** @brief      Macro to get the first element in list pointed by @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_sll_first(sentinel)       nlist_sll_next(sentinel)

/** @brief      Helper macro, get the last element in list pointed by
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_sll_last(sentinel)        nlist_sll_prev(sentinel)

/** @brief      Helper macro, add a node @a node at list head pointed by
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_sll_add_head(sentinel, node)                                  \
        nlist_sll_add_before(sentinel, node)

/** @brief      Helper macro, add a node @a node at list tail pointed by
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_sll_add_tail(sentinel, node)                                  \
        nlist_sll_add_after(sentinel, node)

/** @brief      Construct for @a FOR loop to iterate over each element in a
 *              list.
 *
 *  @code
 *  struct nlist_sll * current;
 *  struct nlist_sll * sentinel = &g_list_sentinel.list;
 *
 *  for (NLIST_SLL_EACH(current, sentinel)) {
 *      ... do something with @a current (excluding remove)
 *  }
 *  @endcode
 *  @mseffect
 */
#define NLIST_SLL_EACH(current, sentinel)                                   \
    current = nlist_sll_first(sentinel); current != (sentinel);             \
    current = nlist_sll_next(current)

/** @brief      Construct for @a FOR loop to iterate over each element in list
 *              backwards.
 *
 *  @code
 *  struct nlist_sll * current;
 *  struct nlist_sll * sentinel = &g_list_sentinel.list;
 *
 *  for (NLIST_SLL_EACH_BACKWARDS(current, sentinel)) {
 *      ... do something with current (excluding remove)
 *  }
 *  @endcode
 *  @mseffect
 */
#define NLIST_SLL_EACH_BACKWARDS(current, sentinel)                         \
    current = nlist_sll_last(sentinel); current != (sentinel);              \
    current = nlist_sll_prev(current)

/** @brief      Construct for FOR loop to iterate over each element in list
 *              which is safe against element removal.
 *
 *  @code
 *  struct nlist_sll * current;
 *  struct nlist_sll * iterator;
 *  struct nlist_sll * sentinel = &g_list_sentinel.list;
 *
 *  for (NLIST_SLL_EACH_SAFE(current, iterator, sentinel)) {
 *      ... do something with current (including remove)
 *  }
 *  @endcode
 *  @mseffect
 */
#define NLIST_SLL_EACH_SAFE(current, iterator, sentinel)                    \
    current = nlist_sll_first(sentinel), iterator = nlist_sll_next(current);\
    current != (sentinel);                                                  \
    current = iterator, iterator = nlist_sll_next(iterator)

/** @brief      Singly Linked List (SLL) structure.
 */
struct nlist_sll
{
    struct nlist_sll *          next;       /**< Next node in the list.       */
};

/** @brief      Initialize a list sentinel or node.
 *  @param[in]  node
 *              A list sentinel or node.
 *
 *  Before calling this function:
 @verbatim
    +-----+
    |     |--> next
    |  N  |
    |     |
    +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
 +-----------+
 |  +-----+  |
 +->|     |--+
    |  N  |
    |     |
    +-----+
 @endverbatim
 */
NEON_INLINE_DECL(
struct nlist_sll * nlist_sll_init(struct nlist_sll * node))
NEON_INLINE_DEF(
{
    node->next = node;

    return node;
})

/** @brief      Return the next node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Next node.
 */
NEON_INLINE_DECL(
struct nlist_sll * nlist_sll_next(struct nlist_sll * node))
NEON_INLINE_DEF(
{
    return node->next;
})

/** @brief      Return previous node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Previous node.
 */
NEON_INLINE_DECL(
struct nlist_sll * nlist_sll_prev(struct nlist_sll * const node))
NEON_INLINE_DEF(
{
    struct nlist_sll * tmp = node;

    while (tmp->next != node) {
        tmp = tmp->next;
    }
    return tmp;
})

/** @brief      Insert node (N) after current node (C).
 *  @param[in]  current
 *              A list node or sentinel.
 *  @param[in]  node
 *              A list node.
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+             +-----+
        |     |--->|     |--->|     |-->next      |     |
        |  1  |    |  C  |    |  2  |             |  N  |
        |     |    |     |    |     |             |     |
        +-----+    +-----+    +-----+             +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |--->|     |-->next
        |  1  |    |  N  |    |  C  |    |  2  |
        |     |    |     |    |     |    |     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 */
NEON_INLINE_DECL(
void nlist_sll_add_after(struct nlist_sll * current, struct nlist_sll * node))
NEON_INLINE_DEF(
{
    struct nlist_sll * prev = nlist_sll_prev(current);

    node->next = prev->next;
    prev->next = node;
})

/** @brief      Insert node (N) before current node (C).
 *  @param[in]  current
 *              A list node or sentinel.
 *  @param[in]  node
 *              A list node.
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+             +-----+
        |     |--->|     |--->|     |-->next      |     |
        |  1  |    |  C  |    |  2  |             |  N  |
        |     |    |     |    |     |             |     |
        +-----+    +-----+    +-----+             +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |--->|     |-->next
        |  1  |    |  C  |    |  N  |    |  2  |
        |     |    |     |    |     |    |     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 */
NEON_INLINE_DECL(
struct nlist_sll * nlist_sll_add_before(
        struct nlist_sll * current,
        struct nlist_sll * node))
NEON_INLINE_DEF(
{
    node->next = current->next;
    current->next = node;

    return (node);
})

/** @brief      Remove a node (N) which is next from current (C) node
 *  @param[in]  node
 *              A list node.
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |--->|     |-->next
        |  1  |    |  C  |    |  N  |    |  2  |
        |     |    |     |    |     |    |     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
                                                +-----------+
        +-----+    +-----+    +-----+           |  +-----+  |
        |     |--->|     |--->|     |-->next    +->|     |--+
        |  1  |    |  C  |    |  2  |              |  N  |
        |     |    |     |    |     |              |     |
        +-----+    +-----+    +-----+              +-----+
 @endverbatim
 */
NEON_INLINE_DECL(
struct nlist_sll * nlist_sll_remove_from(struct nlist_sll * current))
NEON_INLINE_DEF(
{
    struct nlist_sll * node;
    
    node = current->next;
    current->next = node->next;
    
    return nlist_sll_init(node);
})

/** @brief      Remove a node (N)
 *  @param[in]  node
 *              A list node.
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+
        |     |--->|     |--->|     |-->next
        |  1  |    |  N  |    |  2  |
        |     |    |     |    |     |
        +-----+    +-----+    +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
                                     +-----------+
        +-----+    +-----+           |  +-----+  |
        |     |--->|     |-->next    +->|     |--+
        |  1  |    |  2  |              |  N  |
        |     |    |     |              |     |
        +-----+    +-----+              +-----+
 @endverbatim
 */
NEON_INLINE_DECL(
void nlist_sll_remove(struct nlist_sll * node))
NEON_INLINE_DEF(
{
    struct nlist_sll * prev = nlist_sll_prev(node);

    nlist_sll_remove_from(prev);
})

/** @brief      Check if a list @a node is empty or not.
 *  @param[in]  node
 *              A list sentinel.
 *  @return     List state:
 *  @retval     true - The list is empty.
 *  @retval     false - The list contains at least one node.
 */
NEON_INLINE_DECL(
bool nlist_sll_is_empty(const struct nlist_sll * node))
NEON_INLINE_DEF(
{
    return !!(node->next == node);
})

/** @} *//*==================================================================*/
/** @defgroup   nlist_dll Doubly linked list module
 *  @brief      Doubly linked list module
 *  @{ *//*==================================================================*/

/** @brief      Macro to get the pointer to structure which contains any struct
 *              of a list.
 *  @param[in]  ptr
 *              Pointer to structure/data that is containing a list structure.
 *  @param[in]  type
 *              Type of variable which contains a list structure.
 *  @param[in]  member
 *              Name of member in variable structure.
 *  @return     Pointer to container structure.
 *
 *  @code
 *  struct my_struct
 *  {
 *      char my_name[8];
 *      struct nlist_dll some_list;
 *      int some_stuff;
 *  };
 *
 *  struct nlist_dll * current_element;
 *  struct my_struct * current;
 *
 *  current = NLIST_DLL_ENTRY(current_element, struct my_struct, some_list);
 *  @endcode
 *  @mseffect
 */
#define nlist_dll_entry(ptr, type, member)                                  \
    nlist_sll_entry(ptr, type, member)

#define nlist_dll_is_null(list)         ((list)->next == NULL)

/** @brief      Macro to get the first element in list pointed by @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_dll_first(sentinel)       nlist_dll_next(sentinel)

/** @brief      Helper macro, get the last element in list pointed by
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_dll_last(sentinel)        nlist_dll_prev(sentinel)

/** @brief      Helper macro, add a node @a node at list head pointed by
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_dll_add_head(sentinel, node)                                  \
        nlist_dll_add_before(sentinel, node)

/** @brief      Helper macro, add a node @a node at list tail pointed by
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_dll_add_tail(sentinel, node)                                  \
        nlist_dll_add_after(sentinel, node)

/** @brief      Construct for @a FOR loop to iterate over each element in a
 *              list.
 *
 *  @code
 *  struct nlist_dll * current;
 *  struct nlist_dll * sentinel = &g_list_sentinel.list;
 *
 *  for (nlist_dll_EACH(current, sentinel)) {
 *      ... do something with @a current (excluding remove)
 *  }
 *  @endcode
 *  @mseffect
 */
#define NLIST_DLL_EACH(current, sentinel)                                   \
        current = nlist_dll_first(sentinel);                                \
        current != (sentinel);                                              \
        current = nlist_dll_next(current)

/** @brief      Construct for FOR loop to iterate over each element in list
 *              backwards.
 *
 *  @code
 *  struct nlist_dll * current;
 *  struct nlist_dll * sentinel = &g_list_sentinel.list;
 *
 *  for (nlist_dll_EACH_BACKWARDS(current, sentinel)) {
 *      ... do something with current (excluding remove)
 *  }
 *  @endcode
 *  @mseffect
 */
#define NLIST_DLL_EACH_BACKWARDS(current, sentinel)                         \
        current = nlist_dll_last(sentinel);                                 \
        current != (sentinel);                                              \
        current = nlist_dll_prev(current)

/** @brief      Construct for FOR loop to iterate over each element in list
 *              which is safe against element removal.
 *
 *  @code
 *  struct nlist_dll * current;
 *  struct nlist_dll * iterator;
 *  struct nlist_dll * sentinel = &g_list_sentinel.list;
 *
 *  for (nlist_dll_EACH_SAFE(current, iterator, sentinel)) {
 *      ... do something with current (including remove)
 *  }
 *  @endcode
 *  @mseffect
 */
#define NLIST_DLL_EACH_SAFE(current, iterator, sentinel)                    \
    current = nlist_dll_first(sentinel), iterator = nlist_dll_next(current);\
    current != (sentinel);                                                  \
    current = iterator, iterator = nlist_dll_next(iterator)

/** @brief      Doubly-linked list structure
 */
struct nlist_dll
{
    struct nlist_dll *          next;       /**< Next node in the list.*/
    struct nlist_dll *          prev;       /**< Previous node in the list.*/
};

/** @brief      Initialize a list sentinel or node.
 *  @param[in]  node
 *              A list sentinel or node.
 *
 *  Before calling this function:
 @verbatim
         +-----+
         |     |--> next
         |  N  |
 prev <--|     |
         +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
      +-----------+
      |  +-----+  |
      +->|     |--+
         |  N  |
      +--|     |<-+
      |  +-----+  |
      +-----------+
 @endverbatim
 */
NEON_INLINE_DECL(
struct nlist_dll * nlist_dll_init(struct nlist_dll * node))
NEON_INLINE_DEF(
{
    node->next = node;
    node->prev = node;

    return node;
})

/** @brief      Terminate a list sentinel or node.
 *  @param[in]  node
 *              A list sentinel or node.
 *
 *  Before calling this function:
 @verbatim
         +-----+
         |     |--> next
         |  N  |
 prev <--|     |
         +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
         +-----+   
         |     |--+
         |  N  |  |
         |     | ---
         +-----+
 @endverbatim
 */
NEON_INLINE_DECL(
void nlist_dll_term(struct nlist_dll * node))
NEON_INLINE_DEF(
{
    node->next = NULL;
})

/** @brief      Return the next node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Next node.
 */
NEON_INLINE_DECL(
struct nlist_dll * nlist_dll_next(struct nlist_dll * node))
NEON_INLINE_DEF(
{
    return node->next;
})

/** @brief      Return previous node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Previous node.
 */
NEON_INLINE_DECL(
struct nlist_dll * nlist_dll_prev(struct nlist_dll * node))
NEON_INLINE_DEF(
{
    return node->prev;
})

/** @brief      Insert node (N) before current node (C).
 *  @param[in]  current
 *              A list node or sentinel.
 *  @param[in]  node
 *              A list node.
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+             +-----+
        |     |--->|     |--->|     |-->next      |     |
        |  1  |    |  C  |    |  2  |             |  N  |
 prev<--|     |<---|     |<---|     |             |     |
        +-----+    +-----+    +-----+             +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |--->|     |-->next
        |  1  |    |  N  |    |  C  |    |  2  |
 prev<--|     |<---|     |<---|     |<---|     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 */
NEON_INLINE_DECL(
struct nlist_dll * nlist_dll_add_after(
        struct nlist_dll * current,
        struct nlist_dll * node))
NEON_INLINE_DEF(
{
    node->next          = current;
    node->prev          = current->prev;
    current->prev->next = node;
    current->prev       = node;

    return node;
})

/** @brief      Insert node (N) after current node (C).
 *  @param[in]  current
 *              A list node or sentinel.
 *  @param[in]  node
 *              A list node.
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+             +-----+
        |     |--->|     |--->|     |-->next      |     |
        |  1  |    |  C  |    |  2  |             |  N  |
 prev<--|     |<---|     |<---|     |             |     |
        +-----+    +-----+    +-----+             +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |--->|     |-->next
        |  1  |    |  C  |    |  N  |    |  2  |
 prev<--|     |<---|     |<---|     |<---|     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 */
NEON_INLINE_DECL(
struct nlist_dll * nlist_dll_add_before(
        struct nlist_dll * current,
        struct nlist_dll * node))
NEON_INLINE_DEF(
{
    node->prev          = current;
    node->next          = current->next;
    current->next->prev = node;
    current->next       = node;

    return node;
})

/** @brief      Remove a node (N)
 *  @param[in]  node
 *              A list node.
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+
        |     |--->|     |--->|     |-->next
        |  1  |    |  N  |    |  2  |
 prev<--|     |<---|     |<---|     |
        +-----+    +-----+    +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
                                     +-----------+
        +-----+    +-----+           |  +-----+  |
        |     |--->|     |-->next    +->|     |--+
        |  1  |    |  2  |              |  N  |
 prev<--|     |<---|     |           +--|     |
        +-----+    +-----+           |  +-----+
                                    ---
 @endverbatim
 */
NEON_INLINE_DECL(
void nlist_dll_remove(struct nlist_dll * node))
NEON_INLINE_DEF(
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
})

/** @brief      Check if a list @a node is empty or not.
 *  @param[in]  node
 *              A list sentinel.
 *  @return     List state:
 *  @retval     true - The list is empty.
 *  @retval     false - The list contains at least one node.
 *  @mseffect
 */
#define NLIST_DLL_IS_EMPTY(a_node)      ((a_node)->next == (a_node))

/** @} *//*==================================================================*/
/** @defgroup   nqueue_lqueue Lightweight queue module
 *  @brief      Lightweight queue module
 *  @{ *//*==================================================================*/

/** @brief      Lightweight queue custom structure.
 *
 *  Contains the Base structure and buffer of type @a T with @a elements
 *  number of elements in that buffer. The buffer contains only pointers
 *  to items, not the actual items. This macro should be used to define a
 *  custom @a nlqueue structure.
 *
 *  @param      T
 *              Type of items in this queue.
 *  
 *  @code
 *  struct event_queue nlqueue(void *, 16);
 *  @endcode
 *
 *  @note       The macro can accept the parameter @a elements which is
 *              greater than 2 and equal to a number which is power of 2.
 *  @api
 */
#define nlqueue_dynamic(T)                                                  \
    {                                                                       \
        struct nlqueue super;                                               \
        T * np_lq_storage;                                                  \
    }

#define nlqueue_dynamic_storage(T, size)                                    \
    {                                                                       \
        T np_lq_storage[(((size < 2) || !NBITS_IS_POWEROF2(size)) ?         \
            -1 : size)];                                                    \
    }
        
#define nlqueue(T, size)                                                    \
    {                                                                       \
        struct nlqueue super;                                               \
        T np_lq_storage[(((size < 2) || !NBITS_IS_POWEROF2(size)) ?         \
            -1 : size)];                                                    \
    }
        

/** @brief      Lightweight base structure.
 *  @notapi
 */
struct NPLATFORM_ALIGN(NARCH_ALIGN, nlqueue)
{
    uint_fast8_t                head;
    uint_fast8_t                tail;
    uint_fast8_t                empty;
    uint_fast8_t                mask;
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
#define NLQUEUE_INIT_DYNAMIC(Q, a_size_bytes, a_storage)                    \
        do {                                                                \
            np_lqueue_super_init(                                           \
                    &(Q)->super,                                            \
                    (a_size_bytes) / sizeof(*(Q)->np_lq_storage));          \
            (Q)->np_lq_storage = (a_storage);                               \
        } while (0)

/** @brief      Initialize a static queue structure
 *  @param      Q
 *              Pointer to statically allocated lightweight queue.
 *  @mseffect
 */
#define NLQUEUE_INIT(Q)                                                     \
        np_lqueue_super_init(                                               \
                &(Q)->super,                                                \
                NBITS_ARRAY_SIZE((Q)->np_lq_storage))

/** @brief      Put an item to queue in FIFO mode.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @mseffect
 */
#define NLQUEUE_IDX_FIFO(Q)             nlqueue_super_idx_fifo(&(Q)->super)

/** @brief      Put an item to queue in LIFO mode.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @note       Before calling this function ensure that queue is not full, see
 *              @ref nqueue_is_full.
 *  @mseffect
 */
#define NLQUEUE_IDX_LIFO(Q)             nlqueue_super_idx_lifo(&(Q)->super)

/** @brief      Get an item from the queue buffer.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @note       Before calling this function ensure that queue has an item. See
 *              @ref nqueue_is_empty.
 *  @mseffect
 */
#define NLQUEUE_IDX_GET(Q)              nlqueue_super_idx_get(&(Q)->super)

/** @brief      Reference an object from queue storage.
 *  @param      Q
 *              Ponter to lightweight queue.
 *  @param      a_index
 *              Index of an object in the queue storage.
 *  @return     A object with given index in queue storage.
 */
#define NLQUEUE_IDX_REFERENCE(Q, a_index)                                   \
        (Q)->np_lq_storage[(a_index)]

/** @brief      Put an item to queue in FIFO mode.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @note       Before calling this function ensure that queue is not full, see
 *              @ref nqueue_is_full.
 *  @mseffect
 */
#define NLQUEUE_PUT_FIFO(Q, a_item)                                         \
        do {                                                                \
            (Q)->np_lq_storage[NLQUEUE_IDX_FIFO(Q)] = (a_item);             \
        } while (0)

/** @brief      Put an item to queue in LIFO mode.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @note       Before calling this function ensure that queue is not full, see
 *              @ref nqueue_is_full.
 *  @mseffect
 */
#define NLQUEUE_PUT_LIFO(Q, a_item)                                         \
        do {                                                                \
            (Q)->np_lq_storage[NLQUEUE_IDX_LIFO(Q)] = (a_item);             \
        } while (0)

/** @brief      Get an item from the queue buffer.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @note       Before calling this function ensure that queue has an item. See
 *              @ref nqueue_is_empty.
 *  @mseffect
 */
#define NLQUEUE_GET(Q)                                                      \
        (Q)->np_lq_storage[nlqueue_super_idx_get(&(Q)->super)]

/** @brief      Peek to queue head; the item is not removed from queue.
 *
 *  Get the pointer to head item in the queue. The item is not removed from
 *  queue buffer.
 * 
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @mseffect
 */
#define NLQUEUE_HEAD(Q)                                                     \
        (Q)->np_lq_storage[np_lqueue_super_head(&(Q)->super)]

/** @brief      Peek to queue tail; the item is not removed from queue.
 *
 *  Get the pointer to tail item in the queue. The item is not removed from
 *  queue buffer.
 *
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @mseffect
 */
#define NLQUEUE_TAIL(Q)                                                     \
        (Q)->np_lq_storage[np_lqueue_super_tail(&(Q)->super)]

/** @brief      Returns the queue buffer size in number of elements.
 *  @param      Q
 *              Pointer to lightweight queue.
 */
#define NLQUEUE_SIZE(Q)                 (Q)->super.mask + 1u

/** @brief      Returns the current number of free elements in queue buffer.
 *  @param      Q
 *              Pointer to lightweight queue.
 */
#define NLQUEUE_EMPTY(Q)                (Q)->super.empty

/** @brief      Return true if queue is full else false.
 *  @param      Q
 *              Pointer to lightweight queue.
 */
#define NLQUEUE_IS_FULL(Q)              (!NLQUEUE_EMPTY(Q))

/** @brief      Return true if queue is empty else false.
 *  @param      Q
 *              Pointer to lightweight queue.
 */
#define NLQUEUE_IS_EMPTY(Q)             (NLQUEUE_EMPTY(Q) == NLQUEUE_SIZE(Q))

/** @brief      Return true if queue has only single element.
 *  @param      Q
 *              Pointer to lightweight queue.
 */
#define NLQUEUE_IS_FIRST(Q)                                                 \
        ((Q)->super.empty == (Q)->super.mask)

/** @brief      Initialise the base queue structure.
 *  @param      lqs
 *              Pointer to lightweight queue super.
 *  @param      elements
 *  @notapi
 */
void np_lqueue_super_init(struct nlqueue * lqs, uint8_t elements);

/** @brief      Put an item to queue in FIFO mode.
 *  @param      qb
 *              Pointer to lightweight queue base.
 *  @return     Index of the item where it should be put.
 *  @notapi
 */
NEON_INLINE_DECL(int_fast8_t nlqueue_super_idx_fifo(struct nlqueue * qb))
NEON_INLINE_DEF(
{
    int_fast8_t retval;
    
    if (qb->empty != 0u) {
        qb->empty--;
        retval = qb->tail++;
        qb->tail &= qb->mask;
    } else {
        retval = -1;
    }
    return retval;
})

/** @brief      Put an item to queue in LIFO mode.
 *  @param      qb
 *              Pointer to lightweight queue base.
 *  @return     Index of the item where it should be put.
 *  @notapi
 */
NEON_INLINE_DECL(int32_t nlqueue_super_idx_lifo(struct nlqueue * qb))
NEON_INLINE_DEF(
{
    int32_t retval;
    
    if (qb->empty != 0u) {
        qb->empty--;
        retval = qb->head--;
        qb->head &= qb->mask;
    } else {
        retval = -1;
    }
    return retval;
})

/** @brief      Get an item from the queue buffer.
 *  @param      qb
 *              Pointer to lightweight queue base.
 *  @return     Index of the item which was got from the queue.
 *  @notapi
 */
NEON_INLINE_DECL(int_fast8_t nlqueue_super_idx_get(struct nlqueue * qb))
NEON_INLINE_DEF(
{
    qb->head++;
    qb->head &= qb->mask;
    qb->empty++;

    return qb->head;
})

/** @brief      Peek to queue head; the item is not removed from queue.
 *  @param      qb
 *              Pointer to lightweight queue base.
 *  @return     Index of the item where the queue head is located.
 *  @notapi
 */
int_fast8_t np_lqueue_super_head(const struct nlqueue * qb);

/** @brief      Peek to queue head; the item is not removed from queue.
 *  @param      qb
 *              Pointer to lightweight queue base.
 *  @return     Index of the item where the queue tail is located.
 *  @notapi
 */
int_fast8_t np_lqueue_super_tail(const struct nlqueue * qb);

/** @} *//*==================================================================*/
/** @defgroup   nqueue_pqueue Priority sorted queue module
 *  @brief      Priority sorted queue module
 *  @{ *//*==================================================================*/

/** @defgroup   npqueue_sentinel Priority sorted queue sentinel
 *  @brief      Priority sorted queue sentinel.
 *  @{ */

/** @brief      Priority sorted queue sentinel structure
 */
struct npqueue_sentinel
{
    struct nlist_dll list;                      /**< Head of the queue. */
};

/** @brief      Initialise a queue sentinel object.
 *  @param      a_sentinel
 *              Pointer to priority queue sentinel.
 */
#define npqueue_sentinel_init(a_sentinel)                                   \
        nlist_dll_init(&(a_sentinel)->list)

/** @brief      Terminate a queue sentinel object
 *  @param      a_sentinel
 *              Pointer to priority queue sentinel.
 */
#define npqueue_sentinel_term(a_sentinel)                                   \
        npqueue_sentinel_init(a_sentinel)

/** @brief      Test if queue is empty.
 *  @param      a_sentinel
 *              Pointer to priority queue sentinel.
 *  @return     Boolean type
 *  @retval     - true - Queue managed by @a a_sentinel is empty.
 *  @retval     - false - Queue managed by @a a_sentinel is not empty.
 *  @mseffect
 */
#define NPQUEUE_SENTINEL_IS_EMPTY(a_sentinel)                              \
        NLIST_DLL_IS_EMPTY(&(a_sentinel)->list)

/** @brief      Head of the queue
 *  @param      a_sentinel
 *              Pointer to priority queue sentinel.
 *  @return     Pointer to head queue node.
 */
#define npqueue_sentinel_head(a_sentinel)                                   \
        npqueue_next(a_sentinel)

void npqueue_sentinel_shift(struct npqueue_sentinel * sentinel);

/** @} */
/** @defgroup   npqueue_node Priority sorted queue node
 *  @brief      Priority sorted queue node.
 *  @{ */

/** @brief      Priority sorted queue node structure.
 *
 *  Each node has a priority attribute. The attribute type is 8-bit unsigned
 *  integer. The highest priority has the value 255. The lowest priority has
 *  value 0.
 */
struct npqueue
{
    struct nlist_dll list;                      /**< Linked list of items */
    uint_fast8_t priority;                      /**< Priotity attribute */
};

/** @brief      Convert a list entry to node entry.
 *  @param      a_node
 *              Pointer to a priority sorted queue node.
 *  @return     Pointer to priority queue node structure.
 */
#define npqueue_from_list(a_node)                                           \
        nlist_dll_entry((a_node), struct npqueue, list)

/** @brief      Initialize a node and define its priority.
 *
 *  A node structure needs to be initialized before it can be used within a
 *  queue.
 *
 *  @param      node
 *              Pointer to a priority sorted queue node.
 *  @param      priority
 *              An 8-bit unsigned integer number specifying this node priority.
 *              The highest priority has the value 255. The lowest priority has
 *              the value is 0.
 *  @return     The pointer @a node.
 */
struct npqueue * npqueue_init(struct npqueue * node, uint_fast8_t priority);

/** @brief      Terminate a node.
 *
 *  The function will re-initialize the node and set the priority to zero.
 *
 *  @param      node
 *              Pointer to a priority sorted queue node.
 */
void npqueue_term(struct npqueue * node);

/** @brief      Get a node priority.
 *  @param      a_node
 *              Pointer to a priority sorted queue node.
 *  @return     An 8-bit unsigned integer number representing this node
 *              priority.
 */
#define npqueue_priority(a_node)                (a_node)->priority

/** @brief      Set a node priority.
 *  @param      node
 *              Pointer to a node structure.
 *  @param      a_priority
 *              An 8-bit unsigned integer number representing this node
 *              priority.
 */
#define npqueue_priority_set(a_node, a_priority)                            \
        do {                                                                \
            (a_node)->priority = (a_priority);                              \
        } while (0)

/** @brief      Get a next node from @a a_node.
 *  @param      a_node
 *              Pointer to a priority sorted queue node.
 *  @return     A pointer to next node from @a a_node.
 */
#define npqueue_next(a_node)                                                \
        npqueue_from_list(nlist_dll_next(&(a_node)->list))

/** @brief      Insert a node into the queue using sorting method.
 *  @param      sentinel
 *              Pointer to a priority sorted queue sentinel.
 *  @param      node
 *              Pointer to a priority sorted queue node.
 */
void npqueue_insert_sort(struct npqueue_sentinel * sentinel,
        struct npqueue * node);

/** @brief      Insert a node into the queue using the FIFO method.
 *  @param      a_sentinel
 *              Pointer to a priority sorted queue sentinel.
 *  @param      a_node
 *              Pointer to a priority sorted queue node.
 */
#define npqueue_insert_fifo(a_sentinel, a_node)                             \
        nlist_dll_add_after(&(a_sentinel)->list, &(a_node)->list)

/** @brief      Remove the node from queue.
 *  @param      a_node
 *              Pointer to a priority sorted queue node.
 */
#define npqueue_remove(a_node)                                              \
        nlist_dll_remove(&(a_node)->list)

/** @} */
/** @} *//*==================================================================*/
/** @defgroup   nmem_pool Memory pool module
 *  @brief      Memory pool module
 *  @{ *//*==================================================================*/

struct nmem_pool
{
    struct nlist_sll next;
    uint32_t free;
    uint32_t element_size;
};

#define npool(T, size)                                                      \
    {                                                                       \
        struct nmem_pool mem_pool;                                          \
        T storage[size];                                                    \
    }

#define NMEM_POOL_INIT(MP)                                                  \
    do {                                                                    \
        np_mem_pool_init(                                                   \
                &(MP)->mem_pool,                                            \
                &(MP)->storage[0],                                          \
                sizeof((MP)->storage),                                      \
                NBITS_ARRAY_SIZE((MP)->storage));                           \
    } while (0)
        
void np_mem_pool_init(
        struct nmem_pool * pool, 
        void * storage, 
        size_t storage_size, 
        uint32_t elements);

#define NMEM_POOL(MP)                   &(MP)->mem_pool

void * np_mem_pool_alloc(struct nmem_pool * pool);
void   np_mem_pool_free (struct nmem_pool * pool, void * mem);

/** @} *//*==================================================================*/
/** @defgroup   nlogger_x Extended logger module
 *  @brief      Extended logger module
 *  @{ *//*==================================================================*/


/** @brief      Logger levels
 *  @details    Default log level is @ref NLOGGER_LVL_DEBUG.
 */
#define NLOGGER_LEVEL_DEBUG             4
#define NLOGGER_LEVEL_INFO              3
#define NLOGGER_LEVEL_WARN              2
#define NLOGGER_LEVEL_ERR               1

/** @defgroup   loggerprinters Logger printers
 *  @brief      Logger printers.
 *  @{
 */

#if defined(NCONFIG_ENABLE_LOGGER) && (NCONFIG_ENABLE_LOGGER == 1)
/** @brief      Macro that returns current nlogger configuration
 */
#define NLOGGER_IS_ENABLED              1
#else
#define NLOGGER_IS_ENABLED              0
#endif

#if (NLOGGER_IS_ENABLED == 1) && (NCONFIG_LOGGER_LEVEL >= 4) || defined(__DOXYGEN__)
/** @brief      Log a debug message.
 */
#define nlogger_debug(msg, ...)         nlogger_print(msg, __VA_ARGS__)
#else
#define nlogger_debug(msg, ...)
#endif

#if (NLOGGER_IS_ENABLED == 1) && (NCONFIG_LOGGER_LEVEL >= 3) || defined(__DOXYGEN__)
/** @brief      Log an informational message.
 */
#define nlogger_info(msg, ...)          nlogger_print(msg, __VA_ARGS__)
#else
#define nlogger_info(msg, ...)
#endif

#if (NLOGGER_IS_ENABLED == 1) && (NCONFIG_LOGGER_LEVEL >= 2) || defined(__DOXYGEN__)
/** @brief      Log a warning message.
 */
#define nlogger_warn(msg, ...)          nlogger_print(msg, __VA_ARGS__)
#else
#define nlogger_warn(msg, ...)
#endif

#if (NLOGGER_IS_ENABLED == 1) && (NCONFIG_LOGGER_LEVEL >= 1) || defined(__DOXYGEN__)
/** @brief      Log an error message.
 */
#define nlogger_err(msg, ...)           nlogger_print(msg, __VA_ARGS__)
#else
#define nlogger_err(msg, ...)
#endif

#if (NCONFIG_ENABLE_LOGGER == 1) || defined(__DOXYGEN__)
bool nlogger_flush(void);
#else
#define nlogger_flush()
#endif

#if (NCONFIG_ENABLE_LOGGER == 1) || defined(__DOXYGEN__)
/** @brief      Print a formated string to a logger.
 */
bool nlogger_print(const char * msg, ...);
#else
#define nlogger_print(msg, ...)
#endif

/** @} *//*==================================================================*/
/** @defgroup   nevent Event module
 *  @brief      Event module
 *  @{ *//*==================================================================*/

#define NEVENT_INITIALIZER(a_id)                                            \
        {                                                                   \
            .id = (a_id),                                                   \
        }                                                           

struct nmem_pool;

struct nevent
{
    uint16_t id;
#if (NCONFIG_EVENT_USE_DYNAMIC == 1)
    uint16_t ref;
    struct nmem_pool * pool;
#endif /* (NCONFIG_EVENT_USE_DYNAMIC == 1) */
};

void * nevent_create(struct nmem_pool * pool, uint_fast16_t id);

/** @} *//*==================================================================*/
/** @defgroup   nstate_machine_processor State machine processor module
 *  @brief      State machine processor module
 *  @{ *//*==================================================================*/

/**
 * @brief       Get the state machine workspace pointer
 */
#define nsm_wspace(sm)                  ((sm)->wspace)

/**
 * @brief       State machine action, given event was handled.
 * @return      Actions enumerator @ref NACTION_HANDLED.
 */
#define nsm_event_handled()             (NACTION_HANDLED)

/**
 * @brief       State machine action, given event was ignored.
 * @return      Actions enumerator @ref NACTION_IGNORED.
 */
#define nsm_event_ignored()             (NACTION_IGNORED)

/**
 * @brief       State machine action, state is returning its super state
 * @param       sm
 *              Pointer to the state machine
 * @param       state_ptr
 *              State function pointer to super state
 * @return      Actions enumerator @ref NACTION_SUPER.
 */
#define nsm_super_state(sm, state_ptr)                                      \
        ((sm)->state = (state_ptr), NP_SMP_SUPER_STATE)

/**
 * @brief       State machine action, state machine wants to transit to new
 *              state
 * @param       sm
 *              Pointer to the state machine
 * @param       state_ptr
 *              State function pointer to new state
 * @return      Actions enumerator @ref NACTION_TRANSIT_TO.
 * @api
 */
#define nsm_transit_to(sm, state_ptr)                                       \
        ((sm)->state = (state_ptr), NP_SMP_TRANSIT_TO)

/** @brief       State machine event identifications
 */
enum nsm_event
{
    NSM_SUPER,               /**<@brief Get the state super 
                                             *         state.
                                             */
    NSM_ENTRY,               /**<@brief Process state entry.   */
    NSM_EXIT,               /**<@brief Process state exit.    */
    NSM_INIT,               /**<@brief Process state init.    */
    NSIGNAL_RETRIGGER,
    NSIGNAL_AFTER,
    NSIGNAL_EVERY,
    NEVENT_NULL,              /**<@brief NULL event.            */
    
    NEVENT_USER_ID
};

/** @brief      Returned actions enumerator
 *  
 * This enumerator is for internal use only. It defines what actions should 
 * dispatcher execute for the given state machine.
 * 
 * @note        Do not use this enumerator directly, but use the appropriate
 *              naction_*() function.
 * @notapi
 */
typedef enum np_sm_action
{
    NP_SMP_SUPER_STATE  = 0u,               /**< Returns super state          */
    NP_SMP_TRANSIT_TO   = 1u,               /**< Transit to a state           */
    NACTION_HANDLED     = 2u,               /**< Event is handled             */
    NACTION_IGNORED     = 3u,               /**< Event is ignored             */
} nsm_action;

struct nsm;

/** @brief      State function prototype.
 * 
 *  Each state machine state is described by a single state function. A state
 *  will receive a state machine which is being executed and an event which
 *  needs to be processed by the state function.
 * 
 *  @param      sm
 *              Pointer to state machine being executed
 *  @param      event
 *              Pointer to event that has been dispatched to the state machine
 *  @return     Action enumerator of the specified state. Action enumerator can
 *              be one of the following:
 *              - @ref NACTION_SUPER - state is returning its super state
 *              - @ref NACTION_TRANSIT_TO - state machine wants to transit to
 *                  new state
 *              - @ref NACTION_HANDLED - given event was handled
 *              - @ref NACTION_IGNORED - given event was ignored
 * @note        Do not use return enumerator directly but use the appropriate
 *              naction_*() function.
 */
typedef nsm_action (nstate_fn)(struct nsm *, const struct nevent *);

/** @} *//*==================================================================*/
/** @defgroup   nepa Event Processing Agent (EPA) module
 *  @brief      Event Processing Agent (EPA) module
 *  @{ *//*==================================================================*/

/** @brief      The highest EPA priority value.
 *
 *  The EPA with this priority has the highest urgency to be selected and
 *  dispatched by scheduler.
 */
#define NEPA_PRIO_MAX                   255

/** @brief      The lowest EPA priority value
 *  @note       This priority level is reserved by Neon idle task.
 */
#define NEPA_PRIO_MIN                   0

/** @brief      The pointer to currently executed EPA.
 */
#define ncurrent                        nepa_current()

/** @brief      Define a structure of an event queue of fixed size.
 * 
 *  This is a helper macro which is used to ease the process of defining an
 *  event queue. For example, if you want to declare an event queue of a size
 *  @a M you would use the macro in the following way:
 * 
 *  @code
 *  struct my_epa_queue nevent_queue(M);
 *  @endcode
 * 
 *  Then in the code you would create an instance of the structure:
 * 
 *  @code
 *  static struct my_epa_queue g_my_epa_queue;
 *  @endcode
 * 
 *  @param      a_size
 *              Number of event this queue would hold.
 */
#define nevent_queue(a_size)                                                \
        nlqueue_dynamic_storage(const struct nevent *, a_size)

#if (NCONFIG_EPA_USE_HSM == 1) || defined(__DOXYGEN__)
/** @brief      Initialize an Event Processing Agent (EPA)
 *  
 *  Each EPA is described by an event queue, state machine type, initial state
 *  and a workspace storage.
 * 
 *  @param      a_queue
 *              Pointer to an event queue. See @ref nevent_queue on details how
 *              to define and instantiate a queue.
 *  @param      a_type_id
 *              Type of state machine, see @ref nepa_type for details.
 *  @param      a_init_state
 *              Initial state function of the state machine. For more details
 *              about state functions see @ref nstate_fn.
 *  @param      a_ws
 *              State machine workspace. A workspace pointer is just passed to
 *              state machine state functions. It is a void pointer, so any kind
 *              of additional data can be passed to the state functions.
 */
#define NEPA_INITIALIZER(a_queue, a_type_id, a_init_state, a_ws)            \
        {                                                                   \
            .sm =                                                           \
            {                                                               \
                .type =                                                     \
                {                                                           \
                    .id = (a_type_id),                                      \
                },                                                          \
                .state = (a_init_state),                                    \
                .ws = (a_ws),                                               \
            },                                                              \
            .equeue =                                                       \
            {                                                               \
                .super =                                                    \
                {                                                           \
                    .head = 0                                               \
                    .tail = 1,                                              \
                    .empty = NBITS_ARRAY_SIZE(&(a_queue)->np_lq_storage),   \
                    .mask = NBITS_ARRAY_SIZE(&(a_queue)->np_lq_storage) - 1u,     \
                },                                                          \
                .np_lq_storage = &(a_queue)->np_lq_storage[0],              \
            },                                                              \
        }
#else
#define NEPA_INITIALIZER(a_queue, a_type_id, a_init_state, a_ws)            \
        {                                                                   \
            .sm =                                                           \
            {                                                               \
                .state = (a_init_state),                                    \
                .ws = (a_ws),                                               \
            },                                                              \
            .equeue =                                                       \
            {                                                               \
                .super =                                                    \
                {                                                           \
                    .head = 0,                                              \
                    .tail = 1,                                              \
                    .empty = NBITS_ARRAY_SIZE((a_queue)->np_lq_storage),    \
                    .mask = NBITS_ARRAY_SIZE((a_queue)->np_lq_storage) - 1u,     \
                },                                                          \
                .np_lq_storage = &(a_queue)->np_lq_storage[0],              \
            },                                                              \
        }
#endif

/** @brief      EPA state machine type
 *  
 *  There are two different state machine types: a Finite State Machine (FSM)
 *  and a Hierarchical State Machine. FSM is a subclass of a HSM, as it has only
 *  one level of hierarchy.
 */
enum nepa_type
{
    NEPA_FSM_TYPE,                          /**<@brief Finite State Machine.  */
    NEPA_HSM_TYPE                           /**<@brief Hierarchical State
                                             *         Machine.
                                             */
};

/** @brief      Event Processing Agent (EPA)
 */
struct nepa
{
    struct nsm
    {
#if (NCONFIG_EPA_USE_HSM == 1)
        union nsm_type
        {
            nstate_fn *                 dispatch;
            enum nepa_type              id;
        }                       type;
#endif
        nstate_fn *                 state;
        void *                      ws;
    }                           sm;
    struct ntask
    {
        uint_fast8_t                prio;
    }                           task;
    struct nequeue nlqueue_dynamic(const struct nevent *)
                                equeue;
    NSIGNATURE_DECLARE
};

struct nepa * nepa_current(void);

nerror nepa_send_signal(struct nepa * epa, uint_fast16_t signal);

nerror nepa_send_event(struct nepa * epa, const struct nevent * event);


/** @} *//*==================================================================*/
/** @defgroup   nsys System module
 *  @brief      System module
 *  @{ *//*==================================================================*/

extern struct nepa g_nsys_epa_idle;
extern struct nepa * g_nsys_epa_list[NCONFIG_EPA_INSTANCES];

void nsys_init(void);

bool nsys_is_scheduler_started(void);

#if (NCONFIG_SYS_EXITABLE_SCHEDULER != 1)
NPLATFORM_NORETURN(void nsys_schedule_start(void));
#else
void nsys_schedule_start(void);
#endif

#if (NCONFIG_SYS_EXITABLE_SCHEDULER == 1)
void nsys_schedule_stop(void);
#endif

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* NEON_H_ */
