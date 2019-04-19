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

#include "board_variant/board.h"
#include "arch_variant/arch.h"
#include "pic32_uart.h"
#include "pic32_isr.h"
#include "pic32_osc.h"
#include "neon.h"
#include <xc.h>

// PIC32MX534F064H Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config FSRSSEL = PRIORITY_7     // SRS Select (SRS Priority 7)
#pragma config FCANIO = ON              // CAN I/O Pin Select (Default CAN I/O)
#pragma config FUSBIDIO = OFF           // USB USID Selection (Controlled by Port Function)
#pragma config FVBUSONIO = OFF          // USB VBUS ON Selection (Controlled by Port Function)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider (2x Divider)
#pragma config UPLLEN = ON              // USB PLL Enable (Enabled)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

// DEVCFG1
#pragma config FNOSC = PRI              // Oscillator Selection Bits (Primary Osc (XT,HS,EC))
#pragma config FSOSCEN = ON             // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor Selection (Clock Switch Enable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

const struct pic32_uart_board_config g_pic32_uart_5_board_config =
{
    .isr_vector_prio = PIC32_ISR_PRIO(PIC32MX_CLICKER_UART_ISR_PRIO, 0),
    .control_code = PIC32MX_CLICKER_UART_CONTROL,
    .arg = PIC32MX_CLICKER_UART_BAUDRATE
};

void nboard_init(void)
{
    /* Disable JTAG since it is not available on this board */
    DDPCONbits.JTAGEN = 0;

    nlogger_info(NBOARD_PIC32MX_CLICKER " V1.00", 0);
    
    /* Initialise architecture */
    narch_init();

    /* Setup clocks */
    /* After boot default system clock is set to PRI oscillator by
     * configuration bits. Which with 8MHz crystal means that the main clock is
     * 8MHz. When using the PRIPLL clock source the main clock becomes 80MHz.
     */
    pic32_osc_new_source(PIC32_OSC_SOURCE_PRIPLL);

    /* Enable architecture timer */
    narch_timer_enable();

    /* Setup UART if used */
    pic32_uart_init();
}