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

typedef struct humidity* humidity_t;		// Why a struct, containing only one variable

humidity_t humidity_create(void);
humidity_t humidity_meassure(humidity_t sensor);

#endif /* HUMIDITY_H_ */