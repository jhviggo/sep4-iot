#pragma once

#include <stdio.h>
#include <stdio_driver.h>
#include <serial.h>
#include <lora_driver.h>
#include <status_leds.h>

#define LORA_appEUI "2BBE8F09765BBF4B"
#define LORA_appKEY "5F83717BC67B4646E3F00DC5EC3417DC"
#define LORA_TIMEOUT_5MIN 300000UL
#define LORA_MAX_CONNECTION_RETRIES 10
#define LORA_MAX_BUFFER_SIZE 20

void loraWAN_init(void);
void loraWAN_connect_task(void* pvParameters);
void loraWAN_send_task(void *pvParameter);
void loraWAN_recieve_task(void* pvParameters);
void loraWAN_setPayload(uint8_t port, uint8_t lendth, uint8_t data[LORA_MAX_BUFFER_SIZE]);
