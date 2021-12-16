/*
 * LightHandler.c
 *
 * Created: 11/12/2021 19.17.12
 * Author : Michel Sofus Engelhardt Sommer, 273966
 */ 

#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>
#include <stdint.h>
#include <stddef.h>
#include <task.h>
#include "event_groups.h"

#include "LightHandler.h"
#include "../controllers/light.h"

static EventGroupHandle_t task_eventGroup;
static EventBits_t _readyBit;


void start_light_task(void* self);


void light_messure( lightHandler_t self )
{
	lightMeasure(self->sensorResult);
	lightSensor_t sensorResult = self->sensorResult;
	self->lux = sensorResult->lux;
	self->visibleRaw = sensorResult->visibleRaw;
	self->infraredRaw = sensorResult->infraredRaw;
	self->fullSpectrum = sensorResult->fullSpectrum;
	self->sensorResult = sensorResult;
}


lightHandler_t lightHandler_create(UBaseType_t light_task_priority, EventGroupHandle_t eventBits, EventBits_t bits)
{
	lightHandler_t newHandler = calloc(1, sizeof(lightHandler));
	if (newHandler == NULL) {
		return NULL;
	}

	co2_sensor_init();
	
	newHandler->sensorResult = lightSensor_init();

	_readyBit = bits;
	task_eventGroup = eventBits;
	return newHandler;
}


void light_initialize_task(UBaseType_t light_task_priority, lightHandler_t self)
{
	xEventGroupSetBits(task_eventGroup, _readyBit);

	xTaskCreate(
	start_light_task
	, "lightTask"
	, configMINIMAL_STACK_SIZE + 100
	, (void*)self
	, light_task_priority
	, NULL);
}


void start_light_task(void* self)
{
	EventBits_t readyBits = xEventGroupWaitBits(task_eventGroup,
	_readyBit,
	pdFALSE,
	pdTRUE,
	portMAX_DELAY);
	
	if ((readyBits & (_readyBit)) == (_readyBit)) {
		
		// Light Task
			
		light_messure(self);
		
	}
}


uint32_t lightHandler_getLux( lightHandler_t self)
{
	return self->lux;
}


uint16_t lightHandler_getVisibleRaw( lightHandler_t self)
{
	return self->visibleRaw;
}


uint16_t lightHandler_getInfraredRaw( lightHandler_t self)
{
	return self->infraredRaw;
}


uint16_t lightHandler_getFullSpectrum( lightHandler_t self)
{
	return self->fullSpectrum;
}


void lightHandler_destroy(lightHandler_t self)
{
	if(self == NULL)
	{
		return;

		lightDestroy(self->sensorResult);
		vPortFree(self);
	}
}