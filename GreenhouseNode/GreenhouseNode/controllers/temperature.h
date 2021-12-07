/*
 * temperature.h
 *
 * Created: 12/6/2021 2:48:17 PM
 *  Author: tolde
 */ 


#pragma once
#include <time.h>
#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_
#include <stdint.h>
typedef struct temperature* temperature_t;

temperature_t temperature_create(uint8_t portNo);
void temperarture_meassure(temperature_t sensor1);
float temperature_getTemperature(temperature_t sensor);


#endif /* TEMPERATURE_H_ */