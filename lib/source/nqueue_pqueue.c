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

struct npqueue_node * npqueue_node_init(struct npqueue_node * node,
        uint_fast8_t priority)
{
    npqueue_from_list(nlist_sll_init(&node->node))->priority = priority;

    return (node);
}

void npqueue_node_term(struct npqueue_node * node)
{
    nlist_sll_init(&node->node);
    node->priority = 0u;
}

uint_fast8_t npqueue_node_mod_priority(struct npqueue_node * node,
    	uint_fast8_t priority)
{
    uint_fast8_t retval;
    
    retval = npqueue_node_priority(node);
    npqueue_node_set_priority(node, priority);

    return (retval);
}

void npqueue_init(struct npqueue * queue)
{
    nlist_sll_init(&queue->sentinel);
}

void npqueue_insert(struct npqueue * queue, struct npqueue_node * node)
{
    struct nlist_sll * current;

    for (NLIST_SLL_EACH(current, &queue->sentinel)) {
        if (npqueue_from_list(current)->priority < node->priority) {
            break;
        }
    }
    nlist_sll_add_after(current, &node->node);
}

struct npqueue_node * npqueue_remove_first(struct npqueue * queue)
{
    struct nlist_sll * head = nlist_sll_next(&queue->sentinel);
    
    nlist_sll_remove_from(&queue->sentinel, head);
    
    return npqueue_from_list(head);
}
