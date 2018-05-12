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
#include "driverlib/uart.h"

#include	"FreeRTOS.h"
#include	"task.h"
#include "Drivers/rit128x96x4.h"
extern unsigned long var=0;
static uint32_t Button_Data = 0;
static int flag = 0;
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
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOInput( GPIO_PORTG_BASE, GPIO_PIN_7 );
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,  GPIO_PIN_2);
	GPIOPadConfigSet( GPIO_PORTG_BASE, GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU );
	GPIOPadConfigSet( GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_OD );
	ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END |ADC_CTL_CH0);
	ADCSequenceEnable(ADC0_BASE, 0);
	GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_2, 0x04 );
	while(!GPIOPinRead( GPIO_PORTG_BASE, GPIO_PIN_7));
	    //

//*****************************************************************************
//
//	Task execution.
//
//*****************************************************************************

	while (1) {
		int i=0;
		int data[100];
		Button_Data = GPIOPinRead( GPIO_PORTG_BASE, GPIO_PIN_7);
		Button_Data >>= 3;
		Button_Data ^= 0b10000;
		if(!flag)
		{
			if(Button_Data)
			{
				flag = 1;
			}
			else
			{
				RIT128x96x4StringDraw ("Please press select to start", 20, 40, 8 );
			}
		}
		if(flag)
		{
			vTaskDelay( ( configTICK_RATE_HZ *10 ) / 10000 ); //Debounce
			GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_2, 0x00 ); //Discharge
			vTaskDelay( ( configTICK_RATE_HZ*10*500 ) / 10000 ); //Discharging for 500ms
			GPIOPinWrite( GPIO_PORTD_BASE, GPIO_PIN_2, 0x04 ); //Start charging
			for(i=0; i<100; i++)
			{
				var=0;
				ADCProcessorTrigger(ADC0_BASE, 0);
				while(!ADCIntStatus(ADC0_BASE, 0, false));
				ADCSequenceDataGet(ADC0_BASE, 0, &var);
				ADCIntClear(ADC0_BASE,0);
				data[i] = (var*3300)/1023;
				SysCtlDelay(0.003*(configCPU_CLOCK_HZ/3)); //Delay for 3ms
			}
			for(i=0; i<100; i++)
			{
				UARTprintf("Time: %04d ;Vol: %04d mv \n", 3*i,data[i]);
			}
			flag = 0;
		}
	}
}



