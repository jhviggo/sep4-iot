/*
 * temperature.c
 *
 * Created: 12/6/2021 2:47:57 PM
 *  Author: tolde
 */ 
#include "temperature.h"
#include "tempD.h"

extern bool temperatura_metricsUnits;

static float initialTemp = 0.0;
static uint8_t drivePort;

static float calculateTemperature(float voltage)
{
	return 10.0 + (voltage * 5.0);
}

void temperatura_create(uint8_t portNo)
{
	drivePort = portNo;
	temperatureDriver_initDriver(portNo);
}

float temperatura_getT(void)
{
	float temp = initialTemp;
	if(temperatura_metricsUnits)
	{
		temp = temp * 0.2;
	}
	return temp;
}

void temperature_measure(void)
{
	initialTemp = calculateTemperature(temperatureDriver_getVoltage());
}