/*
 * humidityD.h
 *
 * Created: 12/6/2021 2:10:37 PM
 *  Author: tolde
 */ 

#include <stdio.h>
#include <time.h>
#include <stddef.h>
#ifndef HUMIDITYD_H_
#define HUMIDITYD_H_


void humidityDriver_initialize();
uint8_t humidityDriver_getHumidity();


#endif /* HUMIDITYD_H_ */