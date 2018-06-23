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
 *  @author      Nenad Radulovic
 *  @brief       Priority sorted queue
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_pqueue Priority sorted queue
 *  @brief       Priority sorted queue.
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NEON_QUEUE_PQUEUE_H_
#define NEON_QUEUE_PQUEUE_H_

#include <stdint.h>
#include "port/nport_platform.h"
#include "list/nlist_dll.h"

#ifdef __cplusplus
extern "C" {
#endif

struct npqueue
{
    struct nlist_dll sentinel;
};

struct npqueue_node
{
    struct nlist_dll node;
    uint_fast8_t priority;
};

NPLATFORM_INLINE
struct npqueue_node * npqueue_from_list(struct nlist_dll * node)
{
    return (NLIST_ENTRY(node, struct npqueue_node, node));
}

NPLATFORM_INLINE
void npqueue_node_init(struct npqueue_node * node,
        uint_fast8_t priority)
{
    npqueue_from_list(nlist_dll_init(&node->node))->priority = priority;
}

NPLATFORM_INLINE
void npqueue_node_term(struct npqueue_node * node)
{
    nlist_dll_init(&node->node);
}

NPLATFORM_INLINE
uint_fast8_t npqueue_node_priority(const struct npqueue_node * node)
{
    return (node->priority);
}

NPLATFORM_INLINE
void npqueue_init(struct npqueue * q)
{
    nlist_dll_init(&(q)->sentinel);
}

NPLATFORM_INLINE
void npqueue_insert(struct npqueue * q, struct npqueue_node * node)
{
    struct nlist_dll * current;

    for (NLIST_DLL_EACH(current, &q->sentinel)) {
        if (npqueue_from_list(current)->priority < node->priority) {
            break;
        }
    }
    nlist_dll_add_after(current, &node->node);
}

NPLATFORM_INLINE
void npqueue_remove(struct npqueue_node * node)
{
    nlist_dll_remove(&node->node);
}

NPLATFORM_INLINE
bool npqueue_is_empty(const struct npqueue * q)
{
	return (nlist_dll_is_empty(&q->sentinel));
}

NPLATFORM_INLINE
struct npqueue_node * npqueue_first(struct npqueue * q)
{
    return (npqueue_from_list(nlist_dll_first(&q->sentinel)));
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_QUEUE_PQUEUE_H_ */
