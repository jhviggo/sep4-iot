#pragma once

/*
 * timer_handler.h
 *
 * Created: 12/11/2021 21.42.51
 * Author : Michel Sofus Engelhardt Sommer, 273966
 */

#include "ATMEGA_FreeRTOS.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <timers.h>

TimerHandle_t loraTimer;
TimerHandle_t restartCycleTimer;

void timers_init();

void lora_timer_callback( TimerHandle_t pxTimer );
void restart_cycle_timer_callback( TimerHandle_t pxTimer);
