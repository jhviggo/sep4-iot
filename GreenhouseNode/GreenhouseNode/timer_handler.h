/*
 * timer_handler.h
 *
 * Created: 12/11/2021 10.55.42
 *  Author: Michel Sofus Engelhardt Sommer, 273966
 */ 

#pragma 

#include "ATMEGA_FreeRTOS.h"

#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

TimerHandle_t loraTimer;
TimerHandle_t restartCycleTimer;

void timer_init();

void lora_timer_callback(TimerHandle_t pxTimer);
void restart_cycle_timer_callback(TimerHandle_t pxTimer);