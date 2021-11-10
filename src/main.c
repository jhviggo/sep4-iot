#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Priorities at which the tasks are created. */
#define TASK_MY_TASK_STACK ( configMINIMAL_STACK_SIZE )

/* Task Handles */
SemaphoreHandle_t semaphoreHandle1;
SemaphoreHandle_t semaphoreHandle2;

// --------------------------------------------------------------------------------------
void taskOpA()
{

	if (xSemaphoreTake1(semaphoreHandle, portMAX_DELAY) == pdTRUE)
	{
		puts("R");
		xSemaphoreGive1(semaphoreHandle);
	}
	
	puts("OK");
}

// --------------------------------------------------------------------------------------
void taskOpB()
{
	if (xSemaphoreTake2(semaphoreHandle, portMAX_DELAY) == pdTRUE)
	{
		puts("I");
		xSemaphoreGive(semaphoreHandle);
	}

	puts("OK");
}

void taskOpC()
{
	if (xSemaphoreTake1(semaphoreHandle, portMAX_DELAY) == pdTRUE && xSemaphoreTake1(semaphoreHandle, 5) == pdFALSE)
	{
		puts("O");
		xSemaphoreGive(semaphoreHandle);
	}

	puts("OK");
}

// --------------------------------------------------------------------------------------
void main(void)
{
	semaphoreHandle1 = xSemaphoreCreateMutex();	
	semaphoreHandle2 = xSemaphoreCreateMutex();
	xTaskCreate(
		taskOpA,
		"opA",
		TASK_MY_TASK_STACK,
		(void*)1,
		1,
		NULL);
	
	xTaskCreate(
		taskOpB,
		"opB",
		TASK_MY_TASK_STACK,
		(void*)1,
		1,
		NULL);

	xTaskCreate(
		taskOpC,
		"opC",
		TASK_MY_TASK_STACK,
		(void*)1,
		1,
		NULL);
	
	vTaskStartScheduler();
}