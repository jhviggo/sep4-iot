/*
 * DownLink.h
 *
 * Created: 12/8/2021 7:55:28 PM
 *  Author: tolde
 */ 


#ifndef DOWNLINK_H_
#define DOWNLINK_H_
#pragma once
#include <stddef.h>
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include <lora_driver.h>
#include <status_leds.h>
#include "event_groups.h"

void DownLinkHandler_Create(UBaseType_t priority, UBaseType_t stack, MessageBufferHandle_t messageBuffer);
void DownLinkHandler_StartTask(void* messageBuffere);

