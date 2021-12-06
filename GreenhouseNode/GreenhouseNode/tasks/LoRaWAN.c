/*
 * LoRaWAN.c
 *
 * Created: 13/11/2021 12.10.59
 *  Author: Michel Sofus Engelhardt Sommer, 273966
 */ 

#include "LoRaWAN.h"

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <message_buffer.h>
#include <lora_driver_utils.h>
#include <lora_driver.h>


// Down link messages in the message buffer
MessageBufferHandle_t downLinkMessageBufferHandle;

// Define a payload struct variable (in lora_driver.h)
lora_driver_payload_t uplinkPayload ,downlinkPayload;
	
void LoRaWAN_init()
{
	// The parameter is the USART port the RN2483 module is connected to
	lora_driver_initialise(ser_USART1, downLinkMessageBufferHandle);
}

// Create dummy packet
void LoRaWAN_hum_temp_packet() 
{
	downLinkMessageBufferHandle = xMessageBufferCreate(sizeof(lora_driver_payload_t));

	//SETUP the packet/message, change for each message type
	uplinkPayload.portNo = 1; // The LoRaWAN port no to sent the message to
	uplinkPayload.len = 4;		// Length of the actual payload
	
	// Dummy values (We gets values as float)
	//float humidity = 25.456;
	//float temperature = 13.95;
	int16_t hum_payload = 242;
	int16_t temp_payload = 153;
	
	uplinkPayload.bytes[0] = hum_payload >> 8;
	uplinkPayload.bytes[1] = hum_payload & 0xFF;
	uplinkPayload.bytes[2] = temp_payload >> 8;
	uplinkPayload.bytes[3] = temp_payload & 0xFF;
}

// Connect
void LoRaWAN_connect()
{
		// lora_driver_returnCode_t returnCode;
		
		lora_driver_resetRn2483(1); // Activate reset line
		vTaskDelay(2);
		lora_driver_resetRn2483(0); // Release reset line
		vTaskDelay(150);			// Wait for transceiver module to wake up after reset

		if (lora_driver_rn2483FactoryReset() != LORA_OK)
		{
			lora_driver_rn2483FactoryReset();
			printf("RN2483 Factory Reset");
		}
		
		lora_driver_flushBuffers();	// Flush the internal buffers in the driver.
		
		if (lora_driver_configureToEu868() != LORA_OK)
		{
			lora_driver_configureToEu868();
			printf("freq. set to 867MHz");
		}

		if (lora_driver_getRn2483Hweui(LORA_devEUI) != LORA_OK)
		{
			lora_driver_getRn2483Hweui(LORA_devEUI);
			printf("Retrieving device ID");
		}

		if (lora_driver_setOtaaIdentity(LORA_appEUI,LORA_appKEY,LORA_devEUI) != LORA_OK)
		{
			lora_driver_setOtaaIdentity(LORA_appEUI,LORA_appKEY,LORA_devEUI);
			printf("Access Credentials is set: appEUI, appKEY, devEUI");
		}
		
		if (lora_driver_join(LORA_OTAA) == LORA_ACCEPTED)
		{
			lora_driver_join(LORA_OTAA);
			printf("Something went right :-) network access granted");
		}
}

// TX
void LoRaWAN_uplink() {
		lora_driver_returnCode_t returnCode;

		if ((returnCode = lora_driver_sendUploadMessage(false, &uplinkPayload)) == LORA_MAC_TX_OK )
		{
			printf("The up link message is sent and there is no down link message received");
		}
		else if (returnCode == LORA_MAC_RX)
		{
			lora_driver_setAdaptiveDataRate(LORA_ON);	// update tx signal strength according lo last received packet
			printf("The up link message is sent and a down link message is received");
			printf("Down Link, returnCode: %d", returnCode);
		}
}

// RX
void LoRaWAN_downlink()
{
	downlinkPayload.len = 4;	// Length of the actual payload
	
	uint16_t maxHumSetting; // Max Humidity
	int16_t maxTempSetting; // Max Temperature

	// this code must be in the loop of a FreeRTOS task!
	xMessageBufferReceive(downLinkMessageBufferHandle, &downlinkPayload, sizeof(lora_driver_payload_t), portMAX_DELAY);
	printf("DOWN LINK: from port: %d with %d bytes received!", downlinkPayload.portNo, downlinkPayload.len); // Just for Debug
	if (4 == downlinkPayload.len) // Check that we have got the expected 4 bytes
	{
		// decode the payload into our variables
		maxHumSetting = (downlinkPayload.bytes[0] << 8) + downlinkPayload.bytes[1];
		maxTempSetting = (downlinkPayload.bytes[2] << 8) + downlinkPayload.bytes[3];
	}
}

// Transmit
void LoRaWAN_send(/* int8_t packetType */)
{
	LoRaWAN_hum_temp_packet();	// later select packet type
	LoRaWAN_uplink();
	// lora_driver_sleep(300000); // sleep time = 300000ms = 5 minuets, only for hardware
}