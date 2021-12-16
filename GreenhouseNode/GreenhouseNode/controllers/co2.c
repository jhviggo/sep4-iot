/*
 * co2.c
 *
 * Created: 08/12/2021 12.48.05
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 */ 

#include <stddef.h>
#include "co2.h"
#include <mh_z19.h>
#include <serial.h>

uint16_t ppm;

// https://ihavn.github.io/IoT_Semester_project/mh_z19_driver_quick_start.html
// https://ihavn.github.io/IoT_Semester_project/group__mh__z19__driver.html

void co2CallBack(uint16_t ppmCall);

void co2_sensor_init()
{
	mh_z19_initialise(ser_USART3);
	mh_z19_injectCallBack(co2CallBack);
}

void co2CallBack(uint16_t ppmCall)
{
	ppm = ppmCall;
}

void co2_measure()
{
	mh_z19_returnCode_t returnCode = mh_z19_takeMeassuring();
	
	if (returnCode != MHZ19_OK)
	{
		printf("CO_SENSOR_ERROR: %d\n", returnCode);
	}
}


uint16_t co2_getLevel()
{
	return ppm;
}