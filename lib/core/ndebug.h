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
/** @defgroup   ndebug Debug
 *  @brief      Debug
 *  @{
 */

#ifndef NEON_DEBUG_H_
#define NEON_DEBUG_H_

#include <stdint.h>

#include "sys/nport.h"
#include "sys/nconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup   debug_errorcheck Error checking
 *  @brief      Error checking
 *  @{ */

/** @brief      Generic assert macro.
 */
#if (NCONFIG_ENABLE_DEBUG == 1) || defined(__DOXYGEN__)
#define NASSERT(expr)                                                        \
    if (!(expr)) {                                                           \
        NASSERT_ALWAYS(# expr);                                              \
    }
#else
#define NASSERT(expr)                   (void)0
#endif

/** @brief      Assert macro that will always fail (no conditional).
 */
#if (NCONFIG_ENABLE_DEBUG == 1) || defined(__DOXYGEN__)
#define NASSERT_ALWAYS(text)                                                \
        nassert(text, NPLATFORM_FILE, NPLATFORM_FUNC, NPLATFORM_LINE)
#else
#define NASSERT_ALWAYS(text)             (void)0
#endif

/** @} */
/** @defgroup   debug_api_valid API contract validation
 *  @brief      These macros are enabled/disabled using the option
 *              @ref NCONFIG_ENABLE_DEBUG.
 *  @{ */

/** @brief      Execute code to fulfill the contract.
 */
#if (NCONFIG_ENABLE_DEBUG == 1) || defined(__DOXYGEN__)
#define NOBLIGATION(expr)               expr
#else
#define NOBLIGATION(expr)               (void)0
#endif

/** @brief      Make sure the caller has fulfilled all contract preconditions.
 */
#define NREQUIRE(expr)                  NASSERT(expr)

/** @brief      Make sure the callee has fulfilled all contract postconditions.
 */
#define NENSURE(expr)                   NASSERT(expr)

/**@} */
/** @defgroup   debug_internal Internal checking
 *  @brief      These macros are enabled/disabled using the option
 *              @ref NCONFIG_ENABLE_DEBUG.
 *  @{ */

/** @brief      Assert macro used for internal execution checking.
 */
#define NASSERT_INTERNAL(expr)          NASSERT(expr)

/** @} */
/** @defgroup   debug_signature Object debug signatures
 *  @brief      During debugging the objects will use the signatures.
 *  @{ */

/** @brief      Object signature for heap memory allocation.
 */
#define NSIGNATURE_HEAP                 ((unsigned int)0xdeadbee0u)

/** @brief      Object signature for pool memory allocation.
 */
#define NSIGNATURE_POOL                 ((unsigned int)0xdeadbee1u)

/** @brief      Object signature for static memory allocation.
 */
#define NSIGNATURE_STATIC               ((unsigned int)0xdeadbee2u)

/** @brief      Object signature for heap memory allocation from standard C
 *              library.
 */
#define NSIGNATURE_STDHEAP              ((unsigned int)0xdeadbee3u)

/** @brief      Object signature for Timer object.
 */
#define NSIGNATURE_TIMER                ((unsigned int)0xdeadcee0u)

/** @brief      Object signature for Event Processing Agent object.
 */
#define NSIGNATURE_EPA                  ((unsigned int)0xdeaddee0u)

/** @brief      Object signature for Event Queue object.
 */
#define NSIGNATURE_EQUEUE               ((unsigned int)0xdeadfeebu)

/** @brief      Object signature for Event Timer object.
 */
#define NSIGNATURE_ETIMER               ((unsigned int)0xdeadfeecu)

/** @brief      Object signature for Event object.
 */
#define NSIGNATURE_EVENT                ((unsigned int)0xdeadfeedu)

/** @brief      Object signature for State Machine object.
 */
#define NSIGNATURE_SM                   ((unsigned int)0xdeadfeeeu)

/** @brief      Object signature for Deferred Queue object.
 */
#define NSIGNATURE_DEFER                ((unsigned int)0xdeadfeefu)


#if (NCONFIG_ENABLE_DEBUG == 1) || defined(__DOXYGEN__)
/** @brief      Declare an object signature structure member
 */
#define NSIGNATURE_DECLARE              unsigned int _signature;
#else
#define NSIGNATURE_DECLARE
#endif

#if (NCONFIG_ENABLE_DEBUG == 1) || defined(__DOXYGEN__)
/** @brief      Initialize an object signature during object instantiation.
 */
#define NSIGNATURE_INITIALIZER(signature)                                   \
        ._signature = signature,
#else
#define NSIGNATURE_INITIALIZER(signature)
#endif

/** @brief      Return an object signature value.
 */
#define NSIGNATURE_OF(object)                                               \
        ((object) ? (object)->_signature : 0)

/** @brief      Sets an object signature value.
 */
#define NSIGNATURE_IS(object, signature)                                    \
        (object)->_signature = (signature)

/** @brief      Assert callback function
 */
NPLATFORM_NORETURN(void nassert(
        const char * text, 
        const char * file, 
        const char * func, 
        uint32_t line));

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_DEBUG_H_ */
