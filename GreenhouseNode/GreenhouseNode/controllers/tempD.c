/*
 * tempD.c
 *
 * Created: 12/6/2021 2:49:31 PM
 *  Author: tolde
 */ 
#include "tempD.h"
#include "temperature.h"

void temperatureDriver_initDriver(uint8_t port)
{
	srand(time(NULL));
}

void temperaturaDriver_getVoltage()
{
	int r = (rand()%(50 - 0 + 1));
	return ((double)r + 0.5) / 10/0;
}

