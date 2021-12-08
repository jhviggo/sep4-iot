/*
 * DownLink.c
 *
 * Created: 12/7/2021 4:46:55 PM
 *  Author: tolde
 */ 
#include <rc_servo.h>
#include <ATMEGA_FreeRTOS.h>
#include <stddef.h>
#include <stdio.h>
#include "DownLink.h"
#include <stdlib.h>
#include <avr/eeprom.h>
#include <lora_driver.h>
#include <message_buffer.h>

static lora_driver_payload_t downLink_payLoad;

void lora_DownLinkHandler_StartTask(void* messageBuffer);

void lora_DownLinkHandler_StartTask(void* messageBuffer)
{
	for(;;)
	{
		lora_DownLinkHandler_Task((MessageBufferHandle_t)messageBuffer);
	}
}

void lora_DownLinkHandler_Create(UBaseType_t priority, UBaseType_t stack, MessageBufferHandle_t messageBuffer)
{
	xTaskCreate(
	,"LRDHDownHand"
	,stack
	,(void*)messageBuffer
	,priority
	,NULL
	);
}

void lora_DownLinkHandler_Task(MessageBufferHandle_t messageBuffer)
{
	printf("DownLink task started.\n");
	xMessageBufferReceive(messageBuffer, &downLink_payLoad, sizeof(lora_driver_payload_t), portMAX_DELAY);
	printf("DownLink: from port: %d with %d bytes received \n", downLink_payLoad.portNo, downLink_payLoad.len);
	
	if(downLink_payLoad.len = 2)
	{
		int i;
		for(i = 0; i < 1; i++)
		{
			if(i > 0)
			printf(":");
			printf("%02X", downLink_payLoad.bytes[i]);
		}
		
		if((downLink_payLoad.bytes[0] << 8) + downLink_payLoad.bytes[1] ==0)
		{
			rc_servo_setPosition(0, -100);
		}
		else
		{
			rc_servo_setPosition(0, 100);
		}
	}
}