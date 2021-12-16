/*
 * WindowHandler.c
 *
 * Created: 12/14/2021 2:27:42 PM
 *  Author: tolde
 */ 
#include <ATMEGA_FreeRTOS.h>
#include <rc_servo.h>
#include <task.h>
#include <stdlib.h>
#include "WindowHandler.h"
#include "../controllers/WServo.h"
#include "../Configuration.h"

EventGroupHandle_t startGroup_task;
EventBits_t dBit;

typedef struct direction{
	int8_t direction_servo;
	}direction;

void start_directionTask(void * self);

directionHandler_t windowHandler_create(UBaseType_t window_task_priority, EventGroupHandle_t eventBits, EventBits_t bits)
{
	directionHandler_t newWindow = calloc(1, sizeof(direction));
	
	if((newWindow == NULL))
	{
		return NULL;
	}
	
	initialise_servo();
	
	dBit = bits;
	startGroup_task = eventBits;	
	return newWindow;
}

void direction_handler_intiliase(UBaseType_t directionHandler_priority, directionHandler_t self)
{
	xEventGroupSetBits(startGroup_task, dBit);

	xTaskCreate(
	start_directionTask
	, "WindowTask"
	, configMINIMAL_STACK_SIZE + 100
	, (void*)self
	, directionHandler_priority
	, NULL);
}

void start_directionTask(void* self)
{
	EventBits_t readyBits = xEventGroupWaitBits(startGroup_task,
	dBit,
	pdFALSE,
	pdTRUE,
	portMAX_DELAY);

	TickType_t xLastWorkingTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(15000UL);
	xLastWorkingTime = xTaskGetTickCount();
	const TickType_t xFrequency1 = pdMS_TO_TICKS(100UL);
	
	if((readyBits & (dBit)) == (dBit))
	{
		xTaskDelayUntil(&xLastWorkingTime, xFrequency);
		uint8_t position = configuration_getWindowPosition();
		set_servo(0, position);
	}
	xTaskDelayUntil(&xLastWorkingTime, xFrequency1);
	
}

int8_t windowHandler_getStatus(directionHandler_t self)
{
	return self->direction_servo;
}

void windowHandler_destroy(directionHandler_t self)
{
	if(self == NULL)
	{
		free(self);
	}
}
