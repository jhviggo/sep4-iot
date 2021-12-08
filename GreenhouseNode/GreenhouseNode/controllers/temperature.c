/*
 * temperature.c
 *
 * Created: 12/6/2021 2:47:57 PM
 *  Author: tolde
 */ 
#include "temperature.h"

extern bool temperature_metricsUnit;

typedef struct temperature
{
	 float _latestTemp;
	 
}temperature;

	
	temperature_t temperature_create(uint8_t value)
	{
		temperature_t newTemperature = calloc(1, sizeof(temperature));
		newTemperature ->_latestTemp = 0.0;
		return newTemperature;
	}
	
void temperature_meassure(temperature_t sensor1)
{
	return sensor1 ->_latestTemp;
}	

float temperature_getTemperature(temperature_t sensor)
{
	float temp = sensor ->_latestTemp;
	if(temperature_metricsUnit)
	{
		temp *= 0.2; //dummy again
	}
	return temp;
}

