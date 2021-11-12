/*
 * LoRaWAN_handler.h
 *
 * Created: 12/11/2021 10.55.09
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

#pragma 
#include "ATMEGA_FreeRTOS.h"

#include <stdio.h>
#include <stdint.h>

#include <lora_driver.h>
#include <ihal.h>

// Parameters for OTAA join
#define LORA_appEUI "2BBE8F09765BBF4B"
#define LORA_appKEY "5F83717BC67B4646E3F00DC5EC3417DC"

#define LORA_INIT_TASK_PRIORITY 7

void lora_init();
void lora_start();
void lora_send_data();