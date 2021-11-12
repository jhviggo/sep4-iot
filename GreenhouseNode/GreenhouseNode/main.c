/*
 * GreenhouseNode.c
 *
 * Created: 11/11/2021 15.33.20
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 * Started from Semester project template at VIA University Collage Horsens, Denmark by Ib Havn, https://github.com/ihavn/IoT_Semester_project
 */ 

#include <avr/io.h>
#include <avr/sfr_defs.h>

#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#include "../FreeRTOSTraceDriver/FreeRTOSTraceDriver.h"

#include <stdio.h>
#include <stdio_driver.h>
#include <ihal.h>

// Needed for LoRaWAN
#include <lora_driver.h>
#include <status_leds.h>

#include "LoRaWAN_handler.h"
#include "timer_handler.h"
#include "semaphores.h"
#include "task_handler.h"

/*-----------------------------------------------------------*/
int main(void)
{
	trace_init();
	stdioCreate(0);
	
	//init
	semaphores_init();
	timers_init();
	
	//drivers
	lora_init();
	
	//Semaphores
	xSemaphoreTake(loraSemaphore, portMAX_DELAY);
	
	//tasks
	create_tasks();
	
	vTaskStartScheduler(); // Initialise and run the freeRTOS scheduler. Execution should never return from here.

	while (1) {} // we never should reach here
}


