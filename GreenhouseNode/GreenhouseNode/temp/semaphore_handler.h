#pragma once

/*
 * semaphore_handler.h
 *
 * Created: 12/11/2021 20.02.18
 *  Author : Michel Sofus Engelhardt Sommer, 273966
 */

#include "ATMEGA_FreeRTOS.h"

#include <stdio.h>
#include <semphr.h>

SemaphoreHandle_t loraSemaphore;
SemaphoreHandle_t queueSemaphore;

void semaphores_init();
