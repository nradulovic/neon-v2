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
 *  @brief       Lightweight queue
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_lqueue Lightweight queue
 *  @brief       Lightweight queue.
 *  @{
 */
/*---------------------------------------------------------------------------*/

#ifndef NEON_QUEUE_LQUEUE_H_
#define NEON_QUEUE_LQUEUE_H_

#include <stdint.h>
#include <stdbool.h>

#include "nport_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t nlqueue_idx;

/** @brief    	Lightweight proxy structure.
 *  @api
 */
struct nlqueue
{
	nlqueue_idx head;
	nlqueue_idx tail;
	nlqueue_idx empty;
	nlqueue_idx mask;
};


/** @brief    	Lightweight queue custom structure.
 *  
 *  Contains the Base structure and buffer of type @a T with @a items
 *  number of items in that buffer. The buffer contains only pointers
 *  to items, not the actual items. This macro should be used to define a
 *  custom @a nlqueue structure.
 *  
 *  @param    	T
 *    			Type of items in this queue.
 *  @param    	no_items
 *    			Number of items in queue buffer.
 *
 *  @note    	The macro can accept the parameter @a no_items which is
 *              greater than 2 and equal to a number which is a power of 2.
 *  @api
 */
#define NLQUEUE_TEMPLATE(T, no_items)     									\
    { 																		\
    	struct nlqueue proxy; 												\
    	T items[no_items]; 													\
    }

#define NLQUEUE_PROXY(Q)				&((Q)->proxy)

#define NLQUEUE_ITEM_EXCHG(Q, idx)		(Q)->items[idx]

#define NLQUEUE_

/** @brief      Initialize a queue structure
 *  @api
 */
#define NLQUEUE_INIT(Q)     												\
    nlqueue_init(&(Q)->proxy, 									    \
    		sizeof((Q)->items) / sizeof((Q)->items[0]))

#define nnlqueue_init(T, Q)													\
	do {																	\
		T * this = (Q);														\
		nlqueue_init(														\
				&this->proxy, sizeof(this->items) / sizeof(this->items[0]));\
	} while (0)

/** @brief      Put an item to queue in FIFO mode.
 *  @note       Before calling this function ensure that queue is not full, see
 *     			@ref nlqueue_is_full.
 *  @api
 */
#define NLQUEUE_PUT_FIFO(T, Q, item)     									\
	do {																	\
		T * this = (Q);														\
		this->items[nlqueue_put_fifo(&this->proxy)] = (item);				\
	} while (0)

/** @brief      Put an item to queue in LIFO mode.
 *  @note       Before calling this function ensure that queue is not full, see
 *     			@ref nqueue_is_full.
 *  @api
 */
#define NLQUEUE_PUT_LIFO(Q, item)     										\
    (Q)->items[nlqueue_put_lifo(&(Q)->proxy)] = (item)

/** @brief      Get an item from the queue buffer.
 *  @note       Before calling this function ensure that queue has an item. See 
 *              @ref nqueue_is_empty.
 *  @api
 */ 
#define NLQUEUE_GET(Q)    													\
    (Q)->items[nlqueue_get(&(Q)->proxy)]

/** @brief      Peek to queue head; the item is not removed from queue.
 *  
 *  Get the pointer to head item in the queue. The item is not removed from
 *  queue buffer.
 *
 *  @api
 */
#define NLQUEUE_HEAD(Q)    													\
    (Q)->items[nlqueue_peek_head(&(Q)->proxy)]

#define NLQUEUE_TAIL(Q)    													\
    (Q)->items[nlqueue_peek_tail(&(Q)->proxy)]

/** @brief         Returns the buffer size in number of items.
 *  @api
 */
#define NLQUEUE_SIZE(Q)    				(Q)->proxy.mask + 1u

/** @brief      Returns the current number of free items in queue buffer.
 *  @api
 */
#define NLQUEUE_EMPTY(Q)    			(Q)->proxy.empty

/** @brief      Return true if queue is full else false.
 *  @api
 */
#define NLQUEUE_IS_FULL(Q)    			(!NLQUEUE_EMPTY(Q))

/** @brief       Return true if queue is empty else false.
 *     @api
 */
#define NLQUEUE_IS_EMPTY(Q)    												\
    (NLQUEUE_EMPTY(Q) == NLQUEUE_SIZE(Q))

NPLATFORM_INLINE
void nlqueue_init(struct nlqueue * qb, nlqueue_idx items)
{
    qb->head = 0u;
    qb->tail = 0u;
    qb->empty = items;
    qb->mask = items - 1u;
}

NPLATFORM_INLINE
nlqueue_idx nlqueue_put_fifo(struct nlqueue * qb)
{
	qb->empty--;
	qb->tail--;

	if (qb->tail > qb->mask) {
		qb->tail = qb->mask;
	}

    return (qb->tail);
}

NPLATFORM_INLINE
nlqueue_idx nlqueue_put_lifo(struct nlqueue * qb)
{
	nlqueue_idx retval;

    qb->empty--;
    retval = qb->head;

    qb->head++;

    if (qb->head > qb->mask) {
    	qb->head = 0u;
    }
    
    return (retval);
}

NPLATFORM_INLINE
nlqueue_idx nlqueue_get(struct nlqueue * qb)
{
	nlqueue_idx retval;

    retval = qb->tail;
    qb->tail++;

    if (qb->tail > qb->mask) {
		qb->tail = 0u;
	}
    qb->empty++;

    return (retval);
}

NPLATFORM_INLINE
nlqueue_idx nlqueue_peek_head(const struct nlqueue * qb)
{
	nlqueue_idx real_head;
    
    real_head = qb->head;
    real_head--;
    real_head &= qb->mask;
    
    return (real_head);
}

NPLATFORM_INLINE
nlqueue_idx nlqueue_peek_tail(const struct nlqueue * qb)
{
    return (qb->tail);
}

NPLATFORM_INLINE
nlqueue_idx nlqueue_empty(const struct nlqueue * qb)
{
	return qb->empty;
}

NPLATFORM_INLINE
nlqueue_idx nlqueue_size(const struct nlqueue * qb)
{
	return qb->mask + 1u;
}

NPLATFORM_INLINE
bool nlqueue_is_full(const struct nlqueue * qb)
{
	return qb->empty == 0 ? true : false;
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_QUEUE_LQUEUE_H_ */

