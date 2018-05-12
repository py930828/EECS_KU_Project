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

#include	"FreeRTOS.h"
#include	"task.h"
#include "Drivers/rit128x96x4.h"
extern unsigned long var;
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

extern void Task_ReportSysTick( void *pvParameters ) {
	RIT128x96x4Init(1000000);
	    //

//*****************************************************************************
//
//	Task execution.
//
//*****************************************************************************

	while (1) {
		char	TimeString[24];
		char    volString[24];
		sprintf( TimeString, "Task_SysTickCount: %d", xTaskGetTickCount());
		sprintf( volString, "Task_ADC: %04d", var);
		RIT128x96x4StringDraw (TimeString, 10, 0, 8 );
		RIT128x96x4StringDraw (volString, 20, 20, 8 );
		RIT128x96x4StringDraw ("Chen Long", 28, 50, 8 );
		RIT128x96x4StringDraw ("KU ID:2774386", 20, 60, 8 );
		vTaskDelay( 10000 );
	}
}



