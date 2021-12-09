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
EventBits_t _readyBit;

typedef struct humidityHandler
{
	uint16_t humidity;
	uint16_t averageH;
	int countHumidityMeasurement;
}humidityHandler;

void start_humidity_task(void* self);

void humidity_handler_initialise(UBaseType_t humidityHandler_priority, humidityHandler_t self)
{
	xEventGroupSetBits(task_startGroup, _readyBit);
	
	xTaskCreate(
	start_humidity_task
	, "HumidityTask"
	,configMINIMAL_STACK_SIZE + 100
	, (void*)self
	,humidityHandler_priority
	,NULL
	);
}

void start_humidity_task(void* self)
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
			printf("Task FAILED");
		}
		xTaskDelayUntil(&xLastAwakeTime, xFrequency1);
		humidity_handler_task((humidityHandler_t) self);
	}
}

void humidityHandler_reset_averageHumidity(humidityHandler_t self)
{
	self ->averageH = 0;
	self ->countHumidityMeasurement = 0;
}

humidityHandler_t humidityHandler_create(UBaseType_t hum_task_priority, EventGroupHandle_t eventBits, EventBits_t bits)
{
	humidityHandler_t newReader = calloc(1, sizeof(humidityHandler));
	
	if(newReader == NULL)
	{
		return NULL;
	}
	
	newReader ->humidity = 0;
	newReader ->countHumidityMeasurement = 0;
	newReader ->averageH = 0;
	
	_readyBit = bits;
	task_startGroup = eventBits;
	
	if(HIH8120_OK == hih8120_initialise())
	{
		printf("Humidity sensor is INITIALIZED");
	}
	
	humidity_handler_task(hum_task_priority, newReader);
	
	return newReader;
}

void humidityHandler_getHumidityMeasurement(humidityHandler_t self)
{
	self ->humidity = self->averageH / self ->countHumidityMeasurement;
}

uint16_t humidityHandler_getHumidity(humidityHandler_t self)
{
	printf("Humidity: %d", self -> humidity);
	return self ->averageH / self ->countHumidityMeasurement;
}

void humidity_handler_task(humidityHandler_t self)
{
	EventBits_t readyBits = xEventGroupWaitBits(
	task_startGroup,
	_readyBit,
	pdFALSE,
	pdTRUE,
	portMAX_DELAY);
	
	if((readyBits & (_readyBit) == (_readyBit)))
	{
		printf("Humidity task FAILED");
	}
	else
	{
		printf("Humidity: %f\n", hih8120_getHumidity());
		
		self ->countHumidityMeasurement ++;
		
		self ->averageH += (uint16_t)hih8120_getHumidity();
		
		printf("Measurement no: %d\n", self ->countHumidityMeasurement);
		printf("Average humidity: %d\n", self ->averageH / self ->countHumidityMeasurement);
	}
}