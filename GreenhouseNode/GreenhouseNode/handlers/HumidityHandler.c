/*
 * HumidityHandler.c
 *
 * Created: 12/9/2021 1:25:54 PM
 *  Author: tolde
 */ 
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>
#include <rc_servo.h>
#include <stdio.h>
#include <hih8120.h>
#include <task.h>
#include "event_groups.h"
#include "HumidityHandler.h"

EventGroupHandle_t task_startGroup;
EventBits_t measureBit;

typedef struct humidityHandler
{
	uint16_t humidity;
}humidityHandler;

void start_humidity_task(void* self);

void humidity_handler_initialise(UBaseType_t humidityHandler_priority, humidityHandler_t self)
{
	xEventGroupSetBits(task_startGroup, measureBit);

	xTaskCreate(
	start_humidity_task
	, "HumidityTask"
	,configMINIMAL_STACK_SIZE + 10
	, (void*)self
	,humidityHandler_priority
	,NULL
	);
}

void start_humidity_task(void* self)
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
			printf("Task FAILED");
		}
		xTaskDelayUntil(&xLastWorkingTime, xFrequency1);
		humidity_handler_task((humidityHandler_t)self);
	}
}

humidityHandler_t humidityHandler_create(UBaseType_t hum_task_priority, EventGroupHandle_t eventBits, EventBits_t bits)
{
	humidityHandler_t newReader = calloc(1, sizeof(humidityHandler));

	if(newReader == NULL)
	{
		return NULL;
	}

	newReader->humidity = 0;

	measureBit = bits;

	task_startGroup = eventBits;
	if(HIH8120_OK != hih8120_initialise())
	{
		printf("Humidity sensor could not initialize\n");
	}	
	return newReader;
}

humidityHandler_t humidityHandler_destroy(humidityHandler_t self)
{
	 humidity_destroy(self);
}

uint16_t humidityHandler_getHumidity(humidityHandler_t self)
{
	humidity_getHumidity(self);
}

void humidity_handler_task(humidityHandler_t self)
{
	EventBits_t uxBits = xEventGroupWaitBits(
	task_startGroup,
	measureBit,
	pdFALSE,
	pdTRUE,
	portMAX_DELAY);
	
	if((uxBits & measureBit) == 0)
	{
		if(HIH8120_OK != hih8120_measure())
		{
			printf("Humidity task FAILED");
		}
		else
		{
			self->humidity = hih8120_getHumidity();
		}
		xEventGroupSetBits(task_startGroup, measureBit);
   }
}
