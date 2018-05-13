#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>


#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/pwm.h"
#include "driverlib/qei.h"
#include "Drivers/UARTStdio_Initialization.h"
#include "Drivers/uartstdio.h"


#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "limits.h"
#include "stdio.h"

#define SysTickFrequency configTICK_RATE_HZ
char var[25];
uint32_t angle = 0;
uint32_t position = 0;
uint32_t CurrentPosition = 0;
uint32_t LastPosition = 0;
void Task_SetAngle(void *pvParameters) {
	SysCtlPeripheralEnable( SYSCTL_PERIPH_QEI0 ); //Enable QEI
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOL );
	GPIOPinTypeQEI(GPIO_PORTL_BASE, GPIO_PIN_1);
	GPIOPinTypeQEI(GPIO_PORTL_BASE, GPIO_PIN_2);
	GPIOPinConfigure(GPIO_PL1_PHA0);
	GPIOPinConfigure(GPIO_PL2_PHB0);
	QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_RESET_IDX | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), 1120-1);
	QEIEnable(QEI0_BASE);
	UARTprintf("QEI checked!\n");
	QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, 50000000);
	QEIVelocityEnable(QEI0_BASE);
	QEIPositionSet (QEI0_BASE, 0);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOG );
	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM0 );
	GPIOPinTypePWM(GPIO_PORTG_BASE, GPIO_PIN_1); // Enable PG1 for PWM
	//
	// Configure the PWM generator for count down mode with immediate updates
	// to the parameters.
	//
	GPIOPinConfigure(GPIO_PG1_M0PWM5);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	//
	// Set the period. For a 50 KHz frequency, the period = 1/50,000, or 20
	// microseconds. For a 20 MHz clock, this translates to 400 clock ticks.
	// Use this value to set the period.
	//
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, 37500);
	//
	// Set the pulse width of PWM0 for a 25% duty cycle.
	//
	PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_64);
	PWMGenEnable(PWM0_BASE, PWM_GEN_2);
	//
	// Enable the outputs.
	//
	PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT , true);

	while(1){
		UARTprintf("Enter a Angle:\n");
		UARTgets(var,5);
		sscanf(var, "%d", &angle);
		position = (angle/360.0) * 1120.0; //convert angle to rotation unit
		CurrentPosition = QEIPositionGet(QEI0_BASE);
		while(position != CurrentPosition){
			CurrentPosition = QEIPositionGet(QEI0_BASE);
			if(position != CurrentPosition){
				PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, 3000); //rotate the motor
				angle = (CurrentPosition/1120.0)*360.0; // convert rotation unit back to angle
				UARTprintf("the angle is now at %d\n", angle);
			}
			else
			{
				PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, 2812.5); //stop the motor
				UARTprintf("Yeah!!! The angle is now reaches %s\n", var);
			}
		}
		vTaskDelay( configTICK_RATE_HZ );
	}
}
