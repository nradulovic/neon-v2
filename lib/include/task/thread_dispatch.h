/*
 * Neon
 * Copyright (C)  2018  REAL-TIME CONSULTING
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

struct ntask;

struct np_thread_dispatch
{
    struct ntask * current;
};

extern struct np_thread_dispatch ng_thread_dispatch;

#define ng_current  ng_thread_dispath.current

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_TEMPLATE_H_ */
