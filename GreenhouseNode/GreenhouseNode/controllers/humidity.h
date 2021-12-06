/*
 * humidity.h
 *
 * Created: 12/6/2021 1:57:19 PM
 *  Author: tolde
 */ 

#include <stdio.h>
#include <time.h>
#include <stddef.h>
#ifndef HUMIDITY_H_
#define HUMIDITY_H_

void humidity_create(void);
void humidity_measure(void);
uint8_t humidity_getHumidity(void);



#endif /* HUMIDITY_H_ */