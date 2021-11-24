/*
 * GreenhouseNode.c
 *
 * Created: 11/11/2021 15.33.20
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 * Started from Semester project template at VIA University Collage Horsens, Denmark by Ib Havn, https://github.com/ihavn/IoT_Semester_project
 */

#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#include "../FreeRTOSTraceDriver/FreeRTOSTraceDriver.h"

#include "../tasks/LoRaWAN.h"

#define LoRaWAN_TASK_PRIORITY 6
#define LoRaWAN_TASK_RX_PRIORITY 1

// define two Tasks
void lora_tx( void *pvParameters );
void lora_rx( void *pvParameters );

// define semaphore handle
SemaphoreHandle_t xTestSemaphore;

/*-----------------------------------------------------------*/

//TODO Add timers to handle delay and sleep time of LoRa module

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
		lora_tx
		,  "LoRaWAN_Send_Task"  // A name just for humans
		,  configMINIMAL_STACK_SIZE + 200 // This stack size can be checked & adjusted by reading the Stack Highwater
		,  NULL
		,  LoRaWAN_TASK_PRIORITY  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
		,  NULL );

	xTaskCreate(
		lora_rx
		,  "LoRaWAN_Recive_Task"  // A name just for humans
		,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
		,  NULL
		,  LoRaWAN_TASK_RX_PRIORITY  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
		,  NULL );

}


/*-----------------------------------------------------------*/
void lora_tx( void *pvParameters )
{
	#if (configUSE_APPLICATION_TASK_TAG == 1)
	// Set task no to be used for tracing with R2R-Network
	vTaskSetApplicationTaskTag( NULL, ( void * ) 1 );
	#endif

	LoRaWAN_connect();
	for(;;)
	{
	/*	
		size_t xBytesSent;
		char* pcStringToSend = "65535";

		xBytesSent = xMessageBufferSend(xMessageBuffer,
		(void*)pcStringToSend, //object to be send
		strlen(pcStringToSend), //size of object
		portMAX_DELAY); //block forever
	*/	
		LoRaWAN_send();

		PORTA ^= _BV(PA0);	// Pin D22
	}
}

/*-----------------------------------------------------------*/
void lora_rx( void *pvParameters )
{
	#if (configUSE_APPLICATION_TASK_TAG == 1)
	// Set task no to be used for tracing with R2R-Network
	vTaskSetApplicationTaskTag( NULL, ( void * ) 2 );
	#endif

	for(;;)
	{
		LoRaWAN_downlink();
		vTaskDelay(50);
		PORTA ^= _BV(PA7);	// Pin D29
	}
}

void init() {

	DDRA |= _BV(DDA0) | _BV(DDA7);
	trace_init();
	
}

/*-----------------------------------------------------------*/

int main(void)
{
	init();
	create_tasks_and_semaphores();
	LoRaWAN_init();

	/* Add application code */

	vTaskStartScheduler(); //initialize and run the freeRTOS scheduler. Execution should never return here.

	while (1) {} // we never should reach here
}
