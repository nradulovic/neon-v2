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

#include "list/nlist_sll.h"

struct nlist_sll * nlist_sll_init(struct nlist_sll * node)
{
    node->next = node;

    return (node);
}

/*
 * NOTE:
 * This function is not inlined since doing so would generate bigger executable
 * by around 200bytes (gcc-arm-none-eabi, 4.9.3, all optimizations) per each
 * library user.
 */
struct nlist_sll * nlist_sll_prev(struct nlist_sll * const node)
{
    struct nlist_sll * tmp = node;

    while (tmp->next != node) {
        tmp = tmp->next;
    }
    return (tmp);
}

void nlist_sll_add_after(struct nlist_sll * current, struct nlist_sll * node)
{
    struct nlist_sll * prev = nlist_sll_prev(current);

    node->next = prev->next;
    prev->next = node;
}

struct nlist_sll * nlist_sll_add_before(struct nlist_sll * current, 
        struct nlist_sll * node)
{
    node->next = current->next;    
    current->next = node;

    return (node);
}

void nlist_sll_remove(struct nlist_sll * node)
{
    struct nlist_sll * prev = nlist_sll_prev(node);

    nlist_sll_remove_from(prev, node);
}

void nlist_sll_remove_from(struct nlist_sll * prev, struct nlist_sll * node)
{
    prev->next = node->next;
    node->next = node;
}

bool nlist_sll_is_empty(const struct nlist_sll * node)
{
    return (!!(node->next == node));
}
