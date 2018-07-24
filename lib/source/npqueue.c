
#include "queue/nqueue_pqueue.h"

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

