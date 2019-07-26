
#include "neon.h"
#include "neon_uart.h"
#include "pic18_uart.h"
#include "pic18_osc.h"

#if defined(NMCU_PIC18F46K40)
#endif

struct pic18_uart
{
    nuart_callback * callback;
    const uint8_t * buff_out;
    uint8_t * buff_in;
    size_t buff_size;
    size_t current_byte_out;
    size_t current_byte_in;
};

static struct pic18_uart g_pic18_uarts[] =
{
#if (NBOARD_USES_UART_1 == 1)
    {
    },
#endif
#if (NBOARD_USES_UART_2 == 1)
    {
    },
#endif
    /* There are no more than 2 UARTs available on any PIC18 */
};

#if (NBOARD_USES_UART_1 == 1)

static bool pic18_uart1_is_initialized(void)
{
    return !!RC1STAbits.SPEN;
}

static void pic18_uart1_setup_baudrate(uint32_t arg)
{
    uint16_t brg;
    
    TX1STAbits.BRGH = 1;
    BAUD1CONbits.BRG16 = 1;
    
    brg = pic18_osc_get_pbclk_hz() / (arg << 2) - 1;
    
    SP1BRGH = brg >> 8;
    SP1BRGL = brg & 0xffu;
}

static void pic18_uart1_setup(
        const struct pic18_uart_board_config * config, 
        uint32_t control_code, 
        uint32_t arg)
{
    uint32_t data_bits = control_code & NUART_DATA_BITS_Msk;
    uint32_t stop_bits = control_code & NUART_STOP_BITS_Msk;
    uint32_t parity = control_code & NUART_PARITY_Msk;
    
    /* Reset all to default state. */
    RC1STA = 0u;
    TX1STA = 0u;
    BAUD1CON = 0u;
    /* Setup UART mode */
    NASSERT((control_code & NUART_MODE_Msk) == NUART_MODE_ASYNCHRONOUS);
    /* Setup stop bits */
    NASSERT(stop_bits == NUART_STOP_BITS_1);
    /* Setup data bits & parity */
    NASSERT((data_bits == NUART_DATA_BITS_8) || \
            (data_bits == NUART_DATA_BITS_9));
    NASSERT(parity == NUART_PARITY_NONE);
    /* Are we using 9 data bits? */
    if (data_bits == NUART_DATA_BITS_9) {
        TX1STAbits.TX9 = 1;
        RC1STAbits.RC9 = 1;
    }
    /* Setup data polarity */
    if ((control_code & NUART_CPOL_Msk) == NUART_CPOL_1) {
        BAUD1CONbits.SCKP = 1;
    }
    /* Setup data phase */
    NASSERT((control_code & NUART_CPHA_Msk) == NUART_CPHA_0);
    /* Setup flow control */
    NASSERT((control_code & NUART_FLOW_CONTROL_Msk) == NUART_FLOW_CONTROL_NONE);
    /* Setup interrupts */
    PIE3bits.RC1IE = 0;
    PIE3bits.TX1IE = 0;
    /* Is this a high priority task? */
    if (config->isr_vector_prio == 1) {
        IPR3bits.RC1IP = 1;
        IPR3bits.TX1IP = 1;
    } else {
        IPR3bits.RC1IP = 0;
        IPR3bits.TX1IP = 0;
    }
    /* Setup baudrate */
    pic18_uart1_setup_baudrate(arg);
    /* Setup GPIO mux */
    RX1PPSbits.PIN = config->rx_pin;
    RX1PPSbits.PORT = config->rx_port;
    (&RA0PPS)[(config->tx_port << 3) + config->tx_pin] = 0x09;
    /* Enable transmit and receive and UART */
    RC1STAbits.CREN = 1;
    TX1STAbits.TXEN = 1;
    RC1STAbits.SPEN = 1;
}

static void pic18_uart1_control(uint32_t control_code, uint32_t arg)
{
    uint_fast16_t events = 0;
    
    switch (control_code & NUART_COMMAND_Msk) {
        case NUART_COMMAND_SETUP:
            pic18_uart1_setup(&g_pic18_uart_1_board_config, control_code, arg);
            break;
        case NUART_COMMAND_ABORT_SEND:
            PIE3bits.TX1IE = 0;
            events |= NUART_EVENT_TX_ABORTED;
            break;
        case NUART_COMMAND_ABORT_RECEIVE:
            PIE3bits.RC1IE = 0;
            events |= NUART_EVENT_RX_ABORTED;
            break;
        case NUART_COMMAND_ABORT_TRANSFER:
            PIE3bits.TX1IE = 0;
            PIE3bits.RC1IE = 0;
            events |= NUART_EVENT_TRANSFER_ABORTED;
            break;
        default:
            NASSERT_ALWAYS("Wrong control_code in nuart_control");
            break;
    }
    
    if (events) {
        g_pic18_uarts[NUART_ID_1].callback(NUART_ID_1, events);
    }
}

static void pic18_uart1_send(void)
{
    PIE3bits.TX1IE = 1;
}

static void pic18_uart1_receive(void)
{
    PIE3bits.RC1IE = 1;
}

static void pic18_uart1_isr(void)
{
    struct pic18_uart * uart = &g_pic18_uarts[NUART_ID_1];
    uint_fast16_t events = 0;
    
    if (PIE3bits.RC1IE & PIR3bits.RC1IF) {
        while (PIR3bits.RC1IF && (uart->current_byte_in != uart->buff_size)) {
            /* Check for error: Frame error */
            if (RC1STAbits.FERR) {
                events |= NUART_EVENT_RX_FRAMING_ERROR;
            }
            /* Check for error: Overflow error */
            if (RC1STAbits.OERR) {
                events |= NUART_EVENT_RX_OVERFLOW;
                RC1STAbits.CREN = 0;
                RC1STAbits.CREN = 1;
            }
            uart->buff_in[uart->current_byte_in] = RC1REG;
            uart->current_byte_in++;
        }

        if (uart->current_byte_in == uart->buff_size) {
            events |= NUART_EVENT_RX_COMPLETE;
            PIE3bits.RC1IE = 0;
        }
    }
    if (PIE3bits.TX1IE & PIR3bits.TX1IF) {
        
        if (uart->current_byte_out != uart->buff_size) {
            TX1REG = uart->buff_out[uart->current_byte_out];
            uart->current_byte_out++;
        } else {
            PIE3bits.TX1IE = 0;
            events |= NUART_EVENT_TX_COMPLETE;
        }
    }
    
    if (events) {
        uart->callback(NUART_ID_1, events);
    }
}
#endif /* NBOARD_USES_UART_1 == 1 */

void pic18_uart_init(void)
{
#if (NBOARD_USES_UART_1 == 1)
    nlogger_info("PIC18 UART: Init %u with %x:%u",
            NUART_ID_1,
            g_pic18_uart_1_board_config.control_code,
            g_pic18_uart_1_board_config.arg);
    nuart_control(
            NUART_ID_1,
            g_pic18_uart_1_board_config.control_code | NUART_COMMAND_SETUP,
            g_pic18_uart_1_board_config.arg);
#endif
}

void pic18_uart_isr(void)
{
#if (NBOARD_USES_UART_1)
    pic18_uart1_isr();
#endif
#if (NBOARD_USES_UART_2)
    pic18_uart2_isr();
#endif
}

void nuart_init(enum nuart_id uart_id, nuart_callback * callback)
{
    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic18_uarts));
    NASSERT(callback != NULL);

    g_pic18_uarts[uart_id].callback = callback;
}

void nuart_term(enum nuart_id uart_id)
{
    struct pic18_uart * uart;

    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic18_uarts));

    g_pic18_uarts[uart_id].callback = NULL;
}

uint32_t nuart_capabilities(enum nuart_id uart_id)
{
    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic18_uarts));
    
    switch (uart_id) {
#if (NBOARD_USES_UART_1)
        case NUART_ID_1:
            return NUART_CAPA_ASYNCHRONOUS;
#endif
#if (NBOARD_USES_UART_2)
        case NUART_ID_2:
            return NUART_CAPA_ASYNCHRONOUS;
#endif
    }
}

bool nuart_is_initialized(enum nuart_id uart_id)
{
    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic18_uarts));
    
    switch (uart_id) {
#if (NBOARD_USES_UART_1)
        case NUART_ID_1:
            return pic18_uart1_is_initialized();
#endif
#if (NBOARD_USES_UART_2)
        case NUART_ID_2:
            return pic18_uart2_is_initialized();
#endif
    }
}

void nuart_control(enum nuart_id uart_id, uint32_t control_code, uint32_t arg)
{
    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic18_uarts));
    
    switch (uart_id) {
#if (NBOARD_USES_UART_1)
        case NUART_ID_1:
            pic18_uart1_control(control_code, arg);
            return;
#endif
#if (NBOARD_USES_UART_2)
        case NUART_ID_2:
            pic18_uart2_control(control_code, arg);
            return;
#endif
    }
}

void nuart_send(enum nuart_id uart_id, const void * data, size_t size)
{
    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic18_uarts));
    
    g_pic18_uarts[uart_id].buff_out = data;
    g_pic18_uarts[uart_id].buff_size = size;
    g_pic18_uarts[NUART_ID_1].current_byte_out = 0;
    
    switch (uart_id) {
#if (NBOARD_USES_UART_1)
        case NUART_ID_1:
            pic18_uart1_send();
            break;
#endif
#if (NBOARD_USES_UART_2)
        case NUART_ID_2:
            pic18_uart2_send();
            break;
#endif  
    }
}

void nuart_receive(enum nuart_id uart_id, void * data, size_t size)
{
    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic18_uarts));
    
    g_pic18_uarts[uart_id].buff_in = data;
    g_pic18_uarts[uart_id].buff_size = size;
    g_pic18_uarts[uart_id].current_byte_in = 0;
    
    switch (uart_id) {
#if (NBOARD_USES_UART_1)
        case NUART_ID_1:
            pic18_uart1_receive();
            break;
#endif
#if (NBOARD_USES_UART_2)
        case NUART_ID_2:
            pic18_uart2_receive();
            break;
#endif  
    }
}

void nuart_transfer(
        enum nuart_id uart_id, 
        const void * output, 
        void * input, 
        size_t size)
{
    nuart_receive(uart_id, input, size);
    nuart_send(uart_id, output, size);
}
