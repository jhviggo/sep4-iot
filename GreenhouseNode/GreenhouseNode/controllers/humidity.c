/*
 * humidity.c
 *
 * Created: 12/6/2021 1:56:52 PM
 *  Author: tolde
 */ 

#include "humidity.h"

typedef struct humidity{
	int8_t latestHumidity;
	}humidity;

humidity_t humidity_create(uint8_t portNo)
{
	humidity_t newHumidity = calloc(1, sizeof(humidity));
	newHumidity ->latestHumidity = 0;
	newHumidity humidity_initiateH();
	return newHumidity;
}

void humidity_measure(humidity_t sensor_h)
{
	sensor_h ->latestHumidity = humidity_getHumidity();
}

uint8_t humidity_getHumidity(humidity_t h_sensor)
{
  return h_sensor->latestHumidity;
}

void humidity_initiateH()
{
	srand(time(NULL));
}