/*
 * DownLink.c
 *
 * Created: 12/8/2021 7:55:15 PM
 *  Author: tolde
 */ 

#include <ATMEGA_FreeRTOS.h>
#include <stddef.h>
#include <stdio.h>
#include "DownLink.h"
#include <stdlib.h>
#include <avr/eeprom.h>
#include <lora_driver.h>
#include <message_buffer.h>
#include <rc_servo.h>

static lora_driver_payload_t _downlink_Payload;

void lora_DownLinkHandler_StartTask(void* messageBuffer);

void lora_DownLinkHandler_StartTask(void* messageBuffer)
{
	for(;;)
	{
		lora_DownLinkHandler_Task((MessageBufferHandle_t)void* messageBuffer);
	}
}

void lora_DownLinkHandler_Create(UBaseType_t priority, UBaseType_t stack, MessageBufferHandle_t messageBuffer)
{
	xTaskCreate(
	lora_DownLinkHandler_StartTask
	, "LRDHDownHand"
	, stack
	, (void*)messageBuffer
	, priority
	, NULL);
}

void lora_DownLink_Task(MessageBufferHandle_t messageBuffer)
{
	printf("Down link Task Started \n");
	xMessageBufferReceive(messageBuffer, &_downlink_Payload, sizeof(lora_driver_payload_t), portMAX_DELAY);
	printf("DOWN LINK: from port: %d with %d bytes received! \n", _downlink_Payload.portNo, _downlink_Payload.len);
	
	if(_downlink_Payload.len = 2)
	{
		int i;
		
		for(i =0; i<1; i++)
		{
			if(i > 0) 
			printf(":");
			printf("%02X", _downlink_Payload.bytes[i]);
		}
		
		if((_downlink_Payload.bytes[0] << 8) + _downlink_Payload.bytes[1] == 0)
		{
			rc_servo_setPosition(0, -100); //fully open to the right
		}
		else
		{
			rc_servo_setPosition(0, 100); //open
		}
	}
}