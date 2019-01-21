#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <drv8323rs.h>


void init(void);
/**
 * main.c
 */

uint16_t stuff = 0x00;
uint16_t new_stuff;
uint8_t addr = 0x02;


int main(void)
{
    init();
    InitDRV8323RS();
    while(1){
       new_stuff = SPIReadDRV8323(addr);
       new_stuff = new_stuff & 0b1111111110011111;
       new_stuff = new_stuff | 0b0000000000100000;
       SPIWriteDRV8323(addr, new_stuff);
       new_stuff = SPIReadDRV8323(addr);


       GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_INT_PIN_3);
       GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_INT_PIN_4);
       GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_INT_PIN_6);


    }
    return 0;
}

void init(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));


    // Enable the pin used for DRV8323RS chip enable, and set the pin high
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);

    // Configure PWM clock to match system.
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    // Enable the peripherals used by this
    SysCtlPeripheralEnable(DRV8323RS_PWMC_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_PWMC_PERIPH));
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1));

    SysCtlPeripheralEnable(DRV8323RS_INLB_PERIPH);

    // Configure PWM output pin
    GPIOPinConfigure(DRV8323RS_PWMC_PIN_CONFIG);
    GPIOPinTypePWM(DRV8323RS_INLB_PORT, DRV8323RS_INLB_PIN);
    GPIOPinTypePWM(DRV8323RS_INLA_PORT, DRV8323RS_INLA_PIN);

    // Configure PWM options
    //PWMGenConfigure(?????????);
    PWMGenConfigure(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_GEN, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);

    // Set the period (expressed in clock ticks)
    //PWMGenPeriodSet(???????);
    PWMGenPeriodSet(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_GEN, 249);

    // Set the PWM duty cycle to 33%
    //PWMPulseWidthSet(??????????);
    PWMPulseWidthSet(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_OUT, 50);

    // Enable the PWM generator
    //PWMGenEnable(????????);
    PWMGenEnable(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_GEN);

    // Turn on the PWM output pin
    //PWMOutputState(????????????);
    PWMOutputState(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_OUT_BIT,true);



}
