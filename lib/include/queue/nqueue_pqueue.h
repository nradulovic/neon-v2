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
#include "list/nlist_dll.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/** @defgroup   npqueue_structs Data structures
 *  @brief      Data structures for queue and node objects.
 *  @{
 */

/** @brief    	Priority sorted queue node structure.
 *
 *  Each node has a priority attribute. The attribute type is 8-bit unsigned
 *  integer. The highest priority has the value 255. The lowest priority has
 *  the value is 0.
 *
 *  @api
 */
struct npqueue
{
    struct nlist_dll node;
    uint_fast8_t priority;
};

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   npqueue_node Priority sorted queue node
 *  @brief      Functions for manipulating the queue node structure.
 *  @{
 */

/** @brief    	Convert a list entry to node entry.
 *  @param     	node
 *      		Pointer to node member of priority sorted queue node structure.
 *  @return    	Pointer to priority queue node structure.
 *  @api
 */
#define npqueue_from_list(a_list) NLIST_ENTRY((a_list), struct npqueue, node)

/** @brief    	Initialize a node and define its priority.
 *
 *  A node structure needs to be initialized before it can be used within a
 *  queue.
 *
 *  @param     	node
 *      		Pointer to a node structure.
 *  @param      priority
 *      		An 8-bit unsigned integer number specifying this node priority.
 *      		The highest priority has the value 255. The lowest priority has
 *      		the value is 0.
 *  @return    	The pointer @a node.
 */
struct npqueue * npqueue_init(struct npqueue * node,
        uint_fast8_t priority);

/** @brief    	Terminate a node.
 *
 *  The function will re-initialize the node and set the priority to zero.
 *
 *  @param     	node
 *      		Pointer to a node structure.
 */
void npqueue_term(struct npqueue * node);

/** @brief      Get a node priority.
 *  @param      node
 *              Pointer to a node structure.
 *  @return     An 8-bit unsigned integer number representing this node
 *              priority.
 *  @api
 */
#define npqueue_priority(a_node)                                            \
    (a_node)->priority

#define npqueue_set_priority(a_node, a_priority)                            \
    (a_node)->priority = (a_priority)

#define npqueue_next(a_node)                                                \
    npqueue_from_list(nlist_dll_next(&(a_node)->node))

/** @brief      Modify a node priority.
 *  
 *  Return an old priority value and set a new priority.
 *
 *  @note       DO NOT call this function while the node is in some queue. The
 *              node priority can be modified only when the node is not
 *              inserted in any queue.
 *  @param      node
 *              Pointer to a node structure.
 *  @param      priority
 *              New node priority value.
 *  @return     Old node priority value.
 *  @api
 */
uint_fast8_t npqueue_mod_priority(struct npqueue * node, uint_fast8_t priority);

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   npqueue_node Priority sorted queue
 *  @brief      Functions for manipulating the queue.
 *  @{
 */

/** @brief      Insert a node into the queue using sorting method.
 *  @param      queue
 *              Pointer to queue structure.
 *  @param      node
 *              Pointer to node structure.
 *  @api
 */
void npqueue_insert_sorted(struct npqueue * head, struct npqueue * node);

/** @brief      Insert a node into the queue using the FIFO method.
 *  @param      queue
 *              Pointer to queue structure.
 *  @param      node
 *              Pointer to node structure.
 *  @api
 */
#define npqueue_insert_fifo(a_head, a_node)                                 \
    nlist_dll_add_before(&(a_head)->node, &(a_node)->node)

/** @brief      Remove the node from queue.
 *  @param      node
 *              Pointer to node structure.
 *  @api
 */
#define npqueue_remove(a_node)  nlist_dll_remove(&(a_node)->node)

/** @brief      Test if queue is empty.
 *  @param      queue
 *              Pointer to queue structure.
 *  @return     Boolean type
 *  @retval     - true - Queue @a queue is empty.
 *  @retval     - false - Queue @a queue is not empty.
 *  @api
 */
#define npqueue_is_last(a_node) nlist_dll_is_empty(&(a_node)->node)

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_QUEUE_PQUEUE_H_ */
