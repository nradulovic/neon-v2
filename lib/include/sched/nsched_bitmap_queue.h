/*
 * Neon
 * Copyright (C)  2018  REAL-TIME CONSULTING
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/** @file
 *  @author      Developer name
 *  @brief       Template description header
 *
 *  @addtogroup  module
 *  @{
 */
/** @defgroup    mod_template Template
 *  @brief       Template.
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_MODULE_TEMPLATE_H_
#define NEON_MODULE_TEMPLATE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   templateid Template identification information
 *  @brief      Template identification information.
 *  @{
 */

/** @brief      Some brief description.
 * 
 *  More details about the function.
 *
 *  @param      param1
 *              Some information about param1.
 *  @returns    Returns a status information.
 *  @retval     - ERANGE - Something has happened.
 *  @api
 */
void some_function(uint32_t param1);

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_TEMPLATE_H_ */
