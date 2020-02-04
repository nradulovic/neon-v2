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
/** @defgroup   nport Portable layers
 *  @brief      Portable layers
 *  @{
 */

#ifndef NEON_PORT_H_
#define NEON_PORT_H_

#include <stdint.h>
#include <stdbool.h>

#include "core/nconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup   nport_platform_id Platform compiler identification
 *  @brief      Port compiler identification and version information.
 *  @{ */

/** @brief      Defines a constant string representing Neon build date.
 */
extern const char * const nsys_build_date;

/** @brief      Defines a constant string representing Neon build time.
 */
extern const char * const nsys_build_time;

/** @brief      Defines a constant string representing Neon build platform ID.
 */
extern const char * const nsys_platform_id;

/** @brief      Defines a constant string representing Neon build platform version.
 */
extern const char * const nsys_platform_version;

/** @} */
/** @defgroup   nport_platform Platform compiler macros
 *  @brief      Port compiler helper macros.
 *  @{ */

/** @brief      Compiler directive to inline a function.
 * 
 *  Place this macro in front of function declaration to declare it as inline
 *  function. It is up to compiler to decide wheater is worth to inline a
 *  function.
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_INLINE                static inline
#else
#define NPLATFORM_INLINE
#endif

/** @brief      Another compiler directive to inline a function, but this will
 *              force the compiler to inline the function.
 * 
 *  For further details see @ref NPLATFORM_INLINE.
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_INLINE_ALWAYS         NPLATFORM_INLINE
#else
#define NPLATFORM_INLINE_ALWAYS
#endif

/** @brief      Cast a member of a structure to the containing structure.
 *  
 *  @param      a_ptr
 *              The pointer to the member of a structure.
 *  @param      a_type
 *              The type of the container struct the member is embedded in.
 *  @param      a_member
 *              The name of the member within the container struct.
 * 
 *  @code
 *  struct my_struct
 *  {
 *      int a;
 *      int b;
 *  } data;
 * 
 *  int * ptr_to_a = &data.a;
 * 
 *  struct my_struct * ptr_to_data = 
 *          NPLATFORM_CONTAINER_OF(ptr_to_a, struct my_struct, a);
 *  @endcode
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_CONTAINER_OF(a_ptr, a_type, a_member)                     \
    ((a_type *)((char *)a_ptr - offsetof(a_type, a_member)))
#else
#define NPLATFORM_CONTAINER_OF(a_ptr, a_type, a_member)
#endif

/** @brief      Provides function name.
 * 
 *  This macro will return a string containing the function name.
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_FUNC                  "unknown"
#else
#define NPLATFORM_FUNC
#endif

/** @brief      Provides the file's name which is being compiled.
 * 
 *  This macro will return a string containing the file name.
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_FILE                  __FILE__
#else
#define NPLATFORM_FILE
#endif

/** @brief      Provides the file source line where this macro is located at.
 * 
 *  This macro will just return an integer specifying the file source line 
 *  number.
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_LINE                  __LINE__
#else
#define NPLATFORM_LINE
#endif

/** @brief      Omit function prologue/epilogue sequences.
 * 
 *  @param      a_decl
 *              A declaration of the function.
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_NAKED(a_decl)         __attribute__((naked)) a_decl
#else
#define NPLATFORM_NAKED(a_decl)
#endif

/** @brief      Omit warning about unused function.
 * 
 *  @param      a_decl 
 *              A declaration of the function.
 *  @hideinitializer
 */  
#if defined(__GNUC__)
#define NPLATFORM_UNUSED(a_decl)        __attribute__((unused)) a_decl
#else
#define NPLATFORM_UNUSED(a_decl)
#endif
    
/** @brief      Omit warning about unused function argument.
 * 
 *  @param      a_decl
 *              A declaration of the function argument which is not used.
 *  @hideinitializer
 */  
#if defined(__GNUC__)
#define NPLATFORM_UNUSED_ARG(a_decl)    (void)a_decl
#else
#define NPLATFORM_UNUSED_ARG(a_decl)
#endif

/** @brief      Declare a function that will never return.
 * 
 *  Use this macro to tell the compiler that the function will never return,
 *  for example, an infinite loop is implemented inside the function. This 
 *  allows the compiler to do further optimizations regarding stack usage and
 *  save a few instructions in function body.
 * 
 *  @param      a_decl
 *              A declaration of the function.
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_NORETURN(a_decl)      __attribute__((noreturn)) a_decl
#else
#define NPLATFORM_NORETURN(a_decl)
#endif

/** @brief      Declare a structure as packed.
 * 
 *  @param      a_decl
 *              A declaration of a structure.
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_PACKED(a_decl)        __attribute__((packed)) a_decl
#else
#define NPLATFORM_PACKED(a_decl)
#endif

/** @brief      This attribute specifies a minimum alignment (in bytes) for
 *              variables of the specified type.
 * 
 *  @param      a_align
 *              Alignment of the variable in bytes.
 *  @param      a_decl
 *              A declaration of the variable.
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_ALIGN(a_align, a_decl)                                    \
        __attribute__((aligned (a_align))) a_decl
#else
#define NPLATFORM_ALIGN(a_align, a_decl)
#endif

/** @brief      Returns current date.
 * 
 *  This macro will return a string containing the current date.
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_DATE                  __DATE__
#else
#define NPLATFORM_DATE
#endif

/** @brief      Returns current time.
 * 
 *  This macro will return a string containing the current time.
 *  @hideinitializer
 */
#if defined(__GNUC__)
#define NPLATFORM_TIME                  __TIME__
#else
#define NPLATFORM_TIME
#endif
    
/** @} */
/** @defgroup   nport_arch Port CPU architecture
 *  @brief      Port CPU architecture.
 *  @{ */

/** @brief      Defines a string containing the architecture name.
 */
extern const char * const narch_id;

/** @brief      This macro is defined to 1 if current architecture has exclusive
 *              load/store access.
 */
extern const bool narch_has_atomics;

/** @brief      Number of data bus bits of the used CPU architecture.
 */
#if !defined(NARCH_DATA_WIDTH)
#define NARCH_DATA_WIDTH                32
#endif
    
/** @brief      Natural alignment of CPU architecture.
 */
#if !defined(NARCH_ALIGN)
#define NARCH_ALIGN                     NCONFIG_CPU_DATA_ALIGN
#endif
    
/** @brief      Stop the CPU execution.
 * 
 *  On embedded targets this function will actually stop the CPU execution.
 *  Usually you want to stop the execution in case of some serious error. When
 *  a High Level OS is used, this function will terminate the current process
 *  (application).
 */
void narch_cpu_stop(void);

/** @brief      Setup the CPU to enter into sleep state.
 * 
 *  On embedded targets this function will put the CPU into sleep state. The
 *  actual level of sleep (if supported by CPU) is not defined. When a High 
 *  Level OS is used, this function will call standard C library function sleep.
 */
void narch_cpu_sleep(void);

/** @brief      Set a bit in unsigned 32-bit integer variable.
 * 
 *  @param      u32
 *              Pointer to unsigned 32-bit integer.
 *  @param      bit
 *              Argument specifying which bit to set.
 *  @note       Do not use bit >= 32 since it will result in undefined
 *              behaviour.
 */
void narch_atomic_set_bit(uint32_t * u32, uint_fast8_t bit);

/** @brief      Clear a bit in unsigned integer 32-bit variable.
 *  
 *  @param      u32
 *              Pointer to unsigned 32-bit integer.
 *  @param      bit
 *              Argument specifying which bit to clear.
 *  @note       Do not use bit >= 32 since it will result in undefined
 *              behaviour.
 */
void narch_atomic_clear_bit(uint32_t * u32, uint_fast8_t bit);

/** @brief      Calculate exponent of 2.
 * 
 *  @param      x
 *              Input integer value.
 *  @return     exp2(x)
 */
uint32_t narch_exp2(uint_fast8_t x);

/** @brief      Calculate logarithm of base 2.
 * 
 *  @param      x
 *              Input integer value.
 *  @return     log2(x)
 */
uint_fast8_t narch_log2(uint32_t x);

/** @} */
/** @defgroup   nport_mcu Port MCU support
 *  @brief      Port MCU support
 *  @{ */

/** @} */
/** @defgroup   nport_board Port Board support
 *  @brief      Port Board support
 *  @{ */

/** @} */
/** @defgroup   nport_os Port OS support
 *  @brief      Port OS support
 *  @{ */

/** @brief      A critical lock state variable structure.
 */
struct nos_critical 
{
    uint32_t state;
};

/** @brief      Enter the critical code.
 */
void nos_critical_lock(struct nos_critical * lock);

/** @brief      Exit from critical code and restore the execution state stored
 *              in @a local.
 */
void nos_critical_unlock(struct nos_critical * lock);

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_PORT_H_ */
