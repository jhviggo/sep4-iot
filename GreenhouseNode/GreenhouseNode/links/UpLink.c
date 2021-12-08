/*
 * UpLink.c
 *
 * Created: 12/8/2021 7:08:51 PM
 *  Author: tolde
 */ 
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "UpLink.h"

#include <lora_driver.h>
#include <status_leds.h>
#include <message_buffer.h>

#define LORA_appEUI: "2BBE8F09765BBF4B"
#define LORA_appKEY: "5F83717BC67B4646E3F00DC5EC3417DC"

static char _out_buf[100];
static lora_driver_payload_t _uplink_payload;
static MessageBufferHandle_t _buffer;
void lora_handler_task(void* pvParameters);

void lora_UpLinkHandler_startTask(void* messageBuffer)
{
	for(;;)
	{
		lora_UpLinkHandler_task((MessageBufferHandle_t) messageBuffer);
	}
}

void lora_UpLinkHandler_create(UBaseType_t priority, UBaseType_t stack, MessageBufferHandle_t messageBuffer)
{
	_buffer = messageBuffer;
	
	xTaskCreate(
	lora_UpLinkHandler_startTask
	, (const portCHAR *) "LRUpHand" //replacement for this
	,stack + 200
	,(void*) messageBuffer
	, priority
	, NULL);
}

static void lora_setup(void)
{
	lora_driver_returnCode_t rc;
	status_leds_slowBlink(led_ST2); //OPTIONAL: Led green led blink slowly while setting up LORA
	
	//Factory reset the transceiver
	printf("FactoryReset >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_rn2483FactoryReset()));
	
	//Configure to EU868 LoRaWAN standards
	printf("Configure to EU868 >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_configureToEu868()));
	
	//Get the transceivers HW EUI
	rc = lora_driver_getRn2483Hweui();
	
	//
	
}