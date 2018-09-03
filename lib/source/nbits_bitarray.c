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

#include <string.h>
#include "bits/nbits_bitarray.h"

void nbitarray_init(struct nbitarray * ba)
{
    memset(ba, 0, sizeof(*ba));
}

void nbitarray_set(struct nbitarray * ba, uint_fast8_t num)
{
#ifdef NBITARRAY_IS_EXTENDED
    uint_fast8_t group;
    uint_fast8_t index;

    index = num &
        ((uint_fast8_t)~0u >> (NBITS_BIT_SIZE(num) - NBITS_LOG2_8(NARCH_DATA_WIDTH)));
    group = num >> NBITS_LOG2_8(NARCH_DATA_WIDTH);
    ba->group |= narch_exp2(group);
    ba->ids[group] |= narch_exp2(index);
#else
    ba->ids[0] |= narch_exp2(num);
#endif
}

void nbitarray_clear(struct nbitarray * ba, uint_fast8_t num)
{
#ifdef NBITARRAY_IS_EXTENDED
    uint_fast8_t group;
    uint_fast8_t index;

    index = num &
        ((uint_fast8_t)~0u >> (NBITS_BIT_SIZE(num) - NBITS_LOG2_8(NARCH_DATA_WIDTH)));
    group = num >> NBITS_LOG2_8(NARCH_DATA_WIDTH);
    ba->ids[group] &= ~narch_exp2(index);

                                        /* If this is the last bit cleared in */
                                        /* this array_entry then clear bit    */
                                        /* group indicator, too.              */
    if (ba->ids[group] == 0u) {
        ba->group &= ~narch_exp2(group);
    }
#else
    ba->ids[0] &= ~narch_exp2(num);
#endif
}

uint_fast8_t nbitarray_msbs(const struct nbitarray * ba)
{
#ifdef NBITARRAY_IS_EXTENDED
    uint_fast8_t group;
    uint_fast8_t index;

    group = narch_log2(ba->group);
    index = narch_log2(ba->ids[group]);

    return ((group << NBITS_LOG2_8(NARCH_DATA_WIDTH)) | index);
#else
    return (narch_log2(ba->ids[0]));
#endif
}
