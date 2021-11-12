/*
 * timer_handler.c
 *
 * Created: 12/11/2021 11.02.47
 *  Author: Michel Sofus Engelhardt Sommer, 273966
 */ 

#include "timer_handler.h"
#include "semaphores_handler.h"

void timers_init()
{
	// total 1m:10s cycle
	// timers do not restart automatically

	loraTimer = xTimerCreate(
	"LoRa Timer",
	( 1000/portTICK_PERIOD_MS ) /** 60*/ * 5,	// 1 minute
	pdFALSE,
	( void* ) 2,
	lora_timer_callback
	);
	
	restartCycleTimer = xTimerCreate(
	"Restart Cycle Timer",
	( 1000/portTICK_PERIOD_MS ) /** 60*/ * 15,	// 1 minute
	pdFALSE,
	( void* ) 3,
	restart_cycle_timer_callback
	);
}

void lora_timer_callback(TimerHandle_t pxTimer)
{
	printf("5s lora callback");
	if( xSemaphoreTake( tempHumSemaphore, portMAX_DELAY ) != pdTRUE )
	printf("ERROR : TempHum semaphore not taken back.");
	if( xSemaphoreGive( loraSemaphore ) != pdTRUE )
	printf("ERROR : LoRa semaphore not given.");
	
	xTimerStart( restartCycleTimer, 0 );
}

void restart_cycle_timer_callback(TimerHandle_t pxTimer)
{
	printf("5s restart cycle callback");
	if( xSemaphoreTake( loraSemaphore, portMAX_DELAY ) != pdTRUE )
	printf("ERROR : LoRa semaphore not taken back.");
	if( xSemaphoreGive( cycleSemaphore ) != pdTRUE )
	printf("ERROR : Cycle semaphore not given.");
}