/*
 * nk_array.h
 *
 *  Created on: May 26, 2020
 *      Author: nenad
 */

#ifndef NEON_KERNEL_NK_INCLUDE_NK_ARRAY_H_
#define NEON_KERNEL_NK_INCLUDE_NK_ARRAY_H_

#include <stddef.h>

struct nk_allocator;
struct nk_array;

struct nk_array * nk_array__create(
		size_t item_size,
		size_t buffer_size);

void nk_array__delete(struct nk_array * array);

void * nk_array__refence(struct nk_array * array, size_t index);

void * nk_array__buffer(struct nk_array * array);

size_t nk_array__size(struct nk_array * array);

size_t nk_array__item_size(struct nk_array *array);

#endif /* NEON_KERNEL_NK_INCLUDE_NK_ARRAY_H_ */
