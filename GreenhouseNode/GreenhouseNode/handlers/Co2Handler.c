/*
 * Co2Handler.c
 *
 * Created: 11/12/2021 19.16.30
 * Author : Michel Sofus Engelhardt Sommer, 273966
 */ 

#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>
#include <stdint.h>
#include <stddef.h>
#include <task.h>
#include "event_groups.h"

#include "Co2Handler.h"
#include "../controllers/co2.h"


void start_co2_task(void* self)
{
	
}


co2Handler_t co2Handler_create(UBaseType_t co2_task_priority, EventGroupHandle_t eventBits, EventBits_t bits)
{
	return NULL;
}


co2Handler_t co2Handler_destroy(co2Handler_t self)
{
	return NULL;	
}


uint16_t co2Handler_getLevel(co2Handler_t self)
{
	return 0;	
}