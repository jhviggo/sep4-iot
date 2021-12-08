/*
* main.c
* Author : Viggo Petersen & Michel Sofus Engelhardt Sommer
*
*/

#include "application.h"

int main(void) {
	application_create();
	application_run();

	/* Should never be reached */
	while (1) {}
}
