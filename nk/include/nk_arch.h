/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license details please refer to LGPL-3.0.md
 */
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Architecture header
 *
 *  @addtogroup  nk
 *  @{
 */
/** @defgroup    nk_arch Architecture
 *  @brief       Architecture
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NK_INCLUDE_ARCH_H_
#define NK_INCLUDE_ARCH_H_

#include <stdint.h>

#include "variant/arch.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   nk_arch_id Architecture identification information
 *  @brief      Port identification macros.
 *  @{
 */

/** @brief		This macro is defined for each of supported architecture
 *
 *  The macro will expand to human readable text containing the name of the
 *  underlying architecture.
 */
#if !defined(NARCH_ID) || defined(__DOXYGEN__)
#define NK_ARCH_ID            	"unknown"
#endif

/** @brief      Each port defines a macro named NARCH_xxx.
 *  
 *  For example, the ARM based architectures will define 'NARCH_ARM'. In 
 *  addition to this macro it will probably define macros like 'NARCH_ARM_V7M'
 *  which identifies a subset of architecture information.
 *
 *  This macro can be used for conditional code compilation:
 *
 *  @code
 *  #if defined(NARCH_ARM)
 *      Some code related to ARM architecture.
 *      ...
 *  #endif
 *  @endcode
 */
#define NK_ARCH_xxx

/** @brief      Number of bits of the used architecture.
 */
#define NK_ARCH_DATA_WIDTH		(sizeof(unsigned int) * 8u)
    
/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   arch_cpu Architecture CPU operations
 *  @brief      Architecture CPU operations.
 *  @{
 */

/** @brief      Stop the CPU execution.
 *  
 *  On embedded targets this function will actually stop the CPU execution,
 *  probably by executing a NOP instruction in indefinite loop or by executing
 *  the sleep instruction if the CPU supports it.
 *
 *  Usually you want to stop the execution in case of some serious error. When
 *  a High Level OS is used, this function will terminate the current process
 *  (ie it will call POSIX exit function with '0' error return value).
 */
void nk_arch_stop(void);

/** @brief		Stop the CPU execution and wait for interrupt.
 *
 *  On supported architectures the function will put the CPU to sleep while the
 *  peripherals still have the ability to operate. It is up to caller to
 *  properly configure the system for such a power mode. This function will
 *  merely execute the sleep instruction on the CPU.
 */
void nk_arch_sleep(void);

/** @brief      Calculate exponent of 2.
 */
static inline
uint32_t nk_arch_exp2(uint_fast8_t x)
{
	return (UINT32_C(0x1) << x);
}

/** @brief      Calculate logarithm of base 2.
 *  @example    log2(2) = 1, log2(10) = 4
 */
uint_fast8_t nk_arch_log2(uint32_t x);

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NK_INCLUDE_ARCH_H_ */
