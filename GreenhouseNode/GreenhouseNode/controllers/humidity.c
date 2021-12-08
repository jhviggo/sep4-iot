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

humidity_t humidity_create(uint8_t value)
{
	humidity_t newHumidity = calloc(1, sizeof(humidity));
	newHumidity ->latestHumidity = 0;
	return newHumidity;
}

void humidity_measure(humidity_t sensor_h)
{
	return sensor_h ->latestHumidity;
}

uint8_t humidity_getHumidity(humidity_t h_sensor)
{
  return h_sensor->latestHumidity;
}