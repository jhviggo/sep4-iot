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
#include <twi.h>

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
		return NULL;	
	}
	
}

uint16_t humidityHandler_getHumidity(humidityHandler_t self)
{
	return self -> humidity;
}
	
	
humidity_t humidity_measure(humidity_t sensor)
{
	
	hih8120_driverReturnCode_t returnCodeWait = hih8120_initialise();
		
	if( returnCodeWait == HIH8120_OK )
	{
		vTaskDelay(50);
			
		hih8120_driverReturnCode_t returnCode;
		returnCode = hih8120_wakeup();
						
		if ( returnCode == HIH8120_OK )
		{
				
			int16_t humidity = (int16_t) hih8120_getHumidityPercent_x10();
			sensor->latestHumidity = humidity;
		}
		else
		{
			printf("\nHIH8120_TEMP_SENSOR_READING_ERROR: %t\n", returnCode);
		}

	}
	else
	{
		printf("\nHIH8120_TEMP_SENSOR_READING_WAKEUP_ERROR: %t\n", returnCodeWait);
	}
	
	return sensor;
		
}

humidityHandler_t humidityHandler_destroy(humidityHandler_t self)
{
	if(self == NULL)
	{
		return;
		vTaskDelete(self -> humidity);
		vPortFree(self);
	}
}
