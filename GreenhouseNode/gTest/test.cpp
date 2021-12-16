#include "../fff-master/gtest/gtest.h"
#include "../fff-master/fff.h"

DEFINE_FFF_GLOBALS	//	Initialize the framework

extern "C"
{
#include "../GreenhouseNode/driver/mh_z19.h"
#include "co2.h"

#include <stdbool.h>
}


//	Fake function to take a measuring from the CO2 Sensor
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_takeMeassuring);

//	Fake function to get the CO2 value from the CO2 Sensor
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_getCo2Ppm, uint16_t*);

class CO2_Test : public ::testing::Test
{
protected:
	void SetUp() override {
		RESET_FAKE(mh_z19_takeMeassuring);
		RESET_FAKE(mh_z19_getCo2Ppm);
		FFF_RESET_HISTORY();
	}
	void TearDown() override {

	}

};

TEST_F(CO2_Test, Test_get_CO2_value) {

	//	Arrange
	int co2ppm;

	//	Act
	co2ppm = co2_getLastCO2ppm();

	//	Assert
	EXPECT_EQ(0, co2ppm);
}

TEST_F(CO2_Test, Test_CO2_measure_is_called_10_times) {

	//	Arrange

	//	Act
	for (int i = 0; i < 10; i++)
	{
		co2_doMeasurement();
	}

	//	Assert
	ASSERT_EQ(10, mh_z19_takeMeassuring_fake.call_count);
	ASSERT_TRUE(MHZ19_OK == mh_z19_takeMeassuring_fake.return_val);
}

TEST_F(CO2_Test, Test_CO2_set_data_is_called) {

	//	Arrange
	uint16_t value = co2_getLastCO2ppm();

	//	Act
	co2_getLatestMeasurement();

	//	Assert
	ASSERT_TRUE(mh_z19_getCo2Ppm_fake.call_count == 1);
	EXPECT_TRUE(MHZ19_OK == mh_z19_getCo2Ppm_fake.return_val);
	ASSERT_TRUE(1500 == co2_getLastCO2ppm());
	ASSERT_FALSE(value == co2_getLastCO2ppm());
}