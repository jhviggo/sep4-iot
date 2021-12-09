/*
 * Temperature.c
 *
 * Created: 12/8/2021 9:50:07 PM
 *  Author: tolde
 */ 

#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>
#include <rc_servo.h>
#include <task.h>
#include <hih8120.h>
#include "event_groups.h"
#include "TemperatureHandler.h"

EventGroupHandle_t startGroup_task;
EventBits_t _readyBit;

typedef struct tempHandler
{
    uint16_t temperature;
	uint16_t averageTemp;
	int countTempMeasurement;
}tempHandler;
	
void start_tempTask(void* self);
	
void  temperature_handler_initialise(UBaseType_t tempHandler_priority, temperatureHandler_t self)
{
	xEventGroupSetBits(startGroup_task, _readyBit);
		
	xTaskCreate(
	start_tempTask
	,"TemperatureTask"
	, configMINIMAL_STACK_SIZE + 100
	, (void*)self
	, tempHandler_priority
	, NULL);
}
	
void start_tempTask(void* self)
{
	TickType_t xLastAwakeTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(15000UL);
	xLastAwakeTime = xTaskGetTickCount();
	const TickType_t xFrequency1 = pdMS_TO_TICKS(100UL);
		
	for(;;)
	{
		xTaskDelayUntil(&xLastAwakeTime, xFrequency);
			
		if(HIH8120_OK != hih8120_wakeup())
		{
			printf("Temperature task FAILED");
		}
		xTaskDelayUntil(&xLastAwakeTime, xFrequency1);
		temperature_handler_task((temperatureHandler_t) self);
	}
}
	
void temperatureHandler_reset_averageTemp(temperatureHandler_t self)
{
	self -> countTempMeasurement = 0;
	self -> averageTemp = 0;
}
	
temperatureHandler_t temperatureHandler_create(UBaseType_t temp_priority_task, EventGroupHandle_t eventBits, EventBits_t bits)
{
	temperatureHandler_t newReader = calloc(1, sizeof(tempHandler));
	
	if(newReader == NULL)
	{
		return NULL;
	}
	
	newReader -> temperature = 0;
	newReader -> averageTemp = 0;
	newReader -> countTempMeasurement = 0;
	
	_readyBit = bits;
		
	startGroup_task = eventBits;
	
	if(HIH8120_OK == hih8120_initialise())
	{
		printf("T sensor initialized");
	}
	
	temperature_handler_initialise(temp_priority_task, newReader);
	return newReader;
}
	
void temperatureHandler_getTempMeasurements(temperatureHandler_t self)
{
	self -> temperature = self ->averageTemp / self -> countTempMeasurement;
	printf("Getting temp measurements from function");
}
	
int16_t temperatureHandler_getTemperature(temperatureHandler_t self)
{
	printf("Temperature: %d", self -> temperature);
	return self -> averageTemp / self -> countTempMeasurement;
}
	
void temperature_handler_task(temperatureHandler_t self)
{
	EventBits_t ready_bits = xEventGroupWaitBits(startGroup_task,
	_readyBit,
	pdFALSE,
	pdTRUE,
	portMAX_DELAY);
		
	if((ready_bits & (_readyBit)) == (_readyBit))
	{
		if(HIH8120_OK != hih8120_measure())
		{
			printf("Temperature task FAILED");
		}
		else
		{
			printf("Temp: %f\n", hih8120_getTemperature());
				
			self ->countTempMeasurement;
			self ->averageTemp += (int16_t)hih8120_getTemperature();
				
			printf("AverageTemp: %d\n", self ->averageTemp/ self ->countTempMeasurement);
			printf("Measurement no: %d", self ->countTempMeasurement);
		}
	}
}