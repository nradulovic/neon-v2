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

/** @brief    	Priority sorted queue structure.
 *  @api
 */
struct npqueue
{
    struct nlist_dll sentinel;
};

/** @brief    	Priority sorted queue node structure.
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
 *  @brief      Functions for manipulating the queue node structure.
 *  @{
 */

/** @brief    	Convert a list entry to node entry.
 *  @param     	node
 *      		Pointer to node member of priority sorted queue node structure.
 *  @return    	Pointer to priority queue node structure.
 *  @api
 */
#define npqueue_from_list(a_list) NLIST_ENTRY((a_list), struct npqueue_node, node)

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
struct npqueue_node * npqueue_node_init(struct npqueue_node * node,
        uint_fast8_t priority);

/** @brief    	Terminate a node.
 *
 *  The function will re-initialize the node and set the priority to zero.
 *
 *  @param     	node
 *      		Pointer to a node structure.
 */
void npqueue_node_term(struct npqueue_node * node);

/** @brief      Get a node priority.
 *  @param      node
 *              Pointer to a node structure.
 *  @return     An 8-bit unsigned integer number representing this node
 *              priority.
 *  @api
 */
#define npqueue_node_priority(a_node)  (a_node)->priority

#define npqueue_node_set_priority(a_node, a_priority) (a_node)->priority = (a_priority)

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
uint_fast8_t npqueue_node_mod_priority(struct npqueue_node * node,
    	uint_fast8_t priority);

/** @} */
/*---------------------------------------------------------------------------*/
/** @defgroup   npqueue_node Priority sorted queue
 *  @brief      Functions for manipulating the queue.
 *  @{
 */

/** @brief      Initialize a queue.
 *  @param      queue
 *              Pointer to queue structure.
 *  @api
 */
#define npqueue_init(a_queue)   nlist_dll_init(&(a_queue)->sentinel)

/** @brief      Insert a node into the queue using sorting method.
 *  @param      queue
 *              Pointer to queue structure.
 *  @param      node
 *              Pointer to node structure.
 *  @api
 */
void npqueue_insert_sorted(struct npqueue * queue, struct npqueue_node * node);

/** @brief      Insert a node into the queue using the fifo method.
 *  @param      queue
 *              Pointer to queue structure.
 *  @param      node
 *              Pointer to node structure.
 *  @api
 */
void npqueue_insert_fifo(struct npqueue * queue, struct npqueue_node * node);

/** @brief      Remove the node from queue.
 *  @param      node
 *              Pointer to node structure.
 *  @api
 */
struct npqueue_node * npqueue_remove_first(struct npqueue * queue);

/** @brief      Test if queue is empty.
 *  @param      queue
 *              Pointer to queue structure.
 *  @return     Boolean type
 *  @retval     - true - Queue @a queue is empty.
 *  @retval     - false - Queue @a queue is not empty.
 *  @api
 */
#define npqueue_is_empty(a_queue)  nlist_dll_is_empty(&(a_queue)->sentinel)

/** @brief      Return a pointer to a node with highest priority node in queue.
 *  @param      queue
 *              Pointer to queue structure.
 *  @return     Return a pointer to a node with highest priority node in queue.
 *  @api
 */
#define npqueue_first(a_queue) npqueue_from_list(nlist_dll_first(&(a_queue)->sentinel))

/** @} */
#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_QUEUE_PQUEUE_H_ */
