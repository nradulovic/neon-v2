/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @defgroup   nlist_dll_impl Doubly linked list implementation
 *  @brief      Doubly linked list implementation
 *  @{ *//*==================================================================*/

#include "nlist_dll.h"

extern
struct nlist_dll * nlist_dll_init(struct nlist_dll * node);

extern
void nlist_dll_term(struct nlist_dll * node);

extern
struct nlist_dll * nlist_dll_next(struct nlist_dll * node);

extern
struct nlist_dll * nlist_dll_prev(struct nlist_dll * node);

extern
struct nlist_dll * nlist_dll_add_after(
        struct nlist_dll * current,
        struct nlist_dll * node);

extern
struct nlist_dll * nlist_dll_add_before(
        struct nlist_dll * current,
        struct nlist_dll * node);

extern
void nlist_dll_remove(struct nlist_dll * node);

extern
bool nlist_dll_is_empty(const struct nlist_dll * node);

struct nlist_dll * nlist_dll_find(
		struct nlist_dll * list,
		int (* finder)(const struct nlist_dll * object, const void * arg),
		const void * arg)
{
	struct nlist_dll * current;

	for (current = nlist_dll_next(list);
		 current != list;
		 current = nlist_dll_next(current))
	{
		int matches = finder(current, arg);

		if (matches) {
			return current;
		}
	}
	return list;
}

/** @} */
