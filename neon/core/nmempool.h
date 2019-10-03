/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @addtogroup neon
 *  @{
 */
/** @defgroup   nmem_pool Memory pool module
 *  @brief      Memory pool module
 *  @{
 */

#ifndef NEON_MEMPOOL_H_
#define NEON_MEMPOOL_H_

#include <stdint.h>
#include <stddef.h>

#include "core/nlist_sll.h"

#ifdef __cplusplus
extern "C" {
#endif

struct nmem_pool
{
    struct nlist_sll next;
    uint32_t free;
    uint32_t element_size;
};

#define npool(T, size)                                                      \
    {                                                                       \
        struct nmem_pool mem_pool;                                          \
        T storage[size];                                                    \
    }

#define NMEM_POOL_INIT(MP)                                                  \
    do {                                                                    \
        nmem_pool_init(                                                     \
                &(MP)->mem_pool,                                            \
                &(MP)->storage[0],                                          \
                sizeof((MP)->storage),                                      \
                NBITS_ARRAY_SIZE((MP)->storage));                           \
    } while (0)
        
#define NMEM_POOL(MP)                   &(MP)->mem_pool

void nmem_pool_init(
        struct nmem_pool * pool, 
        void * storage, 
        size_t storage_size, 
        uint32_t elements);

void * nmem_pool_alloc(struct nmem_pool * pool);

void   nmem_pool_free (struct nmem_pool * pool, void * mem);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_MEMPOOL_H_ */
