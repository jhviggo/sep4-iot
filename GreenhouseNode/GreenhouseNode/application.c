/*
* application.c
* Created: 12/8/2021 12:03:50 PM
* Author : Viggo Petersen
*/
#include <stdio.h>
#include <avr/io.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>

#include "controllers/humidity.h"
#include "controllers/temperature.h"
#include "LoraWAN.h"
#include "application.h"

typedef struct application{
	humidity_t sensorHumidity;
	temperature_t sensorTemperature;
} application;

#define LoRaWAN_TASK_PRIORITY 6
#define SENSOR_TASK_PRIORITY 5
// define semaphore handle

void _setTestSensorData(void* pvParameters);

void _create_tasks_and_semaphores(void)
{
	xTaskCreate(
		loraWAN_connect_task,
		"loraWAN_connect_task",
		configMINIMAL_STACK_SIZE + 10,
		NULL,
		LoRaWAN_TASK_PRIORITY,
		NULL);
		
	xTaskCreate(
		loraWAN_send_task,
		"LoRaWAN_Send_Task",
		configMINIMAL_STACK_SIZE + 10,
		NULL,
		LoRaWAN_TASK_PRIORITY - 1,
		NULL);
 	
	xTaskCreate(
		_setTestSensorData,
		"Sensor_update_task",
		configMINIMAL_STACK_SIZE + 10,
		NULL,
		LoRaWAN_TASK_PRIORITY - 2,
		NULL);
	
	xTaskCreate(
		loraWAN_recieve_task,
		"loraWAN_recieve_task",
		configMINIMAL_STACK_SIZE + 10,
		NULL,
		LoRaWAN_TASK_PRIORITY - 3,
		NULL);
}

/* Will eventually be replaced with an actual implementation */
void _setTestSensorData(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(5000UL); // 5 sec
	TickType_t xLastWakeTime = xTaskGetTickCount();
	// sample data 00 1D 4A 19 D0 92 23
	// temp=29, hum=74, co2=826, lum=9352
	while (1) {
		uint8_t data[7] = {0, 29, 74, 25, 208, 146, 35};
		loraWAN_setPayload(4, 7, data);
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}

void application_run(void) {
	loraWAN_init();
	printf("Application running...\n");
	_create_tasks_and_semaphores();
	vTaskStartScheduler();
}

void application_create() {
	application_t _app = calloc(1, sizeof(application));
}
