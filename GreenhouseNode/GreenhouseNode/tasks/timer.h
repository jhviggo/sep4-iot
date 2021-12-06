#pragma once

/*
 * timer.h
 *
 * Created: 06/12/2021 14.14.55
 *  Author: Michel Sofus Engelhardt Sommer, 273966
 */


/************************************************************************/
/* Atmega 2560 has 2 x 8-bit, 4 x 16-bit Timers 	                    */
/************************************************************************/
typedef enum TimerID {
	  TIMER_8BIT_A   /**<  8-bit timer  */
	, TIMER_8BIT_B   /**<  8-bit timer  */
	, TIMER_16BIT_A  /**< 16-bit timer  */
	, TIMER_16BIT_B  /**< 16-bit timer  */
	, TIMER_16BIT_C  /**< 16-bit timer  */
	, TIMER_16BIT_D  /**< 16-bit timer  */
} TimerID_t;


