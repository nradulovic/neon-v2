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
/** @file
 *  @author      Nenad Radulovic
 *  @brief       Neon STDOUT header
 *
 *  @defgroup    neon_stdout Neon STDOUT library
 *  @brief       Neon STDOUT library interface
 *  @{
 */

#ifndef NEON_STDOUT_H_
#define NEON_STDOUT_H_

#include "board_variant/board.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#if (NBOARD_USES_STD_STREAM > 0) && (NBOARD_USES_STD_STREAM < 16)
#include "neon_uart.h"

#if (NBOARD_USES_STD_STREAM == 1)
#define NUART_ID                        NUART_ID_1
#elif (NBOARD_USES_STD_STREAM == 2)
#define NUART_ID                        NUART_ID_2
#elif (NBOARD_USES_STD_STREAM == 5)
#define NUART_ID                        NUART_ID_5
#else
#define NUART_ID                        NUART_ID_15
#endif
    
#define NSTREAM_INIT(callback)                                              \
        nuart_init(NUART_ID, (nuart_callback *)(callback))
   
#define NSTREAM_IS_INITIALIZED()        nuart_is_initialized(NUART_ID)
    
#define NSTREAM_SEND(buffer, size)      nuart_send(NUART_ID, (buffer), (size))
    
#elif (NBOARD_USES_STD_STREAM >= 16) && (NBOARD_USES_STD_STREAM < 32)
#include "neon_spi.h"
#elif (NBOARD_USES_STD_STREAM >= 32) && (NBOARD_USES_STD_STREAM < 48)
#include "neon_i2c.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* NEON_STDOUT_H_ */
