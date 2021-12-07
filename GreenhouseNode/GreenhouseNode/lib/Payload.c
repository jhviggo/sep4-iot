/*
 * Payload.c
 *
 * Created: 07/12/2021 18.18.42
 *  Author: skrue
 */ 


int16_t temperature;
uint8_t humidity;
uint16_t co2_ppm;
bool window_open;	// last bit of byte[4]
uint32_t lux;		// only 3 first bytes

// https://ihavn.github.io/IoT_Semester_project/lora_send_uplink_message.html
void upLoad() {
	uplinkPayload.len = 7;		// Length of the actual payload
	uplinkPayload.port_no = 1;	// The LoRaWAN port no to sent the message to
	
	uplink_payload.bytes[0] = temperature >> 8;
	uplink_payload.bytes[1] = temperature & 0xFF;
	uplink_payload.bytes[2] = humidity;
	uplink_payload.bytes[3] = co2_ppm >> 8;
	uplink_payload.bytes[4] = co2_ppm & 0x7F;
	uplink_payload.bytes[4] = window_open >> 7;
	uplink_payload.bytes[5] = lux >> 16;
	uplink_payload.bytes[6] = lux >> 8;
	uplink_payload.bytes[7] = lux & 8;
}



int16_t temperatureHighThreshold;
int16_t temperatureLowThreshold;
uint8_t humidityHighThreshold;
uint8_t humidityLowThreshold;
bool window_open_act;
bool light_act;
bool water_act;

// https://ihavn.github.io/IoT_Semester_project/lora_receive_downlink_message.html
void downLoad() {
	int16_t temperatureHighThreshold = (downlinkPayload.bytes[0] << 8) + downlinkPayload.bytes[1];
	int16_t temperatureLowThreshold = (downlinkPayload.bytes[2] << 8) + downlinkPayload.bytes[3];
	uint8_t humidityHighThreshold = downlinkPayload.bytes[4];
	uint8_t humidityLowThreshold = downlinkPayload.bytes[5];
	
	int8_t window_open_percentage_act = downlinkPayload.bytes[6];	// window position
	bool window_open_act = (downlinkPayload.bytes[7] << 0);			// open/close window
	
	// (Examples for now)
	bool light_act = (downlinkPayload.bytes[7] << 1);				// on/off light
	bool water_act = (downlinkPayload.bytes[7] << 2);				// on/off water	
			
	// add more commands to this byte
	
}
