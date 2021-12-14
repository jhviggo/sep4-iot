/*
* application.h
* Created: 12/8/2021 12:03:52 PM
* Author : Viggo Petersen
*/
#pragma once

typedef struct application* application_t;

application_t application_create(void);
void application_run(void);
