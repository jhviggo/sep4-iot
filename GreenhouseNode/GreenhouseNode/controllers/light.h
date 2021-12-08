#pragma once

/*
 * light.h
 *
 * Created: 08/12/2021 12.47.26
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 */

#include <stdint.h>

typedef struct lightSensor
{
	uint16_t lux;
	int lightMeasurementCount;
	uint16_t averageLight;

}lightSensor;

typedef struct lightSensor* lightSensor_t;


/************************************************************************/
/* Initialize light Sensor, TSL2591                                        */
/* Must be called before vTaskStartScheduler() in FreeRTOS              */
/************************************************************************/
lightSensor_t light_sensor_init();


/************************************************************************/
/* Injects a call-back function that will be                            */
/* called each time a new CO2 value is ready.                           */
/* The call-back function is called from an                             */
/* Interrupt Service Routine (ISR)                                      */
/************************************************************************/
void light_injectCallBack(uint16_t light_lux);	// delete?


/************************************************************************/
/* Preform measuring of light level in lux                              */
/************************************************************************/
uint32_t light_measure(lightSensor_t self);


/************************************************************************/
/* Reset average -level in sensor      ???                              */
/************************************************************************/
void reset_averageLight(lightSensor_t self);


/************************************************************************/
/* Destroy Memory allocated toTSL2591 light sensor                      */
/************************************************************************/
void light_destroy(lightSensor_t self);