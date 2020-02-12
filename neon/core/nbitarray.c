/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @defgroup   bits_bitarray_impl Bit array implementation
 *  @brief      Bit array implementation.
 *  @{ */

#include <string.h>

#include "core/nbitarray.h"

#define NP_BITARRAY_ARRAY_SIZE(size_bits)                                   \
        NBITS_DIVIDE_ROUNDUP(size_bits, NARCH_DATA_WIDTH)

static uint_fast8_t calculate_bit_group(uint_fast8_t bit)
{
    return bit >> NBITS_LOG2_8(NARCH_DATA_WIDTH); /* bit / NARCH_DATA_WIDTH */
}

static uint_fast8_t calculate_bit_position(uint_fast8_t bit)
{
    return bit & (NARCH_DATA_WIDTH - 1u); /* bit % NARCH_DATA_WIDTH */
}

void np_bitarray_init(uint32_t * array, uint8_t size_bytes)
{
    memset(array, 0, size_bytes);
}

void np_bitarray_set(uint32_t * array, uint_fast8_t bit)
{
    uint_fast8_t group;
    uint_fast8_t position;

    group = calculate_bit_group(bit);
    position = calculate_bit_position(bit);

    array[group + 1] |= narch_exp2(position);
    array[0] |= narch_exp2(group);
}

void np_bitarray_clear(uint32_t * array, uint_fast8_t bit)
{
    uint_fast8_t group;
    uint_fast8_t position;

    group = calculate_bit_group(bit);
    position = calculate_bit_position(bit);

    array[group + 1] &= ~narch_exp2(position);

    if (array[group + 1] == 0u) {
        array[0] &= ~narch_exp2(group);
    }
}

uint_fast8_t np_bitarray_msbs(const uint32_t * array)
{
    uint_fast8_t group;
    uint_fast8_t pos;

    group = narch_log2(array[0]);
    pos = narch_log2(array[group + 1]);

    return (uint_fast8_t)(group * (uint_fast8_t)NARCH_DATA_WIDTH + pos);
}

bool np_bitarray_is_set(const uint32_t * array, uint_fast8_t bit)
{
    uint_fast8_t group;
    uint_fast8_t position;

    group = calculate_bit_group(bit);
    position = calculate_bit_position(bit);

    return !!(array[group + 1] & narch_exp2(position));
}

/** @} */
