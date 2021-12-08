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

typedef struct tempHandler* temperatureH_t;

temperatureH_t temperatureHandler_create(UBaseType_t temp_priority_task, EventGroupHandle_t eventBits, EventBits_t bits);
temperatureH_t temperatureHandler_destroy(temperatureH_t self);
int16_t getTemperature(temperatureH_t self);
uint16_t getHumidity(temperatureH_t self);
void getTempMeasurements(temperatureH_t self);
void start_tempTask(void* self);
void reset_averageTemp(temperatureH_t self);