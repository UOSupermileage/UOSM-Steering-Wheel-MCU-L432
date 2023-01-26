/*
 * HallDriver.c
 *
 *  Created on: Jan. 23, 2023
 *      Author: jeremycote
 */

#include "HallDriver.h"
#include "DataAggregation.h"
#include "SerialDebugDriver.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

static uint32_t milisecondsPerRevolution = 0;
static uint32_t lastHallTick = 0;

PUBLIC void HallPeriodicJob() {
	// TODO: What happens when tick overflows and goes back to 0?
	milisecondsPerRevolution = (osKernelGetTickCount() - lastHallTick) * HALL_BOLTS;
	lastHallTick = osKernelGetTickCount();
}

PUBLIC result_t HallConvertSpeed() {


	DebugPrint("Miliseconds Per Revolution: %d", milisecondsPerRevolution);

	DebugPrint("RPM: [%d]", 60000/(milisecondsPerRevolution));

	//Angular velocity in radians/second.
	speed_t speed = 60000/milisecondsPerRevolution * HALL_CIRC * 60 / 1000 ;

	SystemSetSpeed(speed);

	return RESULT_OK;
}
