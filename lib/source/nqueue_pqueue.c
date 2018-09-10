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

#include "queue/nqueue_pqueue.h"

struct npqueue * npqueue_init(struct npqueue * node,
        uint_fast8_t priority)
{
    npqueue_from_list(nlist_dll_init(&node->node))->priority = priority;

    return (node);
}

void npqueue_term(struct npqueue * node)
{
    nlist_dll_init(&node->node);
    node->priority = 0u;
}

uint_fast8_t npqueue_mod_priority(struct npqueue * node, uint_fast8_t priority)
{
    uint_fast8_t retval;
    
    retval = npqueue_priority(node);
    npqueue_set_priority(node, priority);

    return (retval);
}

void npqueue_insert_sorted(struct npqueue * head, struct npqueue * node)
{
    struct nlist_dll * current;

    for (NLIST_DLL_EACH(current, &head->node)) {
        if (npqueue_from_list(current)->priority < node->priority) {
            break;
        }
    }
    nlist_dll_add_after(current, &node->node);
}


