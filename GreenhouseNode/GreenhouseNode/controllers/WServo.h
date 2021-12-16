/*
 * WServo.h
 *
 * Created: 12/14/2021 11:39:30 AM
 *  Author: tolde
 */ 

#pragma once
#include <rc_servo.h>
#include <ATMEGA_FreeRTOS.h>


void initialise_servo();
void close_servo();
void open_servo();
void set_servo(uint8_t portNo, uint8_t position);

