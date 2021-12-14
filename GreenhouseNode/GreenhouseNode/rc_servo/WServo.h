/*
 * WServo.h
 *
 * Created: 12/14/2021 11:39:30 AM
 *  Author: tolde
 */ 


#ifndef WSERVO_H_
#define WSERVO_H_

#pragma once
#include <rc_servo.h>
#include <ATMEGA_FreeRTOS.h>

void initialise_servo();
void close_servo();
void open_servo();




#endif /* WSERVO_H_ */