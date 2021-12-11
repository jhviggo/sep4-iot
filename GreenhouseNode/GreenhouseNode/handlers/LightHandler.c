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


void start_light_task(void* self)
{
	
}


lightHandler_t lightHandler_create(UBaseType_t light_task_priority, EventGroupHandle_t eventBits, EventBits_t bits)
{
	return NULL;
}


lightHandler_t lightHandler_destroy(lightHandler_t self)
{
	return NULL;	
}


uint32_t lightHandler_getLux( lightHandler_t self)
{
	return 0;	
}


uint16_t lightHandler_getVisibleRaw( lightHandler_t self)
{
	return 0;
}


uint16_t lightHandler_getInfraredRaw( lightHandler_t self)
{
	return 0;
}


uint16_t lightHandler_getFullSpectrum( lightHandler_t self)
{
	return 0;
}