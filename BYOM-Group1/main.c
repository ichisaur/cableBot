#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <drv8323rs.h>


void init(void);
/**
 * main.c
 */

uint16_t stuff = 0x0052;
uint16_t new_stuff;
uint8_t addr = 0x02;


int main(void)
{
    init();
    InitDRV8323RS();
    while(1){
       SPIWriteDRV8323(addr, stuff);
       new_stuff = SPIReadDRV8323(addr);
       GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x08);
    }
    return 0;
}

void init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    // Enable the pin used for DRV8323RS chip enable, and set the pin high
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
}
