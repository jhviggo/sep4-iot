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
#include "handlers/Co2Handler.h"
#include "handlers/HumidityHandler.h"
#include "handlers/TemperatureHandler.h"
#include "handlers/WindowHandler.h"

typedef struct application{
} application;

#define LoRaWAN_TASK_PRIORITY 6
#define SENSOR_TASK_PRIORITY 3
// define semaphore handle

EventGroupHandle_t xSensorEventGroup;
EventBits_t xSensorEventBits;

co2Handler_t _co2Sensor;
humidityHandler_t _humiditySensor;
temperatureHandler_t _temperatureSensor;

directionHandler_t _windowServo;

void _setSensorData(void* pvParameters);

void _create_tasks_and_semaphores(void)
{
	xTaskCreate(
		loraWAN_connect_task,
		"loraWAN_connect_task",
		configMINIMAL_STACK_SIZE,
		NULL,
		LoRaWAN_TASK_PRIORITY, // priority 6
		NULL);
		
	xTaskCreate(
		loraWAN_send_task,
		"LoRaWAN_Send_Task",
		configMINIMAL_STACK_SIZE,
		NULL,
		LoRaWAN_TASK_PRIORITY - 1, // priority 5
		NULL);
 	
	xTaskCreate(
		loraWAN_recieve_task,
		"loraWAN_recieve_task",
		configMINIMAL_STACK_SIZE,
		NULL,
		LoRaWAN_TASK_PRIORITY - 2, // priority 4
		NULL);
	 
	xTaskCreate(
		_setSensorData,
		"Sensor_update_task",
		configMINIMAL_STACK_SIZE + 200,
		NULL,
		SENSOR_TASK_PRIORITY, // priority 3
		NULL);
		
	
	/*
	* BUG: Whenever we create 5 tasks no matter the stack size, the application halts
	*
	* The hardware seems to be running out of space on the stack, so because of the
	* large stack size required by FreeRTOS. Therefore the sensors cannot have a 
	* task for them selves.
	*/
	// co2_initialize_task(SENSOR_TASK_PRIORITY, _co2Sensor);
	// light_initialize_task(SENSOR_TASK_PRIORITY, _co2Sensor);
	// temperature_handler_initialise(SENSOR_TASK_PRIORITY, _co2Sensor);
	// humidity_handler_initialise(SENSOR_TASK_PRIORITY, _co2Sensor);
}

void _setSensorData(void* pvParameters) {
	const TickType_t xFrequency = pdMS_TO_TICKS(5000UL); // 5 sec
	TickType_t xLastWakeTime = xTaskGetTickCount();
	
	while (1) {
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		// CO2 sensor
		co2Handler_measure(_co2Sensor);
		vTaskDelay(100);
		// uint16_t _co2Value = co2Handler_getCO2ppm(_co2Sensor);
		uint16_t _co2Value = 461; // Sample value because co2 driver NEVER calls callback function
		
		// Humidity sensor
		humidity_handler_task(_humiditySensor);
		vTaskDelay(100);
		uint16_t _humValue = humidityHandler_getHumidity(_humiditySensor);
		
		// Temperature sensor
		temperature_handler_task(_temperatureSensor);
		vTaskDelay(100);
		int16_t _tempValue = temperatureHandler_getTemperature(_temperatureSensor);

		uint8_t data[7];
		data[0] = _tempValue >> 8;
		data[1] = _tempValue;
		data[2] = _humValue;
		data[3] = _co2Value >> 5;
		data[4] = _co2Value << 3;
		data[5] = 0;
		data[6] = 0;
		
		loraWAN_setPayload(4, 7, data);
		start_directionTask(_windowServo);
	}
}

void application_run(void) {
	loraWAN_init();
	printf("Application running...\n");
	
	// Initialize sensors
	_co2Sensor = co2Handler_create(SENSOR_TASK_PRIORITY, xSensorEventGroup, xSensorEventBits);
	_humiditySensor = humidityHandler_create(SENSOR_TASK_PRIORITY, xSensorEventGroup, xSensorEventBits);
	_temperatureSensor = temperatureHandler_create(SENSOR_TASK_PRIORITY, xSensorEventGroup, xSensorEventBits);
	_windowServo = windowHandler_create(SENSOR_TASK_PRIORITY, xSensorEventGroup, xSensorEventBits);
	
	_create_tasks_and_semaphores();
	vTaskStartScheduler();
}

application_t application_create(void) {
	application_t _app = calloc(1, sizeof(application));
	xSensorEventGroup = xEventGroupCreate();
	xSensorEventBits = xEventGroupGetBits(xSensorEventGroup);
	return _app;
}
