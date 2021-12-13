	/*
 * humidity.h
 *
 * Created: 12/7/2021 12:35:32 PM
 *  Author: tolde
 */ 

#ifndef HUMIDITY_H_
#define HUMIDITY_H_

#include <stdint.h>

typedef struct humidity{
	int8_t latestHumidity;
} humidity;

typedef struct humidity* humidity_t;		

humidity_t humidity_create();
humidity_t humidity_meassure(humidity_t sensor);
uint8_t humidity_getHumidity(humidity_t h_sensor);
humidity_t humidity_destroy(humidity_t self);


#endif /* HUMIDITY_H_ */
