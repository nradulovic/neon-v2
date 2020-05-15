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
#define nk_list__add_head(sentinel, node)                                  	\
        nk_list__add_before(sentinel, node)

/** @brief      Helper macro, add a node @a node at list tail pointed by 
 *              @a sentinel.
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 */
#define nk_list__add_tail(sentinel, node)                                  	\
        nk_list__add_after(sentinel, node)

/** @brief      Construct for @a FOR loop to iterate over each element in a
 *              list.
 *
 *  @code
 *  struct nk_list * current;
 *  struct nk_list * sentinel = &g_list_sentinel.list;
 *
 *  for (NK_LIST_EACH(current, sentinel)) {
 *      ... do something with @a current (excluding remove)
 *  }
 *  @endcode
 */
#define NK_LIST__EACH(current, sentinel)                                 	\
	    current = nk_list__next(sentinel); 									\
	    current != (sentinel);                                              \
	    current = nk_list__next(current)

/** @brief      Construct for FOR loop to iterate over each element in list
 *              backwards.
 *
 *  @code
 *  struct nk_list * current;
 *  struct nk_list * sentinel = &g_list_sentinel.list;
 *
 *  for (NK_LIST_EACH_BACKWARDS(current, sentinel)) {
 *      ... do something with current (excluding remove)
 *  }
 *  @endcode
 */
#define NK_LIST__EACH_BACKWARDS(current, sentinel)                          \
		current = nk_list__prev(sentinel); 									\
		current != (sentinel);                                              \
		current = nk_list__prev(current)

/** @brief      Construct for FOR loop to iterate over each element in list
 *              which is safe against element removal.
 *
 *  @code
 *  struct nk_list * current;
 *  struct nk_list * iterator;
 *  struct nk_list * sentinel = &g_list_sentinel.list;
 *
 *  for (NK_LIST_EACH_SAFE(current, iterator, sentinel)) {
 *      ... do something with current (including remove)
 *  }
 *  @endcode
 */
#define NK_LIST__EACH_SAFE(current, iterator, sentinel)                     \
    current = nk_list__next(sentinel), iterator = nk_list__next(current); 	\
    current != (sentinel);                                                  \
    current = iterator, iterator = nk_list__next(iterator)

/** @brief      Linked list node structure
 */
struct nk_list__node
{
    struct nk_list__node *  next;       /**< Next node in the list.*/
    struct nk_list__node *  prev;       /**< Previous node in the list.*/
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
inline void nk_list__init(struct nk_list__node * node, void * object)
{
    node->next = node;
    node->prev = node;
    node->object = object;
}

inline void nk_list__term(struct nk_list__node * node)
{
	node->next = NULL;
	node->prev = NULL;
	node->object = NULL;
}

/** @brief      Return the next node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Next node.
 */
inline struct nk_list__node * nk_list__next(struct nk_list__node * node)
{
	return node->next;
}

/** @brief      Return previous node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Previous node.
 */
inline struct nk_list__node * nk_list__prev(struct nk_list__node * node)
{
	return node->prev;
}

inline void * nk_list__object(struct nk_list__node * node)
{
	return node->object;
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
inline void nk_list__add_after(
		struct nk_list__node * current,
		struct nk_list__node * node)
{
    node->next          = current;
    node->prev          = current->prev;
    current->prev->next = node;
    current->prev       = node;
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
inline void nk_list__add_before(
		struct nk_list__node * current,
		struct nk_list__node * node)
{
    node->prev          = current;
    node->next          = current->next;
    current->next->prev = node;
    current->next       = node;
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
inline void nk_list__remove(struct nk_list__node * node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;

    /* NOTE:
     * Next pointer must point to itself, since it may be checked by
     * nk_list__is_empty() function.
     */
    node->next = node;
    node->prev = node;
}

inline bool nk_list__is_empty(struct nk_list__node * node)
{
	return nk_list__next(node) == node ? true : false;
}

typedef bool (nk_list__compare_fn)(const void * current, const void * new_node);

void nk_list__insert_at(
		struct nk_list__node * list,
		struct nk_list__node * node,
		nk_list__compare_fn * compare);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NK_LIST_H_ */
