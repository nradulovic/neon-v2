/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @defgroup   nbits_impl Bit operations module implementation
 *  @brief      Bit operations module implementation
 *  @{ *//*==================================================================*/

#include <string.h>

#include "core/nbits.h"

const uint32_t g_np_bits_right_mask[33] =
{
    [ 0] = 0x00000000u,
    [ 1] = 0x00000001u,
    [ 2] = 0x00000003u,
    [ 3] = 0x00000007u,
    [ 4] = 0x0000000fu,
    [ 5] = 0x0000001fu,
    [ 6] = 0x0000003fu,
    [ 7] = 0x0000007fu,
    [ 8] = 0x000000ffu,
    [ 9] = 0x000001ffu,
    [10] = 0x000003ffu,
    [11] = 0x000007ffu,
    [12] = 0x00000fffu,
    [13] = 0x00001fffu,
    [14] = 0x00003fffu,
    [15] = 0x00007fffu,
    [16] = 0x0000ffffu,
    [17] = 0x0001ffffu,
    [18] = 0x0003ffffu,
    [19] = 0x0007ffffu,
    [20] = 0x000fffffu,
    [21] = 0x001fffffu,
    [22] = 0x003fffffu,
    [23] = 0x007fffffu,
    [24] = 0x00ffffffu,
    [25] = 0x01ffffffu,
    [26] = 0x03ffffffu,
    [27] = 0x07ffffffu,
    [28] = 0x0fffffffu,
    [29] = 0x1fffffffu,
    [30] = 0x3fffffffu,
    [31] = 0x7fffffffu,
    [32] = 0xffffffffu
};

uint32_t nbits_ftou32(float val)
{
    uint32_t retval;

    memcpy(&retval, &val, sizeof(retval));

    return retval;
}

float nbits_u32tof(uint32_t val)
{
    float retval;

    memcpy(&retval, &val, sizeof(retval));

    return retval;
}

/** @} */
