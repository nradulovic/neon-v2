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
 *  @brief       Neon UART peripheral
 *
 *  @defgroup    neon_uart UART driver
 *  @brief       UART driver
 *  @{
 */

#ifndef NEON_UART_H_
#define NEON_UART_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "board_variant/board.h"

#ifdef __cplusplus
extern "C" {
#endif
    
/*===========================================================================*/
/** @defgroup   nuart_capa UART capabilities
 *  @brief      UART capabilities
 *  @{ *//*==================================================================*/

/** @brief      Supports UART (Asynchronous) mode.
 */
#define NUART_CAPA_ASYNCHRONOUS         ((uint32_t)0x1ul << 0)
    
/** @brief      Supports Synchronous Master mode.
 */
#define NUART_CAPA_SYNCHRONOYS_MASTER   ((uint32_t)0x1ul << 1)
    
/** @brief      Supports Synchronous Slave mode.
 */
#define NUART_CAPA_SYNCHRONOYS_SLAVE    ((uint32_t)0x1ul << 2)
   
/** @brief      Supports UART Single-wire mode.
 */
#define NUART_CAPA_SINGLE_WIRE          ((uint32_t)0x1ul << 3)
    
/** @brief      Supports UART IrDA mode.
 */
#define NUART_CAPA_IRDA                 ((uint32_t)0x1ul << 4)
    
/** @brief      Supports UART DALI mode.
 */
#define NUART_CAPA_DALI                 ((uint32_t)0x1ul << 5)
    
/** @brief      Supports UART Smart Card mode.
 */
#define NUART_CAPA_SMART_CARD           ((uint32_t)0x1ul << 6)
    
/** @brief      Supports UART Smart Card clock generator mode.
 */
#define NUART_CAPA_SMART_CARD_CLOCK     ((uint32_t)0x1ul << 7)

/** @brief      Supports RTS Flow Control.
 */
#define NUART_CAPA_FLOW_CTRL_RTS        ((uint32_t)0x1ul << 8)
    
/** @brief      Supports CTS Flow Control.
 */
#define NUART_CAPA_FLOW_CTRL_CTS        ((uint32_t)0x1ul << 9)

/** @} *//*==================================================================*/
/** @defgroup   nuart_callback UART callbacks and events
 *  @brief      UART callbacks and events
 *  @{ *//*==================================================================*/

/** @brief      Send completed; however USART may still transmit data.
 */
#define NUART_EVENT_TX_COMPLETE         ((uint_fast8_t)0x1ul << 0)

/** @brief      Receive completed.
 */
#define NUART_EVENT_RX_COMPLETE         ((uint_fast8_t)0x1ul << 1)

/** @brief      Transfer completed.
 */
#define NUART_EVENT_TRANSFER_COMPLETE   ((uint_fast8_t)0x1ul << 2)
    
/** @brief      Transmit data not available (Synchronous Slave).
 */
#define NUART_EVENT_TX_UNDERFLOW        ((uint_fast8_t)0x1ul << 3)
    
/** @brief      Receive data overflow.
 */
#define NUART_EVENT_RX_OVERFLOW         ((uint_fast8_t)0x1ul << 4)
    
/** @brief      Break detected on receive.
 */
#define NUART_EVENT_RX_BREAK            ((uint_fast8_t)0x1ul << 5)
    
/** @brief      Framing error detected on receive.
 */
#define NUART_EVENT_RX_FRAMING_ERROR    ((uint_fast8_t)0x1ul << 6)
    
/** @brief      Parity error detected on receive.
 */
#define NUART_EVENT_RX_PARITY_ERROR     ((uint_fast8_t)0x1ul << 7)
    
/** @brief      Send aborted; however USART may still transmit data.
 */
#define NUART_EVENT_TX_ABORTED          ((uint_fast8_t)0x1ul << 8)

/** @brief      Receive aborted.
 */
#define NUART_EVENT_RX_ABORTED          ((uint_fast8_t)0x1ul << 9)

/** @brief      Transfer aborted.
 */
#define NUART_EVENT_TRANSFER_ABORTED    ((uint_fast8_t)0x1ul << 10)
    
/** @} *//*==================================================================*/
/** @defgroup   nuart_control UART control codes
 *  @brief      UART control codes
 *  @{ *//*==================================================================*/

/** @brief      UART Mode bits position.
 */
#define NUART_MODE_Pos                  0u

/** @brief      UART Mode bits mask.
 */
#define NUART_MODE_Msk                  ((uint32_t)0xful << NUART_MODE_Pos)

/** @brief      UART Data bits position.
 */
#define NUART_DATA_BITS_Pos              4

/** @brief      UART Data bits mask.
 */
#define NUART_DATA_BITS_Msk             ((uint32_t)0x7ul << NUART_DATA_BITS_Pos)

/** @brief      UART Parity position.
 */
#define NUART_PARITY_Pos                7

/** @brief      UART Parity mask.
 */
#define NUART_PARITY_Msk                (3ul << NUART_PARITY_Pos)

/** @brief      UART Stop bits position.
 */
#define NUART_STOP_BITS_Pos             9

/** @brief      UART Stop bits mask.
 */
#define NUART_STOP_BITS_Msk             (3ul << NUART_STOP_BITS_Pos)

/** @brief      UART Flow Control position.
 */
#define NUART_FLOW_CONTROL_Pos          11

/** @brief      UART Flow Control position.
 */
#define NUART_FLOW_CONTROL_Msk          (3ul << NUART_FLOW_CONTROL_Pos)

/** @brief      UART Clock polarity position.
 */
#define NUART_CPOL_Pos                  13

/** @brief      UART Clock polarity mask.
 */
#define NUART_CPOL_Msk                  (1ul << NUART_CPOL_Pos)

/** @brief      UART Clock phase position.
 */
#define NUART_CPHA_Pos                  14

/** @brief      UART Clock phase mask.
 */
#define NUART_CPHA_Msk                  (1ul << NUART_CPHA_Pos)

/** @brief      UART command position.
 */
#define NUART_COMMAND_Pos               15u

/** @brief      UART command mask.
 */
#define NUART_COMMAND_Msk               (0xful << NUART_COMMAND_Pos)

/** @name UART control codes: mode
 *  @{ */

/** @brief      UART (Asynchronous); arg = Baudrate (default)
 */
#define NUART_MODE_ASYNCHRONOUS         (0x0ul << NUART_MODE_Pos)

/** @brief      Synchronous Master (generates clock signal); arg = Baudrate.
 */
#define NUART_MODE_SYNCHRONOUS_MASTER   (0x1ul << NUART_MODE_Pos)

/** @brief      Synchronous Slave (external clock signal).
 */
#define NUART_MODE_SYNCHRONOUS_SLAVE    (0x2ul << NUART_MODE_Pos)

/** @brief      UART Single-wire (half-duplex); arg = Baudrate.
 */
#define NUART_MODE_SINGLE_WIRE          (0x3ul << NUART_MODE_Pos)

/** @brief      UART IrDA; arg = Baudrate.
 */
#define NUART_MODE_IRDA                 (0x4ul << NUART_MODE_Pos)

/** @brief      UART DALI; arg = Bitrate.
 */
#define NUART_MODE_DALI                 (0x5ul << NUART_MODE_Pos)

/** @brief      UART Smart Card; arg = Baudrate.
 */
#define NUART_MODE_SMART_CARD           (0x6ul << NUART_MODE_Pos)

/** @} */
/** @name UART control codes: Data Bits
 *  @{ */

/** @brief      5 Data bits
 */
#define NUART_DATA_BITS_5               (2UL << NUART_DATA_BITS_Pos)

/** @brief      6 Data bits
 */
#define NUART_DATA_BITS_6               (3UL << NUART_DATA_BITS_Pos)

/** @brief      7 Data bits
 */
#define NUART_DATA_BITS_7               (4UL << NUART_DATA_BITS_Pos)

/** @brief      8 Data bits (default)
 */
#define NUART_DATA_BITS_8               (0ul << NUART_DATA_BITS_Pos)

/** @brief      9 Data bits
 */
#define NUART_DATA_BITS_9               (1ul << NUART_DATA_BITS_Pos)

/** @} */
/** @name UART control codes: Parity
 *  @{ */

/** @brief      No Parity.
 */
#define NUART_PARITY_NONE               (0ul << NUART_PARITY_Pos)

/** @brief      Even Parity.
 */
#define NUART_PARITY_EVEN               (1ul << NUART_PARITY_Pos)

/** @brief      Odd Parity.
 */
#define NUART_PARITY_ODD                (2ul << NUART_PARITY_Pos)

/** @} */
/** @name UART control codes: Stop Bits
 *  @{ */

/** @brief      1 Stop bit.
 */
#define NUART_STOP_BITS_1               (0ul << NUART_STOP_BITS_Pos)

/** @brief      2 Stop bit.
 */
#define NUART_STOP_BITS_2               (1ul << NUART_STOP_BITS_Pos)

/** @brief      1.5 Stop bit.
 */
#define NUART_STOP_BITS_1_5             (2ul << NUART_STOP_BITS_Pos)

/** @brief      0.5 Stop bit.
 */
#define NUART_STOP_BITS_0_5             (3ul << NUART_STOP_BITS_Pos)

/** @} */
/** @name UART control codes: Flow Control
 *  @{ */

/** @brief      No Flow Control.
 */
#define NUART_FLOW_CONTROL_NONE         (0ul << NUART_FLOW_CONTROL_Pos)

/** @brief      RTS Flow Control.
 */
#define NUART_FLOW_CONTROL_RTS          (1ul << NUART_FLOW_CONTROL_Pos)

/** @brief      CTS Flow Control.
 */
#define NUART_FLOW_CONTROL_CTS          (2ul << NUART_FLOW_CONTROL_Pos)

/** @brief      RTS/CTS Flow Control.
 */
#define NUART_FLOW_CONTROL_RTS_CTS      (3ul << NUART_FLOW_CONTROL_Pos)

/** @} */
/** @name UART control codes: Clock Polarity (Synchronous mode)
 *  @{ */

/** @brief      CPOL = 0.
 */
#define NUART_CPOL_0                    (0ul << NUART_CPOL_Pos)

/** @brief      CPOL = 1.
 */
#define NUART_CPOL_1                    (1ul << NUART_CPOL_Pos)

/** @} */
/** @name UART control codes: Clock Phase (Synchronous mode)
 *  @{ */

/** @brief      CPHA = 0.
 */
#define NUART_CPHA_0                    (0ul << NUART_CPHA_Pos)

/** @brief      CPHA = 1.
 */
#define NUART_CPHA_1                    (1ul << NUART_CPHA_Pos)

/** @} */
/** @name UART control codes: Commands
 *  @{ */

#define NUART_COMMAND_SETUP             (0x1ul << NUART_COMMAND_Pos)

/** @brief      Abort @ref nuart_send.
 */
#define NUART_COMMAND_ABORT_SEND        (0x2ul << NUART_COMMAND_Pos)

/** @brief      Abort @ref nuart_receive.
 */
#define NUART_COMMAND_ABORT_RECEIVE     (0x3ul << NUART_COMMAND_Pos)

/** @brief      Abort @ref nuart_transfer.
 */
#define NUART_COMMAND_ABORT_TRANSFER    (0x4ul << NUART_COMMAND_Pos)

/** @} */
/** @} *//*==================================================================*/
/** @defgroup   nuart_fn UART functions
 *  @brief      UART functions
 *  @{ *//*==================================================================*/

enum nuart_id
{
#if (NBOARD_USES_UART_1 == 1)
    NUART_ID_1,
#endif
#if (NBOARD_USES_UART_2 == 1)
    NUART_ID_2,
#endif
#if (NBOARD_USES_UART_3 == 1)
    NUART_ID_3,
#endif
#if (NBOARD_USES_UART_4 == 1)
    NUART_ID_4,
#endif
#if (NBOARD_USES_UART_5 == 1)
    NUART_ID_5,
#endif
#if (NBOARD_USES_UART_6 == 1)
    NUART_ID_6,
#endif
};

extern void nuart_callback_1(uint_fast16_t events);

typedef void (nuart_callback)(uint_fast8_t uart_id, uint_fast16_t events);

void nuart_init(enum nuart_id uart_id, nuart_callback * callback);

void nuart_term(enum nuart_id uart_id);

uint32_t nuart_capabilities(enum nuart_id uart_id);

bool nuart_is_initialized(enum nuart_id uart_id);

void nuart_control(enum nuart_id uart_id, uint32_t control_code, uint32_t arg);

void nuart_send(enum nuart_id uart_id, const void * data, size_t size);

void nuart_receive(enum nuart_id uart_id, void * data, size_t size);

void nuart_transfer(
        enum nuart_id uart_id, 
        const void * output, 
        void * input, 
        size_t size);

void nuart_send_byte(enum nuart_id uart_id, uint8_t byte);

uint8_t nuart_receive_byte(enum nuart_id uart_id);

uint8_t nuart_transfer_byte(enum nuart_id uart_id, uint8_t byte);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NEON_H_ */
