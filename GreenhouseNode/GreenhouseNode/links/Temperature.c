/*
 * Temperature.c
 *
 * Created: 12/8/2021 9:50:07 PM
 *  Author: tolde
 */ 

#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>
#include <rc_servo.h>
#include <task.h>
#include <hih8120.h>
#include "PrintShared.h"
#include "event_groups.h"
#include "Temperature.h"

EventGroupHandle_t startGroup_task;
EventBits_t _readyBit;

typedef struct tempHandler
{
	uint16_t humidity;
	uint16_t temperature;
	uint16_t averageH;
	uint16_t averageTemp;
	int countTempMeasurement;
	}tempHandler;
	
	void start_tempTask(void* self);
	
	void  temperature_handler_initialise(UBaseType_t tempHandler_priority, temperatureH_t self)
	{
		xEventGroupSetBits(startGroup_task _readyBit);
		
		xTaskCreate(
		start_tempTask
		,"TemperatureTask"
		, configMINIMAL_STACK_SIZE + 100
		, (void*)self
		, tempHandler_priority
		, NULL);
	}
	
	void start_tempTask(void* self)
	{
		TickType_t xLastAwakeTime;
	    const TickType_t xFrequency = pdMS_TO_TICKS(15000UL);
		xLastAwakeTime = xTaskGetTickCount();
		const TickType_t xFrequency1 = pdMS_TO_TICKS(100UL);
		
		for(;;)
		{
			xTaskDelayUntil(&xLastAwakeTime, xFrequency);
			
			if(HIH8120_OK != hih8120_wakeup())
			{
				printShared("Temperature task FAILED");
			}
			xTaskDelayUntil(&xLastAwakeTime, xFrequency1);
			temperature_handler_task((temperatureH_t) self);
		}	
	}
	
	void reset_averageTemp(temperatureH_t self)
	{
		self -> countTempMeasurement = 0;
		self -> averageTemp = 0;
		self -> averageH = 0;
	}
	
	temperatureH_t temperatureHandler_create(UBaseType_t temp_priority_task, EventGroupHandle_t eventBits, EventBits_t bits)
	{
		temperatureH_t newReader = calloc(1, sizeof(tempHandler));
		
		if(newReader == NULL)
		{
			return NULL;
		}
		
		newReader -> temperature = 0;
		newReader -> averageTemp = 0;
		newReader -> countTempMeasurement = 0;
		newReader -> humidity = 0;
		newReader->averageH = 0;
		
		_readyBit = bits;
		
	startGroup_task = eventBits;
	
	if(HIH8120_OK == hih8120_initialise())
	{
		printShared("T sensor initialized");
	}
	
	temperature_handler_initialise(temp_priority_task, newReader)
	return newReader;
	}
	
	void getTempMeasurements(temperatureH_t self)
	{
		self -> humidity = self ->averageH / self -> countTempMeasurement;
		self -> temperature = self ->averageTemp / self -> countTempMeasurement;
		
		printShared("Getting temp measurements from function");
	}
	
	int16_t getTemperature(temperatureH_t self)
	{
		printShared("Temperature: %d", self -> temperature);
		return self -> averageTemp / self -> countTempMeasurement;
	}
	
	uint16_t getHumidity(temperatureH_t self)
	{
		printShared("Humidity: %d", self ->humidity);
		return self ->averageH / self ->countTempMeasurement;
	}
	
	void temperature_handler_task(temperatureH_t self)
	{
		EventBits_t ready_bits = xEventGroupWaitBits(startGroup_task,
		_readyBit,
		pdFALSE,
		pdTRUE,
		portMAX_DELAY);
		
		if((ready_bits & (_readyBit)) == (_readyBit))
		{
			if(HIH8120_OK != hih8120_measure())
			{
				printShared("Temperature task FAILED");
			}
			else
			{
				printShared("Temp: %f\n", hih8120_getTemperature());
				printShared("Humidity: %f\n", hih8120_getHumidity());
				
				self ->countTempMeasurement;
				self ->averageTemp += (int16_t)hih8120_getTemperature();
				self ->averageH += (int16_t)hih8120_getHumidity();
				
				printShared("AverageTemp: %d\n", self ->averageTemp/ self ->countTempMeasurement);
				printShared("AverageH: %d\n", self ->averageH / self ->countTempMeasurement);
				printShared("Measurement no: %d", self ->countTempMeasurement);
			}
		}
	}