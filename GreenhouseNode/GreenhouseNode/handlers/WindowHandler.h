/*
 * WindowHandler.h
 *
 * Created: 12/14/2021 2:27:53 PM
 *  Author: tolde
 */ 


#pragma once 
#include <stdio.h>
#include <rc_servo.h>
#include "event_groups.h"

typedef struct direction* directionHandler_t;

void windowHandler_getStatus(directionHandler_t self);
void windowHandler_destroy(directionHandler_t self);


