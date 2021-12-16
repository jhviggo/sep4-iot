/*
 * Temperature.h
 *
 * Created: 12/8/2021 9:50:17 PM
 *  Author: tolde
 */ 

#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "event_groups.h"

typedef struct tempHandler* temperatureHandler_t;

void start_tempTask(void* self);
temperatureHandler_t temperatureHandler_create(UBaseType_t temp_priority_task, EventGroupHandle_t eventBits, EventBits_t bits);
temperatureHandler_t temperatureHandler_destroy(temperatureHandler_t self);
int16_t temperatureHandler_getTemperature(temperatureHandler_t self);
void temperature_handler_task(temperatureHandler_t self);
