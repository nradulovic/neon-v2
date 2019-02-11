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
 *  @brief       Debugging support header.
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_debug Debugging support.
 *  @brief       Debugging support.
 *
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_MODULE_DEBUG_H_
#define NEON_MODULE_DEBUG_H_

#include <stdint.h>
#include <stddef.h>

#include "port/nport_platform.h"
#include "port/nport_arch.h"
#include "logger/nlogger.h"
#include "configs/default_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(NCONFIG_ENABLE_DEBUG) && (NCONFIG_ENABLE_DEBUG == 1)
#define NDEBUG_IS_ENABLED 1
#else
/** @brief      Macro that returns current ndebug configuration
 */
#define NDEBUG_IS_ENABLED 0
#endif

/*---------------------------------------------------------------------------*/
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

/**@} */
/*---------------------------------------------------------------------------*/
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
/*---------------------------------------------------------------------------*/
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

/**@} */
/*---------------------------------------------------------------------------*/
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

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_DEBUG_H_ */
