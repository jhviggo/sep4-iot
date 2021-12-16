/*
 * Configuration.h
 *
 * Created: 14/12/2021 13.53.54
 *  Author: Viggo
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Configuration.h"

typedef struct configuration {
	uint8_t windowPosition;
	bool isWatering;
	bool isLightTurnedOn;
} configuration;

// Uses simple struct instead of dynamically allocating new onces, as only one configuration is needed per device
struct configuration config;

void configuration_setWindowPosition(uint8_t position) {
	config.windowPosition = position;
}

uint8_t configuration_getWindowPosition() {
	return config.windowPosition;
}

void configuration_setLightState(bool value) {
	config.isLightTurnedOn = value;
}

bool configuration_getLightState() {
	return config.isLightTurnedOn;
}

void configuration_setWateringState(bool value) {
	config.isWatering = value;
}

bool configuration_getWateringState() {
	return config.isWatering;
}
 