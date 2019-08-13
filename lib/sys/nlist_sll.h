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
/** @defgroup   nlist_sll Singly linked list
 *  @brief      Singly linked list
 *  @{
 */

#ifndef NEON_LIST_SLL_H_
#define NEON_LIST_SLL_H_

#include <stdbool.h>

#include "sys/nport.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief      Macro to get the pointer to structure which contains any struct
 *              of a list.
 * 
 *  @param[in]  ptr
 *              Pointer to structure/data that is containing a list structure.
 *  @param[in]  type
 *              Type of variable which contains a list structure.
 *  @param[in]  member
 *              Name of member in variable structure.
 *  @return     Pointer to container structure.
 *
 *  @code
 *  struct my_struct
 *  {
 *      char my_name[8];
 *      struct nlist_sll some_list;
 *      int some_stuff;
 *  };
 *
 *  struct nlist_sll * current_element;
 *  struct my_struct * current;
 *
 *  current = NLIST_SLL_ENTRY(current_element, struct my_struct, some_list);
 *  @endcode
 *  @hideinitializer
 */
#define nlist_sll_entry(ptr, type, member)                                  \
        NPLATFORM_CONTAINER_OF(ptr, type, member)

/** @brief		Check if list sentinel or list node is initialized.
 * 
 *  @param[in]	list
 * 				A pointer to list sentinel or list node.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 *  @hideinitializer
 */
#define nlist_sll_is_null(list)         ((list)->next == NULL)

/** @brief      Macro to get the first element in list pointed by @a sentinel.
 * 
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 *  @hideinitializer
 */
#define nlist_sll_first(sentinel)       nlist_sll_next(sentinel)

/** @brief      Helper macro, get the last element in list pointed by
 *              @a sentinel.
 *  
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 *  @hideinitializer
 */
#define nlist_sll_last(sentinel)        nlist_sll_prev(sentinel)

/** @brief      Helper macro, add a node @a node at list head pointed by
 *              @a sentinel.
 * 
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 *  @hideinitializer
 */
#define nlist_sll_add_head(sentinel, node)                                  \
        nlist_sll_add_before(sentinel, node)

/** @brief      Helper macro, add a node @a node at list tail pointed by
 *              @a sentinel.
 * 
 *  @param[in]  sentinel
 *              Pointer to sentinel of a list.
 *  @param[in]  node
 *              Pointer to a node to be added to list.
 *  @note       This macro is exception to macro naming rule since it is does
 *              not have side effects.
 *  @hideinitializer
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
 *  @mseffect	
 *				Argument expansion side effects are present in this macro.
 *  @hideinitializer
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
 *  @mseffect
 *				Argument expansion side effects are present in this macro.
 *  @hideinitializer
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
 *  @mseffect
 *				Argument expansion side effects are present in this macro.
 *  @hideinitializer
 */
#define NLIST_SLL_EACH_SAFE(current, iterator, sentinel)                    \
    current = nlist_sll_first(sentinel), iterator = nlist_sll_next(current);\
    current != (sentinel);                                                  \
    current = iterator, iterator = nlist_sll_next(iterator)

/** @brief      Singly Linked List (SLL) structure.
 */
struct nlist_sll
{
    struct nlist_sll *          next;       /**< Next node in the list.       */
};

/** @brief      Initialize a list sentinel or node.
 * 
 *  @param[in]  node
 *              A list sentinel or node.
 *  @return		Pointer to node.
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
    
    return node;
}

/** @brief      Return the next node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Next node.
 */
NPLATFORM_INLINE
struct nlist_sll * nlist_sll_next(struct nlist_sll * node)
{
    return node->next;
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
    return tmp;
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
struct nlist_sll * nlist_sll_add_before(
        struct nlist_sll * current,
        struct nlist_sll * node)
{
    node->next = current->next;
    current->next = node;

    return (node);
}

/** @brief      Remove a node (N) which is next from current (C) node
 *  @param[in]  current
 *              A list node.
 *
 *  Before calling this function:
 @verbatim
        +-----+    +-----+    +-----+    +-----+
        |     |--->|     |--->|     |--->|     |-->next
        |  1  |    |  C  |    |  N  |    |  2  |
        |     |    |     |    |     |    |     |
        +-----+    +-----+    +-----+    +-----+
 @endverbatim
 *
 *  After call to this function:
 @verbatim
                                                +-----------+
        +-----+    +-----+    +-----+           |  +-----+  |
        |     |--->|     |--->|     |-->next    +->|     |--+
        |  1  |    |  C  |    |  2  |              |  N  |
        |     |    |     |    |     |              |     |
        +-----+    +-----+    +-----+              +-----+
 @endverbatim
 */
NPLATFORM_INLINE
struct nlist_sll * nlist_sll_remove_from(struct nlist_sll * current)
{
    struct nlist_sll * node;
    
    node = current->next;
    current->next = node->next;
    
    return nlist_sll_init(node);
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

    nlist_sll_remove_from(prev);
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
    return !!(node->next == node);
}

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_LIST_SLL_H_ */
