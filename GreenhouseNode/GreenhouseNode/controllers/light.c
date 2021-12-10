/*
 * light.c
 *
 * Created: 08/12/2021 12.47.49
 * Author : Michel Sofus Engelhardt Sommer, 273966
 *
 */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <tsl2591.h>
#include "light.h"


// https://ihavn.github.io/IoT_Semester_project/tsl2591_driver_quick_start.html
// https://ihavn.github.io/IoT_Semester_project/group__tsl2591__driver.html

	lightSensor_t light_sensor_init()
	{
		lightSensor_t new_sensor = calloc(1, sizeof(lightSensor));
		
		tsl2591_returnCode_t returnCode = 
		returnCode = tsl2591_initialise(callback(NULL, new_sensor));
		
		if ( returnCode == TSL2591_OK )
		{
			printf("Return code for light sensor is: %s", returnCode);
		}

		if (TSL2591_OK == tsl2591_enable())
		{
			if (new_sensor == NULL) return NULL;
			new_sensor = callback( returnCode, new_sensor);
			
			// new_sensor->lux = 0;
			// new_sensor->visibleRaw = 0;
			// new_sensor->infraredRaw = 0;
			// new_sensor->fullSpectrum = 0;
			
		}
		else
		{
			free(new_sensor);
		}
		
		return new_sensor;

	}


	lightSensor_t light_measure(lightSensor_t self)
	{
		tsl2591_returnCode_t returnCode;
		returnCode = callback(tsl2591_enable());		return self

		
		
		returnCode = tsl2591_disable();
		
		
		
		return self;
		
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

	static lightSensor_t callback( tsl2591_returnCode_t returnCode, lightSensor_t self )
	{
		uint16_t _tmp;
		float _lux;
	
		if(returnCode == TSL2591_DATA_READY) // Data is ready from the last call to \ref tsl2591_fetchData
		{

			// fetch values from sensor
			self = getLux(self);
			self = getVisible(self);
			self = getInfrared(self);
			self = getFullSpectrum(self);

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
	
		return self;
	
	}

		
	static void setGainAndIntegrationTime( tsl2591_gain_t gain, tsl2591_integrationTime_t integrationTime )
	{
		tsl2591_setGainAndIntegrationTime( gain, integrationTime );
	}
		
	static void increaseGain()
	{
		tsl2591_gain_t gain = tsl2591_getGain();
		tsl2591_integrationTime_t time = tsl2591_getIntegrationTime();
		
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
	
	static void decreaseGain()
	{
		tsl2591_gain_t gain = tsl2591_getGain();
		tsl2591_integrationTime_t time = tsl2591_getIntegrationTime();
				
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
		
	static void increaseTime()
	{
		tsl2591_gain_t gain = tsl2591_getGain();
		tsl2591_integrationTime_t time = tsl2591_getIntegrationTime();

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
		
	static void decreaseTime()
	{
		tsl2591_gain_t gain = tsl2591_getGain();
		tsl2591_integrationTime_t time = tsl2591_getIntegrationTime();
		
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
	
	static lightSensor_t getLux(lightSensor_t self)
	{
		tsl2591_returnCode_t returnCode;
		uint16_t _tmp;
		float _lux;
		
		// Retrieve the illumination level from the TSL2591 sensor in lux.
		if ( returnCode == tsl2591_getLux(&_lux) )
		{
			self->lux = (uint32_t) _lux;
			printf("\nTSL25911_LIGHT_SENSOR: LUX: %.3f\n", _lux);
		}
		else if( TSL2591_OVERFLOW == returnCode )
		{
			decreaseGain();
			decreaseTime();
			printf("\nTSL25911_LIGHT_SENSOR: Visible overflow - decrease gain and integration time\n");
			getLux(self);
		}
		else if( returnCode == TSL2591_UNDERFLOW )
		{
			increaseGain();
			increaseTime();
			printf("\nTSL25911_LIGHT_SENSOR: Visible underflow - increase gain and integration time\n");
			getLux(self);
		}
		else // Something went wrong
		{
			printf("\nTSL25911_LIGHT_SENSOR_ERROR: %d\n", returnCode);
		}
			
		return self;
			
	}

	static lightSensor_t getVisible(lightSensor_t self)
	{
		tsl2591_returnCode_t returnCode;
		uint16_t _tmp;
		
		// Retrieve the latest visible light spectrum as raw data fetched from the TSL2591 sensor.
		if ( returnCode == tsl259_getVisibleRaw(&_tmp) )
		{
			self->visibleRaw = _tmp;
			printf("\nTSL25911_LIGHT_SENSOR: Visible Raw:%04X\n", _tmp);
		}
		else if( TSL2591_OVERFLOW == returnCode )
		{
			decreaseGain();
			decreaseTime();
			printf("\nTSL25911_LIGHT_SENSOR: Visible overflow - decrease gain and integration time\n");
			getVisible(self);
		}
		else if( returnCode == TSL2591_UNDERFLOW )
		{
			increaseGain();
			increaseTime();
			printf("\nTSL25911_LIGHT_SENSOR: Visible underflow - increase gain and integration time\n");
			getVisible(self);
		}
		else // Something went wrong
		{
			printf("\nTSL25911_LIGHT_SENSOR_ERROR: %d\n", returnCode);
		}
		
		return self;
			
	}
	
	static lightSensor_t getInfrared(lightSensor_t self)
	{
		tsl2591_returnCode_t returnCode;
		uint16_t _tmp;
					
		// Retrieve the latest infrared light spectrum as raw data fetched from the TSL2591 sensor.
		if ( returnCode == tsl2591_getInfraredRaw(&_tmp) )
		{
			self->infraredRaw = _tmp;
			printf("\nTSL25911_LIGHT_SENSOR: Infrared Raw:%04X\n", _tmp);
		}
		else if( returnCode == TSL2591_OVERFLOW )
		{
			decreaseGain();
			decreaseTime();
			printf("\nTSL25911_LIGHT_SENSOR: Infrared overflow - decrease gain and integration time\n");
			getInfrared(self);
		}
		else if( returnCode == TSL2591_UNDERFLOW )
		{
			increaseGain();
			increaseTime();
			printf("\nTSL25911_LIGHT_SENSOR: Infrared underflow - increase gain and integration time\n");
			getInfrared(self);
		}	
		else // Something went wrong
		{
			printf("\nTSL25911_LIGHT_SENSOR_ERROR: %d\n", returnCode);
		}
		
		return self;
			
	}
		
	static lightSensor_t getFullSpectrum(lightSensor_t self)
	{
		tsl2591_returnCode_t returnCode;
		uint16_t _tmp;	
		
		// Retrieve the latest full light spectrum as raw data fetched from the TSL2591 sensor.
		if ( returnCode == tsl2591_getFullSpectrumRaw(&_tmp) )
		{
			self->fullSpectrum = _tmp;
			printf("\nTSL25911_LIGHT_SENSOR: Full Raw:%04X\n", _tmp);
		}
		else if( TSL2591_OVERFLOW == returnCode )
		{
			decreaseGain();
			decreaseTime();
			printf("\nTSL25911_LIGHT_SENSOR: Full spectrum overflow - change gain and integration time\n");
			getFullSpectrum(self);
		}
		else if( returnCode == TSL2591_UNDERFLOW )
		{
			increaseGain();
			increaseTime();
			printf("\nTSL25911_LIGHT_SENSOR: Full spectrum overflow - increase gain and integration time\n");
			getFullSpectrum(self);
		}
		else // Something went wrong
		{
			printf("\nTSL25911_LIGHT_SENSOR_ERROR: %d\n", returnCode);
		}
		
		return self;
				
	}
	
}
