/*
 * GreenhouseNode.c
 *
 * Created: 11/11/2021 15.33.20
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 * Started from Semester project template at VIA University Collage Horsens, Denmark by Ib Havn, https://github.com/ihavn/IoT_Semester_project
 */

#include <avr/io.h>
#include <avr/sfr_defs.h>

#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#include "semaphore_handler.h"
#include "timer_handler.h"
#include "task_handler.h"
#include "LoRaWAN_Task.h"


#include "../FreeRTOSTraceDriver/FreeRTOSTraceDriver.h"

// define two Tasks
void task1( void *pvParameters );
void task2( void *pvParameters );

// define semaphore handle
SemaphoreHandle_t xTestSemaphore;


/*-----------------------------------------------------------*/

/*
void create_tasks_and_semaphores(void)
{
	// Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
	// because it is sharing a resource, such as the Serial port.
	// Semaphores should only be used whilst the scheduler is running, but we can set it up here.
	if ( xTestSemaphore == NULL )  // Check to confirm that the Semaphore has not already been created.
	{
		xTestSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore.
		if ( ( xTestSemaphore ) != NULL )
		{
			xSemaphoreGive( ( xTestSemaphore ) );  // Make the mutex available for use, by initially "Giving" the Semaphore.
		}
	}

	xTaskCreate(
	task1
	,  "Task1"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );

	xTaskCreate(
	task2
	,  "Task2"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );

}
*/

/*-----------------------------------------------------------*/

/*
void task1( void *pvParameters )
{
	#if (configUSE_APPLICATION_TASK_TAG == 1)
	// Set task no to be used for tracing with R2R-Network
	vTaskSetApplicationTaskTag( NULL, ( void * ) 1 );
	#endif

	for(;;)
	{
		//xSemaphoreTake(xTestSemaphore,portMAX_DELAY);
		vTaskDelay(10);
		//xSemaphoreGive(xTestSemaphore);

		PORTA ^= _BV(PA0);
	}
}
*/

/*-----------------------------------------------------------*/

/*
void task2( void *pvParameters )
{
	#if (configUSE_APPLICATION_TASK_TAG == 1)
	// Set task no to be used for tracing with R2R-Network
	vTaskSetApplicationTaskTag( NULL, ( void * ) 2 );
	#endif

	for(;;)
	{
		vTaskDelay(50);
		PORTA ^= _BV(PA7);
	}
}

*/

/*-----------------------------------------------------------*/

void init()
{
	DDRA |= _BV(DDA0) | _BV(DDA7);
	trace_init();

	// param[in] usartNo no of the USART to setup and connect to stdin and stdout [0..3].
	//note This function must be called before using printf(), scanf etc.
	//note Remember to enable global interrupt by calling sei() after the driver is initialised.
	void stdio_initialise(0);
}

/*-----------------------------------------------------------*/

int main(void)
{
	init();

	semaphores_init();
	timers_init();
	lora_init();

	/* Add application code */

	xSemaphoreTake( loraSemaphore, portMAX_DELAY );

	// tasks
	create_tasks();

	// initialize and run the freeRTOS scheduler.
	vTaskStartScheduler();

	// we never should reach here
	while (1){}

}
