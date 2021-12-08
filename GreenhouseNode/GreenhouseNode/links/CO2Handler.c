/*
 * CO2Handler.c
 *
 * Created: 12/8/2021 8:39:08 PM
 *  Author: tolde
 */ 
#include <mh_z19.h>
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include "CO2Handler.h"
#include "SharedPrint.h"
#include "event_groups.h"

uint16_t ppm; 
mh_z19_returnCode_t rc;

void myCo2CallBack(uint16_t ppmCall);
void start_co2_task(void* self);

EventGroupHandle_t task_startGroup;
EventBits_t readyBit;


typedef struct CO2Handler
{
	uint16_t value;
	int countCO2Measurement;
	uint16_t averageCO2;
	}CO2Handler;
	
	CO2Handler_t co2_create(UBaseType_t co2_task_priority, EventGroupHandle_t eventBits, EventBits_t bits)
	{
		CO2Handler_t new_reader = calloc(sizeof(CO2Handler), 1);
		if(new_reader == NULL)
		{
			return NULL;
		}
		
		new_reader -> value = 0;
		new_reader -> averageCO2 = 0;
		new_reader -> countCO2Measurement = 0;
		initialiseCO2Sensor();
		
		readyBit = bits;
		task_startGroup = eventBits;
		
		rc = mh_z19_takeMeassuring();
		co2_initialise_task(co2_task_priority, new_reader);
		return new_reader;
	}
	
	void start_co2_task(void* self)
	{
	   TickType_t xLastAwakeTime;
	   const TickType_t xFrequency = pdMS_TO_TICKS(16000UL);
	   xLastAwakeTime = xTaskGetTickCount();
	   
	   for(;;)
	   {
		   xTaskDelayUntil(&xLastAwakeTime, xFrequency);
		   co2_task_handler((CO2Handler_t)self);
	   }
	}
	
	void reset_averageCO2(CO2Handler_t self)
	{
		self ->countCO2Measurement = 0;
		self ->averageCO2 = 0;
	}
	
	void co2_initialise_task(UBaseType_t co2_task_priority, CO2Handler_t self)
	{
		xEventGroupSetBits(task_startGroup _readyBit);
		
		xTaskCreate(
		start_co2_task
		, "co2Task"
		, configMINIMAL_STACK_SIZE + 100
		,(void*) self
		, co2_task_priority
		, NULL);
	}
	
	void initialiseCO2Sensor()
	{
		mh_z19_initialise(ser_USART3);
		mh_z19_injectCallBack(myCo2CallBack);
	}
	
	void myCo2CallBack(uint16_t ppmCall)
	{
		ppm = ppmCall;
	}
	
	uint16_t getCO2(CO2Handler_t self)
	{
		self -> value = self ->averageCO2 / self ->countCO2Measurement;
		return self ->value;
	}
	
	void co2_task_handler(CO2Handler_t self)
	{
		EventBits_t _readyBit = xEventGroupWaitBits(task_startGroup,
		readyBit,
		pdFALSE,
		pdTRUE,
		portMAX_DELAY);
		
		if((_readyBit & (readyBit)) == (readyBit))
		{
			rc = mh_z19_takeMeassuring();
			
			if(rc != MHZ19_OK)
			{
				printShared("CO2 MEASUREMENT FAILED");
				return;
			}
			
			self ->countCO2Measurement++;
			self ->averageCO2 += ppm;
			printShared("Measurement number: %d \n", self ->countCO2Measurement);
			printShared("Average CO2: %d \n", self ->averageCO2 / self ->countCO2Measurement);
		}
	}