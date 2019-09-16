/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @addtogroup neon
 *  @{
 */
/** @defgroup   npqueue Priority sorted queue
 *  @brief      Priority sorted queue
 *  @{
 */

#ifndef NEON_PSQUEUE_H_
#define NEON_PSQUEUE_H_

#include <stdint.h>

#include "sys/nlist_dll.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup   npqueue_sentinel Priority sorted queue sentinel
 *  @brief      Priority sorted queue sentinel.
 *  @{ */

/** @brief      Priority sorted queue sentinel structure
 */
struct npqueue_sentinel
{
    struct nlist_dll list;                      /**< Head of the queue. */
};

/** @brief      Initialise a queue sentinel object.
 *  @param      a_sentinel
 *              Pointer to priority queue sentinel.
 */
#define npqueue_sentinel_init(a_sentinel)                                   \
        nlist_dll_init(&(a_sentinel)->list)

/** @brief      Terminate a queue sentinel object
 *  @param      a_sentinel
 *              Pointer to priority queue sentinel.
 */
#define npqueue_sentinel_term(a_sentinel)                                   \
        npqueue_sentinel_init(a_sentinel)

/** @brief      Test if queue is empty.
 *  @param      a_sentinel
 *              Pointer to priority queue sentinel.
 *  @return     Boolean type
 *  @retval     true - Queue managed by @a a_sentinel is empty.
 *  @retval     false - Queue managed by @a a_sentinel is not empty.
 *  @mseffect
 */
#define NPQUEUE_SENTINEL_IS_EMPTY(a_sentinel)                              \
        NLIST_DLL_IS_EMPTY(&(a_sentinel)->list)

/** @brief      Head of the queue
 *  @param      a_sentinel
 *              Pointer to priority queue sentinel.
 *  @return     Pointer to head queue node.
 */
#define npqueue_sentinel_head(a_sentinel)                                   \
        npqueue_next(a_sentinel)

/** @brief      Shift the sentinel through list.
 */
void npqueue_sentinel_shift(struct npqueue_sentinel * sentinel);

/** @} */
/** @defgroup   npqueue_node Priority sorted queue node
 *  @brief      Priority sorted queue node.
 *  @{ */

/** @brief      Priority sorted queue node structure.
 *
 *  Each node has a priority attribute. The attribute type is 8-bit unsigned
 *  integer. The highest priority has the value 255. The lowest priority has
 *  value 0.
 */
struct npqueue
{
    struct nlist_dll list;                      /**< Linked list of items */
    uint_fast8_t priority;                      /**< Priotity attribute */
};

/** @brief      Convert a list entry to node entry.
 *  @param      a_node
 *              Pointer to a priority sorted queue node.
 *  @return     Pointer to priority queue node structure.
 */
#define npqueue_from_list(a_node)                                           \
        nlist_dll_entry((a_node), struct npqueue, list)

/** @brief      Initialize a node and define its priority.
 *
 *  A node structure needs to be initialized before it can be used within a
 *  queue.
 *
 *  @param      node
 *              Pointer to a priority sorted queue node.
 *  @param      priority
 *              An 8-bit unsigned integer number specifying this node priority.
 *              The highest priority has the value 255. The lowest priority has
 *              the value is 0.
 *  @return     The pointer @a node.
 */
struct npqueue * npqueue_init(struct npqueue * node, uint_fast8_t priority);

/** @brief      Terminate a node.
 *
 *  The function will re-initialize the node and set the priority to zero.
 *
 *  @param      node
 *              Pointer to a priority sorted queue node.
 */
void npqueue_term(struct npqueue * node);

/** @brief      Get a node priority.
 *  @param      a_node
 *              Pointer to a priority sorted queue node.
 *  @return     An 8-bit unsigned integer number representing this node
 *              priority.
 */
#define npqueue_priority(a_node)        (a_node)->priority

/** @brief      Set a node priority.
 *  @param      a_node
 *              Pointer to a node structure.
 *  @param      a_priority
 *              An 8-bit unsigned integer number representing this node
 *              priority.
 */
#define npqueue_priority_set(a_node, a_priority)                            \
        do {                                                                \
            (a_node)->priority = (a_priority);                              \
        } while (0)

/** @brief      Get a next node from @a a_node.
 *  @param      a_node
 *              Pointer to a priority sorted queue node.
 *  @return     A pointer to next node from @a a_node.
 */
#define npqueue_next(a_node)                                                \
        npqueue_from_list(nlist_dll_next(&(a_node)->list))

/** @brief      Insert a node into the queue using sorting method.
 *  @param      sentinel
 *              Pointer to a priority sorted queue sentinel.
 *  @param      node
 *              Pointer to a priority sorted queue node.
 */
void npqueue_insert_sort(
        struct npqueue_sentinel * sentinel,
        struct npqueue * node);

/** @brief      Insert a node into the queue using the FIFO method.
 *  @param      a_sentinel
 *              Pointer to a priority sorted queue sentinel.
 *  @param      a_node
 *              Pointer to a priority sorted queue node.
 */
#define npqueue_insert_fifo(a_sentinel, a_node)                             \
        nlist_dll_add_after(&(a_sentinel)->list, &(a_node)->list)

/** @brief      Remove the node from queue.
 *  @param      a_node
 *              Pointer to a priority sorted queue node.
 */
#define npqueue_remove(a_node)          nlist_dll_remove(&(a_node)->list)

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_PSQUEUE_H_ */
