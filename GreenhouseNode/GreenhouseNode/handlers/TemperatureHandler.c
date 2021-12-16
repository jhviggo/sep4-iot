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
EventBits_t measureBit;


typedef struct tempHandler
{
	uint16_t temperature;
}tempHandler;

void start_tempTask(void* self);

void  temperature_handler_initialise(UBaseType_t tempHandler_priority, temperatureHandler_t self)
{
	xEventGroupSetBits(startGroup_task, measureBit);

	xTaskCreate(
	start_tempTask
	,"TemperatureTask"
	, configMINIMAL_STACK_SIZE + 10
	, (void*)self
	, tempHandler_priority
	, NULL);
}

void start_tempTask(void* self)
{
	TickType_t xLastWorkingTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(15000UL);
	xLastWorkingTime = xTaskGetTickCount();
	const TickType_t xFrequency1 = pdMS_TO_TICKS(100UL);

	for(;;)
	{
		xTaskDelayUntil(&xLastWorkingTime, xFrequency);

		if(HIH8120_OK != hih8120_wakeup())
		{
			printf("Temperature task FAILED");
		}
		xTaskDelayUntil(&xLastWorkingTime, xFrequency1);
		temperature_handler_task((temperatureHandler_t) self);
	}
}

temperatureHandler_t temperatureHandler_create(UBaseType_t temp_priority_task, EventGroupHandle_t eventBits, EventBits_t bits)
{
	temperatureHandler_t newReader = calloc(1, sizeof(tempHandler));

	if(newReader == NULL)
	{
		return NULL;
	}

	newReader->temperature = 0;

	measureBit = bits;

	startGroup_task = eventBits;

	if(HIH8120_OK != hih8120_initialise())
	{
		printf("Temperature sensor could not initialized");
	}
	return newReader;
}

temperatureHandler_t temperatureHandler_destroy(temperatureHandler_t self)
{
	temperature_destroy(self);
}

int16_t temperatureHandler_getTemperature(temperatureHandler_t self)
{
	temperature_getTemperature(self);
}

void temperature_handler_task(temperatureHandler_t self)
{
	EventBits_t uxBits = xEventGroupWaitBits(startGroup_task,
	measureBit,
	pdFALSE,
	pdTRUE,
	portMAX_DELAY);

	if((uxBits & (measureBit)) == (measureBit))
	{
		if(HIH8120_OK != hih8120_measure())
		{
			printf("Temperature task FAILED");
		}
		else
		{
			self -> temperature = hih8120_getTemperature();
		}
	}
}