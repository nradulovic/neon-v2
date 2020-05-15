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
 *  @brief       Linked Lists header
 *
 *  @addtogroup  nk_list
 *  @{
 */
/** @defgroup    nk_list Linked Lists
 *  @brief       Linked Lists.
 *
 *  @{
 */
/*---------------------------------------------------------------------------*/


#ifndef NK_LIST_H_
#define NK_LIST_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Helper macro, add a node @a node at list head pointed by 
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nk_list_add_head(sentinel, node)                                  \
        nk_list_add_before(sentinel, node)

/** @brief      Helper macro, add a node @a node at list tail pointed by 
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nk_list_add_tail(sentinel, node)                                  \
        nk_list_add_after(sentinel, node)

/** @brief      Construct for @a FOR loop to iterate over each element in a
 *              list.
 *
 *  @code
 *  struct nk_list * current;
 *  struct nk_list * sentinel = &g_list_sentinel.list;
 *
 *  for (nk_list_EACH(current, sentinel)) {
 *      ... do something with @a current (excluding remove)
 *  }
 *  @endcode
 */
#define NK_LIST_EACH(current, sentinel)                                     \
	    current = nk_list_next(sentinel); 								\
	    current != (sentinel);                                              \
	    current = nk_list_next(current)

/** @brief      Construct for FOR loop to iterate over each element in list
 *              backwards.
 *
 *  @code
 *  struct nk_list * current;
 *  struct nk_list * sentinel = &g_list_sentinel.list;
 *
 *  for (nk_list_EACH_BACKWARDS(current, sentinel)) {
 *      ... do something with current (excluding remove)
 *  }
 *  @endcode
 */
#define NK_LIST_EACH_BACKWARDS(current, sentinel)                           \
		current = nk_list_prev(sentinel); 								\
		current != (sentinel);                                                  \
		current = nk_list_prev(current)

/** @brief      Construct for FOR loop to iterate over each element in list
 *              which is safe against element removal.
 *
 *  @code
 *  struct nk_list * current;
 *  struct nk_list * iterator;
 *  struct nk_list * sentinel = &g_list_sentinel.list;
 *
 *  for (nk_list_EACH_SAFE(current, iterator, sentinel)) {
 *      ... do something with current (including remove)
 *  }
 *  @endcode
 */
#define NK_LIST_EACH_SAFE(current, iterator, sentinel)                      \
    current = nk_list_next(sentinel), iterator = nk_list_next(current); \
    current != (sentinel);                                                  \
    current = iterator, iterator = nk_list_next(iterator)

/** @brief      Linked list node structure
 */
struct nk_list
{
    struct nk_list *        next;       /**< Next node in the list.*/
    struct nk_list *        prev;       /**< Previous node in the list.*/
    void *					object;		/**< Object which is inserted in list.*/
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
         +-----+
         |     |--+
         |  N  |  |
      +--|     |  v
      |  +-----+
      v
 @endverbatim
 */
void nk_list_init(struct nk_list * node, void * object);

void nk_list_term(struct nk_list * node);

/** @brief      Return the next node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Next node.
 */
struct nk_list * nk_list_next(struct nk_list * node);

/** @brief      Return previous node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Previous node.
 */
struct nk_list * nk_list_prev(struct nk_list * node);

void * nk_list_object(struct nk_list * node);

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
void nk_list_add_after(struct nk_list * current, struct nk_list * node);

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
void nk_list_add_before(struct nk_list * current, struct nk_list * node);

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
void nk_list_remove(struct nk_list * node);

inline bool nk_list_is_empty(struct nk_list * node)
{
	return nk_list_next(node) == node ? true : false;
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NK_LIST_H_ */
