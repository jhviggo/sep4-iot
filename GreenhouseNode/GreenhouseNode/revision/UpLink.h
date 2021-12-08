/*
 * UpLink.h
 *
 * Created: 12/7/2021 4:46:42 PM
 *  Author: tolde
 */ 


#ifndef UPLINK_H_
#define UPLINK_H_
#pragma once
#include <stddef.h>
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include <lora_driver.h>
#include <status_leds.h>
#include "event_groups.h"

void lora_handler_initialise(UBaseType_t lora_handle_task_priority);


#endif /* UPLINK_H_ */