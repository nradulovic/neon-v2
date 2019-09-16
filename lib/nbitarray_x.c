/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @defgroup   bits_bitarray_x_impl Extended bit array implementation
 *  @brief      Extended bit array implementation.
 *  @{ *//*==================================================================*/

#include "core/nbitarray_x.h"

static uint_fast8_t calculate_bit_group(uint_fast8_t bit)
{
	return bit >> NBITS_LOG2_8(NARCH_DATA_WIDTH); /* bit / NARCH_DATA_WIDTH */
}

static uint_fast8_t calculate_bit_position(uint_fast8_t bit)
{
	return bit & (NARCH_DATA_WIDTH - 1u); /* bit % NARCH_DATA_WIDTH */
}

struct nbitarray_base
{
	uint32_t group;
};

#define nbitarray_type(size) \
		{ \
			struct nbitarray_base base; \
			narch_uint array[size / NARCH_DATA_WIDTH]; \
		}


#define NBITARRAY_X_SET(a_bitarray, a_bit) \
	do { \
		np_bitarray_x_set((a_bitarray)->base, (a_bitarray)->array, (a_bit)); \
	} while (0)

#define NBITARRAY_X_CLEAR(a_bitarray, a_bit) \


void np_bitarray_x_set(
		struct nbitarray_base * base,
		narch_uint * array,
		uint_fast8_t bit)
{
	uint_fast8_t group;
	uint_fast8_t position;

	group = calculate_bit_group(bit);
	position = calculate_bit_position(bit);

	array[group] |= narch_exp2(position);
	base->group |= narch_exp2(group);
}

void nbitarray_x_set(nbitarray_x * array, uint_fast8_t bit)
{
	uint_fast8_t group;
	uint_fast8_t position;

	group = calculate_bit_group(bit);
	position = calculate_bit_position(bit);

    array[group + 1u] |= narch_exp2(position);
    array[0] |= narch_exp2(group);
}

void nbitarray_x_clear(nbitarray_x * array, uint_fast8_t bit)
{
	uint_fast8_t group;
	uint_fast8_t position;

	group = calculate_bit_group(bit);
	position = calculate_bit_position(bit);

    array[group + 1u] &= ~narch_exp2(position);

    if (array[group + 1u] == 0u) {
        array[0] &= ~narch_exp2(group);
    }
}

uint_fast8_t nbitarray_x_msbs(const nbitarray_x * array)
{
	uint_fast8_t group;
	uint_fast8_t pos;

	group = narch_log2(array[0]);
	pos = narch_log2(array[group + 1u]);

	return (uint_fast8_t)(group * (uint_fast8_t)NARCH_DATA_WIDTH + pos);
}

bool nbitarray_x_is_set(const nbitarray_x * array, uint_fast8_t bit)
{
    uint_fast8_t group;
	uint_fast8_t pos;

	group = bit >> NBITS_LOG2_8(NARCH_DATA_WIDTH); /* bit / NARCH_DATA_WIDTH */
	pos = bit & (NARCH_DATA_WIDTH - 1u);           /* bit % NARCH_DATA_WIDTH */

    return !!(array[group + 1u] & narch_exp2(pos));
}

/** @} */
