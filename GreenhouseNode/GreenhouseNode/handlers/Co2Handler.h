/*
 * Co2Handler.h
 *
 * Created: 11/12/2021 19.16.16
 * Author : Michel Sofus Engelhardt Sommer, 273966
 */ 

#pragma once

#include <stdint.h>

typedef struct co2Handler
{
	uint16_t co2_ppm;
}co2Handler;

typedef struct co2Handler* co2Handler_t;

void start_co2_task(void* self);
co2Handler_t co2Handler_create(UBaseType_t co2_task_priority, EventGroupHandle_t eventBits, EventBits_t bits);
co2Handler_t co2Handler_destroy(co2Handler_t self);

uint16_t co2Handler_getLevel(co2Handler_t self);