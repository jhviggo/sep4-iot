/*
 * humidity.h
 *
 * Created: 12/7/2021 12:35:32 PM
 *  Author: tolde
 */ 
#pragma once

#include <stdint.h>

typedef struct humidity* humidity_t;		

humidity_t humidity_create();
humidity_t humidity_meassure(humidity_t sensor);
uint16_t humidity_getHumidity(humidity_t h_sensor);
void humidity_destroy(humidity_t self);
