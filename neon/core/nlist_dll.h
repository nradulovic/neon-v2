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
/** @defgroup   nlist_dll Doubly linked list
 *  @brief      Doubly linked list
 *  @{
 */

#ifndef NEON_LIST_DLL_H_
#define NEON_LIST_DLL_H_

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define nlist_dll_is_null(list)         ((list)->next == NULL)

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
 *  @mseffect
 */
#define NLIST_DLL_EACH(current, sentinel)                                   \
        current = nlist_dll_first(sentinel);                                \
        current != (sentinel);                                              \
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
 *  @mseffect
 */
#define NLIST_DLL_EACH_BACKWARDS(current, sentinel)                         \
        current = nlist_dll_last(sentinel);                                 \
        current != (sentinel);                                              \
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
 *  @mseffect
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
inline
struct nlist_dll * nlist_dll_init(struct nlist_dll * node)
{
    node->next = node;
    node->prev = node;

    return node;
}

/** @brief      Terminate a list sentinel or node.
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
         |     | ---
         +-----+
 @endverbatim
 */
inline
void nlist_dll_term(struct nlist_dll * node)
{
    node->next = NULL;
}

/** @brief      Return the next node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Next node.
 */
inline
struct nlist_dll * nlist_dll_next(struct nlist_dll * node)
{
    return node->next;
}

/** @brief      Return previous node of @a node in linked list.
 *  @param[in]  node
 *              A list node or sentinel.
 *  @return     Previous node.
 */
inline
struct nlist_dll * nlist_dll_prev(struct nlist_dll * node)
{
    return node->prev;
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
inline
struct nlist_dll * nlist_dll_add_after(
        struct nlist_dll * current,
        struct nlist_dll * node)
{
    node->next          = current;
    node->prev          = current->prev;
    current->prev->next = node;
    current->prev       = node;

    return node;
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
inline
struct nlist_dll * nlist_dll_add_before(
        struct nlist_dll * current,
        struct nlist_dll * node)
{
    node->prev          = current;
    node->next          = current->next;
    current->next->prev = node;
    current->next       = node;

    return node;
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
                                    ---
 @endverbatim
 */
inline
void nlist_dll_remove(struct nlist_dll * node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
}

/** @brief      Check if a list @a node is empty or not.
 *  @param[in]  node
 *              A list sentinel.
 *  @return     List state:
 *  @retval     true - The list is empty.
 *  @retval     false - The list contains at least one node.
 */
inline
bool nlist_dll_is_empty(const struct nlist_dll * node)
{
    return node->next == node;
}

struct nlist_dll * nlist_dll_find(
		struct nlist_dll * list,
		int (* finder)(const struct nlist_dll * object, const void * arg),
		const void * arg);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_LIST_DLL_H_ */
