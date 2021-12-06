/*
 * humidity.c
 *
 * Created: 12/6/2021 1:56:52 PM
 *  Author: tolde
 */ 

#include "humidity.h"

static int8_t latestHumidity = 0;

void humidity_create(void)
{
	
	humidityDriver_set();
}

void humidity_measure(void)
{
	latestHumidity = humidityDriver_getHumidity();
}

uint8_t humidity_getHumidity(void)
{
	return latestHumidity;
}