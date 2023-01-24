/*
 * HallDriver.c
 *
 *  Created on: Jan. 23, 2023
 *      Author: jeremycote
 */

#include "HallDriver.h"

static uint32_t milisecondsPerRevolution = 0;
static uint32_t lastHallTick = 0;

PUBLIC void HallPeriodicJob() {
	// TODO: What happens when tick overflows and goes back to 0?
	milisecondsPerRevolution = osKernelGetTickCount() - lastHallTick;
	lastHallTick = osKernelGetTickCount();
}

PUBLIC result_t HallGetSpeed(speed_t *speed) {

	//Angular velocity in radians/second.
	*speed = 1.00/(milisecondsPerRevolution * HALL_BOLTS / 1000.00) * PI_T2 ;

	// Convert to meters/second. rads/s * m/rads = m/s
	*speed *= HALL_RADIUS;

	// Convert to km/h
	*speed *= 3.6;

	return RESULT_OK;
}
