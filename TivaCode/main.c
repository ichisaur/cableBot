//*****************************************************************************
//
// uart_echo.c - Example for reading data from and writing data to the UART in
//               an interrupt driven fashion.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
#include "PWMSetting.h"
#include "UartSetting.h"

volatile int base =16000000;//=1hz
volatile int myData[8];
volatile int myDataCounter = 0;
volatile int endEffectorOnOff = 0;


void UART0Send(const uint8_t *, uint32_t );


//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>UART Echo (uart_echo)</h1>
//!
//! This example application utilizes the UART to echo text.  The first UART
//! (connected to the USB debug virtual serial port on the evaluation board)
//! will be configured in 115,200 baud, 8-n-1 mode.  All characters received on
//! the UART are transmitted back to the UART.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif



//*****************************************************************************
//
// Sends a char array to UART0
//
//*****************************************************************************
void
UART0Send(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        ROM_UARTCharPut(UART0_BASE, *pui8Buffer++);
    }
}


//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void
UARTIntHandler(void)
{
    uint32_t ui32Status;

    //
    // Get the interrrupt status.
    //
    ui32Status = ROM_UARTIntStatus(UART0_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    ROM_UARTIntClear(UART0_BASE, ui32Status);



    char buf[100];
    int k = 0;

    //Get all the characters until the next delimiter ( ; ) is hit
    while(1)
    {

        // Read the next character from the UART and write it to buffer


        buf[k] = UARTCharGet(UART0_BASE);

        // check for delimiter
        if (buf[k] == ';') break;
        k++;


    }

    // change delimiter value to a space for processing.
    buf[k] = 32;


    char myInput[50];
    int i=0;
    int hwID;
    char hwType;
    int param1;
    int param2;


    // remove trash from the input
    for(i = 0; i<k; i++){
        myInput[i] = buf[i];
    }
    for (i; i<50; i++) {
        myInput[i] = 32;
    }

    // process string for variables
    // TODO: processing the hwType char doesnt work. May not needed, hard program in based on hwID
    sscanf(myInput, "%1i %1c %i %i", &hwID, &hwType, &param1, &param2);


    // Hardcoded implementation of placing it in myData, change structure at later point

    if (hwID == 4) {
        endEffectorOnOff = param1;
    }
    else {
        myData[hwID] = param1;
        myData[hwID + 4] = param2;
        myDataCounter = myDataCounter +1;

    }

    // idk why we have 3 buffers, it made it work and I'm not questioning it. Prints it out to a string
    char buffer[50];
    // Echo value received back to PySerial
    int length = sprintf(buffer, "%d %c %d %d \r\n", hwID, hwType, param1, param2);

    // Length ignores the null character. Add 3 for CRLF
    UART0Send( (uint8_t *) buffer, length+3);


    /* Deprecated code. AVERT YOUR EYES*/
//    UART0Send( (uint8_t *) "\r\n", 2);

//  sscanf(buf, "%d %d %d %d %d %d %d %d", &myData[0], &myData[1], &myData[2], &myData[3], &myData[4], &myData[5], &myData[6], &myData[7]);
//    sscanf(buf, "%d", &myData[myDataCounter]);
//  myDataCounter = (myDataCounter + 1) % 8;


}

//*****************************************************************************
//
// Timer 3 Interrupt handler Initialization
//
//*****************************************************************************


void init_Timer03()
{
    unsigned long Period;
    //configure Timer3

//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    TimerConfigure(TIMER3_BASE, TIMER_CFG_PERIODIC);

    // Get 10 Hz Period
    int freq = 10; //Hz
    Period =  (SysCtlClockGet() / freq);//10=0.1
    TimerLoadSet(TIMER3_BASE, TIMER_A, Period - 1);//5kHZ

    IntEnable(INT_TIMER3A);
    TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);


    TimerEnable(TIMER3_BASE, TIMER_A);


}

//*****************************************************************************
//
// Timer 3 interrupt Handler
//
//*****************************************************************************
void Timer3IntHandler()
{
    // Clear the interrupt
    TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);

    // TODO: SET PWMS HERE
    // TODO: SET DIRECTION PINS HERE
    // TODO: ANY OTHER JUNK HERE

    // Create a buffer to write out to. Not needed anymore really
    char buffer[100] = {0};
    char RSInfo[100] = {0};

    //used for send command to uart1
//    UART1Send( (uint8_t *) "command", 7);

    setPWM01(myData[1],2,myData[3],2,base);
    setTimer01(myData[0],2,myData[2],2,base);
    setDirection(myData[4],myData[5],myData[6],myData[7]);
    setEndeffector(endEffectorOnOff);

    //used for read info from uart1, send with ignoring the \n
//    int len = UART1Read(RSInfo);
//    UART0Send( (uint8_t *) RSInfo, len-1);

    // Should clear the current commands from myData here
    // Send over a "tick" for every time it finishes setting stuff up
    UART0Send( (uint8_t *) "tick", 4);
    UART0Send( (uint8_t *) "\r\n", 2);

    // TODO: Implement tick checking on the python side it just kinda assumes any new line here works

}



int main(void)
{

    /*  INITIALIZE UART */

    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    ROM_FPUEnable();
    ROM_FPULazyStackingEnable();
    //
    // Set the clocking to run directly from the crystal.
    //
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);


    //
    // Enable the peripherals used by this example.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable processor interrupts.
    //
    ROM_IntMasterEnable();

    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    ROM_UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    //
    // Enable the UART interrupt.
    //
    ROM_IntEnable(INT_UART0);
    ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);


    //
    // Initialize Timer 3 for Interrupts
    //
    init_StepPin();
    init_Timer01();
    init_Timer03();
    init_PWM01();
    init_U1();
    setPWM01(0,4,0,4,base);
    setTimer01(0,4,0,4,base);
    setDirection(1,1,1,1);
    setEndeffector(0);
    int i;
    for ( i =0;i<8;i++)
    {
        myData[i]=0;
    }


    //
    // Loop forever while interrupts take care of everything else
    //
    while(1)
    {
    }
}