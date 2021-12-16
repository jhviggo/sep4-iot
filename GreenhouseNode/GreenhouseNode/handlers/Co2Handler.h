/*
 * Co2Handler.h
 *
 * Created: 11/12/2021 19.16.16
 * Author : Michel Sofus Engelhardt Sommer, 273966
 */ 

#pragma once

#include <stdint.h>
#include <event_groups.h>

typedef struct co2Handler
{
	uint16_t co2_ppm;
}co2Handler;

typedef struct co2Handler* co2Handler_t;


/************************************************************************/
/* Initialize co2Handler Task, using a MH_Z19 CO2 Sensor				*/
/* Set task_priority, event group, and event bit                        */
/************************************************************************/
co2Handler_t co2Handler_create(UBaseType_t co2_task_priority, EventGroupHandle_t eventBits, EventBits_t bits);


/************************************************************************/
/* Returns CO2 level in ppm as uint16_t                                 */
/************************************************************************/
uint16_t co2Handler_getCO2ppm(co2Handler_t self);


/************************************************************************/
/* Destroys co2Handler Task                                             */
/************************************************************************/
void co2Handler_destroy(co2Handler_t self);

/************************************************************************/
/* Measures co2                                                         */
/************************************************************************/
void co2Handler_measure(co2Handler_t self);
