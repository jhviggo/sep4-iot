#pragma once

/*
 * co2.h
 *
 * Created: 08/12/2021 12.48.20
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 */

#include <stdint.h>


/************************************************************************/
/* Initialize CO2 Sensor, MH-Z19                                        */
/* Must be called before vTaskStartScheduler() in FreeRTOS              */
/* standard port => ser_USART3											*/
/************************************************************************/
void co2_sensor_init();


/************************************************************************/
/* Preform measuring of co2 level                                       */
/************************************************************************/
void co2_measure();


/************************************************************************/
/* Returns measured co2 level in ppm                                    */
/************************************************************************/
uint16_t co2_getLevel();