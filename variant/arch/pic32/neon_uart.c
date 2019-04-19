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

#include <xc.h>
#include <sys/attribs.h>

#include "neon.h"
#include "pic32_isr.h"
#include "pic32_uart.h"
#include "pic32_common.h"
#include "pic32_osc.h"

#if defined(NMCU_PIC32MX534F064H)
#define HAS_MODE_UEN
#define HAS_MODE_RTSMD
#define HAS_MODE_RUNOVF
#define HAS_MODE_CLKSEL
#define HAS_MODE_ACTIVE
#define HAS_MODE_SLPEN
#define HAS_STA_ADM_EN
#define HAS_TX_FIFO 8
#define HAS_RX_FIFO 8
#endif

/* These are the mask definitions*/
#define    UxMODE_ABAUD_MASK        _U1MODE_ABAUD_MASK
#define UxMODE_BRGH_MASK                _U1MODE_BRGH_MASK
#define UxMODE_ON_MASK                  _U1MODE_ON_MASK
#define UxMODE_RXINV_MASK               _U1MODE_RXINV_MASK
#define    UxMODE_SIDL_MASK         _U1MODE_SIDL_MASK
#define    UxMODE_IREN_MASK         _U1MODE_IREN_MASK
#define    UxMODE_STSEL_MASK        _U1MODE_STSEL_MASK
#define UxMODE_PDSEL_MASK               _U1MODE_PDSEL_MASK
#define UxMODE_PDSEL_POS                _U1MODE_PDSEL_POSITION
#define    UxMODE_LPBACK_MASK       _U1MODE_LPBACK_MASK
#define    UxMODE_WAKE_MASK         _U1MODE_WAKE_MASK
#define UxMODE_UEN_MASK                 _U1MODE_UEN_MASK
#define UxMODE_UEN_POS                  _U1MODE_UEN_POSITION
#define    UxMODE_RUNOVF_MASK       _U1MODE_RUNOVF_MASK
#define    UxMODE_SLPEN_MASK        _U1MODE_SLPEN_MASK

#define UxSTA_URXDA_MASK                _U1STA_URXDA_MASK
#define UxSTA_RIDLE_MASK                _U1STA_RIDLE_MASK
#define UxSTA_UTXISEL_MASK              _U1STA_UTXISEL_MASK
#define UxSTA_UTXISEL_POS               _U1STA_UTXISEL_POSITION
#define UxSTA_TRMT_MASK                 _U1STA_TRMT_MASK
#define UxSTA_UTXBF_MASK                _U1STA_UTXBF_MASK
#define UxSTA_UTXEN_MASK                _U1STA_UTXEN_MASK
#define    UxSTA_URXEN_MASK         _U1STA_URXEN_MASK
#define    UxSTA_ADDR_MASK          _U1STA_ADDR_MASK
#define    UxSTA_ADDR_POSITION      _U1STA_ADDR_POSITION
#define    UxSTA_ADDEN_MASK         _U1STA_ADDEN_MASK
#define    UxSTA_MASK_MASK          _U1STA_MASK_MASK
#define    UxSTA_MASK_POSITION      _U1STA_MASK_POSITION
#define    UxSTA_URXISEL_MASK       _U1STA_URXISEL_MASK
#define    UxSTA_URXISEL_POSITION   _U1STA_URXISEL_POSITION

#define    UxSTA_OERR_MASK          _U1STA_OERR_MASK
#define    UxSTA_UTXBRK_MASK        _U1STA_UTXBRK_MASK
#define UxSTA_UTXINV_MASK               _U1STA_UTXINV_MASK
#define    UxSTA_ADM_EN_MASK        _U1STA_ADM_EN_MASK

#define UxMODE_ACTIVE_Pos               22

#define UxSTA_OERR_Pos                  1
#define UxSTA_FERR_Pos                  2
#define UxSTA_PERR_Pos                  3
#define UxSTA_URXEN_Pos                 12

#define uart_id_from_uart(a_uart)       ((a_uart) - g_pic32_uarts)

struct pic32_uart_sfr
{
    struct pic32_periph_reg mode;
    struct pic32_periph_reg sta;
    struct pic32_periph_reg txreg;
    struct pic32_periph_reg rxreg;
    struct pic32_periph_reg brg;
};

struct pic32_uart_desc
{
    const struct pic32_uart_board_config * board_config;
    uint32_t capabilities;
    uint_fast8_t isr_vector;
    uint_fast8_t isr_irq_e;
    uint_fast8_t isr_irq_rx;
    uint_fast8_t isr_irq_tx;
};

struct pic32_uart
{
    struct pic32_uart_sfr * sfr;
    nuart_callback * callback;
    const uint8_t * buff_out;
    uint8_t * buff_in;
    size_t buff_size;
    size_t current_byte_out;
    size_t current_byte_in;
};

static const struct pic32_uart_desc g_pic32_uarts_desc[] =
{
#if (NBOARD_USES_UART_1 == 1)
    {
        .board_config = &NBOARD_UART_1_CONFIG,
        .capabilities = NUART_CAPA_ASYNCHRONOUS,
        .isr_e_tx_rx_id = PIC32_ISR_U1E_RX_TX,
    },
#endif
#if (NBOARD_USES_UART_2 == 1)
    {
        .board_config = &NBOARD_UART_2_CONFIG,
        .capabilities = NUART_CAPA_ASYNCHRONOUS,
        .isr_e_tx_rx_id = PIC32_ISR_U2E_RX_TX,
    },
#endif
#if (NBOARD_USES_UART_3 == 1)
    {
        .board_config = &NBOARD_UART_3_CONFIG,
        .capabilities = NUART_CAPA_ASYNCHRONOUS,
        .isr_e_tx_rx_id = PIC32_ISR_U3E_RX_TX,
    },
#endif
#if (NBOARD_USES_UART_4 == 1)
    {
        .board_config = &NBOARD_UART_4_CONFIG,
        .capabilities = NUART_CAPA_ASYNCHRONOUS,
        .vector_id_e_rx_tx = PIC32_ISR_U4E_RX_TX,
    },
#endif
#if (NBOARD_USES_UART_5 == 1)
    {
        .board_config = &g_pic32_uart_5_board_config,
        .capabilities = NUART_CAPA_ASYNCHRONOUS,
        .isr_vector = _UART_5_VECTOR,
        .isr_irq_e  = _UART5_ERR_IRQ,
        .isr_irq_rx = _UART5_RX_IRQ,
        .isr_irq_tx = _UART5_TX_IRQ,
    },
#endif
};

static struct pic32_uart g_pic32_uarts[] =
{
#if (NBOARD_USES_UART_1 == 1)
    {
        .sfr = (struct pic32_uart_sfr *)&U1MODE,
    },
#endif
#if (NBOARD_USES_UART_2 == 1)
    {
        .sfr = (struct pic32_uart_sfr *)&U2MODE,
    },
#endif
#if (NBOARD_USES_UART_3 == 1)
    {
        .sfr = (struct pic32_uart_sfr *)&U3MODE,
    },
#endif
#if (NBOARD_USES_UART_4 == 1)
    {
        .sfr = (struct pic32_uart_sfr *)&U4MODE,
    },
#endif
#if (NBOARD_USES_UART_5 == 1)
    {
        .sfr = (struct pic32_uart_sfr *)&U5MODE,
    },
#endif
    /* There are no more than 5 UARTs available on any PIC32 */
};

static void pic32_uart_setup_baudrate(
        struct pic32_uart_sfr * sfr,
        uint32_t baudrate)
{
    uint32_t pbclk;
    uint32_t brgh_lo;
    uint32_t brgh_hi;

    pbclk = pic32_osc_get_pbclk_hz();

    /* Find the BRG Value */
    brgh_lo = (((pbclk >> 4u) + (baudrate >> 1u)) / baudrate) - 1u;
    brgh_hi = (((pbclk >> 2u) + (baudrate >> 1u)) / baudrate) - 1u;

    if (brgh_hi <= UINT16_MAX) {
        /* Set BRGH */
        sfr->mode.set = UxMODE_BRGH_MASK;
        sfr->brg.reg  = brgh_hi;
    } else {
        /* Clear BRGH */
        sfr->mode.clr = UxMODE_BRGH_MASK;
        sfr->brg.reg  = brgh_lo;
    }
}

static void pic32_uart_setup(
        struct pic32_uart * uart,
        const struct pic32_uart_desc * desc,
        uint32_t control_code,
        uint32_t arg)
{
    uint32_t data_bits = control_code & NUART_DATA_BITS_Msk;
    uint32_t stop_bits = control_code & NUART_STOP_BITS_Msk;
    uint32_t parity = control_code & NUART_PARITY_Msk;
    struct pic32_uart_sfr * sfr = uart->sfr;

    NASSERT((control_code & NUART_MODE_Msk) == NUART_MODE_ASYNCHRONOUS);

#if defined(HAS_MODE_ACTIVE)
    while (sfr->mode.reg & (0x1ul << UxMODE_ACTIVE_Pos));
#endif
    sfr->sta.reg = 0ul;
    sfr->mode.reg = 0ul;

    /* Setup stop bits */
    NASSERT((stop_bits == NUART_STOP_BITS_1) || \
            (stop_bits == NUART_STOP_BITS_2));

    if (stop_bits == NUART_STOP_BITS_2) {
        sfr->mode.set = UxMODE_STSEL_MASK;
    }

    /* Setup data bits & parity */
    NASSERT((data_bits == NUART_DATA_BITS_8) || \
            (data_bits == NUART_DATA_BITS_9));

    if (data_bits == NUART_DATA_BITS_8) {
        NASSERT((parity == NUART_PARITY_NONE) || \
                (parity == NUART_PARITY_EVEN) || \
                (parity == NUART_PARITY_ODD));

        if (parity == NUART_PARITY_ODD) {
            sfr->mode.set = 0x2u << UxMODE_PDSEL_POS;
        } else if (parity == NUART_PARITY_EVEN) {
            sfr->mode.set = 0x1u << UxMODE_PDSEL_POS;
        }
    } else {
        NASSERT(parity == NUART_PARITY_NONE);
        sfr->mode.set = 0x3u << UxMODE_PDSEL_POS;
    }

    /* Setup data polarity */
    if ((control_code & NUART_CPOL_Msk) == NUART_CPOL_1) {
        sfr->mode.set = UxMODE_RXINV_MASK;
        sfr->sta.set  = UxSTA_UTXINV_MASK;
    }
    /* Setup data phase */
    NASSERT((control_code & NUART_CPHA_Msk) == NUART_CPHA_0);

    /* Setup low-power wakeup event: TODO: Create API for this feature. */
    /* MODE:WAKE -> leave to zero: Wake up is disabled. */
    /* MODE:SIDL -> leave to zero: Continue operation in Idle mode. */

    /* Setup flow control */
#if defined(HAS_MODE_UEN)
    {
        uint32_t flow_control = control_code & NUART_FLOW_CONTROL_Msk;

        NASSERT((flow_control == NUART_FLOW_CONTROL_NONE) || \
            (flow_control == NUART_FLOW_CONTROL_RTS)  || \
            (flow_control == NUART_FLOW_CONTROL_RTS_CTS));

        if (flow_control == NUART_FLOW_CONTROL_RTS) {
            sfr->mode.set = 0x1ul << UxMODE_UEN_POS;
        } else if (flow_control == NUART_FLOW_CONTROL_RTS_CTS) {
            sfr->mode.set = 0x2ul << UxMODE_UEN_POS;
        }
    }
#else
    NASSERT((control_code & NUART_FLOW_CONTROL_Msk) == NUART_FLOW_CONTROL_NONE);
#endif
#if defined(HAS_MODE_RTSMD)
    /* Setup MODE:RTSMD -> leave to zero: UxRTS pin in Flow Control Mode. */
#endif

    /* Setup interrupts */
    pic32_isr_irq_clear(desc->isr_irq_e);
    pic32_isr_irq_clear(desc->isr_irq_rx);
    pic32_isr_irq_clear(desc->isr_irq_tx);
    pic32_isr_irq_disable(desc->isr_irq_e);
    pic32_isr_irq_disable(desc->isr_irq_rx);
    pic32_isr_irq_disable(desc->isr_irq_tx);
    pic32_isr_vector_set_prio(
            desc->isr_vector,
            desc->board_config->isr_vector_prio);

    /* In 4-level FIFO:
     *  Interrupt is generated when all characters have been transmitted
     *
     * In 8-level FIFO:
     *  Interrupt is generated and asserted when all characters have been
     *  transmitted
     */
    uart->sfr->sta.set = 0x1ul << UxSTA_UTXISEL_POS;

    /* Setup baudrate */
    pic32_uart_setup_baudrate(sfr, arg);

    /* Setup GPIO mux */
    
    /* Enable transmit and receive and UART */
    sfr->sta.set = (UxSTA_UTXEN_MASK | UxSTA_URXEN_MASK);
    sfr->mode.set = UxMODE_ON_MASK; /* Turn on UART peripheral */
}

static void pic32_uart_write_tx_fifo(struct pic32_uart * uart)
{
    while (((uart->sfr->sta.reg & UxSTA_UTXBF_MASK) == 0) &&
            (uart->current_byte_out < uart->buff_size)) {
        uart->sfr->txreg.reg = uart->buff_out[uart->current_byte_out];
        uart->current_byte_out++;
    }
}

static void pic32_uart_read_rx_fifo(struct pic32_uart * uart)
{
    while (((uart->sfr->sta.reg & UxSTA_URXDA_MASK) == 1) &&
            (uart->current_byte_in < uart->buff_size)) {
        uart->buff_in[uart->current_byte_in] = uart->sfr->rxreg.reg;
        uart->current_byte_in++;
    }
}

static void pic32_uart_isr_handler(
        struct pic32_uart * uart,
        const struct pic32_uart_desc * desc)
{
    uint32_t events = 0u;

    if (pic32_isr_irq_is_set(desc->isr_irq_e)) {
        /* UART x Error interrupt */
        uint32_t status = uart->sfr->sta.reg;

        if (status & UxSTA_OERR_MASK) {
            uart->sfr->sta.clr = UxSTA_OERR_MASK;
            events |= NUART_EVENT_RX_OVERFLOW;
        }
        if (status & (0x1ul << UxSTA_FERR_Pos)) {
            events |= NUART_EVENT_RX_FRAMING_ERROR;
        }
        if (status & (0x1ul << UxSTA_PERR_Pos)) {
            events |= NUART_EVENT_RX_PARITY_ERROR;
        }
        pic32_isr_irq_clear(desc->isr_irq_e);
    }

    if (pic32_isr_irq_is_set(desc->isr_irq_rx)) {
        /* UART x Receiver interrupt */
        pic32_uart_read_rx_fifo(uart);
        pic32_isr_irq_clear(desc->isr_irq_rx);

        if (uart->current_byte_in == uart->buff_size) {
            uart->buff_in = NULL;
            pic32_isr_irq_disable(desc->isr_irq_rx);
            pic32_isr_irq_disable(desc->isr_irq_e);
            events |= NUART_EVENT_TX_COMPLETE;
        }
    }
    if (pic32_isr_irq_is_set(desc->isr_irq_tx)) {
        /* UART x Transmitter interrupt */
        pic32_uart_write_tx_fifo(uart);
        pic32_isr_irq_clear(desc->isr_irq_tx);

        if (uart->current_byte_out == uart->buff_size) {
            uart->buff_out = NULL;
            pic32_isr_irq_disable(desc->isr_irq_tx);
            events |= NUART_EVENT_TX_COMPLETE;
        }
    }

    if (events != 0u) {
        uart->callback(uart_id_from_uart(uart), events);
    }
}

void pic32_uart_init(void)
{
#if (NBOARD_USES_UART_5 == 1)
    nlogger_info("PIC32 UART: Init %u with %x:%u",
            NUART_ID_5,
            g_pic32_uart_5_board_config.control_code,
            g_pic32_uart_5_board_config.arg);
    nuart_control(
            NUART_ID_5,
            g_pic32_uart_5_board_config.control_code | NUART_COMMAND_SETUP,
            g_pic32_uart_5_board_config.arg);
#endif
}

void nuart_init(enum nuart_id uart_id, nuart_callback * callback)
{
    struct pic32_uart * uart;

    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic32_uarts));
    NASSERT(callback != NULL);

    uart = &g_pic32_uarts[uart_id];
    uart->callback = callback;
}

void nuart_term(enum nuart_id uart_id)
{
    struct pic32_uart * uart;

    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic32_uarts));

    uart = &g_pic32_uarts[uart_id];
    uart->callback = NULL;
}

uint32_t nuart_capabilities(enum nuart_id uart_id)
{
    const struct pic32_uart_desc * desc;

    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic32_uarts_desc));

    desc = &g_pic32_uarts_desc[uart_id];

    return desc->capabilities;
}

bool nuart_is_initialized(enum nuart_id uart_id)
{
    struct pic32_uart * uart;

    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic32_uarts));

    uart = &g_pic32_uarts[uart_id];

    return !!(uart->sfr->mode.reg & UxMODE_ON_MASK);
}

void nuart_control(enum nuart_id uart_id, uint32_t control_code, uint32_t arg)
{
    struct pic32_uart * uart = &g_pic32_uarts[uart_id];
    const struct pic32_uart_desc * desc = &g_pic32_uarts_desc[uart_id];

    switch (control_code & NUART_COMMAND_Msk) {
        case NUART_COMMAND_SETUP:
            pic32_uart_setup(uart, desc, control_code, arg);
            break;
        case NUART_COMMAND_ABORT_SEND:
            break;
        case NUART_COMMAND_ABORT_RECEIVE:
            break;
        case NUART_COMMAND_ABORT_TRANSFER:
            break;
        default:
            NASSERT_ALWAYS("Wrong control_code in nuart_control");
            break;
    }
}

void nuart_send(enum nuart_id uart_id, const void * data, size_t size)
{
    struct pic32_uart * uart;
    const struct pic32_uart_desc * desc;

    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic32_uarts));

    uart = &g_pic32_uarts[uart_id];

    NASSERT(uart->callback != NULL);

    desc = &g_pic32_uarts_desc[uart_id];

    uart->buff_out = data;
    uart->buff_size = size;
    uart->current_byte_out = 0u;

    /*
     * First, fill in the available buffer.
     */
    pic32_uart_write_tx_fifo(uart);
    pic32_isr_irq_enable(desc->isr_irq_tx);
}

void nuart_receive(enum nuart_id uart_id, void * data, size_t size)
{
    struct pic32_uart * uart;
    const struct pic32_uart_desc * desc;

    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic32_uarts));

    uart = &g_pic32_uarts[uart_id];
    desc = &g_pic32_uarts_desc[uart_id];

    NASSERT(uart->callback != NULL);

    uart->buff_in = data;
    uart->buff_size = size;
    uart->current_byte_out = 0u;
    pic32_isr_irq_enable(desc->isr_irq_e);
    pic32_isr_irq_enable(desc->isr_irq_rx);
}

void nuart_transfer(
        enum nuart_id uart_id,
        const void * output,
        void * input,
        size_t size)
{
    struct pic32_uart * uart;
    const struct pic32_uart_desc * desc;

    NASSERT(uart_id < NBITS_ARRAY_SIZE(g_pic32_uarts));

    uart = &g_pic32_uarts[uart_id];
    desc = &g_pic32_uarts_desc[uart_id];

    NASSERT(uart->callback != NULL);

    uart->buff_out = output;
    uart->buff_in = input;
    uart->buff_size = size;
    uart->current_byte_out = 0u;

    /*
     * First, fill in the available buffer.
     */
    pic32_uart_write_tx_fifo(uart);
    pic32_isr_irq_enable(desc->isr_irq_e);
    pic32_isr_irq_enable(desc->isr_irq_rx);
    pic32_isr_irq_enable(desc->isr_irq_tx);
}

#if (NBOARD_USES_UART_1 == 1)
void __ISR(_UART_1_VECTOR, ipl1AUTO) pic32_uart_1_isr_handler(void)
{
    pic32_uart_isr_handler(NUART_ID_1);
}
#endif

#if (NBOARD_USES_UART_2 == 1)
void __ISR(_UART_2_VECTOR, ipl1AUTO) pic32_uart_2_isr_handler(void)
{
    pic32_uart_isr_handler(NUART_ID_2);
}
#endif

#if (NBOARD_USES_UART_3 == 1)
void __ISR(_UART_3_VECTOR, ipl1AUTO) pic32_uart_3_isr_handler(void)
{
    pic32_uart_isr_handler(NUART_ID_3);
}
#endif

#if (NBOARD_USES_UART_4 == 1)
void __ISR(_UART_4_VECTOR, ipl1AUTO) pic32_uart_4_isr_handler(void)
{
    pic32_uart_isr_handler(NUART_ID_4);
}
#endif


#if (NBOARD_USES_UART_5 == 1)
#if !defined(PIC32_BOARD_UART_5_ISR_PRIO)
#error "Define PIC32_BOARD_UART_5_ISR_PRIO to declare ISR with proper ISR priority"
#endif
void PIC32_SOFT_ISR_DECL(_UART_5_VECTOR, PIC32_BOARD_UART_5_ISR_PRIO) pic32_uart_5_isr_handler(void)
{
    pic32_uart_isr_handler(
            &g_pic32_uarts[NUART_ID_5],
            &g_pic32_uarts_desc[NUART_ID_5]);
}
#endif