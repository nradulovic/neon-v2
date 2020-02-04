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

static uint_fast8_t calculate_bit_group(uint_fast8_t bit)
{
    return bit >> NBITS_LOG2_8(NARCH_DATA_WIDTH); /* bit / NARCH_DATA_WIDTH */
}

static uint_fast8_t calculate_bit_position(uint_fast8_t bit)
{
    return bit & (NARCH_DATA_WIDTH - 1u); /* bit % NARCH_DATA_WIDTH */
}

void np_bitarray_init(
        struct np_bitarray * super,
        uint32_t * array,
        uint8_t size_bits)
{
    super->group = 0u;
    memset(array, 0, sizeof(uint32_t) * NP_BITARRAY_ARRAY_SIZE(size_bits));
}

void np_bitarray_set(
        struct np_bitarray * super,
        uint32_t * array,
        uint_fast8_t bit)
{
    uint_fast8_t group;
    uint_fast8_t position;

    group = calculate_bit_group(bit);
    position = calculate_bit_position(bit);

    array[group] |= narch_exp2(position);
    super->group |= narch_exp2(group);
}

void np_bitarray_clear(
        struct np_bitarray * super,
        uint32_t * array,
        uint_fast8_t bit);
{
    uint_fast8_t group;
    uint_fast8_t position;

    group = calculate_bit_group(bit);
    position = calculate_bit_position(bit);

    array[group] &= ~narch_exp2(position);

    if (array[group] == 0u) {
        super->group &= ~narch_exp2(group);
    }
}

uint_fast8_t np_bitarray_msbs(
        const struct np_bitarray * super,
        const uint32_t * array)
{
    uint_fast8_t group;
    uint_fast8_t pos;

    group = narch_log2(super->group);
    pos = narch_log2(array[group]);

    return (uint_fast8_t)(group * (uint_fast8_t)NARCH_DATA_WIDTH + pos);
}

bool np_bitarray_is_set(
        const np_bitarray * super,
        const uint32_t * array,
        uint_fast8_t bit)
{
    uint_fast8_t group;
    uint_fast8_t position;

    group = calculate_bit_group(bit);
    position = calculate_bit_position(bit);

    return !!(array[group] & narch_exp2(pos));
}

/** @} */
