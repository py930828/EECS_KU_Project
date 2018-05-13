#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/pwm.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "inc/hw_uart.h"


#include "stdio.h"

//
//      Gloabal subroutines and variables
//

//*****************************************************************************
//
//      Task initialization
#define SysTickFrequency configTICK_RATE_HZ
int width = 0;
char var[5];
void Task_DC_motor( void *pvParameters ) {
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOG ); //Enable Part G for PWM
	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM0 ); //Enable PWM0
	GPIOPinTypePWM(GPIO_PORTG_BASE, GPIO_PIN_1); // Enable PG1 for PWM
	GPIOPinConfigure(GPIO_PG1_M0PWM5);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	//Configure PWMGen
	//
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, 37500); //Set PWM period to 37500
	PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_64); //Divide the PWM SYSCLK with 64
	PWMGenEnable(PWM0_BASE, PWM_GEN_2); //Enable PWM_GEN_2
	PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT , true);//Enable PWM output

    while ( 1 ) {
		UARTprintf("Enter a number:\n");
		UARTgets(var,5); // ask user for input
		sscanf(var, "%d", &width); //convert char array to int
		width = 2812.0 + (947.0*(width / 100.0)); // var-'0' convert char to int
		UARTprintf("width:%d\n", width);
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, width); //generate PWM signal
		vTaskDelay( 2*configTICK_RATE_HZ );
    }

}
