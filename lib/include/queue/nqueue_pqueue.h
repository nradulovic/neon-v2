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

/*---------------------------------------------------------------------------*/
/** @defgroup   npqueue_structs Data structures
 *  @brief      Data structures for queue and node objects.
 *  @{
 */

/** @brief		Priority sorted queue structure.
 *  @api
 */
struct npqueue
{
    struct nlist_dll sentinel;
};

/** @brief		Priority sorted queue node structure.
 *
 *  Each node has a priority attribute. The attribute type is 8-bit unsigned
 *  integer. The highest priority has the value 255. The lowest priority has
 *  the value is 0.
 *
 *  @api
 */
struct npqueue_node
{
    struct nlist_dll node;
    uint_fast8_t priority;
};

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   npqueue_node Priority sorted queue node
 *  @brief      Functions for manipulatiog the queue node structure.
 *  @{
 */

/** @brief		Convert a list entry to node entry.
 *  @param 		node
 *  			Pointer to node member of priority sorted queue node structure.
 *  @return		Pointer to priority queue node structure.
 *  @api
 */
NPLATFORM_INLINE
struct npqueue_node * npqueue_from_list(struct nlist_dll * node)
{
    return (NLIST_ENTRY(node, struct npqueue_node, node));
}

/** @brief		Initialize a node and define its priority.
 *
 *  A node structure needs to be initialized before it can be used within a
 *  queue.
 *
 *  @param 		node
 *  			Pointer to a node structure.
 *  @param      priority
 *  			An 8-bit unsigned integer number specifying this node priority.
 *  			The highest priority has the value 255. The lowest priority has
 *  			the value is 0.
 *  @return		The pointer @a node.
 */
NPLATFORM_INLINE
struct npqueue_node * npqueue_node_init(struct npqueue_node * node,
        uint_fast8_t priority)
{
    npqueue_from_list(nlist_dll_init(&node->node))->priority = priority;

    return (node);
}

/** @brief		Terminate a node.
 *
 *  The function will re-initialize the node and set the priority to zero.
 *
 *  @param 		node
 *  			Pointer to a node structure.
 */
NPLATFORM_INLINE
void npqueue_node_term(struct npqueue_node * node)
{
    nlist_dll_init(&node->node);
    node->priority = 0u;
}

/** @brief      Get a node priority.
 *  @param      node
 *              Pointer to a node structure.
 *  @return     An 8-bit unsigned integer number representing this node
 *              priority.
 *  @api
 */
NPLATFORM_INLINE
uint_fast8_t npqueue_node_priority(const struct npqueue_node * node)
{
    return (node->priority);
}

/** @brief      Modify a node priority.
 *  
 *  Return an old priority value and set a new priority.
 *
 *  @param      node
 *              Pointer to a node structure.
 *  @param      priority
 *              New node priority value.
 *  @return     Old node priority value.
 *  @api
 */
NPLATFORM_INLINE
uint_fast8_t npqueue_node_mod_priority(struct npqueue_node * node,
		uint_fast8_t priority)
{
    uint_fast8_t retval;
    
    retval = npqueue_node_priority(node);
    node->priority = priority;

    return (retval);
}

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   npqueue_node Priority sorted queue
 *  @brief      Functions for manipulatiog the queue.
 *  @{
 */

/** @brief      Initialize a queue.
 *  @param      queue
 *              Pointer to queue structure.
 *  @api
 */
NPLATFORM_INLINE
void npqueue_init(struct npqueue * queue)
{
    nlist_dll_init(&queue->sentinel);
}

/** @brief      Insert a node into the queue.
 *  @param      queue
 *              Pointer to queue structure.
 *  @param      node
 *              Pointer to node structure.
 *  @api
 */
NPLATFORM_INLINE
void npqueue_insert(struct npqueue * queue, struct npqueue_node * node)
{
    struct nlist_dll * current;

    for (NLIST_DLL_EACH(current, &queue->sentinel)) {
        if (npqueue_from_list(current)->priority < node->priority) {
            break;
        }
    }
    nlist_dll_add_after(current, &node->node);
}

/** @brief      Remove the node from queue.
 *  @param      node
 *              Pointer to node structure.
 *  @api
 */
NPLATFORM_INLINE
void npqueue_remove(struct npqueue_node * node)
{
    nlist_dll_remove(&node->node);
}

/** @brief      Test if queue is empty.
 *  @param      queue
 *              Pointer to queue structure.
 *  @return     Boolean type
 *  @retval     - true - Queue @a queue is empty.
 *  @retval     - false - Queue @a queue is not empty.
 *  @api
 */
NPLATFORM_INLINE
bool npqueue_is_empty(const struct npqueue * queue)
{
	return (nlist_dll_is_empty(&queue->sentinel));
}

/** @brief      Return a pointer to a node with highest priority node in queue.
 *  @param      queue
 *              Pointer to queue structure.
 *  @return     Return a pointer to a node with highest priority node in queue.
 *  @api
 */
NPLATFORM_INLINE
struct npqueue_node * npqueue_first(struct npqueue * queue)
{
    return (npqueue_from_list(nlist_dll_first(&queue->sentinel)));
}

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_QUEUE_PQUEUE_H_ */