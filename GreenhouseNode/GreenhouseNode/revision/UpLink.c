/*
 * UpLink.c
 *
 * Created: 12/7/2021 4:47:18 PM
 *  Author: tolde
 */ 
#include <stddef.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#include <lora_driver.h>
#include <status_leds.h>


#define LORA_appEUI "2BBE8F09765BBF4B"
#define LORA_appKey "5F83717BC67B4646E3F00DC5EC3417DC"

static char out_buffer[100];

 void lora_handler_task(void* _parameters);
 
 static lora_driver_payload_t upLink_payload;
 
//Humidity, temp...
 
 void lora_handler_initialise(UBaseType_t lora_handler_task_priority, //humid, temp...)
 {
	//humidity, temp...
	 
	 printf("SETTING UP LORA");
	 xTaskCreate(
	 lora_handler_task
	 ,"LRHand"
	 ,configMINIMAL_STACK_SIZE + 200
	 ,NULL
	 ,lora_handler_task_priority
	 ,NULL);
 }
 
 static void _lora_setup(void)
 {
	 lora_driver_returnCode_t rc;
	 status_leds_slowBlink(led_ST2);
	 
	 // Factory reset the transceiver
	 printf("FactoryReset >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_rn2483FactoryReset()));

	 // Configure to EU868 LoRaWAN standards
	 printf("Configure to EU868 >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_configureToEu868()));

	 // Get the transceivers HW EUI
	 rc = lora_driver_getRn2483Hweui(out_buffer);
	 printf("Get HWEUI >%s<: %s\n", lora_driver_mapReturnCodeToText(rc), out_buffer);

	 // Set the HWEUI as DevEUI in the LoRaWAN software stack in the transceiver
	 printf("Set DevEUI: %s >%s<\n", out_buffer, lora_driver_mapReturnCodeToText(lora_driver_setDeviceIdentifier(out_buffer)));

	 // Set Over The Air Activation parameters to be ready to join the LoRaWAN
	 printf("Set OTAA Identity appEUI:%s appKEY:%s devEUI:%s >%s<\n", LORA_appEUI, LORA_appKey, out_buffer, lora_driver_mapReturnCodeToText(lora_driver_setOtaaIdentity(LORA_appEUI, LORA_appKEY, _out_buf)));

	 // Save all the MAC settings in the transceiver
	 printf("Save mac >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_saveMac()));

	 // Enable Adaptive Data Rate
	 printf("Set Adaptive Data Rate: ON >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_setAdaptiveDataRate(LORA_ON)));

	 // Set receiver window1 delay to 500 ms - this is needed if down-link messages will be used
	 printf("Set Receiver Delay: %d ms >%s<\n", 500, lora_driver_mapReturnCodeToText(lora_driver_setReceiveDelay(500)));

	 // Join the LoRaWAN
	 uint8_t maxJoinTriesLeft = 10;
	 
	 do
 {
	 rc = lora_driver_join(LORA_OTAA);
	 printf("Join Network TriesLeft: %d >%s<\n", maxJoinTriesLeft, lora_driver_mapReturnCodeToText(rc));
	 
	 if(rc != LORA_ACCEPTED)
	 {
	    	// Make the red led pulse to tell something went wrong
	    	status_leds_longPuls(led_ST1); // OPTIONAL
	    	// Wait 5 sec and lets try again
	    	vTaskDelay(pdMS_TO_TICKS(5000UL));
     }
	 else
	 {
		 break;
	 }
  } while(--maxJoinTriesLeft);
  
  if(rc == LORA_ACCEPTED)
  {
	  //Connected to LORA
	  //Green led - steady
	  status_leds_ledOn(led_ST2); //this is optional
  }
  else
  {
	  // Something went wrong
	  // Turn off the green led
	  status_leds_ledOff(led_ST2); // OPTIONAL
	  // Make the red led blink fast to tell something went wrong
	  status_leds_fastBlink(led_ST1); // OPTIONAL

	  // Lets stay here
	  while (1)
	  {
		  taskYIELD();
	  }
  }
 }
 
 void lora_handler_task(void* _parameters)
 {

	 lora_driver_resetRn2483(1);
	 vTaskDelay(2);
	 lora_driver_resetRn2483(0);

	 vTaskDelay(150);

	 lora_driver_flushBuffers();

	 _lora_setup();

	 _uplink_payload.len = 8;
	 _uplink_payload.portNo = 2;

	 TickType_t xLastWakeTime;

	 const TickType_t xFrequency = pdMS_TO_TICKS(300000UL);
	 xLastWakeTime = xTaskGetTickCount();

	 for (;;)
	 {
		 xTaskDelayUntil(&xLastWakeTime, xFrequency);
		 printf("Sending data to LORA \n");

		//temp, humidity...

		 _uplink_payload.bytes[0] = hum >> 8;
		 _uplink_payload.bytes[1] = hum & 0xFF;

		 _uplink_payload.bytes[2] = temp >> 8;
		 _uplink_payload.bytes[3] = temp & 0xFF;

		 _uplink_payload.bytes[4] = co2 >> 8;
		 _uplink_payload.bytes[5] = co2 & 0xFF;

		 _uplink_payload.bytes[6] = ltrdr >> 8;
		 _uplink_payload.bytes[7] = ltrdr & 0xFF;

		 //For debugging purposes
		 for (int i = 0; i < 7; i++)
		 {
			 if (i > 0) printf(":");
			 printf("%02X", _uplink_payload.bytes[i]);
		 }

		 status_leds_shortPuls(led_ST4);

		 printf("Upload Message >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_sendUploadMessage(false, &_uplink_payload)));
		 
	 }
 