/*
 * Configuration.h
 *
 * Created: 14/12/2021 13.53.54
 *  Author: Viggo
 */ 

#pragma once

#include <stdint.h>
#include <stdbool.h>

void configuration_create();
void configuration_destroy();

void configuration_setWindowPosition(uint8_t position);
uint8_t configuration_getWindowPosition();

void configuration_setLightState(bool value);
bool configuration_getLightState();

void configuration_setWateringState(bool value);
bool configuration_getWateringState();
