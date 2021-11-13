/*
 * semaphore_handler.c
 *
 * Created: 12/11/2021 20.01.49
 *  Author : Michel Sofus Engelhardt Sommer, 273966
 */

#include "semaphore_handler.h"

void semaphores_init() {

	loraSemaphore = xSemaphoreCreateMutex();
	if( loraSemaphore == NULL )
	{
		loraSemaphore = xSemaphoreCreateMutex();
	}

	queueSemaphore = xSemaphoreCreateMutex();
	if( queueSemaphore == NULL )
	{
		queueSemaphore = xSemaphoreCreateMutex();
	}

}
