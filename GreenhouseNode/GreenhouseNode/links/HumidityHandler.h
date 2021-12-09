/*
 * HumidityHandler.h
 *
 * Created: 12/9/2021 1:26:07 PM
 *  Author: tolde
 */ 
#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "event_groups.h"


typedef struct humidityHandler* humidityHandler_t;

void start_humidity_task(void* self);
void humidityHandler_reset_averageHumidity(humidityHandler_t self);
uint16_t humidityHandler_getHumidity(humidityHandler_t self);
humidityHandler_t humidityHandler_create(UBaseType_t hum_task_priority, EventGroupHandle_t eventBits, EventBits_t bits);
humidityHandler_t humidityHandler_destroy(humidityHandler_t self);
void humidityHandler_getHumidityMeasurement(humidityHandler_t self);

