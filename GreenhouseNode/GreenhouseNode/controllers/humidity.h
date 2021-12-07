	/*
 * humidity.h
 *
 * Created: 12/7/2021 12:35:32 PM
 *  Author: tolde
 */ 


#ifndef HUMIDITY_H_
#define HUMIDITY_H_

typedef struct humidity* humidity_t;

humidity_t humidity_create(uint8_t portNo);
void humidity_meassure(humidity_t sensor_h);
uint8_t humidity_getHumidity(humidity_t h_sensor);
void humidity_initiateH();



#endif /* HUMIDITY_H_ */