/*--Task_Blinky.c
 *
 *  Author:			Gary J. Minden
 *	Organization:	KU/EECS/EECS 388
 *  Date:			2016-09-26 (B60926)
 *
 *  Description:	Blinks Status LED on Stellaris LM3S1968
 *					Evaluation board.
 *
 */

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"

#include "Drivers/uartstdio.h"

#include "inc/hw_memmap.h"
#include "driverlib/pwm.h"

#include	"FreeRTOS.h"
#include	"task.h"
#include "Drivers/rit128x96x4.h"
static unsigned long var=0;
static unsigned long temp=0;
//*****************************************************************************
//
//	External variables.
//
//*****************************************************************************

//*****************************************************************************
//
//	Task local static variables.
//
//*****************************************************************************

extern void Task_ADC( void *pvParameters ) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

	SysCtlPWMClockSet(SYSCTL_PWMDIV_16);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,  GPIO_PIN_1);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,  GPIO_PIN_2);
	GPIOPadConfigSet( GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD );
	GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);

	ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
	PWMGenConfigure(PWM_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END |ADC_CTL_CH0);
	ADCSequenceEnable(ADC0_BASE, 0);
	ADCIntClear(ADC0_BASE, 0);
	PWMGenPeriodSet(PWM_BASE, PWM_GEN_0, 0.02*50000000/16);//50mHZ,systickclock is 50 million, and PWMclock is divided by 16.
	PWMOutputState(PWM_BASE, PWM_OUT_1_BIT, true);
	PWMGenEnable(PWM_BASE, PWM_GEN_0);
	    //
//*****************************************************************************
//
//	Task execution.
//
//*****************************************************************************

	while (1){
			var=0;
			ADCProcessorTrigger(ADC0_BASE, 0);
			while(!ADCIntStatus(ADC0_BASE, 0, false));
			ADCSequenceDataGet(ADC0_BASE, 0, &var);
			ADCIntClear(ADC0_BASE,0);


			temp = 3125 + (3125*var)/1023;
			PWMPulseWidthSet(PWM_BASE, PWM_OUT_1, temp);

			UARTprintf("preVol: %04d mv \n", var);
			UARTprintf("Vol: %04d mv \n", temp);
			vTaskDelay( ( configTICK_RATE_HZ *1000 ) / 10000 ); //delay for 1000ms.
	}
}



