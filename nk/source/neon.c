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

#include "nk_bits.h"
#include "nk_list.h"

extern inline void nk_list__init(struct nk_list__node * node, void * object);

extern inline void nk_list__term(struct nk_list__node * node);

extern inline struct nk_list__node * nk_list__next(struct nk_list__node * node);

extern inline struct nk_list__node * nk_list__prev(struct nk_list__node * node);

extern inline void * nk_list__object(struct nk_list__node * node);

extern inline void nk_list__add_after(
		struct nk_list__node * current,
		struct nk_list__node * node);

extern inline void nk_list__add_before(
		struct nk_list__node * current,
		struct nk_list__node * node);

extern inline void nk_list__remove(struct nk_list__node * node);

extern inline bool nk_list__is_empty(struct nk_list__node * node);

void nk_list__insert_at(
		struct nk_list__node * list,
		struct nk_list__node * node,
		nk_list__compare_fn * compare)
{
	struct nk_list__node * current;
	void * node_object = nk_list__object(node);

	for (NK_LIST__EACH(current, list)) {
		void * current_object = nk_list__object(current);

		if (compare(current_object, node_object) == true) {
			break;
		}
	}
	nk_list__add_after(current, node);
}

#include "nk_queue.h"

extern inline void nk_queue__index_init(
		struct nk_queue__index * qb, size_t items);

extern inline size_t nk_queue__index_push_fifo(struct nk_queue__index * qb);

extern inline size_t nk_queue__index_push_lifo(struct nk_queue__index * qb);

extern inline size_t nk_queue__index_get(struct nk_queue__index * qb);

extern inline size_t nk_queue__index_peek_head(
		const struct nk_queue__index * qb);

extern inline size_t nk_queue__index_peek_tail(
		const struct nk_queue__index * qb);

extern inline size_t nk_queue__index_empty(const struct nk_queue__index * qb);

extern inline size_t nk_queue__index_size(const struct nk_queue__index * qb);

#include "nk_sort_list.h"

void nk_sort_list__insert(
		struct nk_list__node * list,
		struct nk_list__node * node,
		compare_fn * compare)
{
	struct nk_list__node * current;
	void * node_object = nk_list__object(node);

	for (NK_LIST__EACH(current, list)) {
		void * current_object = nk_list__object(current);

		if (compare(current_object, node_object) == true) {
			break;
		}
	}
	nk_list__add_after(current, node);
}

#include "nk_arch.h"
#include "nk_bitarray.h"

void nk_bitarray__indefinite_init(struct nk_bitarray__indefinite * ba, uint32_t * rows)
{
	ba->rows = rows;
}

void nk_bitarray__indefinite_set(struct nk_bitarray__indefinite * ba, uint_fast8_t a_bit)
{
	uint_fast8_t column_idx;
	uint_fast8_t row_idx;

	column_idx = a_bit / NK_BITS__BIT_SIZE(*ba->rows);
	row_idx = a_bit % NK_BITS__BIT_SIZE(*ba->rows);

	ba->rows[column_idx] |= 0x1u << row_idx;
	ba->column |= 0x1u << column_idx;
}

void nk_bitarray__indefinite_clear(struct nk_bitarray__indefinite * ba, uint_fast8_t a_bit)
{
	uint_fast8_t column_idx;
	uint_fast8_t row_idx;

	column_idx = a_bit / NK_BITS__BIT_SIZE(*ba->rows);
	row_idx = a_bit % NK_BITS__BIT_SIZE(*ba->rows);

	ba->rows[column_idx] &= ~(0x1u << row_idx);

	if (ba->rows[column_idx] == 0u) {
		ba->column &= ~(0x1u << column_idx);
	}
}

uint_fast8_t nk_bitarray__indefinite_msbs(const struct nk_bitarray__indefinite * ba)
{
	uint_fast8_t column_idx;
	uint_fast8_t msbs;

	column_idx = nk_arch_log2(ba->column);

	msbs = (uint_fast8_t)(nk_arch_log2(ba->rows[column_idx]) +
						 (column_idx * NK_BITS__BIT_SIZE(*ba->rows)));
	return msbs;
}

bool nk_bitarray__indefinite_is_set(const struct nk_bitarray__indefinite * ba, uint_fast8_t a_bit)
{
	uint_fast8_t column_idx;
	uint_fast8_t row_idx;

	column_idx = a_bit / NK_BITS__BIT_SIZE(*ba->rows);
	row_idx = a_bit % NK_BITS__BIT_SIZE(*ba->rows);

	if ((ba->rows[column_idx] & (0x1u << row_idx)) != 0u) {
		return true;
	} else {
		return false;
	}
}

#include "default_config.h"
#include "nerror.h"
#include "ntask_fiber.h"
#include "nk_sched.h"

struct sched__ready_queue
{

};

void nk_sched__task_init(
		struct nk_sched__task_cb * tcb,
		nk_sched__task_fn * task_fn,
		void * tls,
		void * arg)
{
	nk_list__init(&tcb->node, tcb);
	tcb->fn = task_fn;
	tcb->tls = tls;
	tcb->arg = arg;
}

void nk_sched__task_ready(struct nk_sched__task_cb * tcb)
{

}
