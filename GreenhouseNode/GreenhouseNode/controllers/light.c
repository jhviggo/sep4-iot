/*
 * light.c
 *
 * Created: 08/12/2021 12.47.49
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 */

/*
	Indoor and outdoor light conditions:
	| LUX				| Condition
	| 0.002				| Moonless clear night sky
	| 0.2				| Design minimum for emergency lighting (AS2293)
	| 0.27				| Full moon on a clear night
	| 3.4				| Dark limit of civil twilight under a clear sky
	| 50				| Family living room
	| 80				| Hallway/toilet
	| 100				| Very dark overcast day
	| 300 - 500			| Sunrise or sunset on a clear day. Well-lit office area
	| 1,000				| Overcast day; typical TV studio lighting
	| 10,000 - 25,000	| Full daylight (not direct sun)
	| 32,000 - 130,000	| Direct sunlight

	The Data-sheet for TSL2591 can be found here https://ams.com/documents/20143/36005/TSL2591_DS000338_6-00.pdf/090eb50d-bb18-5b45-4938-9b3672f86b80
*/

#include "light.h"
#include <tsl2591.h>

lightSensor_t light_sensor_init()
{
	
	
}


void light_injectCallBack(uint16_t light_lux)
{
	
}


uint32_t light_measure(lightSensor_t self)
{
	
}


void reset_averageLight(lightSensor_t self)
{
	
	
}


void light_destroy(lightSensor_t self)
{
	
	
}