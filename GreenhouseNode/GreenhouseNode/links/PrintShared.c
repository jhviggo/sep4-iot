/*
 * PrintShared.c
 *
 * Created: 12/8/2021 9:28:34 PM
 *  Author: tolde
 */ 

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>
#include <stdio.h>
#include <stdarg.h>

SemaphoreHandle_t sharedMutex;

void create_shared_print()
{
	sharedMutex = xSemaphoreCreateMutex();
}

void printShared(const char* format, ...)
{
	va_list list1;
	
	if(xSemaphoreTake(sharedMutex, pdMS_TO_TICKS(400)) == pdTRUE)
	{
		va_start(list1, format);
		vprintf(format, list1);
		xSemaphoreGive(sharedMutex);
	}
	else
	{
		
	}
}