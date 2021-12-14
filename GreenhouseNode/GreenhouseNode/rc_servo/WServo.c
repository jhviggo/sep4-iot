/*
 * WServo.c
 *
 * Created: 12/14/2021 11:39:18 AM
 *  Author: tolde
 */ 

#include <ATMEGA_FreeRTOS.h>
#include <rc_servo.h>
#include "WServo.h"

void initialise_servo()
{
	rc_servo_initialise();
}

void open_servo()
{
	rc_servo_setPosition(0, 100);
}

void close_servo()
{
	rc_servo_setPosition(0, -100);
}