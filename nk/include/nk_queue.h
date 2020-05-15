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

#ifdef __cplusplus
extern "C" {
#endif

/** @brief    	Lightweight queue custom structure.
 *  
 *  Contains the Base structure and buffer of type @a T with @a items
 *  number of items in that buffer. The buffer contains only pointers
 *  to items, not the actual items. This macro should be used to define a
 *  custom @a nlqueue structure.
 *  
 *  @param    	T
 *    			Type of queue which was defined using @ref NK_QUEUE_INDEFINITE
 *    			macro.
 *  @param    	no_items
 *    			Number of items in queue buffer.
 *  @api
 */
#define NK_QUEUE_INDEFINITE(item_type)										\
		{																	\
			struct nk_queue_index index;									\
			item_type * items;												\
		}

/**
 * @brief		Initialize indefinite queue type.
 *
 * Indefinite queue type is a constrained queue type with unknown or not yet
 * known constraints. Indefinite queue types are usually used to create generic
 * code which works with pointers to queues with different constraints.
 *
 * @param		T
 * 				Type of queue which was defined using @ref NK_QUEUE_INDEFINITE
 *    			macro.
 * @param		qi
 * 				Pointer to indefinite queue instance.
 * @param		item_buffer
 * 				An array of type item which will hold instances of items.
 */
#define NK_QUEUE_INDEFINITE_INIT(qi, item_buffer, item_buffer_size)			\
		do {																\
			nk_queue_index_init(&(qi)->index, item_buffer_size);			\
			(qi)->items = (item_buffer);									\
		} while (0)

/**
 * @brief		Push an item to indefinite queue type in FIFO mode.
 *
 * @param		qi
 * 				Pointer to indefinite queue instance.
 * @param 		item
 * 				Pointer to item which will be pushed into the queue.
 * @pre			The queue must be previously initialized by
 * 				@ref NK_QUEUE_INDEFINITE_INIT or by
 * 				@ref NK_QUEUE_DEFINITE_INIT macro.
 *    			macro.
 * @note      	Before calling this macro ensure that the queue is not full,
 * 				see @ref NK_QUEUE_INDEFINITE_IS_FULL macro.
 */
#define NK_QUEUE_INDEFINITE_PUSH_FIFO(qi, item)								\
		do {																\
			(qi)->items[nk_queue_index_push_fifo(&(qi)->index)] = *(item);	\
		} while (0)

/**
 * @brief		Push an item to indefinite queue type in LIFO mode.
 *
 * @param		qi
 * 				Pointer to indefinite queue instance.
 * @param 		item
 * 				Pointer to item which will be pushed into the queue.
 * @pre			The queue must be previously initialized by
 * 				@ref NK_QUEUE_INDEFINITE_INIT or by
 * 				@ref NK_QUEUE_DEFINITE_INIT macro.
 *    			macro.
 * @note      	Before calling this macro ensure that the queue is not full,
 * 				see @ref NK_QUEUE_INDEFINITE_IS_FULL macro.
 */
#define NK_QUEUE_INDEFINITE_PUSH_LIFO(qi, item)								\
		do {																\
			(qi)->items[nk_queue_index_push_lifo(&(qi)->index)] = *(item);	\
		} while (0)

#define NK_QUEUE_INDEFINITE_GET(qi, item)									\
		do {																\
			*(item) = (qi)->items[nk_queue_index_get(&(qi)->index)];		\
		} while (0)

#define NK_QUEUE_INDEFINITE_PEEK_HEAD(qi, item)								\
		do {																\
			*(item) = (qi)->items[nk_queue_index_peek_head(&(qi)->index)];	\
		} while (0)

#define NK_QUEUE_INDEFINITE_PEEK_TAIL(qi, item)								\
		do {																\
			*(item) = (qi)->items[nk_queue_index_peek_tail(&(qi)->index)];	\
		} while (0)

#define NK_QUEUE_INDEFINITE_SIZE(qi, size)									\
		do {																\
			size_t * q_size = (size);										\
			*q_size = nk_queue_index_size(&(qi)->index);					\
		} while (0)

#define NK_QUEUE_INDEFINITE_EMPTY(qi, empty)								\
		do {																\
			size_t * q_empty = (empty);										\
			*q_empty = nk_queue_index_empty(&(qi)->index);					\
		} while (0)

#define NK_QUEUE_INDEFINITE_IS_FULL(qi, is_full)							\
		do {																\
			bool * q_is_full = (is_full);									\
																			\
			if (nk_queue_index_empty(&(qi)->index) == 0u) {					\
				*q_is_full = true;											\
			} else {														\
				*q_is_full = false;											\
			}																\
		} while (0)

#define NK_QUEUE_INDEFINITE_IS_EMPTY(qi, is_empty)							\
		do {																\
			bool * q_is_empty = (is_empty);									\
																			\
			if (nk_queue_index_empty(&(qi)->index) == 						\
				nk_queue_index_size(&(qi)->index)) { 						\
				*q_is_empty = true;											\
			} else {														\
				*q_is_empty = false;										\
			}																\
		} while (0)

#define NK_QUEUE_DEFINITE(T, no_items)										\
		{																	\
			struct nk_queue_indefinite  									\
				NK_QUEUE_INDEFINITE(T) indefinite;							\
			T item_buffer[no_items];										\
		}

#define NK_QUEUE_DEFINITE_INIT(qd)											\
		do {																\
			NK_QUEUE_INDEFINITE_INIT(										\
					&(qd)->indefinite, 										\
					&(qd)->item_buffer[0],									\
					sizeof((qd)->item_buffer));								\
		} while (0)

#define NK_QUEUE_DEFINITE_PUSH_FIFO(qd, item)								\
			NK_QUEUE_INDEFINITE_PUSH_FIFO(&(qd)->indefinite, item)

#define NK_QUEUE_DEFINITE_PUSH_LIFO(qd, item)								\
			NK_QUEUE_INDEFINITE_PUSH_LIFO(&(qd)->indefinite, item)

#define NK_QUEUE_DEFINITE_GET(qd, item)										\
			NK_QUEUE_INDEFINITE_GET(&(qd)->indefinite, item)

#define NK_QUEUE_DEFINITE_PEEK_HEAD(qd, item)								\
			NK_QUEUE_INDEFINITE_PEEK_HEAD(&(qd)->indefinite, item)

#define NK_QUEUE_DEFINITE_PEEK_TAIL(qd, item)								\
			NK_QUEUE_INDEFINITE_PEEK_TAIL(&(qd)->indefinite, item)

#define NK_QUEUE_DEFINITE_SIZE(qd, size)									\
			NK_QUEUE_INDEFINITE_SIZE(&(qd)->indefinite, size)

#define NK_QUEUE_DEFINITE_EMPTY(qd, empty)									\
			NK_QUEUE_INDEFINITE_EMPTY(&(qd)->indefinite, empty)

#define NK_QUEUE_DEFINITE_EMPTY(qd, empty)									\
			NK_QUEUE_INDEFINITE_EMPTY(&(qd)->indefinite, empty)

#define NK_QUEUE_DEFINITE_IS_FULL(qd, is_full)								\
			NK_QUEUE_INDEFINITE_IS_FULL(&(qd)->indefinite, is_full)

#define NK_QUEUE_DEFINITE_IS_EMPTY(qd, is_empty)							\
			NK_QUEUE_INDEFINITE_IS_EMPTY(&(qd)->indefinite, is_empty)

/** @brief    	Queue index structure
 *  @api
 */
struct nk_queue_index
{
	size_t head;
	size_t tail;
	size_t empty;
	size_t mask;
};

/** @brief       Return true if queue is empty else false.
 *  @api
 */

inline void nk_queue_index_init(struct nk_queue_index * qb, size_t items)
{
    qb->head = 0u;
    qb->tail = 0u;
    qb->empty = items;
    qb->mask = items - 1u;
}

inline size_t nk_queue_index_push_fifo(struct nk_queue_index * qb)
{
	qb->empty--;
	qb->tail--;

	if (qb->tail > qb->mask) {
		qb->tail = qb->mask;
	}

    return (qb->tail);
}

inline size_t nk_queue_index_push_lifo(struct nk_queue_index * qb)
{
	size_t retval;

    qb->empty--;
    retval = qb->head;

    qb->head++;

    if (qb->head > qb->mask) {
    	qb->head = 0u;
    }
    
    return (retval);
}

inline size_t nk_queue_index_get(struct nk_queue_index * qb)
{
	size_t retval;

    retval = qb->tail;
    qb->tail++;

    if (qb->tail > qb->mask) {
		qb->tail = 0u;
	}
    qb->empty++;

    return (retval);
}

inline size_t nk_queue_index_peek_head(const struct nk_queue_index * qb)
{
	size_t real_head;
    
    real_head = qb->head;
    real_head--;
    real_head &= qb->mask;
    
    return (real_head);
}

inline size_t nk_queue_index_peek_tail(const struct nk_queue_index * qb)
{
    return (qb->tail);
}

inline size_t nk_queue_index_empty(const struct nk_queue_index * qb)
{
	return qb->empty;
}

inline size_t nk_queue_index_size(const struct nk_queue_index * qb)
{
	return qb->mask + 1u;
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_QUEUE_LQUEUE_H_ */

