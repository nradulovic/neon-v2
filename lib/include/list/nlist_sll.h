/*
 * Neon
 * Copyright (C)  2017  Nenad Radulovic
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Singly Linked Lists (SLL) header
 *
 *  @addtogroup  nlist
 *  @{
 */
/** @defgroup    nlist_sll Singly Linked Lists (SLL)
 *  @brief       Singly Linked Lists (SLL).
 *
 *  @{
 */
/*---------------------------------------------------------------------------*/

#ifndef NLIST_SLL_H_
#define NLIST_SLL_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "port/nport_platform.h"
#include "list/nlist.h"

#ifdef __cplusplus
extern "C" {
#endif

#define nlist_sll_is_null(list)                                             \
    ((list)->next == NULL)

/** @brief      Macro to get the first element in list pointed by @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_sll_first(sentinel)       nlist_sll_next(sentinel)

/** @brief      Helper macro, get the last element in list pointed by
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_sll_last(sentinel)        nlist_sll_prev(sentinel)

/** @brief      Helper macro, add a node @a node at list head pointed by 
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_sll_add_head(sentinel, node)                                  \
        nlist_sll_add_before(sentinel, node)

/** @brief      Helper macro, add a node @a node at list tail pointed by 
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_sll_add_tail(sentinel, node)                                  \
        nlist_sll_add_after(sentinel, node)

/** @brief      Construct for @a FOR loop to iterate over each element in a
 *              list.
 *
 *  @code
 *  struct nlist_sll * current;
 *  struct nlist_sll * sentinel = &g_list_sentinel.list;
 *
 *  for (NLIST_SLL_EACH(current, sentinel)) {
 *      ... do something with @a current (excluding remove)
 *  }
 *  @endcode
 */
#define NLIST_SLL_EACH(current, sentinel)                                   \
    current = nlist_sll_first(sentinel); current != (sentinel);             \
    current = nlist_sll_next(current)

/** @brief      Construct for @a FOR loop to iterate over each element in list
 *              backwards.
 *
 *  @code
 *  struct nlist_sll * current;
 *  struct nlist_sll * sentinel = &g_list_sentinel.list;
 *
 *  for (NLIST_SLL_EACH_BACKWARDS(current, sentinel)) {
 *      ... do something with current (excluding remove)
 *  }
 *  @endcode
 */
#define NLIST_SLL_EACH_BACKWARDS(current, sentinel)                         \
    current = nlist_sll_last(sentinel); current != (sentinel);              \
    current = nlist_sll_prev(current)

/** @brief      Construct for FOR loop to iterate over each element in list
 *              which is safe against element removal.
 *
 *  @code
 *  struct nlist_sll * current;
 *  struct nlist_sll * iterator;
 *  struct nlist_sll * sentinel = &g_list_sentinel.list;
 *
 *  for (NLIST_SLL_EACH_SAFE(current, iterator, sentinel)) {
 *      ... do something with current (including remove)
 *  }
 *  @endcode
 */
#define NLIST_SLL_EACH_SAFE(current, iterator, sentinel)                    \
    current = nlist_sll_first(sentinel), iterator = nlist_sll_next(current);\
    current != (sentinel);                                                  \
    current = iterator, iterator = nlist_sll_next(iterator)

/** @brief      Singly Linked List (SLL) structure.
 */
struct nlist_sll
{
    struct nlist_sll *          next;             /**< Next node in the list.*/
};

/** @brief      Initialize a list sentinel or node.
 *  @param[in]  node
 *              A list sentinel or node.
 *
 *  Before calling this function:
 @verbatim
    +-----+
    |     |--> next
    |  N  |
    |     |
    +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
 +-----------+
 |  +-----+  |
 +->|     |--+
    |  N  |
    |     |   
    +-----+   
              
 @endverbatim
 */
NPLATFORM_INLINE
struct nlist_sll * nlist_sll_init(struct nlist_sll * node)
{
    node->next = node;

    return (node);
}

/** @brief      Return the next node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Next node.
 */
NPLATFORM_INLINE
struct nlist_sll * nlist_sll_next(const struct nlist_sll * node)
{
    return (node->next);
}

/** @brief      Return previous node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Previous node.
 */
NPLATFORM_INLINE
struct nlist_sll * nlist_sll_prev(struct nlist_sll * const node)
{
    struct nlist_sll * tmp = node;

    while (tmp->next != node) {
        tmp = tmp->next;
    }
    return (tmp);
}

/** @brief      Insert node (N) after current node (C).
 *  @param[in]  current
 *              A list node or sentinel.
 *  @param[in]  node
 *              A list node.
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+             +-----+
        |     |--->|     |--->|     |-->next      |     |
        |  1  |    |  C  |    |  2  |             |  N  |
        |     |    |     |    |     |             |     |
        +-----+    +-----+    +-----+             +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |--->|     |-->next
        |  1  |    |  N  |    |  C  |    |  2  |
        |     |    |     |    |     |    |     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 */
NPLATFORM_INLINE
void nlist_sll_add_after(struct nlist_sll * current, struct nlist_sll * node)
{
    struct nlist_sll * prev = nlist_sll_prev(current);

    node->next = prev->next;
    prev->next = node;
}

/** @brief      Insert node (N) before current node (C).
 *  @param[in]  current
 *              A list node or sentinel.
 *  @param[in]  node
 *              A list node.
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+             +-----+
        |     |--->|     |--->|     |-->next      |     |
        |  1  |    |  C  |    |  2  |             |  N  |
        |     |    |     |    |     |             |     |
        +-----+    +-----+    +-----+             +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |--->|     |-->next
        |  1  |    |  C  |    |  N  |    |  2  |
        |     |    |     |    |     |    |     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 */
NPLATFORM_INLINE
struct nlist_sll * nlist_sll_add_before(struct nlist_sll * current, 
        struct nlist_sll * node)
{
    node->next = current->next;    
    current->next = node;

    return (node);
}

/** @brief      Remove a node (N)
 *  @param[in]  node
 *              A list node.
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+
        |     |--->|     |--->|     |-->next
        |  1  |    |  N  |    |  2  |
        |     |    |     |    |     |
        +-----+    +-----+    +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
                                     +-----------+
        +-----+    +-----+           |  +-----+  |
        |     |--->|     |-->next    +->|     |--+
        |  1  |    |  2  |              |  N  |
        |     |    |     |              |     |
        +-----+    +-----+              +-----+
 @endverbatim
 */
NPLATFORM_INLINE
void nlist_sll_remove(struct nlist_sll * node)
{
    struct nlist_sll * prev = nlist_sll_prev(node);

    prev->next = node->next;
    node->next = node;
}

/** @brief      Check if a list @a node is empty or not.
 *  @param[in]  node
 *              A list sentinel.
 *  @return     List state:
 *  @retval     true - The list is empty.
 *  @retval     false - The list contains at least one node.
 */
NPLATFORM_INLINE
bool nlist_sll_is_empty(const struct nlist_sll * node)
{
    return (!!(node->next == node));
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NLIST_SLL_H_ */
