/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @defgroup   nlqueue_impl Lightweight queue implementation
 *  @brief      Lightweight queue implementation
 *  @{ *//*==================================================================*/

#include "core/npqueue.h"

static int find_priority(const struct nlist_dll * object, const void * arg)
{
	struct npqueue * current = npqueue_from_list(object);

	if (current->priority == *(uint_fast8_t *)arg) {
		return 1;
	} else {
		return 0;
	}
}

void npqueue_sentinel_shift(struct npqueue_sentinel * sentinel)
{
    struct npqueue * next = npqueue_next(sentinel);

    nlist_dll_remove(&sentinel->list);
    nlist_dll_add_before(&next->list, &sentinel->list);
}

struct npqueue * npqueue_init(struct npqueue * node, uint_fast8_t priority)
{
    nlist_dll_init(&node->list);
    npqueue_priority_set(node, priority);

    return (node);
}

void npqueue_term(struct npqueue * node)
{
    npqueue_priority_set(node, 0);
    nlist_dll_init(&node->list);
}

void npqueue_insert_sort(struct npqueue_sentinel * sentinel,
        struct npqueue * node)
{
    struct nlist_dll * current;

    current = nlist_dll_find(&sentinel->list, find_priority, &node->priority);
    nlist_dll_add_after(current, &node->list);
}

/** @} */
