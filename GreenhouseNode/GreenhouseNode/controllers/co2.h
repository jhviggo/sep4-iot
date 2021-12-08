#pragma once

/*
 * co2.h
 *
 * Created: 08/12/2021 12.48.20
 *  Author: skrue
 */ 

/************************************************************************/
/* Must be called before vTaskStartScheduler() in FreeRTOS              */
/************************************************************************/
void co2_sensor_init(uint16_t co2_ppm, uint8_t com_port);


/************************************************************************/
/* Injects a call-back function that will be                            */
/* called each time a new CO2 value is ready.                           */
/* The call-back function is called from an                             */
/* Interrupt Service Routine (ISR)                                      */
/************************************************************************/
void co2_injectCallBack(uint16_t co2_ppm);


/************************************************************************/
/* Preform measuring of co2 level                                       */
/************************************************************************/
void co2_measure();


/************************************************************************/
/* Returns measured co2 level in ppm                                    */
/************************************************************************/
uint16_t co2_get_value();