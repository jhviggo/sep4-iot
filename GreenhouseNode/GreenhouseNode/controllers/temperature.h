/*
 * temperature.h
 *
 * Created: 12/6/2021 2:48:17 PM
 *  Author: tolde
 */ 


#include <stdio.h>
#include <time.h>
#include <stddef.h>
#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

void temperatura_create(uint8_t port);
void temperature_measure(void);
float temperatura_getT(void);



#endif /* TEMPERATURE_H_ */