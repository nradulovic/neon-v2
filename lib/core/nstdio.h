/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @addtogroup neon
 *  @{
 */
/** @defgroup   nstdio Standard IO
 *  @brief      Standard IO
 *  @{
 */

#ifndef NEON_STDIO_H_
#define NEON_STDIO_H_

#include <stdint.h>
#include <stdbool.h>

#include "core/nconfig.h"
#include "core/nlqueue.h"

#ifdef __cplusplus
extern "C" {
#endif
    
/** @brief      Standard IO buffers structure.
 */
struct nstdio_buff 
{
    struct buff_out nlqueue(uint8_t, NCONFIG_STDIO_OUTPUT_BUFFER_SIZE) out;
    struct buff_in nlqueue(uint8_t, NCONFIG_STDIO_INPUT_BUFFER_SIZE) in;
};

/** @brief      Default buffer instance.
 */
extern struct nstdio_buff nstdio_buff;

void nstdio_putc(struct nstdio_buff * buff, uint8_t c);

uint8_t nstdio_getc(struct nstdio_buff * buff);

bool nstdio_flush(struct nstdio_buff * buff);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NEON_STDIO_H_ */
