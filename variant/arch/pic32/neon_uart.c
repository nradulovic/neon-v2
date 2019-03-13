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

#include "neon.h"
#include "neon_uart.h"
#include "pic32_isr.h"
#include "pic32_uart.h"
#include "pic32_common.h"
#include "pic32_osc.h"
#include <xc.h>

#if defined(__32MX534F064H__)
#define HAS_MODE_UEN
#define HAS_MODE_RTSMD
#define HAS_MODE_RUNOVF
#define HAS_MODE_CLKSEL
#define HAS_MODE_ACTIVE
#define HAS_MODE_SLPEN
#define HAS_STA_ADM_EN
#endif


#define UxMODE_STSEL_Pos                0
#define UxMODE_PDSEL_Pos                1
#define UxMODE_BRGH_Pos                 3
#define UxMODE_RXINV_Pos                4
#define UxMODE_UEN_Pos                  8
#define UxMODE_ON_Pos                   15
#define UxMODE_ACTIVE_Pos               22

#define UxSTA_UTXEN_Pos                 10
#define UxSTA_URXEN_Pos                 12
#define UxSTA_UTXINV_Pos                13

#define MOD_REG(reg, mask, pos, data)                                       \
        do {                                                                \
            *(reg) &= ~(mask);                                              \
            *(reg) |= ((uint32_t)(data)) << (pos);                          \
        } while (0)

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
    uint8_t isr_e_id;
    uint8_t isr_tx_id;
    uint8_t isr_rx_id;
};

struct nuart
{
    struct pic32_uart_sfr * sfr;
    const struct pic32_uart_desc * desc;
    nuart_callback * callback;
};

#if defined(NMCU_HAS_UART_5)
static const struct pic32_uart_desc g_uart_5_desc =
{
    .board_config = &g_uart_5_board_config,
    .capabilities = NUART_CAPA_ASYNCHRONOUS,
    .isr_e_id = PIC32_ISR_U5E,
    .isr_rx_id = PIC32_ISR_U5RX,
    .isr_tx_id = PIC32_ISR_U5TX
};

struct nuart g_uart_5 =
{
    .sfr = (struct pic32_uart_sfr *)&U5MODE,
    .desc = &g_uart_5_desc
};

#endif

void nuart_init(struct nuart * uart, nuart_callback * callback)
{
    uart->callback = callback;
}

void nuart_term(struct nuart * uart)
{
    
}

uint32_t nuart_capabilities(const struct nuart * uart)
{
    return uart->desc->capabilities;
}

static void uart_setup(struct nuart * uart, uint32_t control_code, uint32_t arg)
{
    uint32_t data_bits = control_code & NUART_DATA_BITS_Msk;
    uint32_t stop_bits = control_code & NUART_STOP_BITS_Msk;
    uint32_t parity = control_code & NUART_PARITY_Msk;
    struct pic32_uart_sfr * sfr = uart->sfr;
    
    NASSERT((control_code & NUART_MODE_Msk) == NUART_MODE_ASYNCHRONOUS);

#if defined(HAS_MODE_ACTIVE)
    while (sfr->mode.reg & UxMODE_ACTIVE_Msk);
#endif
    sfr->sta.reg = 0ul;
    sfr->mode.reg = 0ul;
         
    /* Setup baudrate */
    if (arg > (g_osc_pbclk / 16)) {
        sfr->mode.set = 0x1ul << UxMODE_BRGH_Pos;
        sfr->brg = g_osc_pbclk / (4ul * arg) - 1ul;
    } else {
        sfr->brg = g_osc_pbclk / (16ul * arg) - 1ul;
    }
    
    /* Setup stop bits */
    NASSERT((stop_bits == NUART_STOP_BITS_1) || \
            (stop_bits == NUART_STOP_BITS_2));
    
    if (stop_bits == NUART_STOP_BITS_2) {
        sfr->mode.set = 0x1u << UxMODE_STSEL_Pos;
    }
    
    /* Setup data bits & parity */
    NASSERT((data_bits == NUART_DATA_BITS_8) || \
            (data_bits == NUART_DATA_BITS_9));
    
    if (data_bits == NUART_DATA_BITS_8) {
        NASSERT((parity == NUART_PARITY_NONE) || \
                (parity == NUART_PARITY_EVEN) || \
                (parity == NUART_PARITY_ODD));
        
        if (parity == NUART_PARITY_ODD) {
            sfr->mode.set = 0x2u << UxMODE_PDSEL_Pos;
        } else if (parity == NUART_PARITY_EVEN) {
            sfr->mode.set = 0x1u << UxMODE_PDSEL_Pos;
        }
    } else {
        NASSERT(parity == NUART_PARITY_NONE);
        sfr->mode.set = 0x3u << UxMODE_PDSEL_Pos;
    }
    
    /* Setup data polarity */
    if ((control_code & NUART_CPOL_Msk) == NUART_CPOL_1) {
        sfr->mode.set = 0x1u << UxMODE_RXINV_Pos;
        sfr->sta.set  = 0x1u << UxSTA_UTXINV_Pos;
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
            sfr->mode.set = 0x1ul << UxMODE_UEN_Pos;
        } else if (flow_control == NUART_FLOW_CONTROL_RTS_CTS) {
            sfr->mode.set = 0x2ul << UxMODE_UEN_Pos;
        }
    }
#else
    NASSERT((control_code & NUART_FLOW_CONTROL_Msk) == NUART_FLOW_CONTROL_NONE);
#endif
#if defined(HAS_MODE_RTSMD)
    /* Setup MODE:RTSMD -> leave to zero: UxRTS pin in Flow Control Mode. */
#endif
    sfr->mode.set = 0x1ul << UxMODE_ON_Pos; /* Turn on UART peripheral */
    sfr->sta.set = 0x1ul << UxSTA_UTXEN_Pos;
    sfr->sta.set = 0x1ul << UxSTA_URXEN_Pos;
    
    /* Setup interrupts */
}

void nuart_control(struct nuart * uart, uint32_t control_code, uint32_t arg)
{
    switch (control_code & NUART_COMMAND_Msk) {
        case NUART_COMMAND_SETUP:
            uart_setup(uart, control_code, arg);
            break;
        case NUART_COMMAND_ABORT_SEND:
            break;
        case NUART_COMMAND_ABORT_RECEIVE:
            break;
        case NUART_COMMAND_ABORT_TRANSFER:
            break;
        default:
            NASSERT_ALWAYS(control_code);
            break;
    }
}

void nuart_send(struct nuart * uart, const void * data, size_t size)
{
    
}

void nuart_receive(struct nuart * uart, void * data, size_t size)
{
    
}

void nuart_transfer(struct nuart * uart, const void * output, void * input, size_t size)
{
    
}

uint32_t nuart_rx_count(const struct nuart * uart)
{
    
}

uint32_t nuart_tx_count(const struct nuart * uart)
{
    
}

void pic32_uart_isr_handler(struct nuart * uart)
{
    
}