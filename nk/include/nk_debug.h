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


#ifndef NK_DEBUG_H_
#define NK_DEBUG_H_

#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(NK_DEBUG__IS_ENABLED) || defined(__DOXYGEN__)
/** @brief		Configuration setting for NK_DEBUG module.
 */
#define NK_DEBUG__IS_ENABLED 			1
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
#if (NK_DEBUG__IS_ENABLED == 1)
#define NK_DEBUG__OBLIGATION(expr)      expr
#else
#define NK_DEBUG__OBLIGATION(expr)      (void)0
#endif

/** @brief      Make sure the caller has fulfilled all contract preconditions
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @api
 */
#if (NK_DEBUG__IS_ENABLED == 1)
#define NK_DEBUG__REQUIRE(expr)         assert(expr)
#else
#define NK_DEBUG__REQUIRE(expr)         (void)0
#endif

/** @brief      Make sure the callee has fulfilled all contract postconditions
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @api
 */
#if (NK_DEBUG__IS_ENABLED == 1)
#define NK_DEBUG__ENSURE(expr)          assert(expr)
#else
#define NK_DEBUG__ENSURE(expr)          (void)0
#endif

/**@} */
/*---------------------------------------------------------------------------*/
/** @defgroup   debug_internal Internal checking
 *  @brief      These macros are enabled/disabled using the option
 *              @ref NCONFIG_ENABLE_NDEBUG.
 *  @{ */

/** @brief      Assert macro used for internal execution checking
 *  @param      expr
 *              Expression : C expression : condition which must be 'true'.
 *  @api
 */
#if (NK_DEBUG__IS_ENABLED == 1)
#define NK_DEBUG__ASSERT(expr)          assert(expr)
#else
#define NK_DEBUG__ASSERT(expr)          (void)0
#endif

/**@} */
/**@} */
#ifdef __cplusplus
}
#endif

/**@} */
/**@} */
/*---------------------------------------------------------------------------*/
#endif /* NK_DEBUG_H_ */
