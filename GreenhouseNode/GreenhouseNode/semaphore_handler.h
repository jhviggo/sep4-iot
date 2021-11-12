/*
 * semaphores.h
 *
 * Created: 12/11/2021 10.56.11
 *  Author: Michel Sofus Engelhardt Sommer, 273966
 */ 

#pragma 

#include "ATMEGA_FreeRTOS.h"
#include <stdio.h>
#include <semphr.h>

SemaphoreHandle_t loraSemaphore;
SemaphoreHandle_t queueSemaphore;

void semaphores_init();
