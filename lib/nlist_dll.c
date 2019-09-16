/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @defgroup   nlist_dll_impl Doubly linked list implementation
 *  @brief      Doubly linked list implementation
 *  @{ *//*==================================================================*/

#include "core/nlist_dll.h"

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
