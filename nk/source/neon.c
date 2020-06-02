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

#include "nerror.h"
#include <stdlib.h>

void nk_exception__raise(enum nk_exception__type type)
{
	int status;

	/*
	 * According to C99/11 standard enum can be any of char, int or unsigned int
	 * type. It is implementation-defined which type is compatible with any
	 * given enumerated type. Because we don't know which type will be chosen
	 * we will explicitly cast to int type.
	 */
	status = -(int)type - 1;

	exit(status);
}

#include "nk_allocator.h"
#include "stdlib.h"

void * nk_allocator__alloc(size_t size)
{
	void * mem;

	mem = malloc(size);

	if (mem == NULL) {
		nk_exception__raise(NK_EXCEPTION__TYPE__NO_MEM);
	}
	return mem;
}

void nk_allocator__free(void * mem)
{
	free(mem);
}

#include "nk_array.h"

struct nk_array
{
	size_t item_size;
	size_t buffer_size;
	void * item_buffer;
};

struct nk_array * nk_array__create(
		size_t item_size,
		size_t buffer_size)
{
	struct nk_array * array;

	array = nk_allocator__alloc(sizeof(struct nk_array));
	array->item_size = item_size;
	array->buffer_size = buffer_size;
	array->item_buffer = nk_allocator__alloc(item_size * buffer_size);

	return array;
}

void nk_array__delete(struct nk_array * array)
{
	nk_allocator__free(array->item_buffer);
	nk_allocator__free(array);
}

void * nk_array__buffer(struct nk_array * array)
{
	return array->item_buffer;
}

void * nk_array__refence(struct nk_array * array, size_t index)
{
	char * buffer = array->item_buffer;

	if (index >= array->buffer_size) {
		nk_exception__raise(NK_EXCEPTION__OUT_OF_BOUNDS);
	}

	return &buffer[index * array->item_size];
}

#include "nk_queue.h"

struct nk_queue
{
	size_t head;
	size_t tail;
	size_t empty;
	size_t mask;
	struct nk_array * array;
};

struct nk_queue * nk_queue__create(
		size_t item_size,
		size_t buffer_size)
{
	struct nk_queue * q;

	q = nk_allocator__alloc(sizeof(struct nk_queue));
	q->head = 0u;
	q->tail = 0u;
	q->empty = buffer_size;
	q->mask = buffer_size - 1u;
	q->array = nk_array__create(item_size, buffer_size);

	return q;
}

void nk_queue__delete(struct nk_queue * q)
{
	nk_array__delete(q->array);
	nk_allocator__free(q);
}

void * nk_queue__put_fifo(struct nk_queue * q)
{
	size_t retval;

	q->empty--;
	retval = q->head;

	q->head++;

	if (q->head > q->mask) {
		q->head = 0u;
	}

	return nk_array__refence(q->array, retval);
}

void * nk_queue__put_lifo(struct nk_queue * q)
{
	q->empty--;
	q->tail--;

	if (q->tail > q->mask) {
		q->tail = q->mask;
	}

	return nk_array__refence(q->array, q->tail);
}

void * nk_queue__get(struct nk_queue * q)
{
	size_t retval;

    retval = q->tail;
    q->tail++;

    if (q->tail > q->mask) {
		q->tail = 0u;
	}
    q->empty++;

    return nk_array__refence(q->array, retval);
}

void * nk_queue__peek_head(const struct nk_queue * q)
{
	size_t real_head;

    real_head = q->head;
    real_head--;
    real_head &= q->mask;

    return nk_array__refence(q->array, real_head);
}

void * nk_queue__peek_tail(const struct nk_queue * q)
{
    return nk_array__refence(q->array, q->tail);
}

size_t nk_queue__empty(const struct nk_queue * q)
{
	return q->empty;
}

size_t nk_queue__size(const struct nk_queue * q)
{
	return q->mask + 1u;
}

bool nk_queue__is_empty(const struct nk_queue * q)
{
	return q->empty == (q->mask + 1u);
}

bool nk_queue__is_full(const struct nk_queue * q)
{
	return q->empty == 0u;
}

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

