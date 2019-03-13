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

#ifndef NEON_GPIO_H_
#define NEON_GPIO_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "mcu_variant/mcu.h"

#ifdef __cplusplus
extern "C" {
#endif
    
/*===========================================================================*/
/** @defgroup   ngpio_capa GPIO capabilities
 *  @brief      GPIO capabilities
 *  @{ *//*==================================================================*/

/** @brief      Supports UART (Asynchronous) mode.
 */
#define NGPIO_CAPA_ASYNCHRONOUS         ((uint32_t)0x1ul << 0)
    
/** @brief      Supports Synchronous Master mode.
 */
#define NGPIO_CAPA_SYNCHRONOYS_MASTER   ((uint32_t)0x1ul << 1)
    
/** @brief      Supports Synchronous Slave mode.
 */
#define NGPIO_CAPA_SYNCHRONOYS_SLAVE    ((uint32_t)0x1ul << 2)
   
/** @brief      Supports UART Single-wire mode.
 */
#define NGPIO_CAPA_SINGLE_WIRE          ((uint32_t)0x1ul << 3)
    
/** @brief      Supports UART IrDA mode.
 */
#define NGPIO_CAPA_IRDA                 ((uint32_t)0x1ul << 4)
    
/** @brief      Supports UART DALI mode.
 */
#define NGPIO_CAPA_DALI                 ((uint32_t)0x1ul << 5)
    
/** @brief      Supports UART Smart Card mode.
 */
#define NGPIO_CAPA_SMART_CARD           ((uint32_t)0x1ul << 6)
    
/** @brief      Supports UART Smart Card clock generator mode.
 */
#define NGPIO_CAPA_SMART_CARD_CLOCK     ((uint32_t)0x1ul << 7)

/** @brief      Supports RTS Flow Control.
 */
#define NGPIO_CAPA_FLOW_CTRL_RTS        ((uint32_t)0x1ul << 8)
    
/** @brief      Supports CTS Flow Control.
 */
#define NGPIO_CAPA_FLOW_CTRL_CTS        ((uint32_t)0x1ul << 9)

/** @} *//*==================================================================*/
/** @defgroup   ngpio_callback GPIO callbacks and events
 *  @brief      GPIO callbacks and events
 *  @{ *//*==================================================================*/

/** @brief      Send completed; however USART may still transmit data.
 */
#define NGPIO_EVENT_SEND_COMPLETE       ((uint32_t)0x1ul << 0)

/** @brief      Receive completed.
 */
#define NGPIO_EVENT_RECEIVE_COMPLETE    ((uint32_t)0x1ul << 1)

/** @brief      Transfer completed.
 */
#define NGPIO_EVENT_TRANSFER_COMPLETE   ((uint32_t)0x1ul << 2)
    
/** @brief      Transmit completed (optional).
 */
#define NGPIO_EVENT_TX_COMPLETE         ((uint32_t)0x1ul << 3)

/** @brief      Transmit data not available (Synchronous Slave).
 */
#define NGPIO_EVENT_TX_UNDERFLOW        ((uint32_t)0x1ul << 4)
    
/** @brief      Receive data overflow.
 */
#define NGPIO_EVENT_RX_OVERFLOW         ((uint32_t)0x1ul << 5)
    
/** @brief      Receive character timeout (optional).
 */
#define NGPIO_EVENT_RX_TIMEOUT          ((uint32_t)0x1ul << 6)
    
/** @brief      Break detected on receive.
 */
#define NGPIO_EVENT_RX_BREAK            ((uint32_t)0x1ul << 7)
    
/** @brief      Framing error detected on receive.
 */
#define NGPIO_EVENT_RX_FRAMING_ERROR    ((uint32_t)0x1ul << 8)
    
/** @brief      Parity error detected on receive.
 */
#define NGPIO_EVENT_RX_PARITY_ERROR     ((uint32_t)0x1ul << 9)
    
struct ngpio;

typedef void (ngpio_callback)(struct ngpio * gpio, uint32_t events);

/** @} *//*==================================================================*/
/** @defgroup   ngpio_control UART control codes
 *  @brief      UART control codes
 *  @{ *//*==================================================================*/

/** @brief      UART Mode bits position.
 */
#define NGPIO_MODE_Pos                  0u

/** @brief      UART Mode bits mask.
 */
#define NGPIO_MODE_Msk                  ((uint32_t)0xful << NGPIO_MODE_Pos)

/** @brief      UART Data bits position.
 */
#define NGPIO_DATA_BITS_Pos              4

/** @brief      UART Data bits mask.
 */
#define NGPIO_DATA_BITS_Msk             ((uint32_t)0x7ul << NGPIO_DATA_BITS_Pos)

/** @brief      UART Parity position.
 */
#define NGPIO_PARITY_Pos                7

/** @brief      UART Parity mask.
 */
#define NGPIO_PARITY_Msk                (3ul << NGPIO_PARITY_Pos)

/** @brief      UART Stop bits position.
 */
#define NGPIO_STOP_BITS_Pos             9

/** @brief      UART Stop bits mask.
 */
#define NGPIO_STOP_BITS_Msk             (3ul << NGPIO_STOP_BITS_Pos)

/** @brief      UART Flow Control position.
 */
#define NGPIO_FLOW_CONTROL_Pos          11

/** @brief      UART Flow Control position.
 */
#define NGPIO_FLOW_CONTROL_Msk          (3ul << NGPIO_FLOW_CONTROL_Pos)

/** @brief      UART Clock polarity position.
 */
#define NGPIO_CPOL_Pos                  13

/** @brief      UART Clock polarity mask.
 */
#define NGPIO_CPOL_Msk                  (1ul << NGPIO_CPOL_Pos)

/** @brief      UART Clock phase position.
 */
#define NGPIO_CPHA_Pos                  14

/** @brief      UART Clock phase mask.
 */
#define NGPIO_CPHA_Msk                  (1ul << NGPIO_CPHA_Pos)

/** @brief      UART command position.
 */
#define NGPIO_COMMAND_Pos               15u

/** @brief      UART command mask.
 */
#define NGPIO_COMMAND_Msk               (0xful << NGPIO_COMMAND_Pos)

/** @name UART control codes: mode
 *  @{ */

/** @brief      UART (Asynchronous); arg = Baudrate.
 */
#define NGPIO_MODE_ASYNCHRONOUS         (0x01ul << NGPIO_MODE_Pos)

/** @brief      Synchronous Master (generates clock signal); arg = Baudrate.
 */
#define NGPIO_MODE_SYNCHRONOUS_MASTER   (0x02ul << NGPIO_MODE_Pos)

/** @brief      Synchronous Slave (external clock signal).
 */
#define NGPIO_MODE_SYNCHRONOUS_SLAVE    (0x03ul << NGPIO_MODE_Pos)

/** @brief      UART Single-wire (half-duplex); arg = Baudrate.
 */
#define NGPIO_MODE_SINGLE_WIRE          (0x04UL << NGPIO_MODE_Pos)

/** @brief      UART IrDA; arg = Baudrate.
 */
#define NGPIO_MODE_IRDA                 (0x05UL << NGPIO_MODE_Pos)

/** @brief      UART DALI; arg = Bitrate.
 */
#define NGPIO_MODE_DALI                 (0x06ul << NGPIO_MODE_Pos)

/** @brief      UART Smart Card; arg = Baudrate.
 */
#define NGPIO_MODE_SMART_CARD           (0x07UL << NGPIO_MODE_Pos)

/** @} */
/** @name UART control codes: Data Bits
 *  @{ */

/** @brief      5 Data bits
 */
#define NGPIO_DATA_BITS_5               (5UL << NGPIO_DATA_BITS_Pos)

/** @brief      6 Data bits
 */
#define NGPIO_DATA_BITS_6               (6UL << NGPIO_DATA_BITS_Pos)

/** @brief      7 Data bits
 */
#define NGPIO_DATA_BITS_7               (7UL << NGPIO_DATA_BITS_Pos)

/** @brief      8 Data bits
 */
#define NGPIO_DATA_BITS_8               (0ul << NGPIO_DATA_BITS_Pos)

/** @brief      9 Data bits
 */
#define NGPIO_DATA_BITS_9               (1ul << NGPIO_DATA_BITS_Pos)

/** @} */
/** @name UART control codes: Parity
 *  @{ */

/** @brief      No Parity.
 */
#define NGPIO_PARITY_NONE               (0ul << NGPIO_PARITY_Pos)

/** @brief      Even Parity.
 */
#define NGPIO_PARITY_EVEN               (1ul << NGPIO_PARITY_Pos)

/** @brief      Odd Parity.
 */
#define NGPIO_PARITY_ODD                (2ul << NGPIO_PARITY_Pos)

/** @} */
/** @name UART control codes: Stop Bits
 *  @{ */

/** @brief      1 Stop bit.
 */
#define NGPIO_STOP_BITS_1               (0ul << NGPIO_STOP_BITS_Pos)

/** @brief      2 Stop bit.
 */
#define NGPIO_STOP_BITS_2               (1ul << NGPIO_STOP_BITS_Pos)

/** @brief      1.5 Stop bit.
 */
#define NGPIO_STOP_BITS_1_5             (2ul << NGPIO_STOP_BITS_Pos)

/** @brief      0.5 Stop bit.
 */
#define NGPIO_STOP_BITS_0_5             (3ul << NGPIO_STOP_BITS_Pos)

/** @} */
/** @name UART control codes: Flow Control
 *  @{ */

/** @brief      No Flow Control.
 */
#define NGPIO_FLOW_CONTROL_NONE         (0ul << NGPIO_FLOW_CONTROL_Pos)

/** @brief      RTS Flow Control.
 */
#define NGPIO_FLOW_CONTROL_RTS          (1ul << NGPIO_FLOW_CONTROL_Pos)

/** @brief      CTS Flow Control.
 */
#define NGPIO_FLOW_CONTROL_CTS          (2ul << NGPIO_FLOW_CONTROL_Pos)

/** @brief      RTS/CTS Flow Control.
 */
#define NGPIO_FLOW_CONTROL_RTS_CTS      (3ul << NGPIO_FLOW_CONTROL_Pos)

/** @} */
/** @name UART control codes: Clock Polarity (Synchronous mode)
 *  @{ */

/** @brief      CPOL = 0.
 */
#define NGPIO_CPOL_0                    (0ul << NGPIO_CPOL_Pos)

/** @brief      CPOL = 1.
 */
#define NGPIO_CPOL_1                    (1ul << NGPIO_CPOL_Pos)

/** @} */
/** @name UART control codes: Clock Phase (Synchronous mode)
 *  @{ */

/** @brief      CPHA = 0.
 */
#define NGPIO_CPHA_0                    (0ul << NGPIO_CPHA_Pos)

/** @brief      CPHA = 1.
 */
#define NGPIO_CPHA_1                    (1ul << NGPIO_CPHA_Pos)

/** @} */
/** @name UART control codes: Miscellaneous Controls
 *  @{ */

#define NGPIO_SET_DEFAULT_TX_VALUE      (0x10ul << NGPIO_CONTROL_Pos)   ///< Set default Transmit value (Synchronous Receive only); arg = value
#define NGPIO_SET_IRDA_PULSE            (0x11ul << NGPIO_CONTROL_Pos)   ///< Set IrDA Pulse in ns; arg: 0=3/16 of bit period  
#define NGPIO_SET_SMART_CARD_GUARD_TIME (0x12ul << NGPIO_CONTROL_Pos)   ///< Set Smart Card Guard Time; arg = number of bit periods
#define NGPIO_SET_SMART_CARD_CLOCK      (0x13ul << NGPIO_CONTROL_Pos)   ///< Set Smart Card Clock in Hz; arg: 0=Clock not generated
#define NGPIO_CONTROL_SMART_CARD_NACK   (0x14UL << NGPIO_CONTROL_Pos)   ///< Smart Card NACK generation; arg: 0=disabled, 1=enabled
#define NGPIO_CONTROL_TX                (0x15UL << NGPIO_CONTROL_Pos)   ///< Transmitter; arg: 0=disabled, 1=enabled
#define NGPIO_CONTROL_RX                (0x16UL << NGPIO_CONTROL_Pos)   ///< Receiver; arg: 0=disabled, 1=enabled
#define NGPIO_CONTROL_BREAK             (0x17UL << NGPIO_CONTROL_Pos)   ///< Continuous Break transmission; arg: 0=disabled, 1=enabled

/** @} */
/** @} *//*==================================================================*/
/** @defgroup   ngpio_fn GPIO functions
 *  @brief      GPIO functions
 *  @{ *//*==================================================================*/

struct ngpio;

void ngpio_init(struct ngpio * port, uint8_t pin);

void ngpio_term(struct ngpio * port, uint8_t pin);

uint32_t ngpio_capabilities(const struct ngpio * port, uint8_t pin);

void ngpio_control(struct ngpio * port, uint8_t pin, uint32_t control_code, uint32_t arg);

void ngpio_set(struct ngpio * port, uint8_t pin);

void ngpio_reset(struct ngpio * port, uint8_t pin);

bool ngpio_read(struct ngpio * port, uint8_t pin);

#ifdef __cplusplus
}
#endif



/** @} */
#endif /* NEON_H_ */
