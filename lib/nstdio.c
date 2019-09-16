/*
 * Neon
 * Copyright (C) 2018   REAL-TIME CONSULTING
 *
 * For license information refer to LGPL-3.0.md file at the root of this project.
 */
/** @file
 *  @defgroup   nstdio_impl Standard IO implementation
 *  @brief      Standard IO implementation
 *  @{ *//*==================================================================*/

#include "core/nstdio.h"

#if (NBOARD_USES_STD_STREAM > 0) && (NBOARD_USES_STD_STREAM < 16)
#include "neon_uart.h"

#if (NBOARD_USES_STD_STREAM == 1)
#define NUART_ID                        NUART_ID_1
#define NSTREAM_ISR_CALLBACK                       nuart_callback_1
#elif (NBOARD_USES_STD_STREAM == 2)
#define NUART_ID                        NUART_ID_2
#define NSTREAM_ISR_CALLBACK                       nuart_callback_2
#elif (NBOARD_USES_STD_STREAM == 5)
#define NUART_ID                        NUART_ID_5
#define NSTREAM_ISR_CALLBACK                       nuart_callback_5
#else
#define NUART_ID                        NUART_ID_15
#define NSTREAM_ISR_CALLBACK                       nuart_callback_15
#endif
    
#define NSTREAM_INIT()                  nuart_init(NUART_ID, NULL)
   
#define NSTREAM_IS_INITIALIZED()        nuart_is_initialized(NUART_ID)
    
#define NSTREAM_SEND(buffer, size)      nuart_send(NUART_ID, (buffer), (size))

#define NSTREAM_SEND_BYTE(byte)         nuart_send_byte(NUART_ID, (byte))

#define NSTREAM_RECEIVE_BYTE()          nuart_receive_byte(NUART_ID)

#elif (NBOARD_USES_STD_STREAM >= 16) && (NBOARD_USES_STD_STREAM < 32)
#elif (NBOARD_USES_STD_STREAM >= 32) && (NBOARD_USES_STD_STREAM < 48)
#endif

struct nstdio_buff nstdio_buff;

#if !defined(NSTREAM_RECEIVE_BYTE)
#define NSTREAM_RECEIVE_BYTE()			getchar()
#endif

#if !defined(NSTREAM_SEND_BYTE)
#define NSTREAM_SEND_BYTE(c)			putchar(c)
#endif

#if !defined(NSTREAM_IS_INITIALIZED)
#define NSTREAM_IS_INITIALIZED()		true
#endif

void nstdio_putc(struct nstdio_buff * buff, uint8_t c)
{
    static bool is_initialized;
    
    if (!is_initialized) {
        is_initialized = true;
        NLQUEUE_INIT(&buff->out);
    }
    NLQUEUE_PUT_FIFO(&buff->out, c);
}

uint8_t nstdio_getc(struct nstdio_buff * buff)
{
    return NSTREAM_RECEIVE_BYTE();
}

bool nstdio_flush(struct nstdio_buff * buff)
{
    if (!NSTREAM_IS_INITIALIZED()) {
        return false;
    }
    while (!NLQUEUE_IS_EMPTY(&buff->out)) {
        char c;
        
        c = NLQUEUE_GET(&buff->out);
        NSTREAM_SEND_BYTE(c);
    }
    
    return true;
}

/** @} */
