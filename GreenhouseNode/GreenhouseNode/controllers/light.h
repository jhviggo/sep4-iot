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
	union // save allocated memory 
	{
		uint32_t lux;
		uint16_t visibleRaw;
		uint16_t infraredRaw;
		uint16_t fullSpectrum;
	};

}lightSensor;

typedef struct lightSensor* lightSensor_t;


/************************************************************************/
/* Initialize light Sensor, TSL2591                                     */
/* Must be called before vTaskStartScheduler() in FreeRTOS              */
/************************************************************************/
lightSensor_t lightSensor_init();


/************************************************************************/
/* Preform measuring of light level                                     */
/* uint32_t lux;														*/
/* uint16_t visibleRaw;													*/
/* uint16_t infraredRaw;												*/
/* uint16_t fullSpectrum;												*/
/* uint16_t combinedData;												*/
/************************************************************************/
void lightMeasure(lightSensor_t self);


/************************************************************************/
/* Destroy Memory allocated to TSL2591 light sensor                     */
/************************************************************************/
void lightDestroy(lightSensor_t self);


/************************************************************************/
/* Return latest Lux value                                              */
/************************************************************************/
uint32_t getLux( lightSensor_t self);


/************************************************************************/
/* Return latest Visible Light                                          */
/************************************************************************/
uint16_t getVisibleRaw(lightSensor_t self);


/************************************************************************/
/* Return latest Infrared Raw Light                                     */
/************************************************************************/
uint16_t getInfraredRaw( lightSensor_t self);


/************************************************************************/
/* Return latest Full Spectrum Light                                    */
/************************************************************************/
uint16_t getFullSpectrum( lightSensor_t self);