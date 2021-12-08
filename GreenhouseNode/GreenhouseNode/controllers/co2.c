/*
 * co2.c
 *
 * Created: 08/12/2021 12.48.05
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 */ 

#include "co2.h"
#include <mh_z19.h>

uint16_t co2_ppm_pointer;

void co2_sensor_init(uint16_t co2_ppm, uint8_t com_port)
{
	mh_z19_initialise(serial_comPort_t, com_port);
}


void co2_injectCallBack(uint16_t co2_ppm) {
	co2_ppm_pointer = co2_ppm;
}


void co2_measure()
{
	mh_z19_returnCode_t returnCode;
	
	if (returnCode = mh_z19_takeMeassuring() != MHZ19_OK)
	{
		printf("CO_SENSOR_ERROR: %d\n", returnCode);
		vTaskDelay(10);
	}
}


uint16_t co2_get_value()
{
	return co2_ppm_pointer;
}