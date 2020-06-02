/*
 * Neon
 * Copyright (C)  2018  REAL-TIME CONSULTING
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
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Lightweight queue
 *
 *  @addtogroup  lib
 *  @{
 */
/** @defgroup    lib_lqueue Lightweight queue
 *  @brief       Lightweight queue.
 *  @{
 */
/*---------------------------------------------------------------------------*/

#ifndef NEON_QUEUE_LQUEUE_H_
#define NEON_QUEUE_LQUEUE_H_

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct nk_queue;

struct nk_queue * nk_queue__create(
		size_t item_size,
		size_t buffer_size);

void nk_queue__delete(struct nk_queue * q);

void * nk_queue__put_fifo(struct nk_queue * q);

void * nk_queue__put_lifo(struct nk_queue * q);

void * nk_queue__get(struct nk_queue * q);

void * nk_queue__peek_head(const struct nk_queue * q);

void * nk_queue__peek_tail(const struct nk_queue * q);

size_t nk_queue__empty(const struct nk_queue * q);

size_t nk_queue__size(const struct nk_queue * q);

bool nk_queue__is_empty(const struct nk_queue * q);

bool nk_queue__is_full(const struct nk_queue * q);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* NEON_QUEUE_LQUEUE_H_ */

