/*
 * humidityD.c
 *
 * Created: 12/6/2021 2:10:22 PM
 *  Author: tolde
 */ 

#include "humidityD.h"

void humidityDriver_initialize()
{
	srand(time(NULL));
}

uint8_t humidityDriver_getHumidity()
{
	return (rand()%(55 - 20 + 1)) + 20;
}