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
 *  @brief       Task header
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_task Task
 *  @brief       Task
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_MODULE_TASK_H_
#define NEON_MODULE_TASK_H_

#include <stdint.h>

#include "queue/nqueue_pqueue.h"
#include "task/ntask_fiber.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ntask;

typedef uint_fast8_t (task_fn)(struct ntask * task, void * arg);

struct ntask
{
    struct nfiber fiber;
    struct npqueue_node pnode;
    task_fn * fn;
    void * arg;
    uint_fast8_t state;
};

#define NTASK_DORMANT               NFIBER_TERMINATED
#define NTASK_READY                 NFIBER_YIELDED
#define NTASK_BLOCKED               NFIBER_WAITING
    
#define NTASK(func_call)            NFIBER(func_call)

#define NTASK_BEGIN(task)           NFIBER_BEGIN(&(task)->fiber)

#define NTASK_END()                 NFIBER_END()

#define ntask_yield()               nfiber_yield()

#define ntask_init(a_task, a_task_fn, a_task_arg, a_prio)                   \
    do {                                                                    \
        struct ntask * _self = (a_task);                                    \
        nfiber_init(&_self->fiber);                                         \
        npqueue_node_init(&_self->pnode, (a_prio));                         \
        _self->fn = (a_task_fn);                                            \
        _self->arg = (a_task_arg);                                          \
        _self->state = NFIBER_TERMINATED;                                   \
    } while (0)

#define ntask_dispatch(task)                                                \
    do {                                                                    \
        struct ntask * _self = (task);                                      \
        _self->state = nfiber_dispatch(_self->fn(_self, _self->arg));       \
    } while (0)

#define ntask_state(task)           ((const struct ntask *)(task))->state

#define ntask_priority(task)        npqueue_node_priority(&(task)->pnode)

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_MODULE_TASK_H_ */
