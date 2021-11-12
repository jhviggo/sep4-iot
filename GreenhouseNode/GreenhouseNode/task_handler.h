/*
 * task_handler.h
 *
 * Created: 12/11/2021 10.57.29
 *  Author: Michel Sofus Engelhardt Sommer, 273966
 */ 
#pragma 

#include "ATMEGA_FreeRTOS.h"
#include "stdio.h"
#include "stdint.h"

#include "lora_driver.h"

// Parameters for OTAA join - You have got these in a mail from IHA
/*
 *SEP4_GROUP1
 *Websocket Url: wss://iotnet.cibicom.dk/app?token=vnoUBQAAABFpb3RuZXQuY2liaWNvbS5ka4lPPjDJdv8czIiFOiS49tg=
 *Http to check on loriot network server: https://iotnet.teracom.dk/apps/websocket.html?token=vnoUBQAAABFpb3RuZXQuY2liaWNvbS5ka4lPPjDJdv8czIiFOiS49tg=
 *AppKey:5F83717BC67B4646E3F00DC5EC3417DC
 *AppEUI:2BBE8F09765BBF4B
 *EUI Dev#1:0004A30B00259D2C
 *EUI Dev#2:0004A30B00251192
 */
#define LORA_appEUI "2BBE8F09765BBF4B"
#define LORA_appKEY "5F83717BC67B4646E3F00DC5EC3417DC"

void lora_init();
void lora_start();
void lora_rx_data();