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
 *  @brief       Task Fiber header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_fiber Task Fiber
 *  @brief       Task Fiber
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_FIBER_TASK_H_
#define NEON_FIBER_TASK_H_

#include <stdint.h>
#include "task/ntask.h"
#include "fiber/nfiber.h"

/*---------------------------------------------------------------------------*/
/** @defgroup   fiber_decl Fiber declarations
 *  @brief      Fiber declarations.
 *  @{
 */

struct nfiber_task
{
    struct nfiber fiber;
    nfiber_fn * fiber_fn;
    struct ntask task;
};

/** @brief      Initialize a fiber.
 *
 *  Initializes a fiber. Initialization must be done prior to starting to
 *  execute the fiber.
 *
 *  @param      fiber
 *              A pointer to the fiber control structure.
 *
 *  @hideinitializer
 */
void nfiber_task_create(struct nfiber_task ** fiber, nfiber_fn * fn, void * arg,
    uint_fast8_t prio);

void nfiber_task_delete(struct nfiber_task * fiber);

void np_fiber_task_dispatch(struct ntask * fiber_task, void * arg);

/** @} */
/** @} */
/** @} */

#endif /* NEON_FIBER_TASK_H_ */

