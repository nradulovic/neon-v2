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

#include "../../kernel/include/nbits.h"
#include "../../kernel/include/nport_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief    	Lightweight base structure.
 *  @notapi
 */
struct np_lqueue_base
{
    uint_fast8_t head;
    uint_fast8_t tail;
    uint_fast8_t empty;
    uint_fast8_t mask;
};

/** @brief    	Lightweight queue custom structure.
 *  
 *  Contains the Base structure and buffer of type @a T with @a elements
 *  number of elements in that buffer. The buffer contains only pointers
 *  to items, not the actual items. This macro should be used to define a
 *  custom @a nlqueue structure.
 *  
 *  @param    	T
 *    			Type of items in this queue.
 *  @param    	elements
 *    			Number of elements in queue buffer.
 *
 *  @note    	The macro can accept the parameter @a elements which is
 *              greater than 2 and equal to a number which is power of 2.
 *  @api
 */
#define nlqueue(T, elements)     											\
    struct nlqueue_ ## T { 													\
    	struct np_lqueue_base base; 										\
    	T np_qb_buffer[	((elements < 2) || !NBITS_IS_POWEROF2(elements)) ?  \
    		-1 : elements]; 												\
    }

/** @brief      Initialize a queue structure
 *  @api
 */
#define NLQUEUE_INIT(Q)     												\
    np_lqueue_base_init(&(Q)->base, 									    \
    		sizeof((Q)->np_qb_buffer) / sizeof((Q)->np_qb_buffer[0]))

/** @brief      Put an item to queue in FIFO mode.
 *  @note       Before calling this function ensure that queue is not full, see
 *     			@ref nqueue_is_full.
 *  @api
 */
#define NLQUEUE_PUT_FIFO(Q, item)     										\
    (Q)->np_qb_buffer[np_lqueue_base_put_fifo(&(Q)->base)] = (item)

/** @brief      Put an item to queue in LIFO mode.
 *  @note       Before calling this function ensure that queue is not full, see
 *     			@ref nqueue_is_full.
 *  @api
 */
#define NLQUEUE_PUT_LIFO(Q, item)     										\
    (Q)->np_qb_buffer[np_lqueue_base_put_lifo(&(Q)->base)] = (item)

/** @brief      Get an item from the queue buffer.
 *  @note       Before calling this function ensure that queue has an item. See 
 *              @ref nqueue_is_empty.
 *  @api
 */ 
#define NLQUEUE_GET(Q)    													\
    (Q)->np_qb_buffer[np_lqueue_base_get(&(Q)->base)]

/** @brief      Peek to queue head; the item is not removed from queue.
 *  
 *  Get the pointer to head item in the queue. The item is not removed from
 *  queue buffer.
 *
 *  @api
 */
#define NLQUEUE_HEAD(Q)    													\
    (Q)->np_qb_buffer[np_lqueue_base_head(&(Q)->base)]

#define NLQUEUE_TAIL(Q)    													\
    (Q)->np_qb_buffer[np_lqueue_base_tail(&(Q)->base)]

/** @brief         Returns the buffer size in number of elements.
 *  @api
 */
#define NLQUEUE_SIZE(Q)    				(Q)->base.mask + 1u

/** @brief      Returns the current number of free elements in queue buffer.
 *  @api
 */
#define NLQUEUE_EMPTY(Q)    			(Q)->base.empty

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
void np_lqueue_base_init(struct np_lqueue_base * qb, uint32_t elements)
{
    qb->head = 0u;
    qb->tail = 0u;
    qb->empty = elements;
    qb->mask = elements - 1u;
}

NPLATFORM_INLINE
uint32_t np_lqueue_base_put_fifo(struct np_lqueue_base * qb)
{
    qb->tail--;
    qb->tail &= qb->mask;
    qb->empty--;
    
    return (qb->tail);
}

NPLATFORM_INLINE
uint32_t np_lqueue_base_put_lifo(struct np_lqueue_base * qb)
{
    uint32_t retval;
    
    retval = qb->head++;
    qb->head &= qb->mask;
    qb->empty--;
    
    return (retval);
}

NPLATFORM_INLINE
uint32_t np_lqueue_base_get(struct np_lqueue_base * qb)
{
    uint32_t retval;

    retval = qb->tail++;
    qb->tail &= qb->mask;
    qb->empty++;

    return (retval);
}

NPLATFORM_INLINE
uint32_t np_lqueue_base_head(const struct np_lqueue_base * qb)
{
    uint32_t real_head;
    
    real_head = qb->head;
    real_head--;
    real_head &= qb->mask;
    
    return (real_head);
}

NPLATFORM_INLINE
uint32_t np_lqueue_base_tail(const struct np_lqueue_base * qb)
{
    return (qb->tail);
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_QUEUE_LQUEUE_H_ */

