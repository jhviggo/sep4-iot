/*
 * humidity.h
 *
 * Created: 12/6/2021 1:57:19 PM
 *  Author: tolde
 */ 

#pragma once
#define HUMIDITY_H_

void humidity_create(void);
void humidity_measure(void);
uint8_t humidity_getHumidity(void);
typedef struct humiditySensor* humiditySensor_t;



#endif /* HUMIDITY_H_ */