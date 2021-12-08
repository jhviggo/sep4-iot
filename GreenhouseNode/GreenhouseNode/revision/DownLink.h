/*
 * DownLink.h
 *
 * Created: 12/7/2021 4:47:30 PM
 *  Author: tolde
 */ 

#pragma once
#ifndef DOWNLINK_H_
#define DOWNLINK_H_
#include <stddef.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <lora_driver.h>
#include "event_groups.h"


void DownLinkHandler_Create(UBaseType_t priority, UBaseType_t stack, MessageBufferHandle_t messageBuffer);
void DownLinkHandler_StartTask(void* messageBuffer);


#endif /* DOWNLINK_H_ */