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


// https://ihavn.github.io/IoT_Semester_project/tsl2591_driver_quick_start.html
// https://ihavn.github.io/IoT_Semester_project/group__tsl2591__driver.html

lightSensor_t light_sensor_init()
{
		lightSensor_t new_sensor = calloc(1, sizeof(lightSensor));
		
		tsl2591_returnCode_t returnCode;
	
	       uint16_t _tmp;
	       float _lux;
		   
		   // TODO
		   



}


void light_injectCallBack(uint16_t light_lux)
{
	
}


uint32_t light_measure(lightSensor_t self)
{
	// return (uint32_t) tsl2591_getLux(float *lux);
}


void reset_averageLight(lightSensor_t self)
{
	
	
}


void light_destroy(lightSensor_t self)
{
	
	
}


//TODO method for changing gain
protected void tsl2591Callback(tsl2591_returnCode_t returnCode)
{
	uint16_t _tmp;
	float _lux;
	
	if(returnCode == TSL2591_DATA_READY) // Data is ready from the last call to \ref tsl2591_fetchData
	{
		// Retrieve the latest full light spectrum as raw data fetched from the TSL2591 sensor.
		if ( returnCode == tsl2591_getFullSpectrumRaw(&_tmp) )
		{
			printf("\nTSL25911_LIGHT_SENSOR: Full Raw:%04X\n", _tmp);
		}
		else if( TSL2591_OVERFLOW == returnCode )
		{
			increaseGain();
			printf("\nTSL25911_LIGHT_SENSOR: Full spectrum overflow - change gain and integration time\n");
		}
		else if( returnCode == TSL2591_UNDERFLOW )
		{
			decreaseGain();
			printf("\nTSL25911_LIGHT_SENSOR: Full spectrum overflow - increase gain and integration time\n");
		}
					  
		// Retrieve the latest visible light spectrum as raw data fetched from the TSL2591 sensor.	  
        if ( returnCode == tsl259_getVisibleRaw(&_tmp) )
        {
			printf("\nTSL25911_LIGHT_SENSOR: Visible Raw:%04X\n", _tmp);
        }
        else if( TSL2591_OVERFLOW == returnCode )
        {
			increaseGain();
	        printf("\nTSL25911_LIGHT_SENSOR: Visible overflow - decrease gain and integration time\n");
        }
		else if( returnCode == TSL2591_UNDERFLOW )
		{
			decreaseGain();
			printf("\nTSL25911_LIGHT_SENSOR: Visible underflow - increase gain and integration time\n");
		}
						
		// Retrieve the latest infrared light spectrum as raw data fetched from the TSL2591 sensor.
		if ( returnCode == tsl2591_getInfraredRaw(&_tmp) )
		{
			printf("\nTSL25911_LIGHT_SENSOR: Infrared Raw:%04X\n", _tmp);
		}
		else if( returnCode == TSL2591_OVERFLOW )
		{
			increaseGain();
			printf("\nTSL25911_LIGHT_SENSOR: Infrared overflow - decrease gain and integration time\n");
		}
		else if( returnCode == TSL2591_UNDERFLOW )
		{
			decreaseGain();
			printf("\nTSL25911_LIGHT_SENSOR: Infrared underflow - increase gain and integration time\n");
		}

	}
	else if(returnCode == TSL2591_OK) // Everything went well
	{
		printf("\nTSL25911_LIGHT_SENSOR: Last command performed successful\n");
	} 
	else if(returnCode == TSL2591_DEV_ID_READY) // Device ID is ready from the last call to \ref tsl2591_fetchDeviceId
	{
		printf("\nTSL25911_LIGHT_SENSOR_ERROR: Dev ID now fetched\n");
	}
	else // // Something went wrong
	{
		printf("\nTSL25911_LIGHT_SENSOR_ERROR: %d\n", returnCode);
	}
	
	
	protected void increaseGain()
	{
		// tsl2591_gain_t tsl2591_getGain(void);
		// tsl2591_integrationTime_t tsl2591_getIntegrationTime(void);
		// tsl2591_returnCode_t tsl2591_setGainAndIntegrationTime(tsl2591_gain_t gain, tsl2591_integrationTime_t integrationTime);
		
	}
	
	
	protected void decreaseGain()
	{
		// tsl2591_gain_t tsl2591_getGain(void);
		// tsl2591_integrationTime_t tsl2591_getIntegrationTime(void);
		// tsl2591_returnCode_t tsl2591_setGainAndIntegrationTime(tsl2591_gain_t gain, tsl2591_integrationTime_t integrationTime);
		
	}
	
}
