/*
 * co2.h
 *
 * Created: 15/12/2021 20.13.36
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 * Dummy driver
 *
 */ 

#include "co2.h"

static uint16_t lastCO2ppm;
static mh_z19_returnCode_t returnCode;


//	Return the CO2 value
uint16_t co2_getLastCO2ppm() {

	return lastCO2ppm;
}

//	Initialize a driver measurement
void co2_doMeasurement() {

	returnCode = mh_z19_takeMeassuring();

	if (returnCode != MHZ19_OK) {
		//	Something went wrong
	}
}

//	Set the CO2 value
mh_z19_returnCode_t co2_getLatestMeasurement() {

	returnCode = mh_z19_getCo2Ppm(&lastCO2ppm);
	lastCO2ppm = 1500;	// Just a dummy value
	return returnCode;
}