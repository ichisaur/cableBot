#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <drv8323rs.h>

#define PWM_PERIOD 399


void init(void);
void timer_pwm_init(void);
void pwma_config(void);
void pwmb_config(void);
void pwmc_config(void);
void inl_config(void);

/**
 * main.c
 */

uint16_t stuff = 0x00;
uint16_t new_stuff;
uint8_t addr = 0x02;


int main(void)
{
    // set pwm clock to system clock
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
void pwma_config(void)
{
        // Enable PWMA PWM periph (PWM0)
        SysCtlPeripheralEnable(DRV8323RS_PWMA_PERIPH);
        while(!SysCtlPeripheralReady(DRV8323RS_PWMA_PERIPH))
        {
        }

        //Enable PWMA GPIO periph (GPIOF)
        SysCtlPeripheralEnable(DRV8323RS_PWMA_GPIO_PERIPH);
        while(!SysCtlPeripheralReady(DRV8323RS_PWMA_GPIO_PERIPH))
        {
        }

        // Configure PWM output pin
        GPIOPinConfigure(DRV8323RS_PWMA_PIN_CONFIG);
        GPIOPinTypePWM(DRV8323RS_PWMA_GPIO_PORT,DRV8323RS_PWMA_GPIO_PIN);

        // Configure PWM options
        PWMGenConfigure(DRV8323RS_PWMA_BASE, DRV8323RS_PWMA_GEN, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);

        // Set the period (expressed in clock ticks)
        PWMGenPeriodSet(DRV8323RS_PWMA_BASE, DRV8323RS_PWMA_GEN, PWM_PERIOD);

        // Set the PWM duty cycle to 33%
        PWMPulseWidthSet(DRV8323RS_PWMA_BASE, DRV8323RS_PWMA_OUT, 133);

        // Enable the PWM generator
        PWMGenEnable(DRV8323RS_PWMA_BASE, DRV8323RS_PWMA_GEN);

        // Turn on the PWM output pin
        PWMOutputState(DRV8323RS_PWMA_BASE, DRV8323RS_PWMA_OUT_BIT,true);

}

void pwmb_config(void)
{
    // Enable the Timer3 peripheral.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    // Wait for the Timer3 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3))
    {
    }

    // Use T3CCP1 with port B pin 3. Start by enabling port B
    SysCtlPeripheralEnable(DRV8323RS_PWMB_GPIO_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_PWMB_GPIO_PERIPH))
        {
        }


    // Configure GPIO pin muxing for the Timer/CCP function
    GPIOPinConfigure(DRV8323RS_PWMB_PIN_CONFIG);

    // Configure the ccp settings for CCP pin
    GPIOPinTypeTimer(DRV8323RS_PWMB_GPIO_PORT, DRV8323RS_PWMB_GPIO_PIN);

    // Configure TimerB as a periodic timer
    TimerConfigure(DRV8323RS_PWMB_BASE, (TIMER_CFG_SPLIT_PAIR |
            TIMER_CFG_B_PWM));
    //set count time/period
    TimerLoadSet(DRV8323RS_PWMB_BASE, DRV8323RS_PWMB_TIMER, PWM_PERIOD);
    TimerControlLevel(DRV8323RS_PWMB_BASE,DRV8323RS_PWMB_TIMER,true);
    //set duty cycle
    TimerMatchSet(DRV8323RS_PWMB_BASE, DRV8323RS_PWMB_TIMER, 133);
    TimerEnable(DRV8323RS_PWMB_BASE, TIMER_B);
}

void pwmc_config(void)
{
        // Enable PWMC PWM periph (PWM0)
        SysCtlPeripheralEnable(DRV8323RS_PWMC_PERIPH);
        while(!SysCtlPeripheralReady(DRV8323RS_PWMC_PERIPH))
        {
        }

        //Enable PWMC GPIO periph (GPIOF)
        SysCtlPeripheralEnable(DRV8323RS_PWMC_GPIO_PERIPH);
        while(!SysCtlPeripheralReady(DRV8323RS_PWMC_GPIO_PERIPH))
        {
        }

        // Configure PWM output pin
        GPIOPinConfigure(DRV8323RS_PWMC_PIN_CONFIG);
        GPIOPinTypePWM(DRV8323RS_PWMC_GPIO_PORT,DRV8323RS_PWMC_GPIO_PIN);

        // Configure PWM options
        PWMGenConfigure(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_GEN, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);

        // Set the period (expressed in clock ticks)
        PWMGenPeriodSet(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_GEN, PWM_PERIOD);

        // Set the PWM duty cycle to 33%
        PWMPulseWidthSet(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_OUT, 133);

        // Enable the PWM generator
        PWMGenEnable(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_GEN);

        // Turn on the PWM output pin
        PWMOutputState(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_OUT_BIT,true);

}

void inl_config(void)
{
    //INLA pin config
    SysCtlPeripheralEnable(DRV8323RS_INLA_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_INLA_PERIPH));
    GPIOPinTypeGPIOOutput(DRV8323RS_INLA_PORT, DRV8323RS_INLA_PIN);
    //INLB pin config
    SysCtlPeripheralEnable(DRV8323RS_INLB_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_INLB_PERIPH));
    GPIOPinTypeGPIOOutput(DRV8323RS_INLB_PORT, DRV8323RS_INLB_PIN);

    //INLC pin config
    SysCtlPeripheralEnable(DRV8323RS_INLC_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_INLC_PERIPH));
    GPIOPinTypeGPIOOutput(DRV8323RS_INLC_PORT, DRV8323RS_INLC_PIN);
}



void init(void)
{
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
    pwma_config();
    pwmb_config();
    pwmc_config();
    //SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    inl_config();





}
