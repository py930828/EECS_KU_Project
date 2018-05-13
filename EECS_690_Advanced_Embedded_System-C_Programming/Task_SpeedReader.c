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
float speed = 0;
char buffer[25];
#define SysTickFrequency configTICK_RATE_HZ
void Task_SpeedReader(void *pvParameters) {
	SysCtlPeripheralEnable( SYSCTL_PERIPH_QEI0 ); //Enable QEI
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOL ); //Enable PWM
	GPIOPinTypeQEI(GPIO_PORTL_BASE, GPIO_PIN_1);
	GPIOPinTypeQEI(GPIO_PORTL_BASE, GPIO_PIN_2);
	GPIOPinConfigure(GPIO_PL1_PHA0);//Enable PHA0
	GPIOPinConfigure(GPIO_PL2_PHB0); //Enable PHB0
	QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), 1120-1);
	QEIEnable(QEI0_BASE);
	UARTprintf("QEI checked!\n");
	QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, 50000000);
	QEIVelocityEnable(QEI0_BASE);

	while(1){
		vTaskDelay( 0.5*configTICK_RATE_HZ ); //delay for 0.5s to allow Task_DCmotor generate PWM signal
		speed = (2*QEIVelocityGet(QEI0_BASE)*(12/5.0)/1120.0);  //rpm = (clock * (2 ^ VELDIV) * SPEED * 60) � (LOAD * ppr * edges)
		sprintf(buffer, "RPS is %f", speed); //buffer = RPS is “speed”
		UARTprintf("%s\n", buffer);
		vTaskDelay( configTICK_RATE_HZ );
	}
}
