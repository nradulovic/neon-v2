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
/** @defgroup   nlqueue Lightweight queue
 *  @brief      Lightweight queue
 *  @{
 */

#ifndef NEON_LQUEUE_H_
#define NEON_LQUEUE_H_

#include <stdbool.h>
#include <stdint.h>

#include "sys/nport.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Lightweight queue custom structure.
 *
 *  Contains the Base structure and buffer of type @a T with @a elements
 *  number of elements in that buffer. The buffer contains only pointers
 *  to items, not the actual items. This macro should be used to define a
 *  custom @a nlqueue structure.
 *
 *  @param      T
 *              Type of items in this queue.
 *  
 *  @code
 *  struct event_queue nlqueue(void *, 16);
 *  @endcode
 *
 *  @note       The macro can accept the parameter @a elements which is
 *              greater than 2 and equal to a number which is power of 2.
 */
#define nlqueue_dynamic(T)                                                  \
    {                                                                       \
        struct nlqueue super;                                               \
        T * np_lq_storage;                                                  \
    }

#define nlqueue_dynamic_storage(T, size)                                    \
    {                                                                       \
        T np_lq_storage[(((size < 2) || !NBITS_IS_POWEROF2(size)) ?         \
            -1 : size)];                                                    \
    }
        
#define nlqueue(T, size)                                                    \
    {                                                                       \
        struct nlqueue super;                                               \
        T np_lq_storage[(((size < 2) || !NBITS_IS_POWEROF2(size)) ?         \
            -1 : size)];                                                    \
    }
        

/** @brief      Lightweight base structure.
 *  @notapi
 */
struct NPLATFORM_ALIGN(NARCH_ALIGN, nlqueue)
{
    uint_fast8_t                head;
    uint_fast8_t                tail;
    uint_fast8_t                empty;
    uint_fast8_t                mask;
};

/** @brief      Initialize a dynamic queue structure
 *  @param      Q
 *              Pointer to dynamically allocated lightweight queue.
 *  @param      a_size_bytes
 *              The size of storage in bytes.
 *  @param      a_storage
 *              Pointer to allocated storage.
 *  @mseffect
 */
#define NLQUEUE_INIT_DYNAMIC(Q, a_size_bytes, a_storage)                    \
        do {                                                                \
            np_lqueue_super_init(                                           \
                    &(Q)->super,                                            \
                    (a_size_bytes) / sizeof(*(Q)->np_lq_storage));          \
            (Q)->np_lq_storage = (a_storage);                               \
        } while (0)

/** @brief      Initialize a static queue structure
 *  @param      Q
 *              Pointer to statically allocated lightweight queue.
 *  @mseffect
 */
#define NLQUEUE_INIT(Q)                                                     \
        np_lqueue_super_init(                                               \
                &(Q)->super,                                                \
                NBITS_ARRAY_SIZE((Q)->np_lq_storage))

/** @brief      Put an item to queue in FIFO mode.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @mseffect
 */
#define NLQUEUE_IDX_FIFO(Q)             nlqueue_super_idx_fifo(&(Q)->super)

/** @brief      Put an item to queue in LIFO mode.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @note       Before calling this function ensure that queue is not full, see
 *              @ref NLQUEUE_IS_FULL.
 *  @mseffect
 */
#define NLQUEUE_IDX_LIFO(Q)             nlqueue_super_idx_lifo(&(Q)->super)

/** @brief      Get an item from the queue buffer.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @note       Before calling this function ensure that queue has an item. See
 *              @ref NLQUEUE_IS_EMPTY.
 *  @mseffect
 */
#define NLQUEUE_IDX_GET(Q)              nlqueue_super_idx_get(&(Q)->super)

/** @brief      Reference an object from queue storage.
 *  @param      Q
 *              Ponter to lightweight queue.
 *  @param      a_index
 *              Index of an object in the queue storage.
 *  @return     A object with given index in queue storage.
 */
#define NLQUEUE_IDX_REFERENCE(Q, a_index)                                   \
        (Q)->np_lq_storage[(a_index)]

/** @brief      Put an item to queue in FIFO mode.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @note       Before calling this function ensure that queue is not full, see
 *              @ref NLQUEUE_IS_FULL.
 *  @mseffect
 */
#define NLQUEUE_PUT_FIFO(Q, a_item)                                         \
        do {                                                                \
            (Q)->np_lq_storage[NLQUEUE_IDX_FIFO(Q)] = (a_item);             \
        } while (0)

/** @brief      Put an item to queue in LIFO mode.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @note       Before calling this function ensure that queue is not full, see
 *              @ref NLQUEUE_IS_FULL.
 *  @mseffect
 */
#define NLQUEUE_PUT_LIFO(Q, a_item)                                         \
        do {                                                                \
            (Q)->np_lq_storage[NLQUEUE_IDX_LIFO(Q)] = (a_item);             \
        } while (0)

/** @brief      Get an item from the queue buffer.
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @note       Before calling this function ensure that queue has an item. See
 *              @ref NLQUEUE_IS_EMPTY.
 *  @mseffect
 */
#define NLQUEUE_GET(Q)                                                      \
        (Q)->np_lq_storage[nlqueue_super_idx_get(&(Q)->super)]

/** @brief      Peek to queue head; the item is not removed from queue.
 *
 *  Get the pointer to head item in the queue. The item is not removed from
 *  queue buffer.
 * 
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @mseffect
 */
#define NLQUEUE_HEAD(Q)                                                     \
        (Q)->np_lq_storage[np_lqueue_super_head(&(Q)->super)]

/** @brief      Peek to queue tail; the item is not removed from queue.
 *
 *  Get the pointer to tail item in the queue. The item is not removed from
 *  queue buffer.
 *
 *  @param      Q
 *              Pointer to lightweight queue.
 *  @mseffect
 */
#define NLQUEUE_TAIL(Q)                                                     \
        (Q)->np_lq_storage[np_lqueue_super_tail(&(Q)->super)]

/** @brief      Returns the queue buffer size in number of elements.
 *  @param      Q
 *              Pointer to lightweight queue.
 */
#define NLQUEUE_SIZE(Q)                 (Q)->super.mask + 1u

/** @brief      Returns the current number of free elements in queue buffer.
 *  @param      Q
 *              Pointer to lightweight queue.
 */
#define NLQUEUE_EMPTY(Q)                (Q)->super.empty

/** @brief      Return true if queue is full else false.
 *  @param      Q
 *              Pointer to lightweight queue.
 */
#define NLQUEUE_IS_FULL(Q)              (!NLQUEUE_EMPTY(Q))

/** @brief      Return true if queue is empty else false.
 *  @param      Q
 *              Pointer to lightweight queue.
 */
#define NLQUEUE_IS_EMPTY(Q)             (NLQUEUE_EMPTY(Q) == NLQUEUE_SIZE(Q))

/** @brief      Return true if queue has only single element.
 *  @param      Q
 *              Pointer to lightweight queue.
 */
#define NLQUEUE_IS_FIRST(Q)                                                 \
        ((Q)->super.empty == (Q)->super.mask)

/** @brief      Initialise the base queue structure.
 *  @param      lqs
 *              Pointer to lightweight queue super.
 *  @param      elements
 *  @notapi
 */
void np_lqueue_super_init(struct nlqueue * lqs, uint8_t elements);

/** @brief      Put an item to queue in FIFO mode.
 *  @param      qb
 *              Pointer to lightweight queue base.
 *  @return     Index of the item where it should be put.
 *  @notapi
 */
NPLATFORM_INLINE
int_fast8_t nlqueue_super_idx_fifo(struct nlqueue * qb)
{
    int_fast8_t retval;
    
    if (qb->empty != 0u) {
        qb->empty--;
        retval = qb->tail++;
        qb->tail &= qb->mask;
    } else {
        retval = -1;
    }
    return retval;
}

/** @brief      Put an item to queue in LIFO mode.
 *  @param      qb
 *              Pointer to lightweight queue base.
 *  @return     Index of the item where it should be put.
 *  @notapi
 */
NPLATFORM_INLINE
int32_t nlqueue_super_idx_lifo(struct nlqueue * qb)
{
    int32_t retval;
    
    if (qb->empty != 0u) {
        qb->empty--;
        retval = qb->head--;
        qb->head &= qb->mask;
    } else {
        retval = -1;
    }
    return retval;
}

/** @brief      Get an item from the queue buffer.
 *  @param      qb
 *              Pointer to lightweight queue base.
 *  @return     Index of the item which was got from the queue.
 *  @notapi
 */
NPLATFORM_INLINE
int_fast8_t nlqueue_super_idx_get(struct nlqueue * qb)
{
    qb->head++;
    qb->head &= qb->mask;
    qb->empty++;

    return qb->head;
}

/** @brief      Peek to queue head; the item is not removed from queue.
 *  @param      qb
 *              Pointer to lightweight queue base.
 *  @return     Index of the item where the queue head is located.
 *  @notapi
 */
int_fast8_t np_lqueue_super_head(const struct nlqueue * qb);

/** @brief      Peek to queue head; the item is not removed from queue.
 *  @param      qb
 *              Pointer to lightweight queue base.
 *  @return     Index of the item where the queue tail is located.
 *  @notapi
 */
int_fast8_t np_lqueue_super_tail(const struct nlqueue * qb);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_LQUEUE_H_ */
