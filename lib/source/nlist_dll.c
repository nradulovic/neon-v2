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

#include "list/nlist_dll.h"

struct nlist_dll * nlist_dll_init(struct nlist_dll * node)
{
    node->next = node;
    node->prev = node;

    return (node);
}

struct nlist_dll * nlist_dll_add_after(struct nlist_dll * current,
        struct nlist_dll * node)
{
    node->next          = current;
    node->prev          = current->prev;
    current->prev->next = node;
    current->prev       = node;

    return (node);
}

struct nlist_dll * nlist_dll_add_before(struct nlist_dll * current,
        struct nlist_dll * node)
{
    node->prev          = current;
    node->next          = current->next;
    current->next->prev = node;
    current->next       = node;

    return (node);
}

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

