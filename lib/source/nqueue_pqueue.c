
#include "queue/nqueue_pqueue.h"

struct npqueue_node * npqueue_node_init(struct npqueue_node * node,
        uint_fast8_t priority)
{
    npqueue_from_list(nlist_dll_init(&node->node))->priority = priority;

    return (node);
}

void npqueue_node_term(struct npqueue_node * node)
{
    nlist_dll_init(&node->node);
    node->priority = 0u;
}

void npqueue_insert(struct npqueue * queue, struct npqueue_node * node)
{
    struct nlist_dll * current;

    for (NLIST_DLL_EACH(current, &queue->sentinel)) {
        if (npqueue_from_list(current)->priority < node->priority) {
            break;
        }
    }
    nlist_dll_add_after(current, &node->node);
}

