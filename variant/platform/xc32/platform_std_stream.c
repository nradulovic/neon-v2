/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */

#include <stdbool.h>
#include <stdio.h>

#include "board_variant/board.h"
#include "neon_uart.h"

static char buffer[100];
static uint32_t buffer_c;

#if (NBOARD_USES_STD_STREAM == 5)
#define drain_is_initialized()          nuart_is_initialized(NUART_ID_5)
#define drain_putc(c)                                                       \
    do {                                                                    \
        nuart_send(NUART_ID_5, (c), 1);                                     \
        while (!nuart_is_idle(NUART_ID_5));                                 \
    } while (0)
#endif

void nplatform_std_stream_init(void)
{
}

bool nplatform_std_stream_is_initialized(void)
{
    
}

#if (NBOARD_USES_STD_STREAM != 0)
void _mon_putc(char c)
{
    buffer[buffer_c] = c;
    
    if (c == '\n') {
        if (!drain_is_initialized()) {
            return;
        }
        drain_putc(&c);
    }
}
#endif