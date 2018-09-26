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
    struct nlist_dll * current_list;
    
    for (NLIST_DLL_EACH(current_list, &sentinel->list)) {
        struct npqueue * current = npqueue_from_list(current_list);
        
        if (current->priority < node->priority) {
            break;
        }
    }
    nlist_dll_add_after(current_list, &node->list);
}
