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
#include <assert.h>

#if defined(NEON_APP_CONFIG)
#include "neon_app_config.h"
#else
#include "default_config.h"
#endif

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
#define NREQUIRE(expr)                  assert(expr)

/** @brief      Make sure the callee has fulfilled all contract postconditions
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @api
 */
#define NENSURE(expr)                   assert(expr)

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
#define NASSERT_INTERNAL(expr)          assert(expr)

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
#define NSIGNATURE_DECLARE                     int _signature;
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
