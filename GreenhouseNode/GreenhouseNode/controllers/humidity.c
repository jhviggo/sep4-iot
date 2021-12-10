/*
 * humidity.c
 *
 * Created: 12/6/2021 1:56:52 PM
 *  Author: tolde
 */ 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <hih8120.h>

#include "humidity.h"

humidity_t humidity_create(void)
{
	
	hih8120_driverReturnCode_t returnCode = hih8120_initialise();
		
	humidity_t newHumidity = calloc(1, sizeof(humidity));
	newHumidity->latestHumidity = 0;
		
	if (returnCode == HIH8120_OK)
	{
		// success
		return newHumidity;
	}
	else
	{
		printf("\nHIH8120_TEMP_SENSOR_ERROR: %t\n", returnCode);
		free(newHumidity);
		return NULL;		// catch this
	}
		
}

humidity_t humidity_measure(humidity_t sensor)
{
	
	hih8120_driverReturnCode_t returnCode;
	returnCode = hih8120_wakeup()
		
	if ( returnCode == HIH8120_OK )
	{
		// Something went wrong
		// Investigate the return code further
			
		int16_t humidity = (int16_t) hih8120_getHumidityPercent_x10();
		sensor->latestHumidity = humidity;
	}
	else
	{
		printf("\nHIH8120_TEMP_SENSOR_READING_ERROR: %t\n", returnCode);
	}

	return sensor;
		
}
