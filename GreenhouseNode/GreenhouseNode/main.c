/*
* main.c
* Author : Viggo Petersen & Michel Sofus Engelhardt Sommer
*
*/

#include "LoraWAN.h"

#define LoRaWAN_TASK_PRIORITY 6
// define semaphore handle
SemaphoreHandle_t xTestSemaphore;

void create_tasks_and_semaphores(void)
{
	{
		xTestSemaphore = xSemaphoreCreateMutex();
		if ( ( xTestSemaphore ) != NULL ){
			xSemaphoreGive( ( xTestSemaphore ) );
		}
	}

	xTaskCreate(
		loraWAN_send_task,
		"LoRaWAN_Send_Task",
		configMINIMAL_STACK_SIZE + 200,
		NULL,
		LoRaWAN_TASK_PRIORITY,
		NULL);
}

void _setTestSensorData() {
	uint8_t data[6] = {1,2,3,4,5,6};
	loraWAN_setPayload(4, 6, data);
}

int main(void)
{
	loraWAN_init();
	printf("Program Started!!\n");
	_setTestSensorData();
	create_tasks_and_semaphores();
	vTaskStartScheduler();

	/* Should never be reached */
	while (1) {}
}
