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

directionHandler_t windowHandler_create(UBaseType_t window_task_priority, EventGroupHandle_t eventBits, EventBits_t bits);
int8_t windowHandler_getStatus(directionHandler_t self);
void windowHandler_destroy(directionHandler_t self);
void start_directionTask(void* self);


