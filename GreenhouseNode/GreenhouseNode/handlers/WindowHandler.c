/*
 * WindowHandler.c
 *
 * Created: 12/14/2021 2:27:42 PM
 *  Author: tolde
 */ 
#include <ATMEGA_FreeRTOS.h>
#include <rc_servo.h>
#include <task.h>
#include "WindowHandler.h"
#include "../controllers/WServo.h"

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
	
	vTaskDelay(400);
	
	direction_handler_intiliase(window_task_priority, newWindow);
	
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
	
	for(;;)
	{
			TickType_t xLastWorkingTime;
			const TickType_t xFrequency = pdMS_TO_TICKS(15000UL);
			xLastWorkingTime = xTaskGetTickCount();
			const TickType_t xFrequency1 = pdMS_TO_TICKS(100UL);
	
	  if((readyBits & (dBit)) == (dBit))
	  {
		xTaskDelayUntil(&xLastWorkingTime, xFrequency);
		if(1)
		{
			open_servo(self);
		}
		else if(0)
		{
			close_servo(self);
		}
		else
		{
			printf("Window task has FAILED");
		}
	  }
	  	xTaskDelayUntil(&xLastWorkingTime, xFrequency1);
	  	//direction_handler_intiliase((directionHandler_t) self);
	}
}

void windowHandler_getStatus(directionHandler_t self)
{
	//return self->direction;
}

void windowHandler_destroy(directionHandler_t self)
{
	if(self == NULL)
	{
		vPortFree(self);
	}
}
