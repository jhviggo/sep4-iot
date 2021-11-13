#pragma once

/*
 * task_handler.h
 *
 * Created: 12/11/2021 21.24.53
 *  Author : Michel Sofus Engelhardt Sommer, 273966
 */

#include "ATMEGA_FreeRTOS.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <task.h>
#include <timers.h>

#include "LoRaWAN_Task.h"
#include "semaphore_handler.h"
#include "timer_handler.h"

TaskHandle_t startCycleTaskHandler;
TaskHandle_t loraSendDataTask;

void start_cycle_task( void *pvParameters );
void lora_send_data_task( void *pvParameters );
