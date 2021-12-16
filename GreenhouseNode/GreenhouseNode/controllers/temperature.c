/*
 * temperature.c
 *
 * Created: 12/6/2021 2:47:57 PM
 *  Author: tolde
 */ 
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <hih8120.h>
#include <stdio.h>
#include <twi.h>

#include "temperature.h"

typedef struct temperature
{
	int16_t _latestTemp;
} temperature;

// https://ihavn.github.io/IoT_Semester_project/group__hih8120__driver__creation.html#ga1cc535a1c62ff6adc53a0de7a1bc6960	
temperature_t temperature_create(void)
{
	hih8120_driverReturnCode_t returnCode = hih8120_initialise();
	
	temperature_t newTemperature = calloc(1, sizeof(temperature));
	newTemperature->_latestTemp = 0;
	
	if (returnCode == HIH8120_OK)
	{
		// success
		return newTemperature;
	}
	else
	{
		printf("\nHIH8120_TEMP_SENSOR_ERROR: %t\n", returnCode);
		free(newTemperature);
	}
	
}

int16_t temperature_getTemperature(temperature_t t_sensor)
{
	return t_sensor->_latestTemp;
}
	
temperature_t temperature_meassure(temperature_t sensor)
{
		
	hih8120_driverReturnCode_t returnCodeWait = hih8120_initialise();
		
	if( returnCodeWait == HIH8120_OK )
	{
		vTaskDelay(50);
			
		hih8120_driverReturnCode_t returnCode;
		returnCode = hih8120_wakeup();
	
		if ( returnCode == HIH8120_OK )
		{
		
			int16_t temperature = (int16_t) hih8120_getTemperature_x10();
			sensor->_latestTemp = temperature;
		}
		else
		{
			printf("\nHIH8120_HUM_SENSOR_READING_ERROR: %t\n", returnCode);
		}
	}
	else
	{
		printf("\nHIH8120_HUM_SENSOR_READING_WAKEUP_ERROR: %t\n", returnCodeWait);
	}
	return sensor;

}

void temperature_destroy(temperature_t self)
{
	if(self == NULL)
	{
		free(self);
	}
}
