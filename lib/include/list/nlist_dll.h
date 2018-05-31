/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
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
 *  @brief       Doubly Linked Lists (DLL) header
 *
 *  @addtogroup  nlist
 *  @{
 */
/** @defgroup    nlist_dll Doubly Linked Lists (DLL)
 *  @brief       Doubly Linked Lists (DLL).
 *
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NLIST_DLL_H_
#define NLIST_DLL_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "port/nport_platform.h"
#include "list/nlist.h"

#ifdef __cplusplus
extern "C" {
#endif

#define nlist_dll_is_null(list)                                             \
    ((list)->next == NULL)

/** @brief      Macro to get the first element in list pointed by @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_dll_first(sentinel)       nlist_dll_next(sentinel)

/** @brief      Helper macro, get the last element in list pointed by
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_dll_last(sentinel)        nlist_dll_prev(sentinel)

/** @brief      Helper macro, add a node @a node at list head pointed by 
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_dll_add_head(sentinel, node)                                  \
        nlist_dll_add_before(sentinel, node)

/** @brief      Helper macro, add a node @a node at list tail pointed by 
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nlist_dll_add_tail(sentinel, node)                                  \
        nlist_dll_add_after(sentinel, node)

/** @brief      Construct for @a FOR loop to iterate over each element in a
 *              list.
 *
 *  @code
 *  struct nlist_dll * current;
 *  struct nlist_dll * sentinel = &g_list_sentinel.list;
 *
 *  for (nlist_dll_EACH(current, sentinel)) {
 *      ... do something with @a current (excluding remove)
 *  }
 *  @endcode
 */
#define NLIST_DLL_EACH(current, sentinel)                                      \
    current = nlist_dll_first(sentinel); current != (sentinel);                \
    current = nlist_dll_next(current)

/** @brief      Construct for FOR loop to iterate over each element in list
 *              backwards.
 *
 *  @code
 *  struct nlist_dll * current;
 *  struct nlist_dll * sentinel = &g_list_sentinel.list;
 *
 *  for (nlist_dll_EACH_BACKWARDS(current, sentinel)) {
 *      ... do something with current (excluding remove)
 *  }
 *  @endcode
 */
#define NLIST_DLL_EACH_BACKWARDS(current, sentinel)                            \
    current = nlist_dll_last(sentinel); current != (sentinel);                 \
    current = nlist_dll_prev(current)

/** @brief      Construct for FOR loop to iterate over each element in list
 *              which is safe against element removal.
 *
 *  @code
 *  struct nlist_dll * current;
 *  struct nlist_dll * iterator;
 *  struct nlist_dll * sentinel = &g_list_sentinel.list;
 *
 *  for (nlist_dll_EACH_SAFE(current, iterator, sentinel)) {
 *      ... do something with current (including remove)
 *  }
 *  @endcode
 */
#define NLIST_DLL_EACH_SAFE(current, iterator, sentinel)                    \
    current = nlist_dll_first(sentinel), iterator = nlist_dll_next(current);\
    current != (sentinel);                                                  \
    current = iterator, iterator = nlist_dll_next(iterator)

/** @brief      Doubly-linked list structure
 */
struct nlist_dll
{
    struct nlist_dll *          next;       /**< Next node in the list.*/
    struct nlist_dll *          prev;       /**< Previous node in the list.*/
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
 prev <--|     |
         +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
      +-----------+
      |  +-----+  |
      +->|     |--+
         |  N  |
      +--|     |<-+
      |  +-----+  |
      +-----------+
 @endverbatim
 */
NPLATFORM_INLINE
struct nlist_dll * nlist_dll_init(struct nlist_dll * node)
{
    node->next = node;
    node->prev = node;

    return (node);
}

/** @brief      Return the next node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Next node.
 */
NPLATFORM_INLINE
struct nlist_dll * nlist_dll_next(const struct nlist_dll * node)
{
    return (node->next);
}

/** @brief      Return previous node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Previous node.
 */
NPLATFORM_INLINE
struct nlist_dll * nlist_dll_prev(const struct nlist_dll * node)
{
    return (node->prev);
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
 prev<--|     |<---|     |<---|     |             |     |
        +-----+    +-----+    +-----+             +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |--->|     |-->next
        |  1  |    |  N  |    |  C  |    |  2  |
 prev<--|     |<---|     |<---|     |<---|     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 */
NPLATFORM_INLINE
struct nlist_dll * nlist_dll_add_after(struct nlist_dll * current,
        struct nlist_dll * node)
{
    node->next          = current;
    node->prev          = current->prev;
    current->prev->next = node;
    current->prev       = node;

    return (node);
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
 prev<--|     |<---|     |<---|     |             |     |
        +-----+    +-----+    +-----+             +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |--->|     |-->next
        |  1  |    |  C  |    |  N  |    |  2  |
 prev<--|     |<---|     |<---|     |<---|     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 */
NPLATFORM_INLINE
struct nlist_dll * nlist_dll_add_before(struct nlist_dll * current,
        struct nlist_dll * node)
{
    node->prev          = current;
    node->next          = current->next;
    current->next->prev = node;
    current->next       = node;

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
 prev<--|     |<---|     |<---|     |
        +-----+    +-----+    +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
                                     +-----------+
        +-----+    +-----+           |  +-----+  |
        |     |--->|     |-->next    +->|     |--+
        |  1  |    |  2  |              |  N  |
 prev<--|     |<---|     |           +--|     |
        +-----+    +-----+           |  +-----+
                                    ———
 @endverbatim
 */
NPLATFORM_INLINE
void nlist_dll_remove(struct nlist_dll * node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;

    /* NOTE:
     * Next pointer must point to itself, since it may be checked by
     * nlist_dll_is_empty() function.
     */
    node->next = node;
    /* NOTE:
     * During debugging it is easier to catch errors with NULL pointer.
     */
    node->prev = NULL;
}

/** @brief      Check if a list @a node is empty or not.
 *  @param[in]  node
 *              A list sentinel.
 *  @return     List state:
 *  @retval     true - The list is empty.
 *  @retval     false - The list contains at least one node.
 */
NPLATFORM_INLINE
bool nlist_dll_is_empty(const struct nlist_dll * node)
{
    return (!!(node->next == node));
}

/** @brief      Rotate list (S) to left
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |<---|     |-->next
        |  1  |    |  S  |    |  2  |    |  3  |
 prev<--|     |<---|     |<---|     |--->|     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |<---|     |-->next
        |  1  |    |  2  |    |  S  |    |  3  |
 prev<--|     |<---|     |<---|     |--->|     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 *  @note       This function will not work correctly on empty lists. Before
 *              calling this function first check the list with
 *              @ref nlist_dll_is_empty function.
 *  @code
 *  if (!nlist_dll_is_empty(&my_list) {
 *      nlist_dll_rotate_left(&my_list);
 *  }
 *  @endcode
 */
NPLATFORM_INLINE
void nlist_dll_rotate_left(struct nlist_dll * list)
{
    struct nlist_dll *             first;

    first = list->next;
    nlist_dll_remove(first);
    nlist_dll_add_before(list, first);
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NLIST_DLL_H_ */
