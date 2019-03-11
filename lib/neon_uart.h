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

#include "mcu_variant/mcu.h"

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
#define NUART_EVENT_SEND_COMPLETE       ((uint32_t)0x1ul << 0)

/** @brief      Receive completed.
 */
#define NUART_EVENT_RECEIVE_COMPLETE    ((uint32_t)0x1ul << 1)

/** @brief      Transfer completed.
 */
#define NUART_EVENT_TRANSFER_COMPLETE   ((uint32_t)0x1ul << 2)
    
/** @brief      Transmit completed (optional).
 */
#define NUART_EVENT_TX_COMPLETE         ((uint32_t)0x1ul << 3)

/** @brief      Transmit data not available (Synchronous Slave).
 */
#define NUART_EVENT_TX_UNDERFLOW        ((uint32_t)0x1ul << 4)
    
/** @brief      Receive data overflow.
 */
#define NUART_EVENT_RX_OVERFLOW         ((uint32_t)0x1ul << 5)
    
/** @brief      Receive character timeout (optional).
 */
#define NUART_EVENT_RX_TIMEOUT          ((uint32_t)0x1ul << 6)
    
/** @brief      Break detected on receive.
 */
#define NUART_EVENT_RX_BREAK            ((uint32_t)0x1ul << 7)
    
/** @brief      Framing error detected on receive.
 */
#define NUART_EVENT_RX_FRAMING_ERROR    ((uint32_t)0x1ul << 8)
    
/** @brief      Parity error detected on receive.
 */
#define NUART_EVENT_RX_PARITY_ERROR     ((uint32_t)0x1ul << 9)
    
typedef void (*nuart_callback)(struct nuart * uart, uint32_t events);

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

#define NUART_PARITY_Pos                12
#define NUART_PARITY_Msk                (3ul << NUART_PARITY_Pos)

#define NUART_STOP_BITS_Pos             14
#define NUART_STOP_BITS_Msk             (3ul << NUART_STOP_BITS_Pos)

#define NUART_FLOW_CONTROL_Pos          16
#define NUART_FLOW_CONTROL_Msk          (3ul << NUART_FLOW_CONTROL_Pos)

#define NUART_CPOL_Pos                  18
#define NUART_CPOL_Msk                  (1ul << NUART_CPOL_Pos)

#define NUART_CPHA_Pos                  19
#define NUART_CPHA_Msk                  (1ul << NUART_CPHA_Pos)

#define NUART_COMMAND_Pos               22u
#define NUART_COMMAND_Msk               (0xful << NUART_COMMAND_Pos)

/** @name UART control codes: mode
 *  @{ */

/** @brief      UART (Asynchronous); arg = Baudrate.
 */
#define NUART_MODE_ASYNCHRONOUS         (0x01ul << NUART_MODE_Pos)

/** @brief      Synchronous Master (generates clock signal); arg = Baudrate.
 */
#define NUART_MODE_SYNCHRONOUS_MASTER   (0x02ul << NUART_MODE_Pos)

/** @brief      Synchronous Slave (external clock signal).
 */
#define NUART_MODE_SYNCHRONOUS_SLAVE    (0x03UL << NUART_MODE_Pos)

/** @brief      UART Single-wire (half-duplex); arg = Baudrate.
 */
#define NUART_MODE_SINGLE_WIRE          (0x04UL << NUART_MODE_Pos)

/** @brief      UART IrDA; arg = Baudrate.
 */
#define NUART_MODE_IRDA                 (0x05UL << NUART_MODE_Pos)

/** @brief      UART DALI; arg = Bitrate.
 */
#define NUART_MODE_DALI                 (0x06ul << NUART_MODE_Pos)

/** @brief      UART Smart Card; arg = Baudrate.
 */
#define NUART_MODE_SMART_CARD           (0x07UL << NUART_MODE_Pos)

/** @} */
/** @name UART control codes: Data Bits
 *  @{ */

#define NUART_DATA_BITS_5               (5UL << NUART_DATA_BITS_Pos)    ///< 5 Data bits
#define NUART_DATA_BITS_6               (6UL << NUART_DATA_BITS_Pos)    ///< 6 Data bit
#define NUART_DATA_BITS_7               (7UL << NUART_DATA_BITS_Pos)    ///< 7 Data bits
#define NUART_DATA_BITS_8               (0ul << NUART_DATA_BITS_Pos)    ///< 8 Data bits (default)
#define NUART_DATA_BITS_9               (1ul << NUART_DATA_BITS_Pos)    ///< 9 Data bits

/** @} */
/** @name UART control codes: Parity
 *  @{ */

#define NUART_PARITY_NONE               (0ul << NUART_PARITY_Pos)       ///< No Parity (default)
#define NUART_PARITY_EVEN               (1ul << NUART_PARITY_Pos)       ///< Even Parity
#define NUART_PARITY_ODD                (2ul << NUART_PARITY_Pos)       ///< Odd Parity

/** @} */
/** @name UART control codes: Stop Bits
 *  @{ */

#define NUART_STOP_BITS_1               (0ul << NUART_STOP_BITS_Pos)    ///< 1 Stop bit (default)
#define NUART_STOP_BITS_2               (1ul << NUART_STOP_BITS_Pos)    ///< 2 Stop bits
#define NUART_STOP_BITS_1_5             (2ul << NUART_STOP_BITS_Pos)    ///< 1.5 Stop bits
#define NUART_STOP_BITS_0_5             (3UL << NUART_STOP_BITS_Pos)    ///< 0.5 Stop bits

/** @} */
/** @name UART control codes: Flow Control
 *  @{ */

#define NUART_FLOW_CONTROL_NONE         (0ul << NUART_FLOW_CONTROL_Pos) ///< No Flow Control (default)
#define NUART_FLOW_CONTROL_RTS          (1ul << NUART_FLOW_CONTROL_Pos) ///< RTS Flow Control
#define NUART_FLOW_CONTROL_CTS          (2ul << NUART_FLOW_CONTROL_Pos) ///< CTS Flow Control
#define NUART_FLOW_CONTROL_RTS_CTS      (3UL << NUART_FLOW_CONTROL_Pos) ///< RTS/CTS Flow Control

/** @} */
/** @name UART control codes: Clock Polarity (Synchronous mode)
 *  @{ */

#define NUART_CPOL0                     (0ul << NUART_CPOL_Pos)         ///< CPOL = 0 (default)
#define NUART_CPOL1                     (1ul << NUART_CPOL_Pos)         ///< CPOL = 1

/** @} */
/** @name UART control codes: Clock Phase (Synchronous mode)
 *  @{ */

#define NUART_CPHA0                     (0ul << NUART_CPHA_Pos)         ///< CPHA = 0 (default)
#define NUART_CPHA1                     (1ul << NUART_CPHA_Pos)         ///< CPHA = 1

/** @} */
/** @name UART control codes: Miscellaneous Controls
 *  @{ */

#define NUART_SET_DEFAULT_TX_VALUE      (0x10ul << NUART_CONTROL_Pos)   ///< Set default Transmit value (Synchronous Receive only); arg = value
#define NUART_SET_IRDA_PULSE            (0x11ul << NUART_CONTROL_Pos)   ///< Set IrDA Pulse in ns; arg: 0=3/16 of bit period  
#define NUART_SET_SMART_CARD_GUARD_TIME (0x12ul << NUART_CONTROL_Pos)   ///< Set Smart Card Guard Time; arg = number of bit periods
#define NUART_SET_SMART_CARD_CLOCK      (0x13UL << NUART_CONTROL_Pos)   ///< Set Smart Card Clock in Hz; arg: 0=Clock not generated
#define NUART_CONTROL_SMART_CARD_NACK   (0x14UL << NUART_CONTROL_Pos)   ///< Smart Card NACK generation; arg: 0=disabled, 1=enabled
#define NUART_CONTROL_TX                (0x15UL << NUART_CONTROL_Pos)   ///< Transmitter; arg: 0=disabled, 1=enabled
#define NUART_CONTROL_RX                (0x16UL << NUART_CONTROL_Pos)   ///< Receiver; arg: 0=disabled, 1=enabled
#define NUART_CONTROL_BREAK             (0x17UL << NUART_CONTROL_Pos)   ///< Continuous Break transmission; arg: 0=disabled, 1=enabled

/** @} */
/** @name UART control codes: Commands
 *  @{ */

#define NUART_ABORT_SEND                (0x1ul << NUART_COMMAND_Pos)   ///< Abort \ref NUART_Send
#define NUART_ABORT_RECEIVE             (0x2ul << NUART_COMMAND_Pos)   ///< Abort \ref NUART_Receive
#define NUART_ABORT_TRANSFER            (0x3ul << NUART_COMMAND_Pos) ///< Abort \ref NUART_Transfer

/** @} */
/** @} *//*==================================================================*/
/** @defgroup   nuart_fn UART functions
 *  @brief      UART functions
 *  @{ *//*==================================================================*/

struct nuart;

void nuart_init(struct nuart * uart);

void nuart_term(struct nuart * uart);

uint32_t nuart_capabilities(const struct nuart * uart);


#ifdef __cplusplus
}
#endif



/** @} */
#endif /* NEON_H_ */
