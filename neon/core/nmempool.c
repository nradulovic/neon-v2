/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @defgroup   nmem_pool_impl Memory pool implementation
 *  @brief      Memory pool implementation
 *  @{ *//*==================================================================*/

#include "core/nport.h"
#include "core/nmempool.h"

void nmem_pool_init(
        struct nmem_pool * pool,
        void * storage,
        size_t storage_size,
        uint32_t elements)
{
    size_t element_size = storage_size / elements;
    char * current_element;

    nlist_sll_init(&pool->next);
    pool->free = elements;
    current_element = storage;

    for (uint32_t i = 0u; i < elements; i++) {
        struct nlist_sll * current_list = (struct nlist_sll *)current_element;
        nlist_sll_init(current_list);
        nlist_sll_add_before(&pool->next, current_list);
        current_element += element_size;
    }
}

void * nmem_pool_alloc(struct nmem_pool * pool)
{
    void * retval = NULL;
    struct nos_critical local;

    nos_critical_lock(&local);
    if (pool->free != 0u) {
        pool->free--;
        retval = nlist_sll_next(&pool->next);
        nlist_sll_remove_from(&pool->next);
    }
    nos_critical_unlock(&local);

    return retval;
}

void nmem_pool_free(struct nmem_pool * pool, void * mem)
{
    struct nlist_sll * current = mem;
    struct nos_critical local;

    nos_critical_lock(&local);
    pool->free++;
    nlist_sll_add_before(&pool->next, current);
    nos_critical_unlock(&local);
}

/** @} */
