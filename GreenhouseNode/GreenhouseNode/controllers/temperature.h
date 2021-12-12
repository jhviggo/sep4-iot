/*
 * temperature.h
 *
 * Created: 12/6/2021 2:48:17 PM
 *  Author: tolde
 */ 
#pragma once

#include <time.h>
#include <stdint.h>

typedef struct temperature
{
	int16_t _latestTemp;
} temperature;

typedef struct temperature* temperature_t;		

temperature_t temperature_create();
temperature_t temperarture_meassure(temperature_t sensor);
uint8_t temperature_getTemperature(temperature_t t_sensor);
temperature_t temperature_destroy(temperature_t self);
