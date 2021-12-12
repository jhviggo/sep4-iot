/*
 * LightHandler.h
 *
 * Created: 11/12/2021 19.17.33
 * Author : Michel Sofus Engelhardt Sommer, 273966
 */ 

#pragma once

#include <stdint.h>


typedef struct lightHandler
{
	union // save allocated memory
	{
		uint32_t lux;
		uint16_t visibleRaw;
		uint16_t infraredRaw;
		uint16_t fullSpectrum;
	};
	
}lightHandler;

typedef struct lightHandler* lightHandler_t;

void start_light_task(void* self);
lightHandler_t lightHandler_create(UBaseType_t light_task_priority, EventGroupHandle_t eventBits, EventBits_t bits);
void lightHandler_destroy(lightHandler_t self);

uint32_t lightHandler_getLux( lightHandler_t self);
uint16_t lightHandler_getVisibleRaw( lightHandler_t self);
uint16_t lightHandler_getInfraredRaw( lightHandler_t self);
uint16_t lightHandler_getFullSpectrum( lightHandler_t self);