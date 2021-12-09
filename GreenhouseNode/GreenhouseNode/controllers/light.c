/*
 * light.c
 *
 * Created: 08/12/2021 12.47.49
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 */


#include "light.h"
#include <tsl2591.h>


// https://ihavn.github.io/IoT_Semester_project/tsl2591_driver_quick_start.html
// https://ihavn.github.io/IoT_Semester_project/group__tsl2591__driver.html

	lightSensor_t light_sensor_init()
	{
		lightSensor_t new_sensor = calloc(1, sizeof(lightSensor));
		
		tsl2591_returnCode_t returnCode = callback(tsl2591_initialise());
		
		if (new_sensor == NULL) return NULL;
		new_sensor->lux = 0;
		new_sensor->averageLight = 0;
		new_sensor->lightMeasurementCount = 0;
		
		return new_sensor;

	}


	uint32_t light_measure(lightSensor_t self)
	{
		tsl2591_returnCode_t returnCode;
		returnCode = callback(tsl2591_enable());
		
		
		returnCode = callback(tsl2591_initialise());
		
		
		returnCode = callback(tsl2591_disable());
		
		
		
		// return (uint32_t) tsl2591_getLux(float *lux);
	}


	void light_destroy( lightSensor_t self )
	{
	
		tsl2591_returnCode_t returnCode = tsl2591_destroy();
		
		if( returnCode == TSL2591_DRIVER_NOT_INITIALISED ) // Everything went well
		{
			free(self);
			printf("\nTSL25911_LIGHT_SENSOR: destroyed successfully");
		}
		else // Something went wrong
		{
			printf("\nTSL25911_LIGHT_SENSOR_ERROR: %d\n", returnCode);
		}
	
	}

	protected void callback( tsl2591_returnCode_t returnCode )
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
				increaseTime();
				printf("\nTSL25911_LIGHT_SENSOR: Visible overflow - decrease gain and integration time\n");
			}
			else if( returnCode == TSL2591_UNDERFLOW )
			{
				decreaseGain();
				increaseTime();
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
				decreaseTime();
				printf("\nTSL25911_LIGHT_SENSOR: Infrared overflow - decrease gain and integration time\n");
			}
			else if( returnCode == TSL2591_UNDERFLOW )
			{
				decreaseGain();
				decreaseTime();
				printf("\nTSL25911_LIGHT_SENSOR: Infrared underflow - increase gain and integration time\n");
			}

		}
		else if( returnCode == TSL2591_OK ) // Everything went well
		{
			printf("\nTSL25911_LIGHT_SENSOR: Last command performed successful\n");
		} 
		else if( returnCode == TSL2591_DEV_ID_READY ) // Device ID is ready from the last call to \ref tsl2591_fetchDeviceId
		{
			printf("\nTSL25911_LIGHT_SENSOR_ERROR: Dev ID now fetched\n");
		}
		else // Something went wrong
		{
			printf("\nTSL25911_LIGHT_SENSOR_ERROR: %d\n", returnCode);
		}
	
	}

	protected void increaseGain()
	{
		tsl2591_gain_t gain = tsl2591_getGain(void);
		tsl2591_integrationTime_t time = tsl2591_getIntegrationTime(void);
		
		if( gain == TSL2591_GAIN_LOW )
		{
			gain = TSL2591_GAIN_MED;
		}
		else if( gain == TSL2591_GAIN_MED )
		{
			gain = TSL2591_GAIN_HIGH;
		}
		else if( gain == TSL2591_GAIN_HIGH )
		{
			gain = TSL2591_GAIN_MAX;
		}
				
		setGainAndIntegrationTime(gain, time);
		
	}
	
	protected void decreaseGain()
	{
		tsl2591_gain_t gain = tsl2591_getGain(void);
		tsl2591_integrationTime_t time = tsl2591_getIntegrationTime(void);
				
		if( gain == TSL2591_GAIN_MED )
		{
			gain = TSL2591_GAIN_LOW;
		}
		else if( gain == TSL2591_GAIN_HIGH )
		{
			gain = TSL2591_GAIN_MED;
		}
		else if( gain == TSL2591_GAIN_MAX )
		{
			gain = TSL2591_GAIN_HIGH;
		}
	
		setGainAndIntegrationTime(gain, time);
		
	}
		
	protected void increaseTime()
	{
		tsl2591_gain_t gain = tsl2591_getGain(void);
		tsl2591_integrationTime_t time = tsl2591_getIntegrationTime(void);

		if( time == TSL2591_INTEGRATION_TIME_100MS )
		{
			time = TSL2591_INTEGRATION_TIME_200MS;
		}
		else if( time == TSL2591_INTEGRATION_TIME_200MS )
		{
			time = TSL2591_INTEGRATION_TIME_300MS;
		}
		else if( time == TSL2591_INTEGRATION_TIME_300MS )
		{
			time = TSL2591_INTEGRATION_TIME_400MS;
		}
		else if( time == TSL2591_INTEGRATION_TIME_400MS )
		{
			time = TSL2591_INTEGRATION_TIME_500MS;
		}
		else if( time == TSL2591_INTEGRATION_TIME_500MS )
		{
			time = TSL2591_INTEGRATION_TIME_600MS;
		}
		
		setGainAndIntegrationTime(gain, time);
		
	}
		
	protected void decreaseTime()
	{
		tsl2591_gain_t gain = tsl2591_getGain(void);
		tsl2591_integrationTime_t time = tsl2591_getIntegrationTime(void);
		
		if( time == TSL2591_INTEGRATION_TIME_200MS )
		{
			time = TSL2591_INTEGRATION_TIME_100MS;
		}
		else if( time == TSL2591_INTEGRATION_TIME_300MS )
		{
			time = TSL2591_INTEGRATION_TIME_200MS;
		}
		else if( time == TSL2591_INTEGRATION_TIME_400MS )
		{
			time = TSL2591_INTEGRATION_TIME_300MS;
		}
		else if( time == TSL2591_INTEGRATION_TIME_500MS )
		{
			time = TSL2591_INTEGRATION_TIME_400MS;
		}
		else if( time == TSL2591_INTEGRATION_TIME_600MS )
		{
			time = TSL2591_INTEGRATION_TIME_500MS;
		}
		
		setGainAndIntegrationTime(gain, time);
		
	}
		
	protected void setGainAndIntegrationTime( tsl2591_gain_t gain, tsl2591_integrationTime_t integrationTime )
	{
		callback( tsl2591_setGainAndIntegrationTime( gain, integrationTime ) );
	}
	
}
