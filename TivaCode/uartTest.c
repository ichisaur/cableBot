//#include <stdbool.h>
//#include <stdint.h>
//#include <stdarg.h>
//#include <stdio.h>
//#include "inc/hw_gpio.h"
//#include "inc/hw_ints.h"
//#include "inc/hw_memmap.h"
//#include "inc/hw_timer.h"
//#include "inc/hw_types.h"
//#include "driverlib/gpio.h"
//#include "driverlib/interrupt.h"
//#include "driverlib/pin_map.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/timer.h"
//#include "driverlib/uart.h"
//#include <driverlib/pwm.h>
//#include "utils/uartstdio.h"
//int main()
//{
//    //
//    // Enable the UART0 module.
//    //
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
//    //
//    // Wait for the UART0 module to be ready.
//    //
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
//    { }
//    // Initialize the UART. Set the baud rate, number of data bits, turn off
//    // parity, number of stop bits, and stick mode. The UART is enabled by the
//    // function call.
//    //
//    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 38400,
//    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
//    UART_CONFIG_PAR_NONE));
//    //
//    // Check for characters. Spin here until a character is placed
//    // into the receive FIFO.
//    //
//    while(!UARTCharsAvail(UART0_BASE))
//    { }
//    //
//    // Get the character(s) in the receive FIFO.
//    //
//    while(UARTCharGetNonBlocking(UART0_BASE))
//    { }
//    //
//    // Put a character in the output buffer.
//    //
//    UARTCharPut(UART0_BASE, 'c');
//    //
//    // Disable the UART.
//    //
//    UARTDisable(UART0_BASE);
//}
