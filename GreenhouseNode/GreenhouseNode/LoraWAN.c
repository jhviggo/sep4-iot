#include "LoraWAN.h"

MessageBufferHandle_t downLinkMessageBufferHandle;
static lora_driver_payload_t _uplink_payload;

void loraWAN_init(void) {
	// Set output ports for LED
	DDRA |= _BV(DDA0) | _BV(DDA7);
	
	// Create down link buffer
	downLinkMessageBufferHandle = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2);
	
	// Configure serial at baumerate 57600,8,N,1
	stdio_initialise(ser_USART0);
	status_leds_initialise(5);
	lora_driver_initialise(1, downLinkMessageBufferHandle);
}

void _loraWAN_connect(void) {
	// led_ST1 = RED LED
	// led_ST2 = GREEN LED
	char _out_buf[LORA_MAX_BUFFER_SIZE];
	lora_driver_returnCode_t rc;
	
	status_leds_slowBlink(led_ST2);
	printf("FactoryReset >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_rn2483FactoryReset()));
	printf("Configure to EU868 >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_configureToEu868()));
	rc = lora_driver_getRn2483Hweui(_out_buf);
	printf("Get HWEUI >%s<: %s\n",lora_driver_mapReturnCodeToText(rc), _out_buf);
	printf("Set DevEUI: %s >%s<\n", _out_buf, lora_driver_mapReturnCodeToText(lora_driver_setDeviceIdentifier(_out_buf)));
	printf("Set OTAA Identity appEUI:%s appKEY:%s devEUI:%s >%s<\n", LORA_appEUI, LORA_appKEY, _out_buf, lora_driver_mapReturnCodeToText(lora_driver_setOtaaIdentity(LORA_appEUI,LORA_appKEY,_out_buf)));
	printf("Save mac >%s<\n",lora_driver_mapReturnCodeToText(lora_driver_saveMac()));
	printf("Set Adaptive Data Rate: ON >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_setAdaptiveDataRate(LORA_ON)));
	printf("Set Receiver Delay: %d ms >%s<\n", 500, lora_driver_mapReturnCodeToText(lora_driver_setReceiveDelay(500)));
	uint8_t maxJoinTriesLeft = LORA_MAX_CONNECTION_RETRIES;
	
	do {
		rc = lora_driver_join(LORA_OTAA);
		printf("Join Network >%s< Attempts left: %d\n", lora_driver_mapReturnCodeToText(rc), maxJoinTriesLeft);

		if ( rc != LORA_ACCEPTED) {
			status_leds_longPuls(led_ST1);
			// Retry in 5 sec
			vTaskDelay(pdMS_TO_TICKS(5000UL));
		}
		else {
			break;
		}
	} while (--maxJoinTriesLeft);

	if (rc == LORA_ACCEPTED) {
		status_leds_ledOn(led_ST2);
	}
	else {
		status_leds_ledOff(led_ST2);
		status_leds_fastBlink(led_ST1);

		// ERRORED OUT!
		while (1) { taskYIELD(); }
	}
}

void _resetLoRaWANTransceiver() {
	lora_driver_resetRn2483(1);
	vTaskDelay(2);
	lora_driver_resetRn2483(0);
	vTaskDelay(150);
	lora_driver_flushBuffers();
}

void loraWAN_send_task(void* pvParameters) {
	// Hardware reset of LoRaWAN transceiver
	_resetLoRaWANTransceiver();
	// Establish connection to LoRaWAN network
	_loraWAN_connect();

	// Setup timeout
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(LORA_TIMEOUT_5MIN);
	xLastWakeTime = xTaskGetTickCount();
	printf("Sending: %d, %d", _uplink_payload.portNo, _uplink_payload.len);
	
	while(1) {
		// Blink LED to show message transmission
		status_leds_shortPuls(led_ST4);
		printf("Upload Message >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_sendUploadMessage(false, &_uplink_payload)));
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}

void loraWAN_downLink() {
	printf("MISSING IMPLEMENTATION! <loraWAN_downLink>");
}

void loraWAN_setPayload(uint8_t port, uint8_t len, uint8_t data[LORA_MAX_BUFFER_SIZE]) {
	_uplink_payload.portNo = port;
	_uplink_payload.len = len;
	memcpy(_uplink_payload.bytes, data, len);
}