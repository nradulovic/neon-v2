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
 *  @brief       Error support header.
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_error Error support.
 *  @brief       Error support.
 *
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_MODULE_ERROR_H_
#define NEON_MODULE_ERROR_H_

#ifdef __cplusplus
extern "C" {
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
enum nerror_types
{
    EOBJ_INVALID, /* Invalid object error */
    EOBJ_INITIALIZED,
    EARG_OUTOFRANGE, /* Argument is out of range */
};

/** @} */
/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_ERROR_H_ */
