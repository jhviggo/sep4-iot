/*
 * CO2Handler.h
 *
 * Created: 12/8/2021 8:38:55 PM
 *  Author: tolde
 */ 

#pragma once
#include <ATMEGA_FreeRTOS.h>
#include<stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include "task.h"
#include "event_groups.h"

typedef struct CO2Handler* CO2Handler_t;

CO2Handler_t co2_create(UBaseType_t co2_task_priority, EventGroupHandle_t eventBits, EventBits_t bits);
void initialiseCO2Sensor();
void getCO2Measurement(CO2Handler_t self);
uint16_t getCO2Measurement(CO2Handler_t self);
void start_co2_task(void* self);
void co2_initialise_task(UBaseType_t co2_task_priority, CO2Handler_t self);
void reset_averageCO2(CO2Handler_t self);