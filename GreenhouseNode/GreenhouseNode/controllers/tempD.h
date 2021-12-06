/*
 * tempD.h
 *
 * Created: 12/6/2021 2:49:13 PM
 *  Author: tolde
 */ 
#include <stdio.h>
#include <time.h>
#include <stddef.h>
#ifndef TEMPD_H_
#define TEMPD_H_

void temperatureDriver_initDriver(uint8_t port);
float temperatureDriver_getVoltage();



#endif /* TEMPD_H_ */