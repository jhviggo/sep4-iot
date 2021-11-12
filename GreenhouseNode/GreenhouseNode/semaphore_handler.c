/*
 * semaphores.c
 *
 * Created: 12/11/2021 11.03.38
 *  Author: Michel Sofus Engelhardt Sommer, 273966
 */ 

#include "semaphore_handler.h"

void semaphores_init()
{
	loraSemaphore = xSemaphoreCreateMutex();
	if( loraSemaphore == NULL )
	loraSemaphore = xSemaphoreCreateMutex();

	queueSemaphore = xSemaphoreCreateMutex();
	if( queueSemaphore == NULL )
	queueSemaphore = xSemaphoreCreateMutex();
}
