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

#include "bits/nbits.h"

uint32_t nbits_ftou32(float val)
{
    union float_to_u32
    {
        float                       fvalue;
        uint32_t                    ivalue;
    }                           u;
    u.fvalue = val;

    return (u.ivalue);
}

float nbits_u32tof(uint32_t val)
{
    union u32_to_float
    {
        uint32_t                    ivalue;
        float                       fvalue;
    }                           u;
    u.ivalue = val;

    return (u.fvalue);
}

void nbitarray_x_set(nbitarray_x * array, uint_fast8_t bit)
{
	uint_fast8_t group;
	uint_fast8_t pos;

	group = (bit / NARCH_DATA_WIDTH) + 1u;
	pos = bit % NARCH_DATA_WIDTH;
	narch_set_bit(&array[group], pos);
	narch_set_bit(&array[0], group - 1u);
}

void nbitarray_x_clear(nbitarray_x * array, uint_fast8_t bit)
{
	uint_fast8_t group;
	uint_fast8_t pos;

	group = bit / NARCH_DATA_WIDTH;
	pos = bit % NARCH_DATA_WIDTH;

	narch_clear_bit(&array[group + 1u], pos);

	if (array[group + 1u] == 0u) {
		narch_clear_bit(&array[0], group);
	}
}

uint_fast8_t nbitarray_x_msbs(const nbitarray_x * array)
{
	uint_fast8_t group;
	uint_fast8_t pos;

	group = narch_log2(array[0]);
	pos = narch_log2(array[group + 1u]);

	return group * NARCH_DATA_WIDTH + pos;
}
