/*
 * Neon
 * Copyright (C)  2017  Nenad Radulovic
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
 *  @author      Nenad Radulovic
 *  @brief       Platform header for GCC C89 standard
 *
 *  @addtogroup  mod_platform
 *  @{
 */
/** @defgroup    platform_gcc_c89 GCC Platform for C89 standard
 *  @brief       GCC Platform for C89 standard
 *  @{
 */
/*---------------------------------------------------------------------------*/

#ifndef NEON_GCC_VARIANT_GCC_C89_H_
#define NEON_GCC_VARIANT_GCC_C89_H_

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------------------------------------------------------*/

#define PORT_C_FUNC             __FUNCTION__

#ifdef __cplusplus
}
#endif
/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_GCC_VARIANT_GCC_C89_H_ */
