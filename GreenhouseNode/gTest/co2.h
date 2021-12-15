/*
 * co2.h
 *
 * Created: 15/12/2021 20.13.36
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 *
 */ 

#pragma once

#include <stdint.h>
#include "../GreenhouseNode/driver/mh_z19.h"
#include <stdio.h>
#include <stdlib.h>


 //	Function to return the CO2 value from the created CO2 ADT
uint16_t co2_getLastCO2ppm();

//	Function to set the CO2 value in the CO2 ADT
mh_z19_returnCode_t co2_getLatestMeasurement();

//	Function to initialize a measurement of the driver - MhZ19
void co2_doMeasurement();