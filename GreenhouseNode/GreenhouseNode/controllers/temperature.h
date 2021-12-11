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

typedef struct temperature* temperature_t;		// Why a struct, containing only one variable

temperature_t temperature_create(void);
temperature_t temperarture_meassure(temperature_t sensor);
