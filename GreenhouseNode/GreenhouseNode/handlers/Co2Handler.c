/*
 * Co2Handler.c
 *
 * Created: 11/12/2021 19.16.30
 * Author : Michel Sofus Engelhardt Sommer, 273966
 */ 

#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>
#include <stdint.h>
#include <stddef.h>
#include <task.h>
#include "event_groups.h"

#include "Co2Handler.h"
#include "../controllers/co2.h"

static EventGroupHandle_t task_eventGroup;
static EventBits_t _readyBit;


void start_co2_task(void* self);

co2Handler_t co2Handler_create(UBaseType_t co2_task_priority, EventGroupHandle_t eventBits, EventBits_t bits)
{
	co2Handler_t newSensor = calloc(1, sizeof(co2Handler));
	if (newSensor == NULL) {
		return NULL;
	}

	co2_sensor_init();

	_readyBit = bits;
	task_eventGroup = eventBits;

	co2_measure();
	vTaskDelay(300);
		
	newSensor->co2_ppm = co2_getLevel();
	
	co2_initialize_task(co2_task_priority, newSensor);
	return newSensor;
}

void co2_initialize_task(UBaseType_t co2_task_priority, co2Handler_t self)
{
	xEventGroupSetBits(task_eventGroup, _readyBit);

	xTaskCreate(
	start_co2_task
	, "co2Task"
	, configMINIMAL_STACK_SIZE + 100
	, (void*)self
	, co2_task_priority
	, NULL);
}

void co2Handler_destroy(co2Handler_t self)
{
	if(self == NULL)
	{
		return;
	//	vTaskDelete(self->handleTask);
		vPortFree(self);
	}
}


void start_co2_task(void* self)
{
		EventBits_t readyBits = xEventGroupWaitBits(task_eventGroup,
		_readyBit,
		pdFALSE,
		pdTRUE,
		portMAX_DELAY);

		if ((readyBits & (_readyBit)) == (_readyBit)) {
		
		co2Handler_measure(self);

	}
}


void co2Handler_measure(co2Handler_t self) {
	
	EventBits_t readyBits = xEventGroupWaitBits(task_eventGroup,
	_readyBit,
	pdFALSE,
	pdTRUE,
	portMAX_DELAY);
	
	if ((readyBits & (_readyBit)) == (_readyBit)) {
		
		co2_measure();
		
		vTaskDelay(300);
		
		self->co2_ppm = co2_getLevel();

		xEventGroupSetBits(task_eventGroup, _readyBit);
	}
}