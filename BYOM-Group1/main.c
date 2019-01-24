#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <drv8323rs.h>
#include "driverlib/uart.h"
#include "uartstdio.h"

#define PWM_PERIOD 399
#define PWM_SPEED 8


void init(void);
void InitConsole(void);
void pwma_config(void);
void pwmb_config(void);
void pwmc_config(void);
void pwma(int duty);
void pwmb(int duty);
void pwmc(int duty);
void inl_config(void);
void int_config(void);
void adc_config(void);
void read_adc(void);
void Timer3AConfig(void);
void commutate(void);
extern void halla_int(void);
extern void hallb_int(void);
extern void hallc_int(void);
extern void Timer3Int(void);

/**
 * main.c
 */

int test = 0;
volatile uint16_t ArrayFlag=0;
uint16_t stuff = 0x00;
uint16_t new_stuff;
uint8_t addr = 0x02;
//uint32_t testa = 0;
//uint32_t testb = 0;
//uint32_t testc = 0;
volatile uint32_t ui32Value1;
volatile uint32_t ui32Value2;
volatile uint32_t ui32Value3;
volatile uint16_t Data[15000];
volatile uint8_t halla_state = 0x04;
volatile uint8_t hallb_state = 0;
volatile uint8_t hallc_state = 0x10;
volatile uint8_t commState= 0;
volatile uint32_t arrayIndex = 0;
volatile uint16_t hallState = 0b000;


int main(void)
{
    // set pwm clock to system clock
    init();

    InitDRV8323RS();
    commutate();

    while(!ArrayFlag){
       //UARTprintf("hello\r\n");
       new_stuff = SPIReadDRV8323(addr);
       new_stuff = new_stuff & 0b1111111110011111;
       new_stuff = new_stuff | 0b0000000000100000;
       SPIWriteDRV8323(addr, new_stuff);
       new_stuff = SPIReadDRV8323(addr);
       //read_adc();


       //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, !(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3)));
       //GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_INT_PIN_4);
       //GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2)
       //GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_INT_PIN_6);


    }
    UARTprintf("vSense, Hall State\r\n");
int jj;
for(jj=0; jj<15000; jj++){
    int currState = Data[jj] & (0b111);
    int vSense = Data[jj] >> 3;
    UARTprintf("%d, %d\r\n", vSense, currState);
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
        PWMPulseWidthSet(DRV8323RS_PWMA_BASE, DRV8323RS_PWMA_OUT, 1);

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
    TimerConfigure(DRV8323RS_PWMB_BASE, (TIMER_CFG_SPLIT_PAIR |TIMER_CFG_A_PERIODIC |
            TIMER_CFG_B_PWM));
    //set count time/period
    TimerLoadSet(DRV8323RS_PWMB_BASE, DRV8323RS_PWMB_TIMER, PWM_PERIOD);
    TimerControlLevel(DRV8323RS_PWMB_BASE,DRV8323RS_PWMB_TIMER,true);
    //set duty cycle
    TimerMatchSet(DRV8323RS_PWMB_BASE, DRV8323RS_PWMB_TIMER, 1);
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
        PWMPulseWidthSet(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_OUT, 1);

        // Enable the PWM generator
        PWMGenEnable(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_GEN);

        // Turn on the PWM output pin
        PWMOutputState(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_OUT_BIT,true);

}

void pwma(int duty){
    PWMPulseWidthSet(DRV8323RS_PWMA_BASE, DRV8323RS_PWMA_OUT, (duty/100.0)*399+1);
    // Enable the PWM generator
    PWMGenEnable(DRV8323RS_PWMA_BASE, DRV8323RS_PWMA_GEN);
    // Turn on the PWM output pin
    PWMOutputState(DRV8323RS_PWMA_BASE, DRV8323RS_PWMA_OUT_BIT,true);
}

void pwmb(int duty){
    TimerDisable(DRV8323RS_PWMB_BASE, TIMER_B);
    TimerMatchSet(DRV8323RS_PWMB_BASE, DRV8323RS_PWMB_TIMER, (duty/100.0)*399+1);
    TimerEnable(DRV8323RS_PWMB_BASE, TIMER_B);
}

void pwmc(int duty){
    // Set the PWM duty cycle to 33%
    PWMPulseWidthSet(DRV8323RS_PWMC_BASE, DRV8323RS_PWMC_OUT, (duty/100.0)*399+1);

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

void halla_int(void)
{

    halla_state = GPIOPinRead(DRV8323RS_HALLA_PORT, DRV8323RS_HALLA_PIN);
    hallb_state = GPIOPinRead(DRV8323RS_HALLB_PORT, DRV8323RS_HALLB_PIN);
    hallc_state = GPIOPinRead(DRV8323RS_HALLC_PORT, DRV8323RS_HALLC_PIN);
    commutate();
    //testa = testa + 1;
    GPIOIntClear(DRV8323RS_HALLA_PORT, GPIO_INT_PIN_2);
}

void hallb_int(void)
{

    halla_state = GPIOPinRead(DRV8323RS_HALLA_PORT, DRV8323RS_HALLA_PIN);
    hallb_state = GPIOPinRead(DRV8323RS_HALLB_PORT, DRV8323RS_HALLB_PIN);
    hallc_state = GPIOPinRead(DRV8323RS_HALLC_PORT, DRV8323RS_HALLC_PIN);
    commutate();
    //testb = testb + 1;
    GPIOIntClear(DRV8323RS_HALLB_PORT, GPIO_INT_PIN_0);
}

void hallc_int(void)
{

    halla_state = GPIOPinRead(DRV8323RS_HALLA_PORT, DRV8323RS_HALLA_PIN);
    hallb_state = GPIOPinRead(DRV8323RS_HALLB_PORT, DRV8323RS_HALLB_PIN);
    hallc_state = GPIOPinRead(DRV8323RS_HALLC_PORT, DRV8323RS_HALLC_PIN);
    commutate();
    //testc = testc + 1;
    GPIOIntClear(DRV8323RS_HALLC_PORT, GPIO_INT_PIN_4);
}

void commutate(void)
{
    if(halla_state != 0 && hallb_state == 0 && hallc_state != 0){
        GPIOPinWrite(DRV8323RS_INLA_PORT, DRV8323RS_INLA_PIN,0);
        GPIOPinWrite(DRV8323RS_INLB_PORT, DRV8323RS_INLB_PIN,GPIO_INT_PIN_4);
        GPIOPinWrite(DRV8323RS_INLC_PORT, DRV8323RS_INLC_PIN,GPIO_INT_PIN_6);
        pwma(1);
        pwmb(1);
        pwmc(PWM_SPEED);
        commState = 3;
        hallState = 0;
    }
    else if(halla_state != 0 && hallb_state == 0 && hallc_state == 0){
        GPIOPinWrite(DRV8323RS_INLA_PORT, DRV8323RS_INLA_PIN,GPIO_INT_PIN_3);
        GPIOPinWrite(DRV8323RS_INLB_PORT, DRV8323RS_INLB_PIN,0);
        GPIOPinWrite(DRV8323RS_INLC_PORT, DRV8323RS_INLC_PIN,GPIO_INT_PIN_6);
        pwma(1);
        pwmb(1);
        pwmc(PWM_SPEED);
        commState = 3;
        hallState = 1;
    }
    else if(halla_state != 0 && hallb_state != 0 && hallc_state == 0){
        GPIOPinWrite(DRV8323RS_INLA_PORT, DRV8323RS_INLA_PIN,GPIO_INT_PIN_3);
        GPIOPinWrite(DRV8323RS_INLB_PORT, DRV8323RS_INLB_PIN,GPIO_INT_PIN_4);
        GPIOPinWrite(DRV8323RS_INLC_PORT, DRV8323RS_INLC_PIN,0);
        pwma(1);
        pwmb(PWM_SPEED);
        pwmc(1);
        commState = 2;
        hallState = 2;
    }
    else if(halla_state == 0 && hallb_state != 0 && hallc_state == 0){
        GPIOPinWrite(DRV8323RS_INLA_PORT, DRV8323RS_INLA_PIN,0);
        GPIOPinWrite(DRV8323RS_INLB_PORT, DRV8323RS_INLB_PIN,GPIO_INT_PIN_4);
        GPIOPinWrite(DRV8323RS_INLC_PORT, DRV8323RS_INLC_PIN,GPIO_INT_PIN_6);
        pwma(1);
        pwmb(PWM_SPEED);
        pwmc(1);
        commState = 2;
        hallState = 3;
    }
    else if(halla_state == 0 && hallb_state != 0 && hallc_state != 0 ){
        GPIOPinWrite(DRV8323RS_INLA_PORT, DRV8323RS_INLA_PIN,GPIO_INT_PIN_3);
        GPIOPinWrite(DRV8323RS_INLB_PORT, DRV8323RS_INLB_PIN,0);
        GPIOPinWrite(DRV8323RS_INLC_PORT, DRV8323RS_INLC_PIN,GPIO_INT_PIN_6);
        pwma(PWM_SPEED);
        pwmb(1);
        pwmc(1);
        commState = 1;
        hallState = 4;
    }
    else if(halla_state == 0 && hallb_state == 0 && hallc_state != 0){
        GPIOPinWrite(DRV8323RS_INLA_PORT, DRV8323RS_INLA_PIN,GPIO_INT_PIN_3);
        GPIOPinWrite(DRV8323RS_INLB_PORT, DRV8323RS_INLB_PIN,GPIO_INT_PIN_4);
        GPIOPinWrite(DRV8323RS_INLC_PORT, DRV8323RS_INLC_PIN,0);
        pwma(PWM_SPEED);
        pwmb(1);
        pwmc(1);
        commState = 1;
        hallState = 5;

    }

    else {
        UARTprintf("wtf \r\n");
    }

    //UARTprintf("%d %d %d %d\r\n", halla_state >> 2, hallb_state, hallc_state >>4, hallState);


}


void int_config(void)
{
    //Hall A sensor Interrupt

    SysCtlPeripheralEnable(DRV8323RS_HALLA_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_HALLA_PERIPH));

    GPIOIntRegister(DRV8323RS_HALLA_PORT, halla_int);
    GPIOPinTypeGPIOInput(DRV8323RS_HALLA_PORT, DRV8323RS_HALLA_PIN);
    GPIOIntTypeSet(DRV8323RS_HALLA_PORT,DRV8323RS_HALLA_PIN,GPIO_BOTH_EDGES);
    GPIOIntEnable(DRV8323RS_HALLA_PORT, DRV8323RS_HALLA_PIN);

    //IntRegister(DRV8323RS_HALLA_INT, halla_int);
    //IntEnable(DRV8323RS_HALLA_INT);

    SysCtlPeripheralEnable(DRV8323RS_HALLB_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_HALLB_PERIPH));

    GPIOIntRegister(DRV8323RS_HALLB_PORT, hallb_int);
    GPIOPinTypeGPIOInput(DRV8323RS_HALLB_PORT, DRV8323RS_HALLB_PIN);
    GPIOIntTypeSet(DRV8323RS_HALLB_PORT,DRV8323RS_HALLB_PIN,GPIO_BOTH_EDGES);
    GPIOIntEnable(DRV8323RS_HALLB_PORT, DRV8323RS_HALLB_PIN);

    SysCtlPeripheralEnable(DRV8323RS_HALLC_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_HALLC_PERIPH));

    GPIOIntRegister(DRV8323RS_HALLC_PORT, hallc_int);
    GPIOPinTypeGPIOInput(DRV8323RS_HALLC_PORT, DRV8323RS_HALLC_PIN);
    GPIOIntTypeSet(DRV8323RS_HALLC_PORT,DRV8323RS_HALLC_PIN,GPIO_BOTH_EDGES);
    GPIOIntEnable(DRV8323RS_HALLC_PORT, DRV8323RS_HALLC_PIN);


    IntMasterEnable();


}

void adc_config(void)

{
    SysCtlPeripheralEnable(DRV8323RS_ISENSE_ADC_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_ISENSE_ADC_PERIPH));

    SysCtlPeripheralEnable(DRV8323RS_ISENSEA_GPIO_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_ISENSEA_GPIO_PERIPH));

    GPIOPinTypeADC(DRV8323RS_ISENSEA_GPIO_PORT, DRV8323RS_ISENSEA_GPIO_PIN);

    ADCSequenceConfigure(DRV8323RS_ISENSE_ADC_BASE, 0, ADC_TRIGGER_PROCESSOR,0);
    ADCSequenceStepConfigure(DRV8323RS_ISENSE_ADC_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH1);
    ADCSequenceEnable(DRV8323RS_ISENSE_ADC_BASE, 0);

    SysCtlPeripheralEnable(DRV8323RS_ISENSEB_GPIO_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_ISENSEB_GPIO_PERIPH));

    GPIOPinTypeADC(DRV8323RS_ISENSEB_GPIO_PORT, DRV8323RS_ISENSEB_GPIO_PIN);

    ADCSequenceConfigure(DRV8323RS_ISENSE_ADC_BASE, 1, ADC_TRIGGER_PROCESSOR,0);
    ADCSequenceStepConfigure(DRV8323RS_ISENSE_ADC_BASE, 1, 0,  ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH2);
    ADCSequenceEnable(DRV8323RS_ISENSE_ADC_BASE, 1); //also or together other adc channel pins, use channel 1, and sequence 0-2

    SysCtlPeripheralEnable(DRV8323RS_ISENSEC_GPIO_PERIPH);
    while(!SysCtlPeripheralReady(DRV8323RS_ISENSEC_GPIO_PERIPH));

    GPIOPinTypeADC(DRV8323RS_ISENSEC_GPIO_PORT, DRV8323RS_ISENSEC_GPIO_PIN);

    ADCSequenceConfigure(DRV8323RS_ISENSE_ADC_BASE, 2, ADC_TRIGGER_PROCESSOR,0);
    ADCSequenceStepConfigure(DRV8323RS_ISENSE_ADC_BASE, 2, 0,  ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH4);
    ADCSequenceEnable(DRV8323RS_ISENSE_ADC_BASE, 2);

}

void read_adc(void)
{
    ADCProcessorTrigger(ADC0_BASE, 0);
    //
    // Wait until the sample sequence has completed.
    //
    while(!ADCIntStatus(ADC0_BASE, 0, false))
    {
    }
    //if (commState == 1) {
        //
        // Read the value from the ADC.
        //
        ADCSequenceDataGet(ADC0_BASE, 0, &ui32Value1);
        ADCProcessorTrigger(ADC0_BASE, 1);
        //
        // Wait until the sample sequence has completed.
        //
        while(!ADCIntStatus(ADC0_BASE, 1, false))
        {
        }
    //} else if (commState == 2) {
        //
        // Read the value from the ADC.
        //
        ADCSequenceDataGet(ADC0_BASE, 1, &ui32Value2);
        ADCProcessorTrigger(ADC0_BASE, 2);
        //
        // Wait until the sample sequence has completed.
        //
        while(!ADCIntStatus(ADC0_BASE, 2, false))
        {
        }
    //} else if (commState == 3) {
        //
        // Read the value from the ADC.
        //
        ADCSequenceDataGet(ADC0_BASE, 2, &ui32Value3);
    //}

}

void Timer3Int(void)
{

    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, !(GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0)));

    if (arrayIndex<15000)
    {
        read_adc();
        if (commState == 1)
        {
            Data[arrayIndex] = (ui32Value1 << 3) | hallState;
            //Data[ii] = ui32Value1;
        } else if (commState == 2) {
            Data[arrayIndex] = (ui32Value2 << 3) | hallState;
        } else if (commState == 3) {
            Data[arrayIndex] = (ui32Value3 << 3) | hallState;
        }
        arrayIndex++;
    }
    else
    {
        ArrayFlag = 1;
    }
    TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
}

void Timer3AConfig(void)
{
    TimerLoadSet(TIMER3_BASE,TIMER_A,3199);
    TimerIntRegister(TIMER3_BASE,TIMER_A, Timer3Int);
    TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER3_BASE, TIMER_A);
}

void InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, SysCtlClockGet());
}



void init(void)
{
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
    pwma_config();
    pwmb_config();
    pwmc_config();
    //SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    inl_config();
    int_config();
    adc_config();
    Timer3AConfig();
    InitConsole();
    //IntPrioritySet(INT_TIMER3A, 0x80);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0);
}

