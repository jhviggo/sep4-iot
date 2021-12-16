/*
 * LightHandler.h
 *
 * Created: 11/12/2021 19.17.33
 * Author : Michel Sofus Engelhardt Sommer, 273966
 */ 

#pragma once

#include <stdint.h>
#include "../controllers/light.h"

typedef struct lightHandler
{
	union // save allocated memory
	{
		uint32_t lux;
		uint16_t visibleRaw;
		uint16_t infraredRaw;
		uint16_t fullSpectrum;
		lightSensor_t sensorResult;
	};
	
}lightHandler;

typedef struct lightHandler* lightHandler_t;


/************************************************************************/
/* Initialize lightHandler Task, using a TSL2591 Light Sensor			*/
/* Set task_priority, event group, and event bit                        */
/************************************************************************/
lightHandler_t lightHandler_create(UBaseType_t light_task_priority, EventGroupHandle_t eventBits, EventBits_t bits);


/************************************************************************/
/* Returns light level in lux as uint32_t						        */
/************************************************************************/
uint32_t lightHandler_getLux(lightHandler_t self);


/************************************************************************/
/* Returns visible light level as uint16_t                              */
/************************************************************************/
uint16_t lightHandler_getVisibleRaw(lightHandler_t self);


/************************************************************************/
/* Returns infrared light level as uint16_t                             */
/************************************************************************/
uint16_t lightHandler_getInfraredRaw(lightHandler_t self);


/************************************************************************/
/* Returns full spectrum light level as uint16_t                        */
/************************************************************************/
uint16_t lightHandler_getFullSpectrum(lightHandler_t self);


/************************************************************************/
/* Destroys lightHandler Task                                           */
/************************************************************************/
void lightHandler_destroy(lightHandler_t self);

/************************************************************************/
/* Measures light                                                       */
/************************************************************************/
void light_messure( lightHandler_t self );
