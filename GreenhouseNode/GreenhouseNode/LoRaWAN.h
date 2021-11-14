/*
 * LoRaWAN.h
 *
 * Created: 13/11/2021 12.10.30
 *  Author: Michel Sofus Engelhardt Sommer, 273966
 */ 

/*
 *SEP4_GROUP1
 *Websocket Url: wss://iotnet.cibicom.dk/app?token=vnoUBQAAABFpb3RuZXQuY2liaWNvbS5ka4lPPjDJdv8czIiFOiS49tg=
 *Http to check on loriot network server: https://iotnet.teracom.dk/apps/websocket.html?token=vnoUBQAAABFpb3RuZXQuY2liaWNvbS5ka4lPPjDJdv8czIiFOiS49tg=
 *AppKey:5F83717BC67B4646E3F00DC5EC3417DC
 *AppEUI:2BBE8F09765BBF4B
 *EUI Dev#1:0004A30B00259D2C
 *EUI Dev#2:0004A30B00251192
 */

#ifndef LORAWAN_H_
#define LORAWAN_H_

#include "ATMEGA_FreeRTOS.h"

#include <stdio.h>
#include <stdint.h>

// Parameters for OTAA join (Over The Air Activation)
#define LORA_devEUI "0004A30B00259D2C"		//Dev#1			<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Set right LoRa device
// #define LORA_devEUI "0004A30B00251192"	//Dev#2			<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	Set right LoRa device
#define LORA_appEUI "2BBE8F09765BBF4B"
#define LORA_appKEY "5F83717BC67B4646E3F00DC5EC3417DC"

void LoRaWAN_init();		// init driver
void LoRaWAN_connect();		// init connection
void LoRaWAN_send(/* int8_t packetType */);		// TX

void LoRaWAN_downlink();	// RX

#endif /* LORAWAN_H_ */